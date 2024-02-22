//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// eml_fftshift.cpp
//
// Code generation for function 'eml_fftshift'
//

// Include files
#include "eml_fftshift.h"
#include "applyEPIcorrection_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Variable Definitions
static emlrtRSInfo ib_emlrtRSI{
    135,            // lineNo
    "eml_fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "fftshift.m" // pathName
};

static emlrtRSInfo jb_emlrtRSI{
    144,            // lineNo
    "eml_fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "fftshift.m" // pathName
};

static emlrtRSInfo kb_emlrtRSI{
    156,            // lineNo
    "eml_fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "fftshift.m" // pathName
};

static emlrtRSInfo lb_emlrtRSI{
    166,            // lineNo
    "eml_fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "fftshift.m" // pathName
};

static emlrtRSInfo oc_emlrtRSI{
    159,            // lineNo
    "eml_fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "fftshift.m" // pathName
};

static emlrtRSInfo pc_emlrtRSI{
    138,            // lineNo
    "eml_fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "fftshift.m" // pathName
};

static emlrtRSInfo qc_emlrtRSI{
    35,             // lineNo
    "eml_fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "fftshift.m" // pathName
};

static emlrtRSInfo rc_emlrtRSI{
    55,         // lineNo
    "prodsize", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\prodsize.m" // pathName
};

// Function Definitions
namespace coder {
void eml_fftshift(const emlrtStack &sp, ::coder::array<creal_T, 2U> &x,
                  int32_T dim)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T xtmp_re_tmp;
  st.prev = &sp;
  st.tls = sp.tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  xtmp_re_tmp = x.size(dim - 1);
  if (xtmp_re_tmp > 1) {
    int32_T lowerDim;
    int32_T midoffset;
    int32_T npages;
    int32_T vlend2;
    int32_T vspread;
    int32_T vstride;
    vlend2 = static_cast<int32_T>(static_cast<uint32_T>(xtmp_re_tmp) >> 1);
    st.site = &qc_emlrtRSI;
    vstride = 1;
    b_st.site = &rc_emlrtRSI;
    if (dim - 1 > 2147483646) {
      c_st.site = &ab_emlrtRSI;
      check_forloop_overflow_error(c_st);
    }
    lowerDim = static_cast<uint8_T>(dim - 1);
    for (int32_T k{0}; k < lowerDim; k++) {
      vstride *= x.size(0);
    }
    npages = 1;
    lowerDim = dim + 1;
    for (int32_T k{lowerDim}; k < 3; k++) {
      npages *= x.size(1);
    }
    vspread = (xtmp_re_tmp - 1) * vstride;
    midoffset = vlend2 * vstride - 1;
    if (vlend2 << 1 == xtmp_re_tmp) {
      int32_T i2;
      i2 = 0;
      st.site = &ib_emlrtRSI;
      if (npages > 2147483646) {
        b_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(b_st);
      }
      for (int32_T i{0}; i < npages; i++) {
        int32_T i1;
        i1 = i2;
        i2 += vspread;
        st.site = &pc_emlrtRSI;
        if (vstride > 2147483646) {
          b_st.site = &ab_emlrtRSI;
          check_forloop_overflow_error(b_st);
        }
        for (int32_T j{0}; j < vstride; j++) {
          int32_T ib;
          i1++;
          i2++;
          ib = i1 + midoffset;
          st.site = &jb_emlrtRSI;
          for (int32_T k{0}; k < vlend2; k++) {
            real_T xtmp_im;
            real_T xtmp_re;
            lowerDim = k * vstride;
            xtmp_re_tmp = (i1 + lowerDim) - 1;
            xtmp_re = x[xtmp_re_tmp].re;
            xtmp_im = x[xtmp_re_tmp].im;
            x[(i1 + lowerDim) - 1] = x[ib + lowerDim];
            xtmp_re_tmp = ib + lowerDim;
            x[xtmp_re_tmp].re = xtmp_re;
            x[xtmp_re_tmp].im = xtmp_im;
          }
        }
      }
    } else {
      int32_T i2;
      i2 = 0;
      st.site = &kb_emlrtRSI;
      if (npages > 2147483646) {
        b_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(b_st);
      }
      for (int32_T i{0}; i < npages; i++) {
        int32_T i1;
        i1 = i2;
        i2 += vspread;
        st.site = &oc_emlrtRSI;
        if (vstride > 2147483646) {
          b_st.site = &ab_emlrtRSI;
          check_forloop_overflow_error(b_st);
        }
        for (int32_T j{0}; j < vstride; j++) {
          real_T xtmp_im;
          real_T xtmp_re;
          int32_T ib;
          i1++;
          i2++;
          ib = i1 + midoffset;
          xtmp_re = x[ib].re;
          xtmp_im = x[ib].im;
          st.site = &lb_emlrtRSI;
          for (int32_T k{0}; k < vlend2; k++) {
            lowerDim = ib + vstride;
            xtmp_re_tmp = (i1 + k * vstride) - 1;
            x[ib] = x[xtmp_re_tmp];
            x[xtmp_re_tmp] = x[lowerDim];
            ib = lowerDim;
          }
          x[ib].re = xtmp_re;
          x[ib].im = xtmp_im;
        }
      }
    }
  }
}

void eml_fftshift(const emlrtStack &sp, ::coder::array<creal_T, 2U> &x)
{
  emlrtStack b_st;
  emlrtStack st;
  st.prev = &sp;
  st.tls = sp.tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  if (x.size(0) > 1) {
    int32_T npages;
    int32_T vlend2;
    int32_T vspread;
    vlend2 = static_cast<int32_T>(static_cast<uint32_T>(x.size(0)) >> 1) - 1;
    npages = x.size(1) - 1;
    vspread = x.size(0);
    if ((vlend2 + 1) << 1 == x.size(0)) {
      int32_T i2;
      i2 = 1;
      st.site = &ib_emlrtRSI;
      if (x.size(1) > 2147483646) {
        b_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(b_st);
      }
      for (int32_T i{0}; i <= npages; i++) {
        int32_T i1;
        int32_T ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        st.site = &jb_emlrtRSI;
        for (int32_T k{0}; k <= vlend2; k++) {
          real_T xtmp_im;
          real_T xtmp_re;
          int32_T b_i;
          int32_T xtmp_re_tmp;
          xtmp_re_tmp = (i1 + k) - 1;
          xtmp_re = x[xtmp_re_tmp].re;
          xtmp_im = x[xtmp_re_tmp].im;
          b_i = ib + k;
          x[xtmp_re_tmp] = x[b_i];
          x[b_i].re = xtmp_re;
          x[b_i].im = xtmp_im;
        }
      }
    } else {
      int32_T i2;
      i2 = 1;
      st.site = &kb_emlrtRSI;
      if (x.size(1) > 2147483646) {
        b_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(b_st);
      }
      for (int32_T i{0}; i <= npages; i++) {
        real_T xtmp_im;
        real_T xtmp_re;
        int32_T i1;
        int32_T ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        xtmp_re = x[ib].re;
        xtmp_im = x[ib].im;
        st.site = &lb_emlrtRSI;
        for (int32_T k{0}; k <= vlend2; k++) {
          int32_T b_i;
          int32_T xtmp_re_tmp;
          b_i = ib + k;
          xtmp_re_tmp = (i1 + k) - 1;
          x[b_i] = x[xtmp_re_tmp];
          x[xtmp_re_tmp] = x[b_i + 1];
        }
        ib = (ib + vlend2) + 1;
        x[ib].re = xtmp_re;
        x[ib].im = xtmp_im;
      }
    }
  }
}

} // namespace coder

// End of code generation (eml_fftshift.cpp)
