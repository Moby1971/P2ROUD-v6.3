//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// repmat.cpp
//
// Code generation for function 'repmat'
//

// Include files
#include "repmat.h"
#include "applyEPIcorrection_data.h"
#include "assertValidSizeArg.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Variable Definitions
static emlrtRSInfo bb_emlrtRSI{
    28,       // lineNo
    "repmat", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m" // pathName
};

static emlrtRSInfo cb_emlrtRSI{
    64,       // lineNo
    "repmat", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m" // pathName
};

static emlrtRSInfo db_emlrtRSI{
    71,       // lineNo
    "repmat", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m" // pathName
};

static emlrtMCInfo emlrtMCI{
    47,       // lineNo
    5,        // colNo
    "repmat", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m" // pName
};

static emlrtRTEInfo sb_emlrtRTEI{
    59,       // lineNo
    28,       // colNo
    "repmat", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m" // pName
};

static emlrtRSInfo pg_emlrtRSI{
    47,       // lineNo
    "repmat", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m" // pathName
};

// Function Declarations
static void b_error(const emlrtStack &sp, const mxArray *m,
                    emlrtMCInfo &location);

// Function Definitions
static void b_error(const emlrtStack &sp, const mxArray *m,
                    emlrtMCInfo &location)
{
  const mxArray *pArray;
  pArray = m;
  emlrtCallMATLABR2012b((emlrtConstCTX)&sp, 0, nullptr, 1, &pArray, "error",
                        true, &location);
}

namespace coder {
void repmat(const emlrtStack &sp, const ::coder::array<creal_T, 2U> &a,
            const real_T varargin_1[2], ::coder::array<creal_T, 2U> &b)
{
  static const int32_T iv[2]{1, 15};
  static const char_T u[15]{'M', 'A', 'T', 'L', 'A', 'B', ':', 'p',
                            'm', 'a', 'x', 's', 'i', 'z', 'e'};
  emlrtStack b_st;
  emlrtStack st;
  const mxArray *m;
  const mxArray *y;
  int32_T ntilecols;
  int32_T outsize_idx_1;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &bb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  internal::assertValidSizeArg(st, varargin_1);
  outsize_idx_1 = static_cast<int32_T>(varargin_1[1]) << 1;
  if (!(outsize_idx_1 ==
        2.0 * static_cast<real_T>(static_cast<int32_T>(varargin_1[1])))) {
    y = nullptr;
    m = emlrtCreateCharArray(2, &iv[0]);
    emlrtInitCharArrayR2013a((emlrtConstCTX)&sp, 15, m, &u[0]);
    emlrtAssign(&y, m);
    st.site = &pg_emlrtRSI;
    b_error(st, y, emlrtMCI);
  }
  b.set_size(&sb_emlrtRTEI, &sp, a.size(0), outsize_idx_1);
  outsize_idx_1 = a.size(0);
  ntilecols = static_cast<int32_T>(varargin_1[1]);
  st.site = &cb_emlrtRSI;
  if (static_cast<int32_T>(varargin_1[1]) > 2147483646) {
    b_st.site = &ab_emlrtRSI;
    check_forloop_overflow_error(b_st);
  }
  for (int32_T jtilecol{0}; jtilecol < ntilecols; jtilecol++) {
    int32_T ibtile;
    boolean_T overflow;
    ibtile = jtilecol * (outsize_idx_1 << 1) - 1;
    overflow = (outsize_idx_1 > 2147483646);
    for (int32_T jcol{0}; jcol < 2; jcol++) {
      int32_T iacol_tmp;
      int32_T ibmat;
      iacol_tmp = jcol * outsize_idx_1;
      ibmat = ibtile + iacol_tmp;
      st.site = &db_emlrtRSI;
      if (overflow) {
        b_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(b_st);
      }
      for (int32_T k{0}; k < outsize_idx_1; k++) {
        b[(ibmat + k) + 1] = a[iacol_tmp + k];
      }
    }
  }
}

} // namespace coder

// End of code generation (repmat.cpp)
