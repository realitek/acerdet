#include "Electron.h"
#include <cstdio>
using namespace AcerDet::analyse;

#include "../core/Smearing.h"
using namespace AcerDet::core;

Electron::Electron( const Configuration& config, IHistogramManager* histoMng ) :
	ETCLU	( config.Cluster.MinEt ),
	RCONE	( config.Cluster.ConeR ),

	PTLMIN	( config.Electron.MinMomenta ),
	ETAMAX	( config.Electron.MaxEta ),
	RJE		( config.Electron.MinJetsRlj ),
	RISOLJ	( config.Electron.MinIsolRlj ),
	RDEP	( config.Electron.ConeR ),
	EDMAX	( config.Electron.MaxEnergy ),

	KEYHID	( config.Flag.HistogramId ),
	KEYSME	( config.Flag.Smearing ),

	IEVENT	( 0 ),
	
	histoManager( histoMng ),
	histoRegistered( false )
{}

Electron::~Electron() {}

void Electron::printInfo() const {
	// print out title
	printf ("*****************************************\n");
	printf ("*                                       *\n");
	printf ("*     *****************************     *\n");
	printf ("*     ***   analyse::Electron   ***     *\n");
	printf ("*     *****************************     *\n");
	printf ("*                                       *\n");
	printf ("*****************************************\n");

	// print out basic params
	printf ("\n\t... electron isolation ...\n");
	printf ("min. lepton p_T %lf\n", PTLMIN);
	printf ("max. lepton eta %lf\n", ETAMAX);
	printf ("max R_ej for ele-clu %lf\n", RJE);
	printf ("min R_lj for isolation %lf\n", RISOLJ);
	printf ("R for energy deposit %lf\n", RDEP);
	printf ("max E_dep for isolation %lf\n", EDMAX);
	printf ("smearing %s\n", KEYSME ? "on" : "off");
	printf ("\n");

}

void Electron::analyseRecord( const io::InputRecord& irecord, io::OutputRecord& orecord ) {
	
	Int32_t idhist = 300 + KEYHID;
	if (!histoRegistered) {
		histoRegistered = true;
		histoManager
			->registerHistogram(idhist+11, "Electron: multiplicity isolated", 10, 0.0, 10.0);
		histoManager
			->registerHistogram(idhist+21, "Electron: multiplicity hard", 10, 0.0, 10.0);
		histoManager
			->registerHistogram(idhist+31, "Electron: multiplicity isol+hard", 10, 0.0, 10.0);
	}

	// variables
	Real64_t PT, ETA, PHI, ENER, JPT, JETA, JPHI, DR, DDR, PTCRU, ENE, EDEP;

	// new event to compute
	IEVENT++;

	// reference to particles container
	const vector<Particle>& parts = irecord.particles();

	// look for isolated electrons, sort clusters common
	for (int i=0; i<parts.size(); ++i) {
		const Particle& part = parts[i];

		// pick only final particles
		if (!part.isFinal())// || !part.isStable())
			continue;
			
		// analyse electrons
		if (part.type == PT_ELECTRON) {

			Bool_t ISOL = true;
			Int32_t LCLU = -1;
			
			PT = part.pT();
        	ETA = part.getEta();
        	PHI = part.getPhi();
   
			// apply smearing
        	PTCRU = PT;
			if (KEYSME) {
				ENE = part.e();
				if (ENE <= 0.0) 
					continue;

				Particle pEle = part;
				pEle.momentum *= (1.0 + Smearing::forElectron(ENE));
				PT = pEle.pT();
			}
        
			if (PT < PTLMIN || abs(ETA) > ETAMAX)
				continue;
				
			// mark eletron-cluster
			DR = 100.0;
			for (int j=0; j<orecord.Clusters.size(); ++j) {
				const ClusterData& cluster = orecord.Clusters[j];
				
				DDR = sqrt(
					pow(ETA - cluster.eta_rec, 2) +
					pow(PHI - cluster.phi_rec, 2)
				);
				
				if (abs(PHI - cluster.phi_rec) > PI)
					DDR = sqrt( 
						pow(ETA - cluster.eta_rec, 2) + 
						pow(abs(PHI - cluster.phi_rec) - 2*PI, 2)
					);
					
				if (DDR < DR) {
					LCLU = j;
					DR = DDR;
				}
			}

			if (DR > RJE) 
				LCLU = -1;

			// check if electron isolated from clusters
			for (int j=0; j<orecord.Clusters.size(); ++j) {
				if (j == LCLU) {
					DDR = 100.0;
				} else {
					const ClusterData& cluster = orecord.Clusters[j];
					
					DDR = sqrt(
						pow(ETA - cluster.eta_rec, 2) + 
						pow(PHI - cluster.phi_rec, 2)
					);
					
					if (abs(PHI - cluster.phi_rec) > PI)
						DDR = sqrt(
							pow(ETA - cluster.eta_rec, 2) + 
							pow(abs(PHI - cluster.phi_rec) - 2*PI, 2)
						);
				}

				if (DDR < RISOLJ) 
					ISOL = false;
			}
			
			// check on energy deposition of cells EDEP in cone RDEP
			EDEP = 0.0;
			for (int j=0; j<orecord.Cells.size(); ++j) {
				const CellData& cell = orecord.Cells[j];
				
				DDR = sqrt(
					pow(ETA - cell.eta, 2) + 
					pow(PHI - cell.phi, 2)
				);
				
				if (abs(PHI - cell.phi) > PI)
					DDR = sqrt(
						pow(ETA - cell.eta, 2) + 
						pow(abs(PHI - cell.phi) - 2*PI, 2)
					);
					
				if (DDR < RDEP) 
					EDEP += cell.pT;
			}

			if (EDEP - PTCRU > EDMAX) 
				ISOL = false;
				
			// fill /ISOELE/ with isolated electron 
			if (ISOL) {
				// remove ele-cluster from /CLUSTER/
				if (LCLU >= 0)
					orecord.Clusters.erase(orecord.Clusters.begin() + LCLU);

				PartData newParton;
				newParton.status = part.statusID;
				newParton.num = i;
				newParton.motherStatus = parts[part.mother].statusID;
				newParton.eta = ETA;
				newParton.phi = PHI;
				newParton.pT = PT;
				
				orecord.Electrons.push_back( newParton );
			}
		}
	}

	// store count in histogram
	histoManager
		->insert(idhist + 11,  orecord.Electrons.size() );

	// arrange electrons in falling E_T sequence
	PartData::sortBy_pT( orecord.Electrons );

	Int32_t IELE = 0, IELEISO = 0;
	for (int i=0; i<parts.size(); ++i) {
		const Particle& part = parts[i];
		
		// pick only particles from hard process
		if (!part.isHardProcess())
			continue;
		
		if (part.type == PT_ELECTRON) {
			PT = part.pT(); 
			ETA = part.getEta(); 
			PHI = part.getPhi();
			ENER = 0.0;
			Bool_t ISOL = true;

			for (int j=0; j<parts.size(); ++j) {
				if (parts[j].isHardProcess()
				&& abs(parts[j].typeID) <= 21
				&& i != j
				&& !parts[j].isNeutrino()) 
				{
					JPT = parts[j].pT(); 
					JETA = parts[j].getEta(); 
					JPHI = parts[j].getPhi();
					DDR = sqrt(
						pow(ETA - JETA, 2) + 
						pow(JPHI - PHI, 2)
					);

					if (abs(JPHI - PHI) > PI)
						DDR = sqrt(
							pow(ETA - JETA, 2) + 
							pow(abs(JPHI - PHI) - 2*PI, 2)
						);

					if (DDR < RISOLJ && JPT > ETCLU) 
						ISOL = false;

					if (DDR < RDEP && JPT < ETCLU) 
						ENER += JPT;
				}
			}

			if (ENER > EDMAX) 
				ISOL = false;

			if (abs(ETA) < ETAMAX && PT > PTLMIN)
				IELE++;

			if (abs(ETA) < ETAMAX && PT > PTLMIN && ISOL)
				IELEISO++;
		}
	}
	
	// store in histos
	histoManager
  	     ->insert(idhist + 21, IELE, 1.0);

	histoManager
  	     ->insert(idhist + 31, IELEISO, 1.0);
}

void Electron::printResults() const {
	printf ("***************************************\n");
	printf ("*                                     *\n");
	printf ("*     ***************************     *\n");
	printf ("*     ***     Output from     ***     *\n");
	printf ("*     ***  analyse::Electron  ***     *\n");
	printf ("*     ***************************     *\n");
	printf ("*                                     *\n");
	printf ("***************************************\n");
	
	printf (" Analysed records: %d\n", IEVENT);
}
