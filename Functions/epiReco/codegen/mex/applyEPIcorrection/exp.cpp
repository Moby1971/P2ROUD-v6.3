//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// exp.cpp
//
// Code generation for function 'exp'
//

// Include files
#include "exp.h"
#include "applyEPIcorrection_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRSInfo
    x_emlrtRSI{
        10,    // lineNo
        "exp", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elfun\\exp.m" // pathName
    };

static emlrtRSInfo y_emlrtRSI{
    33,                           // lineNo
    "applyScalarFunctionInPlace", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\applyScalarFunctionInPlace.m" // pathName
};

// Function Definitions
namespace coder {
void b_exp(const emlrtStack &sp, ::coder::array<creal_T, 2U> &x)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T nx;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &x_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  nx = x.size(1);
  b_st.site = &y_emlrtRSI;
  if (x.size(1) > 2147483646) {
    c_st.site = &ab_emlrtRSI;
    check_forloop_overflow_error(c_st);
  }
  for (int32_T k{0}; k < nx; k++) {
    real_T im;
    real_T r;
    r = x[k].re;
    im = x[k].im;
    if (r == 0.0) {
      x[k].re = muDoubleScalarCos(im);
      x[k].im = muDoubleScalarSin(im);
    } else if (im == 0.0) {
      x[k].re = muDoubleScalarExp(r);
      x[k].im = 0.0;
    } else if (muDoubleScalarIsInf(im) && muDoubleScalarIsInf(r) && (r < 0.0)) {
      x[k].re = 0.0;
      x[k].im = 0.0;
    } else {
      r = muDoubleScalarExp(r / 2.0);
      x[k].re = r * (r * muDoubleScalarCos(im));
      x[k].im = r * (r * muDoubleScalarSin(im));
    }
  }
}

} // namespace coder

// End of code generation (exp.cpp)
