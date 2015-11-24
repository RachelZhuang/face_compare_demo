/*
* GetChiSquare.h
*
* Code generation for function 'GetChiSquare'
*
* C source code generated on: Tue Jul 21 23:01:10 2015
*
*/

#ifndef __GETCHISQUARE_H__
#define __GETCHISQUARE_H__
/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

/* Function Declarations */
extern double GetWeightedChiSquare(const double LBPHist1[2891], const double LBPHist2[2891]);


extern double GetNonWeightedChiSquare(const double LBPHist1[2891], const double LBPHist2[2891]);

double GetEulerDst(const double LBPHist1[2891], const double LBPHist2[2891]);

double GetCosAngle(const double LBPHist1[2891], const double LBPHist2[2891]);


#endif
/* End of code generation (GetChiSquare.h) */
