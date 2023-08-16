//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// applyEPIcorrection_data.cpp
//
// Code generation for function 'applyEPIcorrection_data'
//

// Include files
#include "applyEPIcorrection_data.h"
#include "rt_nonfinite.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

const volatile char_T *emlrtBreakCheckR2012bFlagVar{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131642U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "applyEPIcorrection",                                 // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {3334497894U, 1318968193U, 3466680636U, 2802620837U}, // fSigWrd
    nullptr                                               // fSigMem
};

emlrtRSInfo ab_emlrtRSI{
    20,                               // lineNo
    "eml_int_forloop_overflow_check", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\eml\\eml_int_forloop_"
    "overflow_check.m" // pathName
};

emlrtRSInfo
    nb_emlrtRSI{
        31,    // lineNo
        "fft", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
        "fft\\fft.m" // pathName
    };

emlrtRSInfo
    ob_emlrtRSI{
        58,                // lineNo
        "executeCallback", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
        "fft\\fft.m" // pathName
    };

emlrtRSInfo pb_emlrtRSI{
    44,                        // lineNo
    "Custom1DFFTCallback/fft", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\Custom1DFFTCallback.m" // pathName
};

emlrtRSInfo qb_emlrtRSI{
    54,                            // lineNo
    "Custom1DFFTCallback/fftLoop", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\Custom1DFFTCallback.m" // pathName
};

emlrtRSInfo
    wc_emlrtRSI{
        18,    // lineNo
        "abs", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\elfun\\abs.m" // pathName
    };

emlrtRSInfo xc_emlrtRSI{
    74,                    // lineNo
    "applyScalarFunction", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\applyScalarFunction.m" // pathName
};

emlrtRSInfo qe_emlrtRSI{
    20,    // lineNo
    "sum", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\sum.m" // pathName
};

emlrtRSInfo re_emlrtRSI{
    99,        // lineNo
    "sumprod", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumpro"
    "d.m" // pathName
};

emlrtRSInfo se_emlrtRSI{
    74,                      // lineNo
    "combineVectorElements", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\combin"
    "eVectorElements.m" // pathName
};

emlrtRSInfo ue_emlrtRSI{
    22,                    // lineNo
    "sumMatrixIncludeNaN", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMat"
    "rixIncludeNaN.m" // pathName
};

emlrtRSInfo ve_emlrtRSI{
    42,                 // lineNo
    "sumMatrixColumns", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMat"
    "rixIncludeNaN.m" // pathName
};

omp_lock_t emlrtLockGlobal;

omp_nest_lock_t applyEPIcorrection_nestLockGlobal;

emlrtRTEInfo cb_emlrtRTEI{
    30,                    // lineNo
    21,                    // colNo
    "applyScalarFunction", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\applyScalarFunction.m" // pName
};

emlrtRTEInfo pb_emlrtRTEI{
    26,                   // lineNo
    40,                   // colNo
    "MATLABFFTWCallback", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "fft\\MATLABFFTWCallback.m" // pName
};

// End of code generation (applyEPIcorrection_data.cpp)
