//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// svd.cpp
//
// Code generation for function 'svd'
//

// Include files
#include "svd.h"
#include "applyEPIcorrection_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "lapacke.h"
#include "mwmathutil.h"
#include <cstddef>

// Variable Definitions
static emlrtRSInfo mf_emlrtRSI{
    14,    // lineNo
    "svd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\matfun\\svd.m" // pathName
};

static emlrtRSInfo nf_emlrtRSI{
    18,    // lineNo
    "svd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\matfun\\svd.m" // pathName
};

static emlrtRSInfo of_emlrtRSI{
    29,             // lineNo
    "anyNonFinite", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\anyNonFinite."
    "m" // pathName
};

static emlrtRSInfo
    pf_emlrtRSI{
        44,          // lineNo
        "vAllOrAny", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
        "internal\\vAllOrAny.m" // pathName
    };

static emlrtRSInfo
    qf_emlrtRSI{
        103,                  // lineNo
        "flatVectorAllOrAny", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
        "internal\\vAllOrAny.m" // pathName
    };

static emlrtRSInfo rf_emlrtRSI{
    28,    // lineNo
    "svd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\svd.m" // pathName
};

static emlrtRSInfo sf_emlrtRSI{
    107,          // lineNo
    "callLAPACK", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\svd.m" // pathName
};

static emlrtRSInfo tf_emlrtRSI{
    31,       // lineNo
    "xgesvd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgesvd.m" // pathName
};

static emlrtRSInfo uf_emlrtRSI{
    197,            // lineNo
    "ceval_xgesvd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgesvd.m" // pathName
};

static emlrtRTEInfo o_emlrtRTEI{
    47,          // lineNo
    13,          // colNo
    "infocheck", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\infocheck.m" // pName
};

static emlrtRTEInfo p_emlrtRTEI{
    44,          // lineNo
    13,          // colNo
    "infocheck", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\infocheck.m" // pName
};

static emlrtRTEInfo q_emlrtRTEI{
    111,          // lineNo
    5,            // colNo
    "callLAPACK", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\svd.m" // pName
};

static emlrtRTEInfo yb_emlrtRTEI{
    31,       // lineNo
    33,       // colNo
    "xgesvd", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgesvd.m" // pName
};

// Function Definitions
namespace coder {
int32_T svd(const emlrtStack &sp, const ::coder::array<creal_T, 2U> &A,
            real_T U_data[])
{
  static const char_T fname[14]{'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                '_', 'z', 'g', 'e', 's', 'v', 'd'};
  array<creal_T, 2U> b_A;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack st;
  real_T superb_data[8];
  int32_T U_size;
  int32_T m;
  boolean_T p;
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
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)&sp);
  st.site = &mf_emlrtRSI;
  b_st.site = &of_emlrtRSI;
  c_st.site = &pf_emlrtRSI;
  m = A.size(0) * 9;
  p = true;
  d_st.site = &qf_emlrtRSI;
  if (m > 2147483646) {
    e_st.site = &ab_emlrtRSI;
    check_forloop_overflow_error(e_st);
  }
  for (int32_T k{0}; k < m; k++) {
    if ((!p) ||
        (muDoubleScalarIsInf(A[k].re) || muDoubleScalarIsInf(A[k].im) ||
         (muDoubleScalarIsNaN(A[k].re) || muDoubleScalarIsNaN(A[k].im)))) {
      p = false;
    }
  }
  U_size = static_cast<int32_T>(
      muDoubleScalarMin(static_cast<real_T>(A.size(0)), 9.0));
  if (p) {
    st.site = &nf_emlrtRSI;
    if (A.size(0) == 0) {
      U_size = 0;
    } else {
      ptrdiff_t info_t;
      b_st.site = &rf_emlrtRSI;
      c_st.site = &sf_emlrtRSI;
      d_st.site = &tf_emlrtRSI;
      b_A.set_size(&yb_emlrtRTEI, &d_st, A.size(0), 9);
      for (int32_T k{0}; k < m; k++) {
        b_A[k] = A[k];
      }
      m = A.size(0);
      U_size = muIntScalarMin_sint32(9, m);
      info_t =
          LAPACKE_zgesvd(102, 'N', 'N', (ptrdiff_t)A.size(0), (ptrdiff_t)9,
                         (lapack_complex_double *)&(b_A.data())[0],
                         (ptrdiff_t)A.size(0), &U_data[0], nullptr,
                         (ptrdiff_t)1, nullptr, (ptrdiff_t)1, &superb_data[0]);
      e_st.site = &uf_emlrtRSI;
      if ((int32_T)info_t < 0) {
        if ((int32_T)info_t == -1010) {
          emlrtErrorWithMessageIdR2018a(&e_st, &p_emlrtRTEI, "MATLAB:nomem",
                                        "MATLAB:nomem", 0);
        } else {
          emlrtErrorWithMessageIdR2018a(&e_st, &o_emlrtRTEI,
                                        "Coder:toolbox:LAPACKCallErrorInfo",
                                        "Coder:toolbox:LAPACKCallErrorInfo", 5,
                                        4, 14, &fname[0], 12, (int32_T)info_t);
        }
      }
      if ((int32_T)info_t > 0) {
        emlrtErrorWithMessageIdR2018a(&b_st, &q_emlrtRTEI,
                                      "Coder:MATLAB:svd_NoConvergence",
                                      "Coder:MATLAB:svd_NoConvergence", 0);
      }
    }
  } else {
    for (int32_T k{0}; k < U_size; k++) {
      U_data[k] = rtNaN;
    }
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
  return U_size;
}

} // namespace coder

// End of code generation (svd.cpp)
