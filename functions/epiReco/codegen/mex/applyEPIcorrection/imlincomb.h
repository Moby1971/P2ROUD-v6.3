//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// imlincomb.h
//
// Code generation for function 'imlincomb'
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
void lincombPortableCode(const emlrtStack &sp, real_T varargin_1,
                         const ::coder::array<real_T, 2U> &varargin_2,
                         real_T varargin_3, ::coder::array<real_T, 2U> &Z);

}

// End of code generation (imlincomb.h)
