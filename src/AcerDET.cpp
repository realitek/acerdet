#include "AcerDET.h"
#include <cstdio>

using namespace AcerDet;

/*
 * Construct AcerDET object from given configuration
 */
AcerDET::AcerDET(
	const conf::Configuration& config,
	core::IParticleDataProviderFactory *partFactory,
	core::IHistogramManager *histoManager ) :
		histos( histoManager ),
		histos_initialized( false ),
		analyse_BJet		( config, histoManager ),
		analyse_Calibration	( config ),
		analyse_Cell		( config, histoManager ),
		analyse_CJet		( config, histoManager ),
		analyse_Cluster		( config, histoManager ),
		analyse_Electron	( config, histoManager ),
		analyse_Jet		( config, histoManager ),
		analyse_Mis		( config, histoManager ),
		analyse_Muon		( config, histoManager ),
		analyse_Photon		( config, histoManager ),
		analyse_Tau		( config, histoManager )
{
}

/*
 * Destructor - not used
 */
AcerDET::~AcerDET() {
	histos = NULL;
}

/*
 * Analyse single InputRecord from event
 */
void AcerDET::analyseRecord( const io::InputRecord& irecord, io::OutputRecord& orecord ) {
	printf ("AcerDET: analyse\n");
	if (!histos_initialized) {
		histos->init();
		histos_initialized = true;
	}
	
	analyse_Cell		.analyseRecord( irecord, orecord );
	analyse_Cluster		.analyseRecord( irecord, orecord );
	analyse_Muon		.analyseRecord( irecord, orecord );
	analyse_Electron	.analyseRecord( irecord, orecord );
	analyse_Photon		.analyseRecord( irecord, orecord );
	analyse_Jet			.analyseRecord( irecord, orecord );
	analyse_Mis			.analyseRecord( irecord, orecord );
	analyse_BJet		.analyseRecord( irecord, orecord );
	analyse_CJet		.analyseRecord( irecord, orecord );
	analyse_Tau			.analyseRecord( irecord, orecord );
	analyse_Calibration	.analyseRecord( irecord, orecord );
}

/*
 * Print info about AcerDET class
 */
void AcerDET::printInfo() const {
	// AcerDET version number and release date
	printf ("**********************************************************\n");
	printf ("*                  AcerDET, version: 2.0                 *\n");
	printf ("*                 Released at: xx.yy.2014                *\n");
	printf ("*                                                        *\n");
	printf ("*  Simplied event simulation and reconstruction package  *\n");
	printf ("*                                                        *\n");
	printf ("*              by E. Richter-Was & P. Mikos              *\n");
	printf ("*             Institute of Computer Science              *\n");
	printf ("*         Jagiellonian University, Cracow, Poland        *\n");
	printf ("**********************************************************\n");
	printf ("\n");
	
	// info about subclasses
	printf (" Initial configuration:\n");
	analyse_Cell		.printInfo();
	analyse_Cluster		.printInfo();
	analyse_Muon		.printInfo();
	analyse_Electron	.printInfo();
	analyse_Photon		.printInfo();
	analyse_Jet			.printInfo();
	analyse_Mis			.printInfo();
	analyse_BJet		.printInfo();
	analyse_CJet		.printInfo();
	analyse_Tau			.printInfo();
	analyse_Calibration	.printInfo();
}

void AcerDET::printResults() const {
	analyse_Cell		.printResults();
	analyse_Cluster		.printResults();
	analyse_Muon		.printResults();
	analyse_Electron	.printResults();
	analyse_Photon		.printResults();
	analyse_Jet			.printResults();
	analyse_Mis			.printResults();
	analyse_BJet		.printResults();
	analyse_CJet		.printResults();
	analyse_Tau			.printResults();
}

void AcerDET::storeHistograms( const string& file ) {
	histos->storeHistograms(file);
}
