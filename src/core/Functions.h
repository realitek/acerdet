#ifndef _AcerDet_Core_Functions_
#define _AcerDet_Core_Functions_

#pragma once

#include "Typedefs.h"
#include "Consts.h"

namespace AcerDet {
	namespace core {
		
		/*
		 * Compute radius from given coordinates
		 */
		template<typename T>
		inline T radius(T x, T y) {
			return (T)sqrt(x*x + y*y);
		}
		
		/*
		 * Signum function
		 * Return -1 if value is less than zero
		 * +1 if value us greater than zero
		 * 0 otherwise
		 */
		template<typename T>
		T sgn(T val) {
			if (val > 0) return (T)(+1);
			if (val < 0) return (T)(-1);
			return (T)(0);
		}
		
		/*
		 * Return first value with the sign of second
		 * result = |arg1| * sgn(arg2)
		 */
		template<typename T, typename Q>
		T sign(T val, Q coef) {
			Q sg = sgn(coef);
			return (T)(abs(val) * sg);
		}
		
		/*
		 * Returns angle from given coordinates
		 * in range [-PI,PI]
		 */
		template<typename T>
		T angle(T x, T y) {
			Real64_t epsi = 1E-20;
			T r = radius(x,y);
			
			if (r < epsi)
				return (T)(0);
				
			if (abs(x)/r < 0.8) {
				return sign(acos(x/r),y);
			} else {
				T angle = asin(y/r);
				if (x < 0 && angle >= 0)
					return PI - angle;
				else if (x < 0)
					return -PI - angle;
				else
					return angle;
			}
			
			return radius(x,y);
		}
		
		/*
		 * Code specific functions 
		 * TODO -> dummy implementation
		 */
		Int32_t kfcomp(Real64_t);
		Int32_t kuchge(Real64_t);
	}
}

#endif
