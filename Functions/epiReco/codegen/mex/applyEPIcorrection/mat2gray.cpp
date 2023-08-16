//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// mat2gray.cpp
//
// Code generation for function 'mat2gray'
//

// Include files
#include "mat2gray.h"
#include "applyEPIcorrection_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "imlincomb.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "libmwimlincomb_tbb.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRSInfo yc_emlrtRSI{
    38,         // lineNo
    "mat2gray", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\mat2gray.m" // pathName
};

static emlrtRSInfo ad_emlrtRSI{
    48,         // lineNo
    "mat2gray", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\mat2gray.m" // pathName
};

static emlrtRSInfo bd_emlrtRSI{
    15,    // lineNo
    "min", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\min.m" // pathName
};

static emlrtRSInfo
    cd_emlrtRSI{
        46,         // lineNo
        "minOrMax", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax."
        "m" // pathName
    };

static emlrtRSInfo
    dd_emlrtRSI{
        92,        // lineNo
        "minimum", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax."
        "m" // pathName
    };

static emlrtRSInfo ed_emlrtRSI{
    208,             // lineNo
    "unaryMinOrMax", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pathName
};

static emlrtRSInfo fd_emlrtRSI{
    897,                    // lineNo
    "minRealVectorOmitNaN", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pathName
};

static emlrtRSInfo gd_emlrtRSI{
    72,                      // lineNo
    "vectorMinOrMaxInPlace", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\vectorMinOrMaxInPlace.m" // pathName
};

static emlrtRSInfo hd_emlrtRSI{
    64,                      // lineNo
    "vectorMinOrMaxInPlace", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\vectorMinOrMaxInPlace.m" // pathName
};

static emlrtRSInfo id_emlrtRSI{
    113,         // lineNo
    "findFirst", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\vectorMinOrMaxInPlace.m" // pathName
};

static emlrtRSInfo jd_emlrtRSI{
    130,                        // lineNo
    "minOrMaxRealVectorKernel", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\vectorMinOrMaxInPlace.m" // pathName
};

static emlrtRSInfo kd_emlrtRSI{
    15,    // lineNo
    "max", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\max.m" // pathName
};

static emlrtRSInfo
    ld_emlrtRSI{
        44,         // lineNo
        "minOrMax", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax."
        "m" // pathName
    };

static emlrtRSInfo
    md_emlrtRSI{
        79,        // lineNo
        "maximum", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax."
        "m" // pathName
    };

static emlrtRSInfo nd_emlrtRSI{
    190,             // lineNo
    "unaryMinOrMax", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pathName
};

static emlrtRSInfo od_emlrtRSI{
    901,                    // lineNo
    "maxRealVectorOmitNaN", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pathName
};

static emlrtRSInfo pd_emlrtRSI{
    13,          // lineNo
    "imlincomb", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imlincomb.m" // pathName
};

static emlrtRSInfo qd_emlrtRSI{
    118,              // lineNo
    "lincombGeneric", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imlincomb.m" // pathName
};

static emlrtRSInfo rd_emlrtRSI{
    120,              // lineNo
    "lincombGeneric", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imlincomb.m" // pathName
};

static emlrtRSInfo sd_emlrtRSI{
    170,                    // lineNo
    "lincombSharedLibrary", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imlincomb.m" // pathName
};

static emlrtRTEInfo k_emlrtRTEI{
    134,             // lineNo
    27,              // colNo
    "unaryMinOrMax", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pName
};

static emlrtRTEInfo ub_emlrtRTEI{
    162,         // lineNo
    20,          // colNo
    "imlincomb", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imlincomb.m" // pName
};

static emlrtRTEInfo vb_emlrtRTEI{
    45,         // lineNo
    4,          // colNo
    "mat2gray", // fName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\mat2gray.m" // pName
};

// Function Definitions
namespace coder {
void mat2gray(const emlrtStack &sp, const ::coder::array<real_T, 2U> &A,
              ::coder::array<real_T, 2U> &b_I)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  emlrtStack st;
  real_T multipliers[2];
  real_T delta;
  real_T ex;
  real_T varargin_3;
  int32_T a;
  int32_T idx;
  int32_T k;
  int32_T last;
  boolean_T exitg1;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &yc_emlrtRSI;
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
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  i_st.prev = &h_st;
  i_st.tls = h_st.tls;
  b_st.site = &bd_emlrtRSI;
  c_st.site = &cd_emlrtRSI;
  d_st.site = &dd_emlrtRSI;
  last = A.size(0) * A.size(1);
  if (last < 1) {
    emlrtErrorWithMessageIdR2018a(&d_st, &k_emlrtRTEI,
                                  "Coder:toolbox:eml_min_or_max_varDimZero",
                                  "Coder:toolbox:eml_min_or_max_varDimZero", 0);
  }
  e_st.site = &ed_emlrtRSI;
  f_st.site = &fd_emlrtRSI;
  if (last <= 2) {
    if (last == 1) {
      ex = A[0];
    } else {
      ex = A[1];
      if ((!(A[0] > ex)) &&
          ((!muDoubleScalarIsNaN(A[0])) || muDoubleScalarIsNaN(ex))) {
        ex = A[0];
      }
    }
  } else {
    g_st.site = &hd_emlrtRSI;
    if (!muDoubleScalarIsNaN(A[0])) {
      idx = 1;
    } else {
      idx = 0;
      h_st.site = &id_emlrtRSI;
      if (last > 2147483646) {
        i_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(i_st);
      }
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!muDoubleScalarIsNaN(A[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = A[0];
    } else {
      g_st.site = &gd_emlrtRSI;
      ex = A[idx - 1];
      a = idx + 1;
      h_st.site = &jd_emlrtRSI;
      if ((idx + 1 <= last) && (last > 2147483646)) {
        i_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(i_st);
      }
      for (k = a; k <= last; k++) {
        varargin_3 = A[k - 1];
        if (ex > varargin_3) {
          ex = varargin_3;
        }
      }
    }
  }
  st.site = &yc_emlrtRSI;
  b_st.site = &kd_emlrtRSI;
  c_st.site = &ld_emlrtRSI;
  d_st.site = &md_emlrtRSI;
  e_st.site = &nd_emlrtRSI;
  f_st.site = &od_emlrtRSI;
  if (last <= 2) {
    if (last == 1) {
      delta = A[0];
    } else {
      delta = A[1];
      if ((!(A[0] < delta)) &&
          ((!muDoubleScalarIsNaN(A[0])) || muDoubleScalarIsNaN(delta))) {
        delta = A[0];
      }
    }
  } else {
    g_st.site = &hd_emlrtRSI;
    if (!muDoubleScalarIsNaN(A[0])) {
      idx = 1;
    } else {
      idx = 0;
      h_st.site = &id_emlrtRSI;
      if (last > 2147483646) {
        i_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(i_st);
      }
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!muDoubleScalarIsNaN(A[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      delta = A[0];
    } else {
      g_st.site = &gd_emlrtRSI;
      delta = A[idx - 1];
      a = idx + 1;
      h_st.site = &jd_emlrtRSI;
      if ((idx + 1 <= last) && (last > 2147483646)) {
        i_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(i_st);
      }
      for (k = a; k <= last; k++) {
        varargin_3 = A[k - 1];
        if (delta < varargin_3) {
          delta = varargin_3;
        }
      }
    }
  }
  if (ex == delta) {
    b_I.set_size(&vb_emlrtRTEI, &sp, A.size(0), A.size(1));
    for (a = 0; a < last; a++) {
      b_I[a] = A[a];
    }
  } else {
    delta = 1.0 / (delta - ex);
    st.site = &ad_emlrtRSI;
    varargin_3 = -ex * delta;
    b_st.site = &pd_emlrtRSI;
    if (last > 500000) {
      c_st.site = &qd_emlrtRSI;
      multipliers[0] = delta;
      multipliers[1] = varargin_3;
      b_I.set_size(&ub_emlrtRTEI, &c_st, A.size(0), A.size(1));
      d_st.site = &sd_emlrtRSI;
      imlincomb_tbb_real64(&multipliers[0], 2.0, &b_I[0], 0,
                           static_cast<real_T>(last), 1.0, &A[0]);
    } else {
      c_st.site = &rd_emlrtRSI;
      lincombPortableCode(c_st, delta, A, varargin_3, b_I);
    }
  }
  idx = b_I.size(0) * b_I.size(1);
  for (a = 0; a < idx; a++) {
    varargin_3 = b_I[a];
    b_I[a] = muDoubleScalarMax(0.0, muDoubleScalarMin(varargin_3, 1.0));
  }
}

} // namespace coder

// End of code generation (mat2gray.cpp)
