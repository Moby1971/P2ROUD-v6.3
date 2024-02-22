//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// fft2.cpp
//
// Code generation for function 'fft2'
//

// Include files
#include "fft2.h"
#include "applyEPIcorrection_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Variable Definitions
static emlrtRSInfo sc_emlrtRSI{
    60,     // lineNo
    "fft2", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\fft2.m" // pathName
};

static emlrtRSInfo tc_emlrtRSI{
    56,                            // lineNo
    "Custom1DFFTCallback/fftLoop", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\Custom1DFFTCallback.m" // pathName
};

static emlrtRSInfo uc_emlrtRSI{
    57,                            // lineNo
    "Custom1DFFTCallback/fftLoop", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\Custom1DFFTCallback.m" // pathName
};

static emlrtRTEInfo tb_emlrtRTEI{
    60,     // lineNo
    1,      // colNo
    "fft2", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\fft2.m" // pName
};

// Function Definitions
namespace coder {
void fft2(const emlrtStack &sp, const ::coder::array<creal_T, 2U> &x,
          ::coder::array<creal_T, 2U> &y)
{
  array<creal_T, 2U> acc;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  int32_T lens[2];
  int32_T k;
  boolean_T guard1;
  st.prev = &sp;
  st.tls = sp.tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)&sp);
  lens[0] = x.size(0);
  lens[1] = x.size(1);
  st.site = &sc_emlrtRSI;
  guard1 = false;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    guard1 = true;
  } else {
    boolean_T b_x;
    boolean_T exitg1;
    b_x = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 2)) {
      if (lens[k] == 0) {
        b_x = true;
        exitg1 = true;
      } else {
        k++;
      }
    }
    if (b_x) {
      guard1 = true;
    } else {
      b_st.site = &nb_emlrtRSI;
      c_st.site = &ob_emlrtRSI;
      d_st.site = &pb_emlrtRSI;
      e_st.site = &tc_emlrtRSI;
      emlrtFFTWSetNumThreads(4);
      acc.set_size(&pb_emlrtRTEI, &e_st, x.size(0), x.size(1));
      emlrtFFTW_1D_C2C(
          (real_T *)&(((::coder::array<creal_T, 2U> *)&x)->data())[0],
          (real_T *)&(acc.data())[0], 1, x.size(0), x.size(0), x.size(1), -1);
      e_st.site = &uc_emlrtRSI;
      f_st.site = &qb_emlrtRSI;
      emlrtFFTWSetNumThreads(4);
      y.set_size(&pb_emlrtRTEI, &f_st, acc.size(0), x.size(1));
      emlrtFFTW_1D_C2C((real_T *)&(acc.data())[0], (real_T *)&(y.data())[0],
                       acc.size(0), x.size(1), acc.size(1), acc.size(0), -1);
    }
  }
  if (guard1) {
    y.set_size(&tb_emlrtRTEI, &st, x.size(0), x.size(1));
    k = x.size(0) * x.size(1);
    for (int32_T i{0}; i < k; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
}

} // namespace coder

// End of code generation (fft2.cpp)
