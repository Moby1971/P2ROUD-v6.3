//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// applyEPIcorrection.h
//
// Code generation for function 'applyEPIcorrection'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Function Declarations
void applyEPIcorrection(const emlrtStack *sp,
                        const coder::array<creal_T, 2U> &kSpaceGhost,
                        real_T kCenter, real_T pCenter,
                        const coder::array<char_T, 2U> &method,
                        coder::array<creal_T, 2U> &kSpaceCorrected);

emlrtCTX emlrtGetRootTLSGlobal();

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData);

real_T findEPIshift_anonFcn1(const emlrtStack &sp,
                             const coder::array<creal_T, 2U> &kSpace,
                             const coder::array<char_T, 2U> &method,
                             const coder::array<real_T, 2U> &idxMap,
                             const real_T x[2]);

// End of code generation (applyEPIcorrection.h)
