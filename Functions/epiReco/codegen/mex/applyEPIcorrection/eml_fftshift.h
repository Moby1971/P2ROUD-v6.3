//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// eml_fftshift.h
//
// Code generation for function 'eml_fftshift'
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
void eml_fftshift(const emlrtStack &sp, ::coder::array<creal_T, 2U> &x,
                  int32_T dim);

void eml_fftshift(const emlrtStack &sp, ::coder::array<creal_T, 2U> &x);

} // namespace coder

// End of code generation (eml_fftshift.h)
