//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// circshift.h
//
// Code generation for function 'circshift'
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
namespace coder {
void circshift(const emlrtStack &sp, ::coder::array<creal_T, 2U> &a,
               const real_T p[2]);

}

// End of code generation (circshift.h)
