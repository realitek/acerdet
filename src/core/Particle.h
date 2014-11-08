#ifndef _AcerDet_Core_Particle_
#define _AcerDet_Core_Particle_

#pragma once

#include <cmath>
#include <cstdio>
#include <string>
#include <ostream>
using namespace std;

#include "Typedefs.h"
#include "StlDefs.h"
#include "Consts.h"
#include "Vector4.h"

namespace AcerDet {
	namespace core {
		
		/*
		  A state of particle
		*/
		enum ParticleStatus {
			PS_NULL = 0, /*!< detailed description  */
			PS_BEAM, /*!< detailed description  */
			PS_FINAL, /*!< detailed description  */
			PS_DECAYED, /*!< detailed description  */
			PS_HISTORY /*!< detailed description  */
		};
		
		/*
		  Type of particle - self descriptive
		*/
		enum ParticleType {
			PT_UNKNOWN = 0,	/*!< detailed description  */
			
			PT_JET,			/*!< detailed description  */
			PT_BJET,		/*!< detailed description  */	// 5
			PT_CJET,		/*!< detailed description  */	// 4
			
			PT_CELL,		/*!< detailed description  */
			PT_CLUSTER,		/*!< detailed description  */
			
			PT_MUON,		/*!< muon */					// 13
			PT_ELECTRON,	/*!< electron/positron e-/e+ */	// 11
			PT_PHOTON,		/*!< gamma */					// 22 (gamma)
			PT_TAU,			/*!< tau */						// 15
			
			PT_NEUTRINO_ELE, /*!< electron neutrino */		// 12
			PT_NEUTRINO_MUO, /*!< muon neutrino */			// 14
			PT_NEUTRINO_TAU, /*!< tau neutrion */			// 16
			
			PT_BOSON_Z, /*!< Z0 boson */					// 23
			PT_BOSON_W, /*!< W+ boson */					// 24
			PT_BOSON_H  /*!< Higgs boson */					// 25
		};
		
		/*
		 * Common class representing partons
		 */
		class Particle {
		public:
			ParticleStatus status; /*!< particle status converted to enum */
			Int32_t statusID; /*!< particle status */

			ParticleType type; /*!< pdg_id converted to enum */
			Int32_t pdg_id; /*!< pdg_id */
			
			Vector4f momentum; /*!< momentum */
			Vector4f production; /*!< production vertex if exists */

			Int32_t barcode; /*!< particle barcode (id in sequence [1...n]) */
			Int32_t mother; /*!< mother barcode if exists, -1 otherwise */
			pair<Int32_t,Int32_t> daughters; /*!< pair of daughter barcodes, <-1,-1> otherwise */

			/*
			 * Default ctor
			 * Initialize particle data
			 */
			Particle();

			/*
			 * Check if given particle has mother
			 */
			Bool_t hasMother() const;

			/*
			 * Check if given particle has any daughters
			 */
			Bool_t hasDaughter() const;

			/*
			 * Number of particle daughters
			 */
			Int32_t daughtersCount() const;

			/*
			 * Check if particle is stable
			 */
			//Bool_t isStable() const;

			/*
			 * Check if particle is beam
			 */
			Bool_t isBeam() const;

			/*
			 * Check if particle has decayed status
			 */
			//Bool_t isDecayed() const;
			
			/*
			 * Type Check
			 */
			Bool_t isNeutrino() const;
			
			//Bool_t isFinal() const;
			Bool_t isHardProcess() const;

			/*
			* Print basic informations about particle
			*/			
			friend ostream& operator << (ostream& str, const Particle& p) {
				str << "Particle:" << endl;
				str << "\tBarcode: " << p.barcode << endl;
				str << "\tType: " << p.getTypeName() << "(" << p.pdg_id << ")" << endl;
				str << "\tStatus: " << p.getStatusName() << "(" << p.statusID << ")" << endl;
				str << "\tMomentum (px,py,pz,e) = " << p.momentum << endl;
				str << "\tProduction (x,y,z,t) = " << p.production << endl;
				str << endl;
				return str;
			}
			
			/*
			 * useful
			 */
			Real64_t pT() const;
			
			/*
			 * Momentum short-linked accessors
			 */
			inline Real64_t pX() const { return momentum.p.x; }
			inline Real64_t pY() const { return momentum.p.y; }
			inline Real64_t pZ() const { return momentum.p.z; }
			inline Real64_t e() const { return momentum.e; }
			
			/*
			 * Angle in XY plane
			 */
			Real64_t getPhi() const;
			
			Real64_t getEta() const;
			
			Real64_t getTheta() const;
			
			/*
			 * Folding
			 */
			Real64_t foldPhi() const;

		private:
			string getTypeName() const;
			
			string getStatusName() const;
		};

		/*
		  Single particle class with basic methods such as boost, rotation,
		  and angle calculation.
		*/

/*
		public:
			// Invariant mass. If mass is negative then -sqrt(-mass) is returned
			T recalculated_mass()  const
			{
				T p2 = _px*_px + _py*_py + _pz*_pz;
				T e2 = _e*_e;
				T m2 = e2 - p2;

				if ( m2 < 0.0 ) return -sqrt( -m2 );
				return sqrt( m2 );
			}

		public:
			void rotateXZ(double theta);
			void rotateXY(double theta);
			void boostAlongZ(double pz, double e);
			void boostToRestFrame(ParticleT<T> &p);
			void boostFromRestFrame(ParticleT<T> &p);
		};

		template<typename T>
		inline double ParticleT<T>::getAnglePhi()
		{
			// conventions as in ANGFI(X,Y) of tauola.f and PHOAN1 of photos.f
			// but now 'phi' in name define that it is rotation in px py

			double buf = 0.;

			if ( fabs(getPy()) < fabs(getPx()) ) {
				buf = atan( fabs(getPy()/getPx()) );
				if (getPx() < 0.) buf = M_PI - buf;
			} else buf = acos( getPx()/sqrt(getPx()*getPx() + getPy()*getPy()) );

			if ( getPy() < 0. ) buf = 2.*M_PI - buf;
			return buf;
		}

		template<typename T>
		inline double ParticleT<T>::getAngleTheta()
		{
			// conventions as in ANGXY(X,Y) of tauola.f or PHOAN2 of photos.f
			// but now 'theta' in name define that it is rotation in pz px
			// note that first argument of PHOAN2 was usually z

			double buf = 0.;

			if ( fabs(getPx()) < fabs(getPz()) ) {
				buf = atan( fabs(getPx()/getPz()) );
				if ( getPz() < 0. ) buf = M_PI - buf;
			}
			else buf = acos( getPz()/sqrt(getPz()*getPz() + getPx()*getPx()) );
			return buf;
		}

		template<typename T>
		inline void ParticleT<T>::rotateXZ(double theta)
		{
			// as PHORO2 of photos.f
			T pX = getPx();
			T pZ = getPz();
			setPx( cos(theta)*pX + sin(theta)*pZ);
			setPz(-sin(theta)*pX + cos(theta)*pZ);
		}

		template<typename T>
		inline void ParticleT<T>::rotateXY(double theta)
		{
			// as PHORO3 of photos.f
			T pX = getPx();
			T pY = getPy();
			setPx( cos(theta)*pX - sin(theta)*pY);
			setPy( sin(theta)*pX + cos(theta)*pY);
		}

		template<typename T>
		inline void ParticleT<T>::boostAlongZ(double p_pz, double p_e)
		{
			// as PHOBO3 of photos.f
			double m = sqrt(p_e*p_e-p_pz*p_pz);
			T buf_pz = getPz();
			T buf_e = getE();

			setPz((p_e *buf_pz + p_pz*buf_e)/m);
			setE ((p_pz*buf_pz + p_e *buf_e)/m);
		}

		template<typename T>
		inline void ParticleT<T>::boostToRestFrame(ParticleT<T> &p)
		{
			T p_len = sqrt(p.getPx()*p.getPx() + p.getPy()*p.getPy() + p.getPz()*p.getPz());
			double phi   = p.getAnglePhi();
			p.rotateXY(-phi );
			double theta = p.getAngleTheta();
			p.rotateXY( phi );

			//Now rotate coordinates to get boost in Z direction.
			rotateXY(-phi  );
			rotateXZ(-theta);
			boostAlongZ(-1*p_len, p.getE());
			rotateXZ( theta);
			rotateXY( phi  );
		}

		template<typename T>
		inline void ParticleT<T>::boostFromRestFrame(ParticleT<T> &p)
		{
			T p_len = sqrt(p.getPx()*p.getPx() + p.getPy()*p.getPy() + p.getPz()*p.getPz());
			double phi   = p.getAnglePhi();
			p.rotateXY(-phi );
			double theta = p.getAngleTheta();
			p.rotateXY( phi );

			//Now rotate coordinates to get boost in Z direction.
			rotateXY(-phi  );
			rotateXZ(-theta);
			boostAlongZ(p_len, p.getE());
			rotateXZ( theta);
			rotateXY( phi  );
		}
*/
	}
}

#endif
