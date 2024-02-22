//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// circshift.cpp
//
// Code generation for function 'circshift'
//

// Include files
#include "circshift.h"
#include "applyEPIcorrection_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRSInfo wf_emlrtRSI{
    51,          // lineNo
    "circshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRSInfo xf_emlrtRSI{
    96,                        // lineNo
    "circshift_multiple_dims", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRSInfo yf_emlrtRSI{
    110,              // lineNo
    "circshift_core", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRSInfo ag_emlrtRSI{
    112,              // lineNo
    "circshift_core", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRSInfo bg_emlrtRSI{
    116,              // lineNo
    "circshift_core", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRSInfo cg_emlrtRSI{
    124,              // lineNo
    "circshift_core", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRSInfo dg_emlrtRSI{
    129,              // lineNo
    "circshift_core", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRSInfo eg_emlrtRSI{
    133,              // lineNo
    "circshift_core", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRSInfo fg_emlrtRSI{
    137,              // lineNo
    "circshift_core", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pathName
};

static emlrtRTEInfo s_emlrtRTEI{
    38,          // lineNo
    48,          // colNo
    "circshift", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pName
};

static emlrtRTEInfo bc_emlrtRTEI{
    89,          // lineNo
    25,          // colNo
    "circshift", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\circshift.m" // pName
};

// Function Definitions
namespace coder {
void circshift(const emlrtStack &sp, ::coder::array<creal_T, 2U> &a,
               const real_T p[2])
{
  array<creal_T, 2U> buffer;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  int32_T npages[2];
  int32_T k;
  boolean_T exitg1;
  boolean_T pok;
  st.prev = &sp;
  st.tls = sp.tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)&sp);
  pok = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (static_cast<int32_T>(p[k]) != p[k]) {
      pok = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!pok) {
    emlrtErrorWithMessageIdR2018a(&sp, &s_emlrtRTEI,
                                  "Coder:toolbox:circshift_InvalidShiftType",
                                  "Coder:toolbox:circshift_InvalidShiftType", 6,
                                  4, 5, "int32", 4, 5, "int32");
  }
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int32_T absp[2];
    int32_T i;
    int32_T i1;
    int32_T stride;
    boolean_T shiftright[2];
    st.site = &wf_emlrtRSI;
    stride = static_cast<int32_T>(p[0]);
    shiftright[0] = true;
    i = a.size(0);
    if (i <= 1) {
      stride = 0;
    } else {
      if (static_cast<int32_T>(p[0]) > i) {
        stride = static_cast<int32_T>(p[0]) -
                 i * static_cast<int32_T>(
                         static_cast<uint32_T>(static_cast<int32_T>(p[0])) /
                         static_cast<uint32_T>(i));
      }
      if (stride > (i >> 1)) {
        stride = i - stride;
        shiftright[0] = false;
      }
    }
    absp[0] = stride;
    stride = static_cast<int32_T>(p[1]);
    shiftright[1] = true;
    i = a.size(1);
    if (i <= 1) {
      stride = 0;
    } else {
      if (static_cast<int32_T>(p[1]) > i) {
        stride = static_cast<int32_T>(p[1]) -
                 i * static_cast<int32_T>(
                         static_cast<uint32_T>(static_cast<int32_T>(p[1])) /
                         static_cast<uint32_T>(i));
      }
      if (stride > (i >> 1)) {
        stride = i - stride;
        shiftright[1] = false;
      }
    }
    absp[1] = stride;
    if ((a.size(0) == 0) || (a.size(1) == 0)) {
      stride = 0;
    } else {
      i = a.size(0);
      i1 = a.size(1);
      stride = muIntScalarMax_sint32(i, i1);
    }
    buffer.set_size(&bc_emlrtRTEI, &st, 1, stride / 2);
    stride = 1;
    npages[1] = 1;
    npages[0] = a.size(1);
    for (int32_T dim{0}; dim < 2; dim++) {
      int32_T b_npages;
      int32_T ns;
      int32_T pagesize;
      i = a.size(dim);
      i1 = absp[dim];
      ns = i1 - 1;
      pagesize = stride * i;
      b_st.site = &xf_emlrtRSI;
      b_npages = npages[dim];
      if ((i > 1) && (i1 > 0)) {
        c_st.site = &yf_emlrtRSI;
        if (b_npages > 2147483646) {
          d_st.site = &ab_emlrtRSI;
          check_forloop_overflow_error(d_st);
        }
        for (int32_T b_i{0}; b_i < b_npages; b_i++) {
          int32_T pageroot;
          pageroot = b_i * pagesize;
          c_st.site = &ag_emlrtRSI;
          if (stride > 2147483646) {
            d_st.site = &ab_emlrtRSI;
            check_forloop_overflow_error(d_st);
          }
          for (int32_T j{0}; j < stride; j++) {
            int32_T b_i1;
            b_i1 = pageroot + j;
            if (shiftright[dim]) {
              int32_T i2;
              c_st.site = &bg_emlrtRSI;
              for (k = 0; k <= ns; k++) {
                buffer[k] = a[b_i1 + ((k + i) - i1) * stride];
              }
              i2 = i1 + 1;
              for (k = i; k >= i2; k--) {
                a[b_i1 + (k - 1) * stride] = a[b_i1 + ((k - i1) - 1) * stride];
              }
              c_st.site = &cg_emlrtRSI;
              for (k = 0; k <= ns; k++) {
                a[b_i1 + k * stride] = buffer[k];
              }
            } else {
              int32_T i2;
              c_st.site = &dg_emlrtRSI;
              for (k = 0; k <= ns; k++) {
                buffer[k] = a[b_i1 + k * stride];
              }
              i2 = i - i1;
              c_st.site = &eg_emlrtRSI;
              for (k = 0; k < i2; k++) {
                a[b_i1 + k * stride] = a[b_i1 + (k + i1) * stride];
              }
              c_st.site = &fg_emlrtRSI;
              for (k = 0; k <= ns; k++) {
                a[b_i1 + ((k + i) - i1) * stride] = buffer[k];
              }
            }
          }
        }
      }
      stride = pagesize;
    }
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
}

} // namespace coder

// End of code generation (circshift.cpp)
