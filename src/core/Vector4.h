#ifndef _AcerDet_Core_Vector4_
#define _AcerDet_Core_Vector4_

#pragma once

#include "Vector3.h"
#include <ostream>
using namespace std;

namespace AcerDet {
	namespace core {

		/*
		 * FourVector (Vector3, e/t)
		 */
		template<typename T>
		class Vector4 {
		public:
			Vector3<T> p;
			T e;
			
			Vector4() : p(), e(0) {}
			Vector4(const Vector4<T>& v) : p(v.p), e(v.e) {}
			Vector4(const Vector3<T>& v, T val) : p(v), e(val) {}
			Vector4(T x, T y, T z, T w) : p(Vector3<T>(x,y,z)), e(w) {}
			
			Bool_t operator == (const Vector4<T>&);
			Bool_t operator != (const Vector4<T>&);
			
			friend ostream& operator << (ostream& str, const Vector4<T>& v) {
				str << "(" << v.p.x << ", " << v.p.y << ", " << v.p.z << ", " << v.e << ")";
				return str;
			}
		};
		
		/* Typedefs */
		typedef Vector4<Real64_t> Vector4f;
		
		/* Comparison operators */
		template<typename T>
		Bool_t Vector4<T>::operator == (const Vector4<T>& v) {
			return p == v.p && e == v.e;
		}
		
		template<typename T>
		Bool_t Vector4<T>::operator != (const Vector4<T>& v) {
			return !(*this == v);
		}
		
	}
}

#endif