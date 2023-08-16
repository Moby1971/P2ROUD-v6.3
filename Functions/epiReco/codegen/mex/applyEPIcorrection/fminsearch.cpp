//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// fminsearch.cpp
//
// Code generation for function 'fminsearch'
//

// Include files
#include "fminsearch.h"
#include "anonymous_function.h"
#include "applyEPIcorrection.h"
#include "applyEPIcorrection_internal_types.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "coder_array.h"
#include "mwmathutil.h"
#include <cmath>
#include <emmintrin.h>

// Variable Definitions
static emlrtRSInfo
    f_emlrtRSI{
        86,           // lineNo
        "fminsearch", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

static emlrtRSInfo
    g_emlrtRSI{
        152,          // lineNo
        "fminsearch", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

static emlrtRSInfo
    h_emlrtRSI{
        216,          // lineNo
        "fminsearch", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

static emlrtRSInfo
    i_emlrtRSI{
        226,          // lineNo
        "fminsearch", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

static emlrtRSInfo
    j_emlrtRSI{
        256,          // lineNo
        "fminsearch", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

static emlrtRSInfo
    k_emlrtRSI{
        275,          // lineNo
        "fminsearch", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

static emlrtRSInfo
    l_emlrtRSI{
        298,          // lineNo
        "fminsearch", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

static emlrtRSInfo
    m_emlrtRSI{
        499,           // lineNo
        "getCheckFcn", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

static emlrtRSInfo n_emlrtRSI{
    63,                               // lineNo
    "function_handle/parenReference", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\function_"
    "handle.m" // pathName
};

static emlrtRSInfo
    og_emlrtRSI{
        516,        // lineNo
        "checkfun", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\optimfun\\fminsearch"
        ".m" // pathName
    };

// Function Definitions
namespace coder {
void fminsearch(const emlrtStack &sp, const anonymous_function &funfcn,
                real_T x[2])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  real_T v[6];
  real_T fv[3];
  real_T xbar[2];
  real_T xr[2];
  real_T absx;
  real_T cfv;
  int32_T idx[3];
  int32_T b_exponent;
  int32_T b_firstCol;
  int32_T c_exponent;
  int32_T colIdx;
  int32_T exponent;
  int32_T firstCol;
  int32_T fun_evals;
  int32_T itercount;
  int32_T lastCol;
  boolean_T exitg1;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &f_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  b_st.site = &m_emlrtRSI;
  c_st.site = &n_emlrtRSI;
  fv[0] = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                funfcn.workspace.method,
                                funfcn.workspace.idxMap, x);
  cfv = x[0];
  absx = x[1];
  for (colIdx = 0; colIdx < 3; colIdx++) {
    firstCol = colIdx << 1;
    v[firstCol] = cfv;
    v[firstCol + 1] = absx;
  }
  if (x[0] != 0.0) {
    v[2] = 1.05 * x[0];
  } else {
    v[2] = 0.00025;
  }
  xr[0] = v[2];
  xr[1] = v[3];
  st.site = &g_emlrtRSI;
  b_st.site = &og_emlrtRSI;
  c_st.site = &n_emlrtRSI;
  fv[1] = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                funfcn.workspace.method,
                                funfcn.workspace.idxMap, xr);
  if (x[1] != 0.0) {
    v[5] = 1.05 * x[1];
  } else {
    v[5] = 0.00025;
  }
  xr[0] = v[4];
  xr[1] = v[5];
  st.site = &g_emlrtRSI;
  b_st.site = &og_emlrtRSI;
  c_st.site = &n_emlrtRSI;
  fv[2] = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                funfcn.workspace.method,
                                funfcn.workspace.idxMap, xr);
  internal::sortIdx(fv, idx);
  itercount = 1;
  fun_evals = 3;
  lastCol = (idx[2] - 1) << 1;
  b_firstCol = (idx[0] - 1) << 1;
  exitg1 = false;
  while ((!exitg1) && ((fun_evals < 2000) && (itercount < 400))) {
    real_T b_cfv_tmp_tmp_tmp;
    real_T c_cfv_tmp_tmp_tmp;
    real_T cfv_tmp_tmp_tmp;
    real_T maxfv;
    boolean_T p;
    maxfv = 0.0;
    cfv_tmp_tmp_tmp = fv[idx[0] - 1];
    b_cfv_tmp_tmp_tmp = fv[idx[1] - 1];
    cfv = muDoubleScalarAbs(cfv_tmp_tmp_tmp - b_cfv_tmp_tmp_tmp);
    if (cfv > 0.0) {
      maxfv = cfv;
    }
    c_cfv_tmp_tmp_tmp = fv[idx[2] - 1];
    cfv = muDoubleScalarAbs(cfv_tmp_tmp_tmp - c_cfv_tmp_tmp_tmp);
    if (cfv > maxfv) {
      maxfv = cfv;
    }
    absx = muDoubleScalarAbs(cfv_tmp_tmp_tmp);
    if (muDoubleScalarIsInf(absx) || muDoubleScalarIsNaN(absx)) {
      absx = rtNaN;
    } else if (absx < 4.4501477170144028E-308) {
      absx = 4.94065645841247E-324;
    } else {
      std::frexp(absx, &exponent);
      absx = std::ldexp(1.0, exponent - 53);
    }
    absx *= 10.0;
    if (muDoubleScalarIsNaN(absx)) {
      absx = rtNaN;
    } else if (absx < 4.4501477170144028E-308) {
      absx = 4.94065645841247E-324;
    } else {
      std::frexp(absx, &b_exponent);
      absx = std::ldexp(1.0, b_exponent - 53);
    }
    if (maxfv > muDoubleScalarMax(1.0E-6, 10.0 * absx)) {
      p = false;
    } else {
      maxfv = 0.0;
      firstCol = (idx[0] - 1) << 1;
      colIdx = (idx[1] - 1) << 1;
      cfv = muDoubleScalarAbs(v[firstCol] - v[colIdx]);
      if (cfv > 0.0) {
        maxfv = cfv;
      }
      absx = v[firstCol + 1];
      cfv = muDoubleScalarAbs(absx - v[colIdx + 1]);
      if (cfv > maxfv) {
        maxfv = cfv;
      }
      colIdx = (idx[2] - 1) << 1;
      cfv = muDoubleScalarAbs(v[firstCol] - v[colIdx]);
      if (cfv > maxfv) {
        maxfv = cfv;
      }
      cfv = muDoubleScalarAbs(absx - v[colIdx + 1]);
      if (cfv > maxfv) {
        maxfv = cfv;
      }
      cfv = v[firstCol];
      if (absx > v[firstCol]) {
        cfv = absx;
      }
      absx = muDoubleScalarAbs(cfv);
      if (muDoubleScalarIsInf(absx) || muDoubleScalarIsNaN(absx)) {
        absx = rtNaN;
      } else if (absx < 4.4501477170144028E-308) {
        absx = 4.94065645841247E-324;
      } else {
        std::frexp(absx, &c_exponent);
        absx = std::ldexp(1.0, c_exponent - 53);
      }
      p = (maxfv <= muDoubleScalarMax(1.0E-6, 10.0 * absx));
    }
    if (!p) {
      __m128d r;
      __m128d r1;
      __m128d r2;
      boolean_T guard1;
      boolean_T guard2;
      r = _mm_loadu_pd(&v[b_firstCol]);
      firstCol = (idx[1] - 1) << 1;
      r1 = _mm_loadu_pd(&v[firstCol]);
      r2 = _mm_set1_pd(2.0);
      r = _mm_div_pd(_mm_add_pd(r, r1), r2);
      _mm_storeu_pd(&xbar[0], r);
      r1 = _mm_loadu_pd(&v[lastCol]);
      _mm_storeu_pd(&xr[0], _mm_sub_pd(_mm_mul_pd(r2, r), r1));
      st.site = &h_emlrtRSI;
      b_st.site = &og_emlrtRSI;
      c_st.site = &n_emlrtRSI;
      maxfv = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                    funfcn.workspace.method,
                                    funfcn.workspace.idxMap, xr);
      fun_evals++;
      guard1 = false;
      guard2 = false;
      if (maxfv < cfv_tmp_tmp_tmp) {
        r = _mm_loadu_pd(&xbar[0]);
        r1 = _mm_loadu_pd(&v[lastCol]);
        _mm_storeu_pd(&xbar[0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(3.0), r),
                                           _mm_mul_pd(r2, r1)));
        st.site = &i_emlrtRSI;
        b_st.site = &og_emlrtRSI;
        c_st.site = &n_emlrtRSI;
        cfv = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                    funfcn.workspace.method,
                                    funfcn.workspace.idxMap, xbar);
        fun_evals++;
        if (cfv < maxfv) {
          v[lastCol] = xbar[0];
          v[lastCol + 1] = xbar[1];
          fv[idx[2] - 1] = cfv;
        } else {
          v[lastCol] = xr[0];
          v[lastCol + 1] = xr[1];
          fv[idx[2] - 1] = maxfv;
        }
        guard1 = true;
      } else if (maxfv < b_cfv_tmp_tmp_tmp) {
        v[lastCol] = xr[0];
        v[lastCol + 1] = xr[1];
        fv[idx[2] - 1] = maxfv;
        guard1 = true;
      } else if (maxfv < c_cfv_tmp_tmp_tmp) {
        r = _mm_loadu_pd(&xbar[0]);
        r1 = _mm_loadu_pd(&v[lastCol]);
        _mm_storeu_pd(&x[0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(1.5), r),
                                        _mm_mul_pd(_mm_set1_pd(0.5), r1)));
        st.site = &j_emlrtRSI;
        b_st.site = &og_emlrtRSI;
        c_st.site = &n_emlrtRSI;
        absx = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                     funfcn.workspace.method,
                                     funfcn.workspace.idxMap, x);
        fun_evals++;
        if (absx <= maxfv) {
          v[lastCol] = x[0];
          v[lastCol + 1] = x[1];
          fv[idx[2] - 1] = absx;
          guard1 = true;
        } else {
          guard2 = true;
        }
      } else {
        r = _mm_loadu_pd(&xbar[0]);
        r1 = _mm_loadu_pd(&v[lastCol]);
        r2 = _mm_set1_pd(0.5);
        _mm_storeu_pd(&x[0], _mm_add_pd(_mm_mul_pd(r2, r), _mm_mul_pd(r2, r1)));
        st.site = &k_emlrtRSI;
        b_st.site = &og_emlrtRSI;
        c_st.site = &n_emlrtRSI;
        absx = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                     funfcn.workspace.method,
                                     funfcn.workspace.idxMap, x);
        fun_evals++;
        if (absx < c_cfv_tmp_tmp_tmp) {
          v[lastCol] = x[0];
          v[lastCol + 1] = x[1];
          fv[idx[2] - 1] = absx;
          guard1 = true;
        } else {
          guard2 = true;
        }
      }
      if (guard2) {
        real_T fvt[3];
        int32_T idxb[3];
        v[firstCol] = v[b_firstCol] + 0.5 * (v[firstCol] - v[b_firstCol]);
        x[0] = v[firstCol];
        cfv = v[b_firstCol + 1];
        v[firstCol + 1] = cfv + 0.5 * (v[firstCol + 1] - cfv);
        x[1] = v[firstCol + 1];
        st.site = &l_emlrtRSI;
        b_st.site = &og_emlrtRSI;
        c_st.site = &n_emlrtRSI;
        fv[idx[1] - 1] = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                               funfcn.workspace.method,
                                               funfcn.workspace.idxMap, x);
        colIdx = ((idx[2] - 1) << 1) - 1;
        v[colIdx + 1] = v[b_firstCol] + 0.5 * (v[colIdx + 1] - v[b_firstCol]);
        x[0] = v[colIdx + 1];
        cfv = v[b_firstCol + 1];
        v[colIdx + 2] = cfv + 0.5 * (v[colIdx + 2] - cfv);
        x[1] = v[colIdx + 2];
        st.site = &l_emlrtRSI;
        b_st.site = &og_emlrtRSI;
        c_st.site = &n_emlrtRSI;
        fv[idx[2] - 1] = findEPIshift_anonFcn1(c_st, funfcn.workspace.kSpace,
                                               funfcn.workspace.method,
                                               funfcn.workspace.idxMap, x);
        fun_evals += 2;
        fvt[0] = fv[idx[0] - 1];
        idxb[0] = idx[0];
        fvt[1] = fv[idx[1] - 1];
        idxb[1] = idx[1];
        fvt[2] = fv[idx[2] - 1];
        idxb[2] = idx[2];
        internal::sortIdx(fvt, idx);
        idx[0] = idxb[idx[0] - 1];
        idx[1] = idxb[idx[1] - 1];
        idx[2] = idxb[idx[2] - 1];
      }
      if (guard1) {
        firstCol = idx[2];
        if (fv[idx[2] - 1] < fv[idx[1] - 1]) {
          idx[2] = idx[1];
          idx[1] = firstCol;
        }
        firstCol = idx[1];
        if (fv[idx[1] - 1] < fv[idx[0] - 1]) {
          idx[1] = idx[0];
          idx[0] = firstCol;
        }
      }
      itercount++;
      lastCol = (idx[2] - 1) << 1;
      b_firstCol = (idx[0] - 1) << 1;
    } else {
      exitg1 = true;
    }
  }
  colIdx = (idx[0] - 1) << 1;
  x[0] = v[colIdx];
  x[1] = v[colIdx + 1];
}

} // namespace coder

// End of code generation (fminsearch.cpp)
