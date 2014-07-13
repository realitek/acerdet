#include "Functions.h"
#include "Consts.h"
using namespace AcerDet::core;

#include <cmath>
#include <algorithm>

double radius(double x, double y) {
	return sqrt(x*x + y*y);
}

double angle(double x, double y) {
	/*
	const double epsi = 1e-20;
	double r = radius(x,y);
	if (r < epsi) return 0.0;
	*/
	return 0.0; // dummy TODO
}
		
Int32_t kfcomp(Real64_t KF) {
	
	// MOCK fixed value TODO
	return 0;
	
	Int32_t KCHG[3][500] = 
	{
		{-1,2,-1,2,-1,2,-1,2,0,0,-3,0,-3,0,-3,0,-3,0,0,0,0,0,0,3,0,0,0,
		0,0,0,0,0,0,3,0,0,3,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,-1,2,-1,2,3,
		0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3,
		0,3,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,3,0,3,0,3,0,0,0,
		0,0,0,0,0,0,0,3,0,3,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,
		3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,3,0,3,0,3,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
		0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,
		0,3,0,0,0,0,0,0,0,0,-3,0,0,0,0,0,0,0,0,3,0,-3,0,3,-3,0,0,0,3,6,
		0,3,0,0,0,0,0,-3,0,3,-3,0,-3,0,0,0,0,-3,0,3,6,-3,0,3,-3,0,-3,0,
		3,6,0,3,0,0,0,0,0,-3,0,3,-3,0,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0},
		
		{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		
		{1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,
		0,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0,0,0,0,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
		1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,0,0,0,
		0,0,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,
		1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,
		1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	
	Int32_t KFTAB[25] = 
	{211,111,221,311,321,130,310,213,113,223,313,323,2112,2212,210,
	2110,2210,110,220,330,440,30443,30553,0,0};
	
	Int32_t KCTAB[25] = 
	{101,111,112,102,103,221,222,121,131,132,122,123,332,333,281,
	282,283,284,285,286,287,231,235,0,0};
	
	// Starting values.
	Int32_t result = 0;
	Int32_t KFA = abs(KF);
	
	// Simple cases: direct translations or table.
	if (KFA == 0 || KFA >= 100000)
		return result;

	if (KFA <= 100) {
		result = KFA;
		if (KF < 0 && KCHG[2][KFA-1] == 0)
			result = 0;
		return result;
	}
	
	for (int ikf=0; ikf<=22; ++ikf) {
		if (KFA == KFTAB[ikf]) {
			result = KCTAB[ikf];
			if (KF < 0 && KCHG[2][result] == 0)
				result = 0;
			return result;
		}
	}
	
	// Subdivide KF code into constituent pieces.
	Int32_t KFLR = (KFA/10000) % 10;
	Int32_t KFLA = (KFA/1000) % 10;
	Int32_t KFLB = (KFA/100) % 10;
	Int32_t KFLC = (KFA/10) % 10;
	Int32_t KFLS = KFA % 10;
	
	// Mesons
	if (KFA-10000*KFLR < 1000) {
		if (KFLB == 0 || KFLB == 9 || KFLC == 0 || KFLC == 9) {} 
		else if (KFLB < KFLC) {} 
		else if (KF < 0 && KFLB == KFLC) {} 
		
		else if (KFLB == KFLC) { 
			if      (KFLR == 0 && KFLS == 1) result = 110 + KFLB;
			else if (KFLR == 0 && KFLS == 3) result = 130 + KFLB;
			else if (KFLR == 1 && KFLS == 3) result = 150 + KFLB;
			else if (KFLR == 1 && KFLS == 1) result = 170 + KFLB;
			else if (KFLR == 2 && KFLS == 3) result = 190 + KFLB;
			else if (KFLR == 0 && KFLS == 5) result = 210 + KFLB;
		}
		
		else if (KFLB <= 5) {
			if      (KFLR == 0 && KFLS == 1) result = 100 + ((KFLB-1)*(KFLB-2))/2 + KFLC;
			else if (KFLR == 0 && KFLS == 3) result = 120 + ((KFLB-1)*(KFLB-2))/2 + KFLC;
			else if (KFLR == 1 && KFLS == 3) result = 140 + ((KFLB-1)*(KFLB-2))/2 + KFLC;
			else if (KFLR == 1 && KFLS == 1) result = 160 + ((KFLB-1)*(KFLB-2))/2 + KFLC;
			else if (KFLR == 2 && KFLS == 3) result = 180 + ((KFLB-1)*(KFLB-2))/2 + KFLC;
			else if (KFLR == 0 && KFLS == 5) result = 200 + ((KFLB-1)*(KFLB-2))/2 + KFLC;
		}

		else if ((KFLS == 1 && KFLR <= 1) || (KFLS == 3 && KFLR <= 2) || (KFLS == 5 && KFLR == 0)) 
			result = 80 + KFLB;
	}
	
	// Diquarks.
	else if ((KFLR == 0 || KFLR == 1) && KFLC == 0) {
		if      (KFLS != 1 && KFLS != 3) {} 
		else if (KFLA == 9 || KFLB == 0 || KFLB == 9) {} 
		else if (KFLA < KFLB) {}
		else if (KFLS == 1 && KFLA == KFLB) {} 
        else result = 90; 
    }

    // Spin 1/2 baryons. 
    else if (KFLR == 0 && KFLS == 2) {
		if (KFLA == 9 || KFLB == 0 || KFLB == 9 || KFLC == 9) {} 
		else if (KFLA <= KFLC || KFLA < KFLB) {}
		else if (KFLA >= 6 || KFLB >= 4 || KFLC >= 4) result = 80 + KFLA;
		else if (KFLB < KFLC) result = 300 + ((KFLA+1)*KFLA*(KFLA-1))/6 + (KFLC*(KFLC-1))/2 + KFLB;
		else result = 330 + ((KFLA+1)*KFLA*(KFLA-1))/6 + (KFLB*(KFLB-1))/2 + KFLC;
	}
	
	// Spin 3/2 baryons. 
	else if (KFLR == 0 && KFLS == 4) {
		if (KFLA == 9 || KFLB == 0 || KFLB == 9 || KFLC == 9) {}
		else if (KFLA < KFLB || KFLB < KFLC) {}
		else if (KFLA >= 6 || KFLB >= 4) result = 80 + KFLA;
		else result = 360 + ((KFLA+1)*KFLA*(KFLA-1))/6 + (KFLB*(KFLB-1))/2 + KFLC;
	}
	
	return result;  
}

Int32_t kuchge(Real64_t ku) {
	// MOCK fixed value -> TODO
	return 0;
}
