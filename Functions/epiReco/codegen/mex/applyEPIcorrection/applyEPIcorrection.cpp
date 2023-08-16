//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// applyEPIcorrection.cpp
//
// Code generation for function 'applyEPIcorrection'
//

// Include files
#include "applyEPIcorrection.h"
#include "abs.h"
#include "anonymous_function.h"
#include "applyEPIcorrection_data.h"
#include "applyEPIcorrection_internal_types.h"
#include "circshift.h"
#include "eml_fftshift.h"
#include "eml_int_forloop_overflow_check.h"
#include "entropy.h"
#include "exp.h"
#include "fft2.h"
#include "fminsearch.h"
#include "ifftshift.h"
#include "indexShapeCheck.h"
#include "mat2gray.h"
#include "medfilt2.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sumMatrixIncludeNaN.h"
#include "svd.h"
#include "coder_array.h"
#include "mwmathutil.h"
#include "omp.h"
#include <emmintrin.h>

// Variable Definitions
static emlrtRSInfo emlrtRSI{
    5,                    // lineNo
    "applyEPIcorrection", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo b_emlrtRSI{
    7,                    // lineNo
    "applyEPIcorrection", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo c_emlrtRSI{
    40,                                // lineNo
    "applyEPIcorrection/findEPIshift", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo d_emlrtRSI{
    64,                                // lineNo
    "applyEPIcorrection/findEPIshift", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo e_emlrtRSI{
    16,        // lineNo
    "sub2ind", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\sub2ind.m" // pathName
};

static emlrtRSInfo o_emlrtRSI{
    50,                                            // lineNo
    "@(x)calculateMetric(x,kSpace,method,idxMap)", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo p_emlrtRSI{
    81,                                                // lineNo
    "applyEPIcorrection/findEPIshift/calculateMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo q_emlrtRSI{
    82,                                                // lineNo
    "applyEPIcorrection/findEPIshift/calculateMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo r_emlrtRSI{
    148,                                      // lineNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo s_emlrtRSI{
    164,                                      // lineNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo t_emlrtRSI{
    165,                                      // lineNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo u_emlrtRSI{
    168,                                      // lineNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo v_emlrtRSI{
    171,                                      // lineNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo w_emlrtRSI{
    172,                                      // lineNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo mb_emlrtRSI{
    63,    // lineNo
    "fft", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\fft.m" // pathName
};

static emlrtRSInfo tb_emlrtRSI{
    17,         // lineNo
    "fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\fftshift.m" // pathName
};

static emlrtRSInfo ub_emlrtRSI{
    80,     // lineNo
    "ifft", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\ifft.m" // pathName
};

static emlrtRSInfo vb_emlrtRSI{
    94,                                          // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo wb_emlrtRSI{
    95,                                          // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo xb_emlrtRSI{
    99,                                          // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo yb_emlrtRSI{
    100,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo ac_emlrtRSI{
    101,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo bc_emlrtRSI{
    109,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo cc_emlrtRSI{
    110,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo dc_emlrtRSI{
    111,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo ec_emlrtRSI{
    113,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo fc_emlrtRSI{
    121,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo gc_emlrtRSI{
    122,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo hc_emlrtRSI{
    124,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo ic_emlrtRSI{
    125,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo jc_emlrtRSI{
    127,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo kc_emlrtRSI{
    128,                                         // lineNo
    "applyEPIcorrection/findEPIshift/getMetric", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo vc_emlrtRSI{
    12,         // lineNo
    "fftshift", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\fftshift.m" // pathName
};

static emlrtRSInfo vf_emlrtRSI{
    107,                // lineNo
    "blockedSummation", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\blocke"
    "dSummation.m" // pathName
};

static emlrtRSInfo gg_emlrtRSI{
    34,               // lineNo
    "rdivide_helper", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\rdivide_"
    "helper.m" // pathName
};

static emlrtRSInfo hg_emlrtRSI{
    51,    // lineNo
    "div", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\div.m" // pathName
};

static emlrtRSInfo ig_emlrtRSI{
    13,               // lineNo
    "nullAssignment", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\nullAssignment.m" // pathName
};

static emlrtRSInfo jg_emlrtRSI{
    17,               // lineNo
    "nullAssignment", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\nullAssignment.m" // pathName
};

static emlrtRSInfo kg_emlrtRSI{
    169,                      // lineNo
    "onearg_null_assignment", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\nullAssignment.m" // pathName
};

static emlrtRSInfo lg_emlrtRSI{
    172,                      // lineNo
    "onearg_null_assignment", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\nullAssignment.m" // pathName
};

static emlrtRSInfo mg_emlrtRSI{
    132,        // lineNo
    "num_true", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\nullAssignment.m" // pathName
};

static emlrtRSInfo ng_emlrtRSI{
    49,     // lineNo
    "mean", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\mean.m" // pathName
};

static emlrtBCInfo emlrtBCI{
    -1,                                // iFirst
    -1,                                // iLast
    41,                                // lineNo
    28,                                // colNo
    "idxMap",                          // aName
    "applyEPIcorrection/findEPIshift", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtRTEInfo emlrtRTEI{
    28,        // lineNo
    19,        // colNo
    "sub2ind", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\sub2ind.m" // pName
};

static emlrtDCInfo emlrtDCI{
    30,                                // lineNo
    28,                                // colNo
    "applyEPIcorrection/findEPIshift", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    1                // checkKind
};

static emlrtDCInfo b_emlrtDCI{
    30,                                // lineNo
    28,                                // colNo
    "applyEPIcorrection/findEPIshift", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    4                // checkKind
};

static emlrtDCInfo c_emlrtDCI{
    30,                                // lineNo
    13,                                // colNo
    "applyEPIcorrection/findEPIshift", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    1                // checkKind
};

static emlrtRTEInfo c_emlrtRTEI{
    181,                      // lineNo
    9,                        // colNo
    "onearg_null_assignment", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\nullAssignment.m" // pName
};

static emlrtRTEInfo d_emlrtRTEI{
    85,                // lineNo
    27,                // colNo
    "validate_inputs", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\nullAssignment.m" // pName
};

static emlrtRTEInfo f_emlrtRTEI{
    13,                     // lineNo
    27,                     // colNo
    "assertCompatibleDims", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\assertCompatibleDims.m" // pName
};

static emlrtBCInfo b_emlrtBCI{
    -1,                                          // iFirst
    -1,                                          // iLast
    109,                                         // lineNo
    34,                                          // colNo
    "kSpace",                                    // aName
    "applyEPIcorrection/findEPIshift/getMetric", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtBCInfo c_emlrtBCI{
    -1,                                       // iFirst
    -1,                                       // iLast
    152,                                      // lineNo
    19,                                       // colNo
    "newKspace",                              // aName
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtBCInfo d_emlrtBCI{
    -1,                                       // iFirst
    -1,                                       // iLast
    152,                                      // lineNo
    21,                                       // colNo
    "newKspace",                              // aName
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtBCInfo e_emlrtBCI{
    -1,                                       // iFirst
    -1,                                       // iLast
    152,                                      // lineNo
    39,                                       // colNo
    "newKspace",                              // aName
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtBCInfo f_emlrtBCI{
    -1,                                       // iFirst
    -1,                                       // iLast
    152,                                      // lineNo
    41,                                       // colNo
    "newKspace",                              // aName
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtECInfo emlrtECI{
    -1,                                       // nDims
    152,                                      // lineNo
    9,                                        // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtECInfo b_emlrtECI{
    -1,                                       // nDims
    155,                                      // lineNo
    9,                                        // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtECInfo c_emlrtECI{
    -1,                                       // nDims
    156,                                      // lineNo
    9,                                        // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtBCInfo g_emlrtBCI{
    -1,                                       // iFirst
    -1,                                       // iLast
    164,                                      // lineNo
    27,                                       // colNo
    "phaseCorrection",                        // aName
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtECInfo d_emlrtECI{
    -1,                                       // nDims
    164,                                      // lineNo
    9,                                        // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtBCInfo h_emlrtBCI{
    -1,                                       // iFirst
    -1,                                       // iLast
    165,                                      // lineNo
    27,                                       // colNo
    "phaseCorrection",                        // aName
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtECInfo e_emlrtECI{
    -1,                                       // nDims
    165,                                      // lineNo
    9,                                        // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtECInfo f_emlrtECI{
    1,                                        // nDims
    172,                                      // lineNo
    46,                                       // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtECInfo g_emlrtECI{
    2,                                        // nDims
    172,                                      // lineNo
    46,                                       // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo g_emlrtRTEI{
    37,    // lineNo
    31,    // colNo
    "fft", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\fft.m" // pName
};

static emlrtDCInfo d_emlrtDCI{
    149,                                      // lineNo
    57,                                       // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    1                // checkKind
};

static emlrtDCInfo e_emlrtDCI{
    149,                                      // lineNo
    13,                                       // colNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    1                // checkKind
};

static emlrtBCInfo i_emlrtBCI{
    -1,                                       // iFirst
    -1,                                       // iLast
    168,                                      // lineNo
    52,                                       // colNo
    "phaseCorrection",                        // aName
    "applyEPIcorrection/firstOrderPhaseCorr", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m", // pName
    0                // checkKind
};

static emlrtRTEInfo t_emlrtRTEI{
    45,                   // lineNo
    13,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo u_emlrtRTEI{
    30,                   // lineNo
    13,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo v_emlrtRTEI{
    35,                // lineNo
    13,                // colNo
    "function_handle", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\function_"
    "handle.m" // pName
};

static emlrtRTEInfo w_emlrtRTEI{
    122,                  // lineNo
    21,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo x_emlrtRTEI{
    52,    // lineNo
    9,     // colNo
    "div", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\div.m" // pName
};

static emlrtRTEInfo y_emlrtRTEI{
    126,                  // lineNo
    21,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo ab_emlrtRTEI{
    16,      // lineNo
    9,       // colNo
    "isnan", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elmat\\isnan.m" // pName
};

static emlrtRTEInfo bb_emlrtRTEI{
    127,                  // lineNo
    21,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo db_emlrtRTEI{
    109,                  // lineNo
    27,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo eb_emlrtRTEI{
    146,                  // lineNo
    9,                    // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo fb_emlrtRTEI{
    149,                  // lineNo
    13,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo gb_emlrtRTEI{
    155,                  // lineNo
    32,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo hb_emlrtRTEI{
    156,                  // lineNo
    32,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo ib_emlrtRTEI{
    159,                  // lineNo
    9,                    // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo
    jb_emlrtRTEI{
        28,      // lineNo
        9,       // colNo
        "colon", // fName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" // pName
    };

static emlrtRTEInfo kb_emlrtRTEI{
    161,                  // lineNo
    9,                    // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo lb_emlrtRTEI{
    164,                  // lineNo
    32,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo mb_emlrtRTEI{
    165,                  // lineNo
    32,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo nb_emlrtRTEI{
    168,                  // lineNo
    34,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo ob_emlrtRTEI{
    168,                  // lineNo
    9,                    // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRTEInfo qb_emlrtRTEI{
    63,    // lineNo
    5,     // colNo
    "fft", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\fft.m" // pName
};

static emlrtRTEInfo rb_emlrtRTEI{
    80,     // lineNo
    1,      // colNo
    "ifft", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\ifft.m" // pName
};

static emlrtRTEInfo cc_emlrtRTEI{
    172,                  // lineNo
    46,                   // colNo
    "applyEPIcorrection", // fName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pName
};

static emlrtRSInfo rg_emlrtRSI{
    156,                                      // lineNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

static emlrtRSInfo sg_emlrtRSI{
    155,                                      // lineNo
    "applyEPIcorrection/firstOrderPhaseCorr", // fcnName
    "L:"
    "\\basic\\divh\\BMEPH\\Gustav\\MATLAB\\P2ROUD5\\Functions\\epiReco\\applyEP"
    "Icorrection.m" // pathName
};

// Function Declarations
static void binary_expand_op(const emlrtStack &sp,
                             coder::array<real_T, 2U> &in1,
                             const emlrtRSInfo in2,
                             const coder::array<creal_T, 2U> &in3,
                             const coder::array<creal_T, 2U> &in4);

static int32_T div_s32(const emlrtStack &sp, int32_T numerator,
                       int32_T denominator);

static void firstOrderPhaseCorr(const emlrtStack &sp,
                                const coder::array<creal_T, 2U> &oldKspace,
                                real_T kappa, real_T phi,
                                coder::array<creal_T, 2U> &newKspace);

static void times(const emlrtStack &sp, coder::array<creal_T, 2U> &in1,
                  const coder::array<creal_T, 2U> &in2);

// Function Definitions
static void binary_expand_op(const emlrtStack &sp,
                             coder::array<real_T, 2U> &in1,
                             const emlrtRSInfo in2,
                             const coder::array<creal_T, 2U> &in3,
                             const coder::array<creal_T, 2U> &in4)
{
  coder::array<creal_T, 2U> b_in3;
  emlrtStack st;
  int32_T aux_0_1;
  int32_T aux_1_1;
  int32_T b_loop_ub;
  int32_T loop_ub;
  int32_T stride_0_0;
  int32_T stride_0_1;
  int32_T stride_1_0;
  int32_T stride_1_1;
  st.prev = &sp;
  st.tls = sp.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)&sp);
  if (in4.size(0) == 1) {
    loop_ub = in3.size(0);
  } else {
    loop_ub = in4.size(0);
  }
  if (in4.size(1) == 1) {
    b_loop_ub = in3.size(1);
  } else {
    b_loop_ub = in4.size(1);
  }
  b_in3.set_size(&x_emlrtRTEI, &sp, loop_ub, b_loop_ub);
  stride_0_0 = (in3.size(0) != 1);
  stride_0_1 = (in3.size(1) != 1);
  stride_1_0 = (in4.size(0) != 1);
  stride_1_1 = (in4.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int32_T i{0}; i < b_loop_ub; i++) {
    for (int32_T i1{0}; i1 < loop_ub; i1++) {
      real_T ai;
      real_T ar;
      real_T bi;
      real_T br;
      int32_T ar_tmp;
      ar_tmp = i1 * stride_0_0;
      ar = in3[ar_tmp + in3.size(0) * aux_0_1].re;
      ai = in3[ar_tmp + in3.size(0) * aux_0_1].im;
      ar_tmp = i1 * stride_1_0;
      br = in4[ar_tmp + in4.size(0) * aux_1_1].re;
      bi = in4[ar_tmp + in4.size(0) * aux_1_1].im;
      if (bi == 0.0) {
        if (ai == 0.0) {
          b_in3[i1 + b_in3.size(0) * i].re = ar / br;
          b_in3[i1 + b_in3.size(0) * i].im = 0.0;
        } else if (ar == 0.0) {
          b_in3[i1 + b_in3.size(0) * i].re = 0.0;
          b_in3[i1 + b_in3.size(0) * i].im = ai / br;
        } else {
          b_in3[i1 + b_in3.size(0) * i].re = ar / br;
          b_in3[i1 + b_in3.size(0) * i].im = ai / br;
        }
      } else if (br == 0.0) {
        if (ar == 0.0) {
          b_in3[i1 + b_in3.size(0) * i].re = ai / bi;
          b_in3[i1 + b_in3.size(0) * i].im = 0.0;
        } else if (ai == 0.0) {
          b_in3[i1 + b_in3.size(0) * i].re = 0.0;
          b_in3[i1 + b_in3.size(0) * i].im = -(ar / bi);
        } else {
          b_in3[i1 + b_in3.size(0) * i].re = ai / bi;
          b_in3[i1 + b_in3.size(0) * i].im = -(ar / bi);
        }
      } else {
        real_T bim;
        real_T brm;
        brm = muDoubleScalarAbs(br);
        bim = muDoubleScalarAbs(bi);
        if (brm > bim) {
          real_T s;
          s = bi / br;
          bim = br + s * bi;
          b_in3[i1 + b_in3.size(0) * i].re = (ar + s * ai) / bim;
          b_in3[i1 + b_in3.size(0) * i].im = (ai - s * ar) / bim;
        } else if (bim == brm) {
          real_T s;
          if (br > 0.0) {
            s = 0.5;
          } else {
            s = -0.5;
          }
          if (bi > 0.0) {
            bim = 0.5;
          } else {
            bim = -0.5;
          }
          b_in3[i1 + b_in3.size(0) * i].re = (ar * s + ai * bim) / brm;
          b_in3[i1 + b_in3.size(0) * i].im = (ai * s - ar * bim) / brm;
        } else {
          real_T s;
          s = br / bi;
          bim = bi + s * br;
          b_in3[i1 + b_in3.size(0) * i].re = (s * ar + ai) / bim;
          b_in3[i1 + b_in3.size(0) * i].im = (s * ai - ar) / bim;
        }
      }
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  st.site = const_cast<emlrtRSInfo *>(&in2);
  coder::b_abs(st, b_in3, in1);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
}

static int32_T div_s32(const emlrtStack &sp, int32_T numerator,
                       int32_T denominator)
{
  int32_T quotient;
  if (denominator == 0) {
    emlrtDivisionByZeroErrorR2012b(nullptr, (emlrtConstCTX)&sp);
  } else {
    uint32_T tempAbsQuotient;
    uint32_T u;
    if (numerator < 0) {
      tempAbsQuotient = ~static_cast<uint32_T>(numerator) + 1U;
    } else {
      tempAbsQuotient = static_cast<uint32_T>(numerator);
    }
    if (denominator < 0) {
      u = ~static_cast<uint32_T>(denominator) + 1U;
    } else {
      u = static_cast<uint32_T>(denominator);
    }
    tempAbsQuotient /= u;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -static_cast<int32_T>(tempAbsQuotient);
    } else {
      quotient = static_cast<int32_T>(tempAbsQuotient);
    }
  }
  return quotient;
}

static void firstOrderPhaseCorr(const emlrtStack &sp,
                                const coder::array<creal_T, 2U> &oldKspace,
                                real_T kappa, real_T phi,
                                coder::array<creal_T, 2U> &newKspace)
{
  coder::array<creal_T, 2U> b_phaseCorrection;
  coder::array<creal_T, 2U> fttData;
  coder::array<creal_T, 2U> phaseCorrection;
  coder::array<creal_T, 2U> r1;
  coder::array<creal_T, 2U> r2;
  coder::array<real_T, 2U> xunits;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  real_T ai;
  real_T re_tmp;
  real_T y_im;
  real_T y_re;
  real_T y_re_tmp;
  int32_T b_newKspace[2];
  int32_T b_loop_ub;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T loop_ub;
  int32_T vectorUB;
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
  //  simplexSearch
  //  -----------------------
  //  First order phase correction
  //  -----------------------
  newKspace.set_size(&eb_emlrtRTEI, &sp, oldKspace.size(0), oldKspace.size(1));
  loop_ub = oldKspace.size(0) * oldKspace.size(1);
  for (i = 0; i < loop_ub; i++) {
    newKspace[i].re = 0.0;
    newKspace[i].im = 0.0;
  }
  st.site = &r_emlrtRSI;
  if (oldKspace.size(1) == 0) {
    i = 0;
  } else {
    i = static_cast<int32_T>(
        muDoubleScalarRem(static_cast<real_T>(oldKspace.size(1)), 2.0));
  }
  if (i != 0.0) {
    //  If odd
    newKspace.set_size(&fb_emlrtRTEI, &sp, oldKspace.size(0),
                       newKspace.size(1));
    if (static_cast<real_T>(oldKspace.size(1)) + 1.0 != oldKspace.size(1) + 1) {
      emlrtIntegerCheckR2012b(static_cast<real_T>(oldKspace.size(1)) + 1.0,
                              &d_emlrtDCI, (emlrtConstCTX)&sp);
    }
    newKspace.set_size(&fb_emlrtRTEI, &sp, newKspace.size(0),
                       oldKspace.size(1) + 1);
    if (static_cast<real_T>(oldKspace.size(1)) + 1.0 != oldKspace.size(1) + 1) {
      emlrtIntegerCheckR2012b(static_cast<real_T>(oldKspace.size(1)) + 1.0,
                              &e_emlrtDCI, (emlrtConstCTX)&sp);
    }
    loop_ub = oldKspace.size(0) * (oldKspace.size(1) + 1);
    for (i = 0; i < loop_ub; i++) {
      newKspace[i].re = 0.0;
      newKspace[i].im = 0.0;
    }
  }
  if (oldKspace.size(0) < 1) {
    i = 0;
  } else {
    if (newKspace.size(0) < 1) {
      emlrtDynamicBoundsCheckR2012b(1, 1, newKspace.size(0), &c_emlrtBCI,
                                    (emlrtConstCTX)&sp);
    }
    if (oldKspace.size(0) > newKspace.size(0)) {
      emlrtDynamicBoundsCheckR2012b(oldKspace.size(0), 1, newKspace.size(0),
                                    &d_emlrtBCI, (emlrtConstCTX)&sp);
    }
    i = oldKspace.size(0);
  }
  if (oldKspace.size(1) < 1) {
    i1 = 0;
  } else {
    if (newKspace.size(1) < 1) {
      emlrtDynamicBoundsCheckR2012b(1, 1, newKspace.size(1), &e_emlrtBCI,
                                    (emlrtConstCTX)&sp);
    }
    if (oldKspace.size(1) > newKspace.size(1)) {
      emlrtDynamicBoundsCheckR2012b(oldKspace.size(1), 1, newKspace.size(1),
                                    &f_emlrtBCI, (emlrtConstCTX)&sp);
    }
    i1 = oldKspace.size(1);
  }
  b_newKspace[0] = i;
  b_newKspace[1] = i1;
  emlrtSubAssignSizeCheckR2012b(
      &b_newKspace[0], 2, ((coder::array<creal_T, 2U> *)&oldKspace)->size(), 2,
      &emlrtECI, (emlrtCTX)&sp);
  loop_ub = oldKspace.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = oldKspace.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      newKspace[i1 + newKspace.size(0) * i] =
          oldKspace[i1 + oldKspace.size(0) * i];
    }
  }
  //  Apply phase correction
  if (newKspace.size(1) < 1) {
    i = 1;
    i1 = -1;
    i2 = 1;
    vectorUB = 0;
  } else {
    i = 2;
    i1 = newKspace.size(1) - 1;
    i2 = 2;
    vectorUB = newKspace.size(1);
  }
  y_re_tmp = phi * 0.0;
  if (y_re_tmp == 0.0) {
    y_re = muDoubleScalarCos(phi);
    y_im = muDoubleScalarSin(phi);
  } else if (phi == 0.0) {
    y_re = rtNaN;
    y_im = 0.0;
  } else {
    y_re = rtNaN;
    y_im = rtNaN;
  }
  st.site = &sg_emlrtRSI;
  loop_ub = div_s32(st, i1, i);
  phaseCorrection.set_size(&gb_emlrtRTEI, &sp, newKspace.size(0), loop_ub + 1);
  for (i1 = 0; i1 <= loop_ub; i1++) {
    b_loop_ub = newKspace.size(0);
    for (i3 = 0; i3 < b_loop_ub; i3++) {
      i4 = i * i1;
      ai = newKspace[i3 + newKspace.size(0) * i4].re;
      re_tmp = newKspace[i3 + newKspace.size(0) * i4].im;
      phaseCorrection[i3 + phaseCorrection.size(0) * i1].re =
          ai * y_re - re_tmp * y_im;
      phaseCorrection[i3 + phaseCorrection.size(0) * i1].im =
          ai * y_im + re_tmp * y_re;
    }
  }
  b_newKspace[0] = newKspace.size(0);
  st.site = &sg_emlrtRSI;
  b_newKspace[1] = div_s32(st, vectorUB - 1, i2) + 1;
  emlrtSubAssignSizeCheckR2012b(&b_newKspace[0], 2, phaseCorrection.size(), 2,
                                &b_emlrtECI, (emlrtCTX)&sp);
  loop_ub = phaseCorrection.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = phaseCorrection.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      newKspace[i1 + newKspace.size(0) * (i2 * i)] =
          phaseCorrection[i1 + phaseCorrection.size(0) * i];
    }
  }
  if (newKspace.size(1) < 2) {
    i = 0;
    i1 = 1;
    i2 = -1;
    vectorUB = 1;
    i3 = 1;
    i4 = 0;
  } else {
    i = 1;
    i1 = 2;
    i2 = newKspace.size(1) - 1;
    vectorUB = 2;
    i3 = 2;
    i4 = newKspace.size(1);
  }
  if (y_re_tmp == 0.0) {
    y_re = muDoubleScalarCos(-phi);
    y_im = muDoubleScalarSin(-phi);
  } else if (-phi == 0.0) {
    y_re = rtNaN;
    y_im = 0.0;
  } else {
    y_re = rtNaN;
    y_im = rtNaN;
  }
  st.site = &rg_emlrtRSI;
  loop_ub = div_s32(st, i2 - i, i1);
  phaseCorrection.set_size(&hb_emlrtRTEI, &sp, newKspace.size(0), loop_ub + 1);
  for (i2 = 0; i2 <= loop_ub; i2++) {
    b_loop_ub = newKspace.size(0);
    for (int32_T i5{0}; i5 < b_loop_ub; i5++) {
      int32_T i6;
      i6 = i + i1 * i2;
      ai = newKspace[i5 + newKspace.size(0) * i6].re;
      re_tmp = newKspace[i5 + newKspace.size(0) * i6].im;
      phaseCorrection[i5 + phaseCorrection.size(0) * i2].re =
          ai * y_re - re_tmp * y_im;
      phaseCorrection[i5 + phaseCorrection.size(0) * i2].im =
          ai * y_im + re_tmp * y_re;
    }
  }
  b_newKspace[0] = newKspace.size(0);
  st.site = &rg_emlrtRSI;
  b_newKspace[1] = div_s32(st, i4 - vectorUB, i3) + 1;
  emlrtSubAssignSizeCheckR2012b(&b_newKspace[0], 2, phaseCorrection.size(), 2,
                                &c_emlrtECI, (emlrtCTX)&sp);
  loop_ub = phaseCorrection.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = phaseCorrection.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      newKspace[i1 + newKspace.size(0) * ((vectorUB + i3 * i) - 1)] =
          phaseCorrection[i1 + phaseCorrection.size(0) * i];
    }
  }
  //  FT to image space in readout direction, apply phase correction
  phaseCorrection.set_size(&ib_emlrtRTEI, &sp, newKspace.size(0),
                           newKspace.size(1));
  loop_ub = newKspace.size(0) * newKspace.size(1);
  for (i = 0; i < loop_ub; i++) {
    phaseCorrection[i].re = 0.0;
    phaseCorrection[i].im = 0.0;
  }
  if (newKspace.size(0) < 1) {
    xunits.set_size(&jb_emlrtRTEI, &sp, xunits.size(0), 0);
  } else {
    xunits.set_size(&jb_emlrtRTEI, &sp, 1, newKspace.size(0));
    loop_ub = newKspace.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      xunits[i] = static_cast<real_T>(i) + 1.0;
    }
  }
  xunits.set_size(&kb_emlrtRTEI, &sp, 1, xunits.size(1));
  y_re_tmp = static_cast<real_T>(newKspace.size(0)) / 2.0;
  loop_ub = xunits.size(1) - 1;
  b_loop_ub = (xunits.size(1) / 2) << 1;
  vectorUB = b_loop_ub - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    __m128d r;
    r = _mm_loadu_pd(&xunits[i]);
    _mm_storeu_pd(&xunits[i], _mm_sub_pd(_mm_sub_pd(r, _mm_set1_pd(y_re_tmp)),
                                         _mm_set1_pd(0.5)));
  }
  for (i = b_loop_ub; i <= loop_ub; i++) {
    xunits[i] = (xunits[i] - y_re_tmp) - 0.5;
  }
  //  Specify the even and odd traces
  if (phaseCorrection.size(1) < 1) {
    emlrtDynamicBoundsCheckR2012b(1, 1, phaseCorrection.size(1), &g_emlrtBCI,
                                  (emlrtConstCTX)&sp);
  }
  y_re = kappa * 0.0;
  y_im = kappa * 6.2831853071795862;
  r1.set_size(&lb_emlrtRTEI, &sp, 1, xunits.size(1));
  b_loop_ub = newKspace.size(0);
  loop_ub = xunits.size(1);
  for (i = 0; i < loop_ub; i++) {
    y_re_tmp = y_re * xunits[i];
    ai = y_im * xunits[i];
    if (ai == 0.0) {
      r1[i].re = y_re_tmp / static_cast<real_T>(b_loop_ub);
      r1[i].im = 0.0;
    } else if (y_re_tmp == 0.0) {
      r1[i].re = 0.0;
      r1[i].im = ai / static_cast<real_T>(b_loop_ub);
    } else {
      r1[i].re = rtNaN;
      r1[i].im = ai / static_cast<real_T>(b_loop_ub);
    }
  }
  st.site = &s_emlrtRSI;
  coder::b_exp(st, r1);
  emlrtSubAssignSizeCheckR2012b(phaseCorrection.size(), 1, r1.size(), 2,
                                &d_emlrtECI, (emlrtCTX)&sp);
  loop_ub = phaseCorrection.size(0);
  for (i = 0; i < loop_ub; i++) {
    phaseCorrection[i] = r1[i];
  }
  if (phaseCorrection.size(1) < 2) {
    emlrtDynamicBoundsCheckR2012b(2, 1, phaseCorrection.size(1), &h_emlrtBCI,
                                  (emlrtConstCTX)&sp);
  }
  y_re = kappa * -0.0;
  y_im = kappa * -6.2831853071795862;
  r1.set_size(&mb_emlrtRTEI, &sp, 1, xunits.size(1));
  loop_ub = xunits.size(1);
  for (i = 0; i < loop_ub; i++) {
    y_re_tmp = y_re * xunits[i];
    ai = y_im * xunits[i];
    if (ai == 0.0) {
      r1[i].re = y_re_tmp / static_cast<real_T>(b_loop_ub);
      r1[i].im = 0.0;
    } else if (y_re_tmp == 0.0) {
      r1[i].re = 0.0;
      r1[i].im = ai / static_cast<real_T>(b_loop_ub);
    } else {
      r1[i].re = rtNaN;
      r1[i].im = ai / static_cast<real_T>(b_loop_ub);
    }
  }
  st.site = &t_emlrtRSI;
  coder::b_exp(st, r1);
  emlrtSubAssignSizeCheckR2012b(phaseCorrection.size(), 1, r1.size(), 2,
                                &e_emlrtECI, (emlrtCTX)&sp);
  loop_ub = phaseCorrection.size(0);
  for (i = 0; i < loop_ub; i++) {
    phaseCorrection[i + phaseCorrection.size(0)] = r1[i];
  }
  //  Replicate them over the full matrix
  b_phaseCorrection.set_size(&nb_emlrtRTEI, &sp, phaseCorrection.size(0), 2);
  loop_ub = phaseCorrection.size(0);
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      if (i + 1 > phaseCorrection.size(1)) {
        emlrtDynamicBoundsCheckR2012b(i + 1, 1, phaseCorrection.size(1),
                                      &i_emlrtBCI, (emlrtConstCTX)&sp);
      }
      b_phaseCorrection[i1 + b_phaseCorrection.size(0) * i].re =
          phaseCorrection[i1 + phaseCorrection.size(0) * i].re;
      if (i + 1 > phaseCorrection.size(1)) {
        emlrtDynamicBoundsCheckR2012b(i + 1, 1, phaseCorrection.size(1),
                                      &i_emlrtBCI, (emlrtConstCTX)&sp);
      }
      b_phaseCorrection[i1 + b_phaseCorrection.size(0) * i].im =
          phaseCorrection[i1 + phaseCorrection.size(0) * i].im;
    }
  }
  real_T dv[2];
  dv[0] = 1.0;
  dv[1] = static_cast<real_T>(newKspace.size(1)) / 2.0;
  st.site = &u_emlrtRSI;
  coder::repmat(st, b_phaseCorrection, dv, r2);
  phaseCorrection.set_size(&ob_emlrtRTEI, &sp, r2.size(0), r2.size(1));
  b_loop_ub = r2.size(0) * r2.size(1);
  for (i = 0; i < b_loop_ub; i++) {
    phaseCorrection[i] = r2[i];
  }
  //  Apply phase correction
  st.site = &v_emlrtRSI;
  b_st.site = &v_emlrtRSI;
  coder::ifftshift(b_st, newKspace);
  if (newKspace.size(0) == 1) {
    emlrtErrorWithMessageIdR2018a(&st, &g_emlrtRTEI,
                                  "Coder:toolbox:autoDimIncompatibility",
                                  "Coder:toolbox:autoDimIncompatibility", 0);
  }
  b_st.site = &mb_emlrtRSI;
  if ((newKspace.size(0) == 0) || (newKspace.size(1) == 0)) {
    fttData.set_size(&qb_emlrtRTEI, &b_st, newKspace.size(0),
                     newKspace.size(1));
    loop_ub = newKspace.size(0) * newKspace.size(1);
    for (i = 0; i < loop_ub; i++) {
      fttData[i].re = 0.0;
      fttData[i].im = 0.0;
    }
  } else {
    c_st.site = &nb_emlrtRSI;
    d_st.site = &ob_emlrtRSI;
    e_st.site = &pb_emlrtRSI;
    f_st.site = &qb_emlrtRSI;
    emlrtFFTWSetNumThreads(4);
    fttData.set_size(&pb_emlrtRTEI, &f_st, newKspace.size(0),
                     newKspace.size(1));
    emlrtFFTW_1D_C2C((real_T *)&(newKspace.data())[0],
                     (real_T *)&(fttData.data())[0], 1, newKspace.size(0),
                     newKspace.size(0), newKspace.size(1), -1);
  }
  st.site = &v_emlrtRSI;
  b_st.site = &tb_emlrtRSI;
  coder::eml_fftshift(b_st, fttData);
  if ((fttData.size(0) != phaseCorrection.size(0)) &&
      ((fttData.size(0) != 1) && (phaseCorrection.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(fttData.size(0), phaseCorrection.size(0),
                                &f_emlrtECI, (emlrtConstCTX)&sp);
  }
  if ((fttData.size(1) != phaseCorrection.size(1)) &&
      ((fttData.size(1) != 1) && (phaseCorrection.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(fttData.size(1), phaseCorrection.size(1),
                                &g_emlrtECI, (emlrtConstCTX)&sp);
  }
  st.site = &w_emlrtRSI;
  if ((fttData.size(0) == phaseCorrection.size(0)) &&
      (fttData.size(1) == phaseCorrection.size(1))) {
    loop_ub = fttData.size(0) * fttData.size(1);
    for (i = 0; i < loop_ub; i++) {
      y_re_tmp = fttData[i].re;
      ai = phaseCorrection[i].im;
      re_tmp = fttData[i].im;
      y_re = phaseCorrection[i].re;
      fttData[i].re = y_re_tmp * y_re - re_tmp * ai;
      fttData[i].im = y_re_tmp * ai + re_tmp * y_re;
    }
  } else {
    times(st, fttData, phaseCorrection);
  }
  b_st.site = &w_emlrtRSI;
  coder::ifftshift(b_st, fttData);
  b_st.site = &ub_emlrtRSI;
  if ((fttData.size(0) == 0) || (fttData.size(1) == 0)) {
    newKspace.set_size(&rb_emlrtRTEI, &b_st, fttData.size(0), fttData.size(1));
    loop_ub = fttData.size(0) * fttData.size(1);
    for (i = 0; i < loop_ub; i++) {
      newKspace[i].re = 0.0;
      newKspace[i].im = 0.0;
    }
  } else {
    c_st.site = &nb_emlrtRSI;
    d_st.site = &ob_emlrtRSI;
    e_st.site = &pb_emlrtRSI;
    f_st.site = &qb_emlrtRSI;
    emlrtFFTWSetNumThreads(4);
    newKspace.set_size(&pb_emlrtRTEI, &f_st, fttData.size(0), fttData.size(1));
    emlrtFFTW_1D_C2C((real_T *)&(fttData.data())[0],
                     (real_T *)&(newKspace.data())[0], 1, fttData.size(0),
                     fttData.size(0), fttData.size(1), 1);
  }
  st.site = &w_emlrtRSI;
  coder::ifftshift(st, newKspace);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
}

static void times(const emlrtStack &sp, coder::array<creal_T, 2U> &in1,
                  const coder::array<creal_T, 2U> &in2)
{
  coder::array<creal_T, 2U> b_in1;
  int32_T aux_0_1;
  int32_T aux_1_1;
  int32_T b_loop_ub;
  int32_T loop_ub;
  int32_T stride_0_0;
  int32_T stride_0_1;
  int32_T stride_1_0;
  int32_T stride_1_1;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)&sp);
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }
  if (in2.size(1) == 1) {
    b_loop_ub = in1.size(1);
  } else {
    b_loop_ub = in2.size(1);
  }
  b_in1.set_size(&cc_emlrtRTEI, &sp, loop_ub, b_loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int32_T i{0}; i < b_loop_ub; i++) {
    for (int32_T i1{0}; i1 < loop_ub; i1++) {
      real_T d;
      real_T d1;
      real_T d2;
      real_T d3;
      int32_T i2;
      int32_T i3;
      i2 = i1 * stride_0_0;
      d = in1[i2 + in1.size(0) * aux_0_1].re;
      i3 = i1 * stride_1_0;
      d1 = in2[i3 + in2.size(0) * aux_1_1].im;
      d2 = in1[i2 + in1.size(0) * aux_0_1].im;
      d3 = in2[i3 + in2.size(0) * aux_1_1].re;
      b_in1[i1 + b_in1.size(0) * i].re = d * d3 - d2 * d1;
      b_in1[i1 + b_in1.size(0) * i].im = d * d1 + d2 * d3;
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  in1.set_size(&cc_emlrtRTEI, &sp, b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int32_T i{0}; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (int32_T i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
}

void applyEPIcorrection(const emlrtStack *sp,
                        const coder::array<creal_T, 2U> &kSpaceGhost,
                        real_T kCenter, real_T pCenter,
                        const coder::array<char_T, 2U> &method,
                        coder::array<creal_T, 2U> &kSpaceCorrected)
{
  static const char_T cv[3]{'s', 'v', 'd'};
  static const int8_T kernelOffsetX[9]{0, 1, 2, 0, 1, 2, 0, 1, 2};
  static const int8_T kernelOffsetY[9]{0, 0, 0, 1, 1, 1, 2, 2, 2};
  coder::anonymous_function anonFun;
  coder::array<int32_T, 2U> idxMap;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  real_T x0[2];
  int32_T dimy;
  int32_T i;
  int32_T kstr;
  int32_T siz;
  int32_T siz_idx_0;
  int32_T siz_idx_1;
  uint32_T b_kx;
  boolean_T b_bool;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  //  Apply a first order even/odd k-space line correction
  st.site = &emlrtRSI;
  x0[0] = kCenter;
  x0[1] = pCenter;
  //  -----------------------
  //  find EPI shift
  //  -----------------------
  dimy = kSpaceGhost.size(1);
  //  SVD Indices
  b_bool = false;
  if (method.size(1) == 3) {
    kstr = 0;
    int32_T exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (method[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    real_T d;
    uint32_T count;
    //  kernel size
    //  Precaculate the mapping from kspTmp to the Mat matrix
    d = ((static_cast<real_T>(kSpaceGhost.size(0)) - 3.0) + 1.0) *
        ((static_cast<real_T>(kSpaceGhost.size(1)) - 3.0) + 1.0);
    if (!(d >= 0.0)) {
      emlrtNonNegativeCheckR2012b(d, &b_emlrtDCI, &st);
    }
    if (d != static_cast<int32_T>(d)) {
      emlrtIntegerCheckR2012b(d, &emlrtDCI, &st);
    }
    idxMap.set_size(&u_emlrtRTEI, &st, static_cast<int32_T>(d), 9);
    if (d != static_cast<int32_T>(d)) {
      emlrtIntegerCheckR2012b(d, &c_emlrtDCI, &st);
    }
    kstr = static_cast<int32_T>(d) * 9;
    for (i = 0; i < kstr; i++) {
      idxMap[i] = 0;
    }
    //  These matrices define the offsets for the kernel
    count = 0U;
    i = kSpaceGhost.size(0);
    for (int32_T kx{0}; kx <= i - 3; kx++) {
      if (dimy - 3 >= 0) {
        b_kx = static_cast<uint32_T>(kx);
        siz_idx_0 = kSpaceGhost.size(0);
        siz_idx_1 = dimy;
        siz = kSpaceGhost.size(0);
      }
      for (int32_T ky{0}; ky <= dimy - 3; ky++) {
        int32_T b_varargin_1[9];
        uint32_T varargin_1[9];
        uint32_T varargin_2[9];
        boolean_T exitg2;
        count++;
        b_st.site = &c_emlrtRSI;
        for (kstr = 0; kstr < 9; kstr++) {
          varargin_1[kstr] =
              (static_cast<uint32_T>(kernelOffsetX[kstr]) + b_kx) + 1U;
          varargin_2[kstr] = (static_cast<uint32_T>(kernelOffsetY[kstr]) +
                              static_cast<uint32_T>(ky)) +
                             1U;
        }
        c_st.site = &e_emlrtRSI;
        kstr = 0;
        exitg2 = false;
        while ((!exitg2) && (kstr < 9)) {
          if (static_cast<int32_T>(varargin_1[kstr]) > siz_idx_0) {
            emlrtErrorWithMessageIdR2018a(&c_st, &emlrtRTEI,
                                          "MATLAB:sub2ind:IndexOutOfRange",
                                          "MATLAB:sub2ind:IndexOutOfRange", 0);
          } else {
            kstr++;
          }
        }
        kstr = 0;
        exitg2 = false;
        while ((!exitg2) && (kstr < 9)) {
          if (static_cast<int32_T>(varargin_2[kstr]) > siz_idx_1) {
            emlrtErrorWithMessageIdR2018a(&c_st, &emlrtRTEI,
                                          "MATLAB:sub2ind:IndexOutOfRange",
                                          "MATLAB:sub2ind:IndexOutOfRange", 0);
          } else {
            kstr++;
          }
        }
        //  JAM
        for (kstr = 0; kstr < 9; kstr++) {
          b_varargin_1[kstr] =
              static_cast<int32_T>(varargin_1[kstr]) +
              siz * (static_cast<int32_T>(varargin_2[kstr]) - 1);
        }
        if ((static_cast<int32_T>(count) < 1) ||
            (static_cast<int32_T>(count) > idxMap.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(count), 1,
                                        idxMap.size(0), &emlrtBCI, &st);
        }
        for (kstr = 0; kstr < 9; kstr++) {
          idxMap[(static_cast<int32_T>(count) + idxMap.size(0) * kstr) - 1] =
              b_varargin_1[kstr];
        }
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(&st);
        }
      }
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(&st);
      }
    }
  } else {
    idxMap.set_size(&t_emlrtRTEI, &st, 0, 9);
  }
  //  Create an anonymous function that you can use to pass parameters to the
  //  optimization function
  anonFun.workspace.kSpace.set_size(&v_emlrtRTEI, &st, kSpaceGhost.size(0),
                                    kSpaceGhost.size(1));
  kstr = kSpaceGhost.size(0) * kSpaceGhost.size(1);
  for (i = 0; i < kstr; i++) {
    anonFun.workspace.kSpace[i] = kSpaceGhost[i];
  }
  anonFun.workspace.method.set_size(&v_emlrtRTEI, &st, 1, method.size(1));
  kstr = method.size(1);
  for (i = 0; i < kstr; i++) {
    anonFun.workspace.method[i] = method[i];
  }
  anonFun.workspace.idxMap.set_size(&v_emlrtRTEI, &st, idxMap.size(0), 9);
  kstr = idxMap.size(0) * 9;
  for (i = 0; i < kstr; i++) {
    anonFun.workspace.idxMap[i] = idxMap[i];
  }
  //  Starting values
  //  Specify fitting options
  //  Begin Fitting
  b_st.site = &d_emlrtRSI;
  coder::fminsearch(b_st, anonFun, x0);
  //  JAM
  //  Save outputs
  st.site = &b_emlrtRSI;
  firstOrderPhaseCorr(st, kSpaceGhost, x0[0], x0[1], kSpaceCorrected);
  //  firstOrderPhaseCorr
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

emlrtCTX emlrtGetRootTLSGlobal()
{
  return emlrtRootTLSGlobal;
}

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData)
{
  omp_set_lock(&emlrtLockGlobal);
  emlrtCallLockeeFunction(aLockee, aTLS, aData);
  omp_unset_lock(&emlrtLockGlobal);
}

real_T findEPIshift_anonFcn1(const emlrtStack &sp,
                             const coder::array<creal_T, 2U> &kSpace,
                             const coder::array<char_T, 2U> &method,
                             const coder::array<real_T, 2U> &idxMap,
                             const real_T x[2])
{
  static const char_T cv1[9]{'e', 'n', 't', 'S', 'm', 'o', 'o', 't', 'h'};
  static const char_T cv[3]{'e', 'n', 't'};
  static const char_T cv2[3]{'s', 'v', 'd'};
  coder::array<creal_T, 2U> b_imgTmp;
  coder::array<creal_T, 2U> imgTmp;
  coder::array<creal_T, 2U> kspMod;
  coder::array<real_T, 2U> metGhOb;
  coder::array<real_T, 2U> r;
  coder::array<real_T, 2U> y;
  coder::array<real_T, 1U> b_S_data;
  coder::array<real_T, 1U> mGh;
  coder::array<boolean_T, 1U> b;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack st;
  real_T S_data[9];
  real_T varargout_1;
  int32_T exitg1;
  int32_T nxout;
  boolean_T b_bool;
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
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)&sp);
  st.site = &o_emlrtRSI;
  //  This calculates the metric that needs to be minimized
  //  The optimization parameters kappa and phi are arrayed in the parameter
  //  matrix "x"
  //  Apply these corrections
  b_st.site = &p_emlrtRSI;
  firstOrderPhaseCorr(b_st, kSpace, x[0], x[1], kspMod);
  b_st.site = &q_emlrtRSI;
  b_bool = false;
  if (method.size(1) == 3) {
    nxout = 0;
    do {
      exitg1 = 0;
      if (nxout < 3) {
        if (method[nxout] != cv[nxout]) {
          exitg1 = 1;
        } else {
          nxout++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    nxout = 0;
  } else {
    b_bool = false;
    if (method.size(1) == 9) {
      nxout = 0;
      do {
        exitg1 = 0;
        if (nxout < 9) {
          if (method[nxout] != cv1[nxout]) {
            exitg1 = 1;
          } else {
            nxout++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      nxout = 1;
    } else {
      b_bool = false;
      if (method.size(1) == 3) {
        nxout = 0;
        do {
          exitg1 = 0;
          if (nxout < 3) {
            if (method[nxout] != cv2[nxout]) {
              exitg1 = 1;
            } else {
              nxout++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
      if (b_bool) {
        nxout = 2;
      } else {
        nxout = -1;
      }
    }
  }
  switch (nxout) {
  case 0:
    //  Entropy method, from:
    //  Clare S. Iterative Nyquist ghost correction for single and
    //    multishot EPI using an entropy measure. ISMRM, 2003. p. 1041.
    c_st.site = &vb_emlrtRSI;
    d_st.site = &vb_emlrtRSI;
    coder::b_ifftshift(d_st, kspMod);
    d_st.site = &vb_emlrtRSI;
    coder::fft2(d_st, kspMod, imgTmp);
    d_st.site = &vc_emlrtRSI;
    coder::eml_fftshift(d_st, imgTmp, 1);
    d_st.site = &vc_emlrtRSI;
    coder::eml_fftshift(d_st, imgTmp, 2);
    c_st.site = &wb_emlrtRSI;
    coder::b_abs(c_st, imgTmp, r);
    c_st.site = &wb_emlrtRSI;
    coder::mat2gray(c_st, r, metGhOb);
    c_st.site = &wb_emlrtRSI;
    varargout_1 = coder::entropy(c_st, metGhOb);
    break;
  case 1:
    //  Entropy, plus smoothing
    c_st.site = &xb_emlrtRSI;
    d_st.site = &xb_emlrtRSI;
    coder::b_ifftshift(d_st, kspMod);
    d_st.site = &xb_emlrtRSI;
    coder::fft2(d_st, kspMod, imgTmp);
    d_st.site = &vc_emlrtRSI;
    coder::eml_fftshift(d_st, imgTmp, 1);
    d_st.site = &vc_emlrtRSI;
    coder::eml_fftshift(d_st, imgTmp, 2);
    c_st.site = &yb_emlrtRSI;
    coder::b_abs(c_st, imgTmp, metGhOb);
    c_st.site = &yb_emlrtRSI;
    coder::medfilt2(c_st, metGhOb);
    c_st.site = &ac_emlrtRSI;
    d_st.site = &wc_emlrtRSI;
    nxout = metGhOb.size(0) * metGhOb.size(1);
    y.set_size(&cb_emlrtRTEI, &d_st, metGhOb.size(0), metGhOb.size(1));
    e_st.site = &xc_emlrtRSI;
    if (nxout > 2147483646) {
      f_st.site = &ab_emlrtRSI;
      coder::check_forloop_overflow_error(f_st);
    }
    for (int32_T k{0}; k < nxout; k++) {
      y[k] = muDoubleScalarAbs(metGhOb[k]);
    }
    c_st.site = &ac_emlrtRSI;
    coder::mat2gray(c_st, y, r);
    c_st.site = &ac_emlrtRSI;
    varargout_1 = coder::entropy(c_st, r);
    break;
  case 2: {
    int32_T iv[2];
    int32_T iv1[2];
    int32_T i;
    int32_T k;
    int32_T k0;
    int32_T loop_ub;
    //  SVD method, from:
    //  Peterson E, Aksoy M, Maclaren J, Bammer R. Acquisition?free
    //    Nyquist ghost correction for parallel imaging accelerated EPI.
    //    ISMRM 2015. p. 75.
    //  first index of min zone
    iv[0] = (*(int32_T(*)[2])kspMod.size())[0];
    iv[1] = (*(int32_T(*)[2])kspMod.size())[1];
    iv1[0] = (*(int32_T(*)[2])((coder::array<real_T, 2U> *)&idxMap)->size())[0];
    iv1[1] = (*(int32_T(*)[2])((coder::array<real_T, 2U> *)&idxMap)->size())[1];
    c_st.site = &bc_emlrtRSI;
    coder::internal::indexShapeCheck(c_st, iv, iv1);
    k0 = kspMod.size(0) * kspMod.size(1);
    nxout = idxMap.size(0) * 9;
    for (k = 0; k < nxout; k++) {
      i = static_cast<int32_T>(idxMap[k]);
      if ((i < 1) || (i > k0)) {
        emlrtDynamicBoundsCheckR2012b(i, 1, k0, &b_emlrtBCI, &b_st);
      }
    }
    imgTmp.set_size(&db_emlrtRTEI, &b_st, idxMap.size(0), 9);
    for (k = 0; k < nxout; k++) {
      imgTmp[k] = kspMod[static_cast<int32_T>(idxMap[k]) - 1];
    }
    c_st.site = &cc_emlrtRSI;
    nxout = coder::svd(c_st, imgTmp, S_data);
    if (nxout < 2) {
      k = 0;
      i = 0;
    } else {
      k = 1;
      i = nxout;
    }
    iv[0] = 1;
    loop_ub = i - k;
    iv[1] = loop_ub;
    c_st.site = &dc_emlrtRSI;
    coder::internal::indexShapeCheck(c_st, nxout, iv);
    //          tail = S(minZone+1:end); % HACK
    c_st.site = &ec_emlrtRSI;
    d_st.site = &qe_emlrtRSI;
    e_st.site = &re_emlrtRSI;
    f_st.site = &se_emlrtRSI;
    if (loop_ub == 0) {
      varargout_1 = 0.0;
    } else {
      g_st.site = &vf_emlrtRSI;
      for (i = 0; i < loop_ub; i++) {
        S_data[i] = S_data[k + i];
      }
      b_S_data.set(&S_data[0], loop_ub);
      h_st.site = &ue_emlrtRSI;
      varargout_1 = coder::sumMatrixColumns(h_st, b_S_data, loop_ub);
    }
    //  The integral of the "tail" of the SVD vector
  } break;
  default: {
    real_T bim;
    int32_T k;
    int32_T k0;
    int32_T loop_ub;
    //  Ghost-Object method, from:
    //  McKay JA, Moeller S, Zhang L, Auerbach EJ, Nelson MT, Bolan PJ.
    //    Nyquist ghost correction of breast diffusion weighted imaging
    //    using referenceless methods. MRM 2019 Apr;81(4):2624-2631
    c_st.site = &fc_emlrtRSI;
    d_st.site = &fc_emlrtRSI;
    coder::b_ifftshift(d_st, kspMod);
    d_st.site = &fc_emlrtRSI;
    coder::fft2(d_st, kspMod, imgTmp);
    d_st.site = &vc_emlrtRSI;
    coder::eml_fftshift(d_st, imgTmp, 1);
    d_st.site = &vc_emlrtRSI;
    coder::eml_fftshift(d_st, imgTmp, 2);
    kspMod.set_size(&w_emlrtRTEI, &b_st, imgTmp.size(0), imgTmp.size(1));
    nxout = imgTmp.size(0) * imgTmp.size(1);
    for (k = 0; k < nxout; k++) {
      kspMod[k] = imgTmp[k];
    }
    real_T dv[2];
    dv[0] = 0.0;
    dv[1] = static_cast<real_T>(imgTmp.size(1)) / 2.0;
    c_st.site = &gc_emlrtRSI;
    coder::circshift(c_st, kspMod, dv);
    c_st.site = &hc_emlrtRSI;
    d_st.site = &gg_emlrtRSI;
    e_st.site = &hg_emlrtRSI;
    if (((imgTmp.size(0) != 1) && (kspMod.size(0) != 1) &&
         (imgTmp.size(0) != kspMod.size(0))) ||
        ((imgTmp.size(1) != 1) && (kspMod.size(1) != 1) &&
         (imgTmp.size(1) != kspMod.size(1)))) {
      emlrtErrorWithMessageIdR2018a(&e_st, &f_emlrtRTEI,
                                    "MATLAB:sizeDimensionsMustMatch",
                                    "MATLAB:sizeDimensionsMustMatch", 0);
    }
    if ((imgTmp.size(0) == kspMod.size(0)) &&
        (imgTmp.size(1) == kspMod.size(1))) {
      b_imgTmp.set_size(&x_emlrtRTEI, &b_st, imgTmp.size(0), imgTmp.size(1));
      for (k = 0; k < nxout; k++) {
        real_T ai;
        real_T ar;
        real_T bi;
        real_T br;
        ar = imgTmp[k].re;
        ai = imgTmp[k].im;
        br = kspMod[k].re;
        bi = kspMod[k].im;
        if (bi == 0.0) {
          if (ai == 0.0) {
            b_imgTmp[k].re = ar / br;
            b_imgTmp[k].im = 0.0;
          } else if (ar == 0.0) {
            b_imgTmp[k].re = 0.0;
            b_imgTmp[k].im = ai / br;
          } else {
            b_imgTmp[k].re = ar / br;
            b_imgTmp[k].im = ai / br;
          }
        } else if (br == 0.0) {
          if (ar == 0.0) {
            b_imgTmp[k].re = ai / bi;
            b_imgTmp[k].im = 0.0;
          } else if (ai == 0.0) {
            b_imgTmp[k].re = 0.0;
            b_imgTmp[k].im = -(ar / bi);
          } else {
            b_imgTmp[k].re = ai / bi;
            b_imgTmp[k].im = -(ar / bi);
          }
        } else {
          real_T brm;
          brm = muDoubleScalarAbs(br);
          bim = muDoubleScalarAbs(bi);
          if (brm > bim) {
            real_T s;
            s = bi / br;
            bim = br + s * bi;
            b_imgTmp[k].re = (ar + s * ai) / bim;
            b_imgTmp[k].im = (ai - s * ar) / bim;
          } else if (bim == brm) {
            real_T s;
            if (br > 0.0) {
              s = 0.5;
            } else {
              s = -0.5;
            }
            if (bi > 0.0) {
              bim = 0.5;
            } else {
              bim = -0.5;
            }
            b_imgTmp[k].re = (ar * s + ai * bim) / brm;
            b_imgTmp[k].im = (ai * s - ar * bim) / brm;
          } else {
            real_T s;
            s = br / bi;
            bim = bi + s * br;
            b_imgTmp[k].re = (s * ar + ai) / bim;
            b_imgTmp[k].im = (s * ai - ar) / bim;
          }
        }
      }
      c_st.site = &hc_emlrtRSI;
      coder::b_abs(c_st, b_imgTmp, metGhOb);
    } else {
      c_st.site = &hc_emlrtRSI;
      binary_expand_op(c_st, metGhOb, hc_emlrtRSI, imgTmp, kspMod);
    }
    //  signal/shifted signal
    c_st.site = &ic_emlrtRSI;
    coder::medfilt2(c_st, metGhOb);
    loop_ub = metGhOb.size(0) * metGhOb.size(1);
    mGh.set_size(&y_emlrtRTEI, &b_st, loop_ub);
    for (k = 0; k < loop_ub; k++) {
      mGh[k] = metGhOb[k];
    }
    b.set_size(&ab_emlrtRTEI, &b_st, loop_ub);
    for (k = 0; k < loop_ub; k++) {
      b[k] = muDoubleScalarIsNaN(metGhOb[k]);
    }
    c_st.site = &jc_emlrtRSI;
    d_st.site = &ig_emlrtRSI;
    k = b.size(0);
    while ((k >= 1) && (!b[k - 1])) {
      k--;
    }
    if (k > loop_ub) {
      emlrtErrorWithMessageIdR2018a(&d_st, &d_emlrtRTEI,
                                    "MATLAB:subsdeldimmismatch",
                                    "MATLAB:subsdeldimmismatch", 0);
    }
    d_st.site = &jg_emlrtRSI;
    e_st.site = &kg_emlrtRSI;
    nxout = 0;
    k0 = b.size(0);
    f_st.site = &mg_emlrtRSI;
    if (b.size(0) > 2147483646) {
      g_st.site = &ab_emlrtRSI;
      coder::check_forloop_overflow_error(g_st);
    }
    for (k = 0; k < k0; k++) {
      nxout += b[k];
    }
    nxout = loop_ub - nxout;
    k0 = -1;
    e_st.site = &lg_emlrtRSI;
    if (loop_ub > 2147483646) {
      f_st.site = &ab_emlrtRSI;
      coder::check_forloop_overflow_error(f_st);
    }
    for (k = 0; k < loop_ub; k++) {
      if ((k + 1 > b.size(0)) || (!b[k])) {
        k0++;
        mGh[k0] = mGh[k];
      }
    }
    if (nxout > mGh.size(0)) {
      emlrtErrorWithMessageIdR2018a(&d_st, &c_emlrtRTEI,
                                    "Coder:builtins:AssertionFailed",
                                    "Coder:builtins:AssertionFailed", 0);
    }
    if (nxout < 1) {
      nxout = 0;
    }
    mGh.set_size(&bb_emlrtRTEI, &d_st, nxout);
    c_st.site = &kc_emlrtRSI;
    d_st.site = &ng_emlrtRSI;
    e_st.site = &se_emlrtRSI;
    if (mGh.size(0) == 0) {
      bim = 0.0;
    } else {
      f_st.site = &vf_emlrtRSI;
      g_st.site = &ue_emlrtRSI;
      bim = coder::sumMatrixColumns(g_st, mGh, mGh.size(0));
    }
    varargout_1 = 1.0 / (bim / static_cast<real_T>(mGh.size(0)));
    //  Invert for minizmation problem
  } break;
  }
  //  JAM
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
  return varargout_1;
}

// End of code generation (applyEPIcorrection.cpp)
