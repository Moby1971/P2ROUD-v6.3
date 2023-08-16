//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// ifftshift.cpp
//
// Code generation for function 'ifftshift'
//

// Include files
#include "ifftshift.h"
#include "applyEPIcorrection_data.h"
#include "eml_fftshift.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Variable Definitions
static emlrtRSInfo eb_emlrtRSI{
    17,          // lineNo
    "ifftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\ifftshift.m" // pathName
};

static emlrtRSInfo fb_emlrtRSI{
    23,              // lineNo
    "eml_ifftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "ifftshift.m" // pathName
};

static emlrtRSInfo gb_emlrtRSI{
    31,              // lineNo
    "eml_ifftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "ifftshift.m" // pathName
};

static emlrtRSInfo hb_emlrtRSI{
    41,              // lineNo
    "eml_ifftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "ifftshift.m" // pathName
};

static emlrtRSInfo lc_emlrtRSI{
    12,          // lineNo
    "ifftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\ifftshift.m" // pathName
};

static emlrtRSInfo mc_emlrtRSI{
    34,              // lineNo
    "eml_ifftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "ifftshift.m" // pathName
};

static emlrtRSInfo nc_emlrtRSI{
    26,              // lineNo
    "eml_ifftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\eml_"
    "ifftshift.m" // pathName
};

// Function Definitions
namespace coder {
void b_ifftshift(const emlrtStack &sp, ::coder::array<creal_T, 2U> &x)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  st.prev = &sp;
  st.tls = sp.tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  for (int32_T dim{0}; dim < 2; dim++) {
    int32_T lowerDim;
    st.site = &lc_emlrtRSI;
    lowerDim = x.size(dim);
    if (lowerDim > 1) {
      int32_T vlend2;
      vlend2 = static_cast<int32_T>(static_cast<uint32_T>(lowerDim) >> 1);
      if (vlend2 << 1 == lowerDim) {
        b_st.site = &fb_emlrtRSI;
        eml_fftshift(b_st, x, dim + 1);
      } else {
        int32_T i2;
        int32_T midoffset;
        int32_T npages;
        int32_T vspread;
        int32_T vstride;
        b_st.site = &nc_emlrtRSI;
        vstride = 1;
        for (int32_T k{0}; k < dim; k++) {
          vstride *= x.size(0);
        }
        npages = 1;
        lowerDim = dim + 2;
        for (int32_T k{lowerDim}; k < 3; k++) {
          npages *= x.size(1);
        }
        vspread = (x.size(dim) - 1) * vstride;
        midoffset = vlend2 * vstride - 1;
        i2 = -1;
        b_st.site = &gb_emlrtRSI;
        if (npages > 2147483646) {
          c_st.site = &ab_emlrtRSI;
          check_forloop_overflow_error(c_st);
        }
        for (int32_T i{0}; i < npages; i++) {
          int32_T i1;
          i1 = i2 + 1;
          i2 += vspread;
          b_st.site = &mc_emlrtRSI;
          if (vstride > 2147483646) {
            c_st.site = &ab_emlrtRSI;
            check_forloop_overflow_error(c_st);
          }
          for (int32_T j{0}; j < vstride; j++) {
            real_T xtmp_im;
            real_T xtmp_re;
            int32_T ia;
            int32_T ib_tmp;
            i1++;
            ia = i1 + midoffset;
            ib_tmp = (i2 + j) + 1;
            xtmp_re = x[ib_tmp].re;
            xtmp_im = x[ib_tmp].im;
            b_st.site = &hb_emlrtRSI;
            for (int32_T k{0}; k < vlend2; k++) {
              int32_T b_i;
              lowerDim = (k + 1) * -vstride;
              b_i = ia + lowerDim;
              x[ib_tmp + k * -vstride] = x[b_i];
              x[b_i] = x[ib_tmp + lowerDim];
            }
            lowerDim = ib_tmp + vlend2 * -vstride;
            x[lowerDim].re = xtmp_re;
            x[lowerDim].im = xtmp_im;
          }
          if (vstride - 1 >= 0) {
            i2 += vstride;
          }
        }
      }
    }
  }
}

void ifftshift(const emlrtStack &sp, ::coder::array<creal_T, 2U> &x)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &eb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  if (x.size(0) > 1) {
    int32_T vlend2;
    vlend2 = static_cast<int32_T>(static_cast<uint32_T>(x.size(0)) >> 1);
    if (vlend2 << 1 == x.size(0)) {
      b_st.site = &fb_emlrtRSI;
      eml_fftshift(b_st, x);
    } else {
      int32_T i2;
      int32_T npages;
      npages = x.size(1);
      i2 = -1;
      b_st.site = &gb_emlrtRSI;
      if (x.size(1) > 2147483646) {
        c_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(c_st);
      }
      for (int32_T i{0}; i < npages; i++) {
        real_T xtmp_im;
        real_T xtmp_re;
        int32_T a_tmp;
        int32_T b_i;
        int32_T ia;
        a_tmp = i2 + x.size(0);
        ia = i2 + 1;
        i2 = a_tmp;
        ia += vlend2;
        xtmp_re = x[a_tmp].re;
        xtmp_im = x[a_tmp].im;
        b_st.site = &hb_emlrtRSI;
        for (int32_T k{0}; k < vlend2; k++) {
          int32_T i1;
          b_i = a_tmp - k;
          i1 = (ia - k) - 1;
          x[b_i] = x[i1];
          x[i1] = x[b_i - 1];
        }
        b_i = a_tmp - vlend2;
        x[b_i].re = xtmp_re;
        x[b_i].im = xtmp_im;
      }
    }
  }
}

} // namespace coder

// End of code generation (ifftshift.cpp)
