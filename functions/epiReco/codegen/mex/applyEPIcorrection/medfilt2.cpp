//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// medfilt2.cpp
//
// Code generation for function 'medfilt2'
//

// Include files
#include "medfilt2.h"
#include "applyEPIcorrection_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "libmwordfilt2.h"

// Variable Definitions
static emlrtRSInfo df_emlrtRSI{
    62,         // lineNo
    "medfilt2", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\medfilt2.m" // pathName
};

static emlrtRSInfo ef_emlrtRSI{
    25,         // lineNo
    "ordfilt2", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\ordfilt2.m" // pathName
};

static emlrtRSInfo ff_emlrtRSI{
    137,        // lineNo
    "ordfilt2", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\ordfilt2.m" // pathName
};

static emlrtRSInfo gf_emlrtRSI{
    155,        // lineNo
    "ordfilt2", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\ordfilt2.m" // pathName
};

static emlrtRSInfo hf_emlrtRSI{
    91,         // lineNo
    "padarray", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m" // pathName
};

static emlrtRSInfo if_emlrtRSI{
    685,           // lineNo
    "ConstantPad", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m" // pathName
};

static emlrtRSInfo jf_emlrtRSI{
    700,           // lineNo
    "ConstantPad", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m" // pathName
};

static emlrtRSInfo kf_emlrtRSI{
    179,                     // lineNo
    "ordfilt2SharedLibrary", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\ordfilt2.m" // pathName
};

static emlrtBCInfo r_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    680,           // lineNo
    19,            // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo s_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    694,           // lineNo
    21,            // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo t_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    687,           // lineNo
    19,            // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo u_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    687,           // lineNo
    21,            // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo v_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    724,           // lineNo
    102,           // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo w_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    724,           // lineNo
    104,           // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo x_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    724,           // lineNo
    19,            // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo y_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    724,           // lineNo
    58,            // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo ab_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    701,           // lineNo
    19,            // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtBCInfo bb_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    701,           // lineNo
    21,            // colNo
    "",            // aName
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    0 // checkKind
};

static emlrtDCInfo f_emlrtDCI{
    533,           // lineNo
    35,            // colNo
    "ConstantPad", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m", // pName
    1 // checkKind
};

static emlrtRTEInfo ac_emlrtRTEI{
    533,        // lineNo
    28,         // colNo
    "padarray", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\padarray.m" // pName
};

// Function Definitions
namespace coder {
void medfilt2(const emlrtStack &sp, ::coder::array<real_T, 2U> &varargin_1)
{
  static const int8_T b_a[9]{-1, -1, -1, 0, 0, 0, 1, 1, 1};
  static const int8_T rows[9]{-1, 0, 1, -1, 0, 1, -1, 0, 1};
  array<real_T, 2U> Apad;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack st;
  boolean_T b;
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
  b = ((varargin_1.size(0) == 0) || (varargin_1.size(1) == 0));
  if (!b) {
    real_T d;
    real_T d1;
    int32_T indices[9];
    int32_T a;
    int32_T b_b;
    int32_T i;
    int32_T i1;
    st.site = &df_emlrtRSI;
    b_st.site = &ef_emlrtRSI;
    b_st.site = &ff_emlrtRSI;
    c_st.site = &hf_emlrtRSI;
    d = static_cast<real_T>(varargin_1.size(0)) + 2.0;
    if (d != static_cast<int32_T>(d)) {
      emlrtIntegerCheckR2012b(d, &f_emlrtDCI, &c_st);
    }
    d1 = static_cast<real_T>(varargin_1.size(1)) + 2.0;
    if (d1 != static_cast<int32_T>(d1)) {
      emlrtIntegerCheckR2012b(d1, &f_emlrtDCI, &c_st);
    }
    i = static_cast<int32_T>(d);
    Apad.set_size(&ac_emlrtRTEI, &c_st, static_cast<int32_T>(d),
                  static_cast<int32_T>(d1));
    for (int32_T b_i{0}; b_i < i; b_i++) {
      if ((b_i + 1 < 1) || (b_i + 1 > Apad.size(0))) {
        emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, Apad.size(0), &r_emlrtBCI,
                                      &c_st);
      }
      Apad[b_i] = 0.0;
    }
    a = varargin_1.size(1) + 2;
    b_b = Apad.size(1);
    d_st.site = &if_emlrtRSI;
    if ((varargin_1.size(1) + 2 <= Apad.size(1)) &&
        (Apad.size(1) > 2147483646)) {
      e_st.site = &ab_emlrtRSI;
      check_forloop_overflow_error(e_st);
    }
    for (int32_T j{a}; j <= b_b; j++) {
      i = Apad.size(0);
      for (int32_T b_i{0}; b_i < i; b_i++) {
        if (b_i + 1 > Apad.size(0)) {
          emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, Apad.size(0), &t_emlrtBCI,
                                        &c_st);
        }
        if ((j < 1) || (j > Apad.size(1))) {
          emlrtDynamicBoundsCheckR2012b(j, 1, Apad.size(1), &u_emlrtBCI, &c_st);
        }
        Apad[b_i + Apad.size(0) * (j - 1)] = 0.0;
      }
    }
    i = varargin_1.size(1);
    for (int32_T j{0}; j < i; j++) {
      if ((j + 2 < 1) || (j + 2 > Apad.size(1))) {
        emlrtDynamicBoundsCheckR2012b(j + 2, 1, Apad.size(1), &s_emlrtBCI,
                                      &c_st);
      }
      Apad[Apad.size(0) * (j + 1)] = 0.0;
    }
    i = varargin_1.size(1);
    for (int32_T j{0}; j < i; j++) {
      i1 = varargin_1.size(0);
      a = i1 + 2;
      b_b = Apad.size(0);
      d_st.site = &jf_emlrtRSI;
      if ((i1 + 2 <= Apad.size(0)) && (Apad.size(0) > 2147483646)) {
        e_st.site = &ab_emlrtRSI;
        check_forloop_overflow_error(e_st);
      }
      for (int32_T b_i{a}; b_i <= b_b; b_i++) {
        if ((b_i < 1) || (b_i > Apad.size(0))) {
          emlrtDynamicBoundsCheckR2012b(b_i, 1, Apad.size(0), &ab_emlrtBCI,
                                        &c_st);
        }
        if ((j + 2 < 1) || (j + 2 > Apad.size(1))) {
          emlrtDynamicBoundsCheckR2012b(j + 2, 1, Apad.size(1), &bb_emlrtBCI,
                                        &c_st);
        }
        Apad[(b_i + Apad.size(0) * (j + 1)) - 1] = 0.0;
      }
    }
    i = varargin_1.size(1);
    for (int32_T j{0}; j < i; j++) {
      i1 = varargin_1.size(0);
      for (int32_T b_i{0}; b_i < i1; b_i++) {
        a = varargin_1.size(0);
        if (b_i + 1 > a) {
          emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, a, &v_emlrtBCI, &c_st);
        }
        a = varargin_1.size(1);
        if (j + 1 > a) {
          emlrtDynamicBoundsCheckR2012b(j + 1, 1, a, &w_emlrtBCI, &c_st);
        }
        if ((b_i + 2 < 1) || (b_i + 2 > Apad.size(0))) {
          emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, Apad.size(0), &x_emlrtBCI,
                                        &c_st);
        }
        if ((j + 2 < 1) || (j + 2 > Apad.size(1))) {
          emlrtDynamicBoundsCheckR2012b(j + 2, 1, Apad.size(1), &y_emlrtBCI,
                                        &c_st);
        }
        Apad[(b_i + Apad.size(0) * (j + 1)) + 1] =
            varargin_1[b_i + varargin_1.size(0) * j];
      }
    }
    for (i = 0; i < 9; i++) {
      d = static_cast<real_T>(b_a[i] * Apad.size(0)) +
          static_cast<real_T>(rows[i]);
      if (d < 2.147483648E+9) {
        i1 = static_cast<int32_T>(d);
      } else {
        i1 = MAX_int32_T;
      }
      indices[i] = i1;
    }
    real_T domainSizeT[2];
    real_T sizeB[2];
    real_T startIdxT[2];
    b_st.site = &gf_emlrtRSI;
    c_st.site = &kf_emlrtRSI;
    startIdxT[0] = 1.0;
    domainSizeT[0] = 3.0;
    sizeB[0] = varargin_1.size(0);
    startIdxT[1] = 1.0;
    domainSizeT[1] = 3.0;
    sizeB[1] = varargin_1.size(1);
    ordfilt2_real64(&Apad[0], static_cast<real_T>(Apad.size(0)), &startIdxT[0],
                    &indices[0], 9.0, &domainSizeT[0], 4.0, &varargin_1[0],
                    &sizeB[0], true);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
}

} // namespace coder

// End of code generation (medfilt2.cpp)
