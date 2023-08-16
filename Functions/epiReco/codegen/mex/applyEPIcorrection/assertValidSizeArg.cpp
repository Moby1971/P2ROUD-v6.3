//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// assertValidSizeArg.cpp
//
// Code generation for function 'assertValidSizeArg'
//

// Include files
#include "assertValidSizeArg.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRTEInfo h_emlrtRTEI{
    49,                   // lineNo
    19,                   // colNo
    "assertValidSizeArg", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\assertValidSizeArg.m" // pName
};

static emlrtRTEInfo i_emlrtRTEI{
    64,                   // lineNo
    15,                   // colNo
    "assertValidSizeArg", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\assertValidSizeArg.m" // pName
};

// Function Definitions
namespace coder {
namespace internal {
void assertValidSizeArg(const emlrtStack &sp, const real_T varargin_1[2])
{
  real_T d;
  int32_T exitg2;
  int32_T k;
  boolean_T guard1;
  k = 0;
  guard1 = false;
  do {
    exitg2 = 0;
    if (k < 2) {
      if ((varargin_1[k] != muDoubleScalarFloor(varargin_1[k])) ||
          muDoubleScalarIsInf(varargin_1[k])) {
        guard1 = true;
        exitg2 = 1;
      } else {
        k++;
        guard1 = false;
      }
    } else {
      k = 0;
      exitg2 = 2;
    }
  } while (exitg2 == 0);
  if (exitg2 != 1) {
    boolean_T exitg1;
    exitg1 = false;
    while ((!exitg1) && (k < 2)) {
      if (varargin_1[k] > 2.147483647E+9) {
        guard1 = true;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (guard1) {
    emlrtErrorWithMessageIdR2018a(
        &sp, &h_emlrtRTEI,
        "Coder:toolbox:eml_assert_valid_size_arg_invalidSizeVector",
        "Coder:toolbox:eml_assert_valid_size_arg_invalidSizeVector", 4, 12,
        MIN_int32_T, 12, MAX_int32_T);
  }
  if (varargin_1[0] <= 0.0) {
    d = 0.0;
  } else {
    d = varargin_1[0];
  }
  if (varargin_1[1] <= 0.0) {
    d = 0.0;
  } else {
    d *= varargin_1[1];
  }
  if (!(d <= 2.147483647E+9)) {
    emlrtErrorWithMessageIdR2018a(&sp, &i_emlrtRTEI, "Coder:MATLAB:pmaxsize",
                                  "Coder:MATLAB:pmaxsize", 0);
  }
}

} // namespace internal
} // namespace coder

// End of code generation (assertValidSizeArg.cpp)
