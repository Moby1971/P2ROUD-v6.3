//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// fminsearch.h
//
// Code generation for function 'fminsearch'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Type Declarations
namespace coder {
class anonymous_function;

}

// Function Declarations
namespace coder {
void fminsearch(const emlrtStack &sp, const anonymous_function &funfcn,
                real_T x[2]);

}

// End of code generation (fminsearch.h)
