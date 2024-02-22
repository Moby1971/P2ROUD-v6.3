//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// entropy.cpp
//
// Code generation for function 'entropy'
//

// Include files
#include "entropy.h"
#include "applyEPIcorrection_data.h"
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include "sumMatrixIncludeNaN.h"
#include "warning.h"
#include "coder_array.h"
#include "libmwgetnumcores.h"
#include "libmwgrayto8.h"
#include "libmwtbbhist.h"
#include "mwmathutil.h"
#include <cmath>
#include <cstring>
#include <emmintrin.h>

// Variable Definitions
static emlrtRSInfo td_emlrtRSI{
    38,        // lineNo
    "entropy", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\entropy.m" // pathName
};

static emlrtRSInfo ud_emlrtRSI{
    41,        // lineNo
    "entropy", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\entropy.m" // pathName
};

static emlrtRSInfo vd_emlrtRSI{
    57,        // lineNo
    "entropy", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\entropy.m" // pathName
};

static emlrtRSInfo wd_emlrtRSI{
    59,        // lineNo
    "entropy", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\entropy.m" // pathName
};

static emlrtRSInfo xd_emlrtRSI{
    63,        // lineNo
    "entropy", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\entropy.m" // pathName
};

static emlrtRSInfo yd_emlrtRSI{
    70,        // lineNo
    "entropy", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\entropy.m" // pathName
};

static emlrtRSInfo ae_emlrtRSI{
    79,            // lineNo
    "parseInputs", // fcnName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\entropy.m" // pathName
};

static emlrtRSInfo be_emlrtRSI{
    93,                   // lineNo
    "validateattributes", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\lang\\validateattributes"
    ".m" // pathName
};

static emlrtRSInfo ce_emlrtRSI{
    41,         // lineNo
    "im2uint8", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\im2uint8.m" // pathName
};

static emlrtRSInfo de_emlrtRSI{
    197,                      // lineNo
    "uint8SharedLibraryAlgo", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\im2uint8.m" // pathName
};

static emlrtRSInfo
    ee_emlrtRSI{
        19,        // lineNo
        "grayto8", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\private\\grayto8."
        "m" // pathName
    };

static emlrtRSInfo
    fe_emlrtRSI{
        133,      // lineNo
        "imhist", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m" // pathName
    };

static emlrtRSInfo
    ge_emlrtRSI{
        170,             // lineNo
        "calcHistogram", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m" // pathName
    };

static emlrtRSInfo
    he_emlrtRSI{
        196,             // lineNo
        "calcHistogram", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m" // pathName
    };

static emlrtRSInfo
    ie_emlrtRSI{
        207,             // lineNo
        "calcHistogram", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m" // pathName
    };

static emlrtRSInfo
    je_emlrtRSI{
        452,             // lineNo
        "calcHistogram", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m" // pathName
    };

static emlrtRSInfo
    ke_emlrtRSI{
        456,             // lineNo
        "calcHistogram", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m" // pathName
    };

static emlrtRSInfo le_emlrtRSI{
    39,     // lineNo
    "find", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pathName
};

static emlrtRSInfo me_emlrtRSI{
    144,        // lineNo
    "eml_find", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pathName
};

static emlrtRSInfo ne_emlrtRSI{
    402,                  // lineNo
    "find_first_indices", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pathName
};

static emlrtRSInfo pe_emlrtRSI{
    28,     // lineNo
    "log2", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elfun\\log2.m" // pathName
};

static emlrtRSInfo te_emlrtRSI{
    99,                 // lineNo
    "blockedSummation", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\blocke"
    "dSummation.m" // pathName
};

static emlrtBCInfo
    l_emlrtBCI{
        -1,                   // iFirst
        -1,                   // iLast
        1070,                 // lineNo
        47,                   // colNo
        "",                   // aName
        "imhistAlgo_integer", // fName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m", // pName
        0 // checkKind
    };

static emlrtBCInfo
    m_emlrtBCI{
        -1,                   // iFirst
        -1,                   // iLast
        1058,                 // lineNo
        48,                   // colNo
        "",                   // aName
        "imhistAlgo_integer", // fName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m", // pName
        0 // checkKind
    };

static emlrtBCInfo
    n_emlrtBCI{
        -1,                   // iFirst
        -1,                   // iLast
        1057,                 // lineNo
        48,                   // colNo
        "",                   // aName
        "imhistAlgo_integer", // fName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m", // pName
        0 // checkKind
    };

static emlrtBCInfo
    o_emlrtBCI{
        -1,                   // iFirst
        -1,                   // iLast
        1056,                 // lineNo
        48,                   // colNo
        "",                   // aName
        "imhistAlgo_integer", // fName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m", // pName
        0 // checkKind
    };

static emlrtBCInfo
    p_emlrtBCI{
        -1,                   // iFirst
        -1,                   // iLast
        1055,                 // lineNo
        48,                   // colNo
        "",                   // aName
        "imhistAlgo_integer", // fName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imhist.m", // pName
        0 // checkKind
    };

static emlrtRTEInfo l_emlrtRTEI{
    25,     // lineNo
    13,     // colNo
    "log2", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elfun\\log2.m" // pName
};

static emlrtRTEInfo m_emlrtRTEI{
    13,                 // lineNo
    37,                 // colNo
    "validatenonempty", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "valattr\\validatenonempty.m" // pName
};

static emlrtBCInfo q_emlrtBCI{
    -1,        // iFirst
    -1,        // iLast
    64,        // lineNo
    35,        // colNo
    "",        // aName
    "entropy", // fName
    "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\images\\images\\entropy.m", // pName
    0 // checkKind
};

static emlrtRTEInfo
    xb_emlrtRTEI{
        12,        // lineNo
        20,        // colNo
        "grayto8", // fName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\private\\grayto8."
        "m" // pName
    };

// Function Definitions
namespace coder {
real_T entropy(const emlrtStack &sp,
               const ::coder::array<real_T, 2U> &varargin_1)
{
  __m128d r;
  __m128d r1;
  array<real_T, 1U> b_pNonZeros_data;
  array<uint8_T, 2U> img;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack st;
  real_T localBins1[256];
  real_T localBins2[256];
  real_T localBins3[256];
  real_T p[256];
  real_T pNonZeros_data[256];
  real_T E;
  real_T numCores;
  int32_T iv[2];
  int32_T pNonZeros_size[2];
  int32_T b_i;
  int32_T eint;
  int32_T i;
  int32_T i1;
  int32_T idx;
  int32_T scalarLB_tmp;
  int16_T ii_data[256];
  boolean_T exitg1;
  boolean_T nanFlag;
  boolean_T rngFlag;
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
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)&sp);
  st.site = &td_emlrtRSI;
  b_st.site = &ae_emlrtRSI;
  c_st.site = &be_emlrtRSI;
  if ((varargin_1.size(0) == 0) || (varargin_1.size(1) == 0)) {
    emlrtErrorWithMessageIdR2018a(
        &c_st, &m_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedNonempty",
        "MATLAB:entropy:expectedNonempty", 3, 4, 18, "input number 1, I,");
  }
  st.site = &ud_emlrtRSI;
  b_st.site = &ce_emlrtRSI;
  c_st.site = &de_emlrtRSI;
  img.set_size(&xb_emlrtRTEI, &c_st, varargin_1.size(0), varargin_1.size(1));
  d_st.site = &ee_emlrtRSI;
  grayto8_real64(&varargin_1[0], &img[0],
                 static_cast<real_T>(varargin_1.size(0) * varargin_1.size(1)));
  st.site = &vd_emlrtRSI;
  b_st.site = &fe_emlrtRSI;
  c_st.site = &ge_emlrtRSI;
  numCores = 1.0;
  getnumcores(&numCores);
  i = img.size(0) * img.size(1);
  if ((i > 500000) && (numCores > 1.0)) {
    c_st.site = &he_emlrtRSI;
    nanFlag = false;
    rngFlag = false;
    tbbhist_uint8(&img[0], static_cast<real_T>(i),
                  static_cast<real_T>(img.size(0)),
                  static_cast<real_T>(i) / static_cast<real_T>(img.size(0)),
                  &p[0], 256.0, 256.0, &rngFlag, &nanFlag);
  } else {
    c_st.site = &ie_emlrtRSI;
    std::memset(&p[0], 0, 256U * sizeof(real_T));
    std::memset(&localBins1[0], 0, 256U * sizeof(real_T));
    std::memset(&localBins2[0], 0, 256U * sizeof(real_T));
    std::memset(&localBins3[0], 0, 256U * sizeof(real_T));
    for (b_i = 1; b_i + 3 <= i; b_i += 4) {
      if ((b_i < 1) || (b_i > i)) {
        emlrtDynamicBoundsCheckR2012b(b_i, 1, i, &p_emlrtBCI, &c_st);
      }
      if ((b_i + 1 < 1) || (b_i + 1 > i)) {
        emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, i, &o_emlrtBCI, &c_st);
      }
      if ((b_i + 2 < 1) || (b_i + 2 > i)) {
        emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, i, &n_emlrtBCI, &c_st);
      }
      if ((b_i + 3 < 1) || (b_i + 3 > i)) {
        emlrtDynamicBoundsCheckR2012b(b_i + 3, 1, i, &m_emlrtBCI, &c_st);
      }
      idx = img[b_i - 1];
      localBins1[idx]++;
      localBins2[img[b_i]]++;
      idx = img[b_i + 1];
      localBins3[idx]++;
      idx = img[b_i + 2];
      p[idx]++;
    }
    while (b_i <= i) {
      if ((b_i < 1) || (b_i > i)) {
        emlrtDynamicBoundsCheckR2012b(b_i, 1, i, &l_emlrtBCI, &c_st);
      }
      idx = img[b_i - 1];
      p[idx]++;
      b_i++;
    }
    for (b_i = 0; b_i <= 254; b_i += 2) {
      __m128d r2;
      __m128d r3;
      r = _mm_loadu_pd(&p[b_i]);
      r1 = _mm_loadu_pd(&localBins1[b_i]);
      r2 = _mm_loadu_pd(&localBins2[b_i]);
      r3 = _mm_loadu_pd(&localBins3[b_i]);
      _mm_storeu_pd(&p[b_i], _mm_add_pd(_mm_add_pd(_mm_add_pd(r, r1), r2), r3));
    }
    rngFlag = false;
    nanFlag = false;
  }
  if (rngFlag) {
    c_st.site = &je_emlrtRSI;
    internal::warning(c_st);
  }
  if (nanFlag) {
    c_st.site = &ke_emlrtRSI;
    internal::b_warning(c_st);
  }
  st.site = &wd_emlrtRSI;
  b_st.site = &le_emlrtRSI;
  c_st.site = &me_emlrtRSI;
  idx = 0;
  b_i = 0;
  exitg1 = false;
  while ((!exitg1) && (b_i < 256)) {
    if (p[b_i] != 0.0) {
      idx++;
      ii_data[idx - 1] = static_cast<int16_T>(b_i + 1);
      if (idx >= 256) {
        exitg1 = true;
      } else {
        b_i++;
      }
    } else {
      b_i++;
    }
  }
  if (idx < 1) {
    i1 = 0;
  } else {
    i1 = idx;
  }
  iv[0] = 1;
  iv[1] = i1;
  d_st.site = &ne_emlrtRSI;
  internal::indexShapeCheck(d_st, 256, iv);
  pNonZeros_size[1] = i1;
  st.site = &xd_emlrtRSI;
  for (b_i = 0; b_i < i1; b_i++) {
    if (b_i + 1 > i1) {
      emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, i1, &q_emlrtBCI,
                                    (emlrtConstCTX)&sp);
    }
    pNonZeros_data[b_i] = p[ii_data[b_i] - 1];
  }
  b_i = i1 - 1;
  scalarLB_tmp = (i1 / 2) << 1;
  idx = scalarLB_tmp - 2;
  for (int32_T i2{0}; i2 <= idx; i2 += 2) {
    r = _mm_loadu_pd(&pNonZeros_data[i2]);
    _mm_storeu_pd(&pNonZeros_data[i2],
                  _mm_div_pd(r, _mm_set1_pd(static_cast<real_T>(i))));
  }
  for (int32_T i2{scalarLB_tmp}; i2 <= b_i; i2++) {
    pNonZeros_data[i2] /= static_cast<real_T>(i);
  }
  st.site = &yd_emlrtRSI;
  rngFlag = false;
  for (idx = 0; idx < i1; idx++) {
    if (rngFlag || (pNonZeros_data[idx] < 0.0)) {
      rngFlag = true;
    }
  }
  if (rngFlag) {
    emlrtErrorWithMessageIdR2018a(
        &st, &l_emlrtRTEI, "Coder:toolbox:ElFunDomainError",
        "Coder:toolbox:ElFunDomainError", 3, 4, 4, "log2");
  }
  b_st.site = &pe_emlrtRSI;
  c_st.site = &xc_emlrtRSI;
  for (idx = 0; idx < i1; idx++) {
    numCores = pNonZeros_data[idx];
    if (numCores == 0.0) {
      p[idx] = rtMinusInf;
    } else if (numCores < 0.0) {
      p[idx] = rtNaN;
    } else if ((!muDoubleScalarIsInf(numCores)) &&
               (!muDoubleScalarIsNaN(numCores))) {
      numCores = std::frexp(numCores, &eint);
      if (numCores == 0.5) {
        p[idx] = static_cast<real_T>(eint) - 1.0;
      } else if ((eint == 1) && (numCores < 0.75)) {
        p[idx] = muDoubleScalarLog(2.0 * numCores) / 0.69314718055994529;
      } else {
        p[idx] = muDoubleScalarLog(numCores) / 0.69314718055994529 +
                 static_cast<real_T>(eint);
      }
    } else {
      p[idx] = numCores;
    }
  }
  st.site = &yd_emlrtRSI;
  idx = scalarLB_tmp - 2;
  for (i = 0; i <= idx; i += 2) {
    r = _mm_loadu_pd(&pNonZeros_data[i]);
    r1 = _mm_loadu_pd(&p[i]);
    _mm_storeu_pd(&pNonZeros_data[i], _mm_mul_pd(r, r1));
  }
  for (i = scalarLB_tmp; i <= b_i; i++) {
    pNonZeros_data[i] *= p[i];
  }
  b_st.site = &qe_emlrtRSI;
  c_st.site = &re_emlrtRSI;
  d_st.site = &se_emlrtRSI;
  if (pNonZeros_size[1] == 0) {
    numCores = 0.0;
  } else {
    e_st.site = &te_emlrtRSI;
    f_st.site = &ue_emlrtRSI;
    b_pNonZeros_data.set(&pNonZeros_data[0], pNonZeros_size[1]);
    g_st.site = &ve_emlrtRSI;
    numCores = sumColumnB(g_st, b_pNonZeros_data, pNonZeros_size[1]);
  }
  E = -numCores;
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
  return E;
}

} // namespace coder

// End of code generation (entropy.cpp)
