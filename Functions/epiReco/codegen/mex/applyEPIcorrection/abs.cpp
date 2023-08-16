//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// abs.cpp
//
// Code generation for function 'abs'
//

// Include files
#include "abs.h"
#include "applyEPIcorrection_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mwmathutil.h"

// Function Definitions
namespace coder {
void b_abs(const emlrtStack &sp, const ::coder::array<creal_T, 2U> &x,
           ::coder::array<real_T, 2U> &y)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T nx;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &wc_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  nx = x.size(0) * x.size(1);
  y.set_size(&cb_emlrtRTEI, &st, x.size(0), x.size(1));
  b_st.site = &xc_emlrtRSI;
  if (nx > 2147483646) {
    c_st.site = &ab_emlrtRSI;
    check_forloop_overflow_error(c_st);
  }
  for (int32_T k{0}; k < nx; k++) {
    y[k] = muDoubleScalarHypot(x[k].re, x[k].im);
  }
}

} // namespace coder

// End of code generation (abs.cpp)
