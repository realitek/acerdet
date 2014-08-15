#ifndef _AcerDet_Core_IHistogramManager_
#define _AcerDet_Core_IHistogramManager_

#include <string>
using namespace std;

#include "Typedefs.h"

#pragma once

namespace AcerDet {
	namespace core {
		
		class IHistogramManager {
		public:
			virtual void init() = 0;
			
			virtual void registerHistogram(
				const string& name,
				const string& title,
				Int32_t blocks,
				Real64_t minVal,
				Real64_t maxVal ) = 0;
				
			virtual void insert( const string& histoName, Real64_t value) = 0;
		};

	}
}

#endif