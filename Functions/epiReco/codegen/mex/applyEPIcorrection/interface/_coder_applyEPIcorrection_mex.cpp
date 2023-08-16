//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_applyEPIcorrection_mex.cpp
//
// Code generation for function '_coder_applyEPIcorrection_mex'
//

// Include files
#include "_coder_applyEPIcorrection_mex.h"
#include "_coder_applyEPIcorrection_api.h"
#include "applyEPIcorrection.h"
#include "applyEPIcorrection_data.h"
#include "applyEPIcorrection_initialize.h"
#include "applyEPIcorrection_terminate.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <stdexcept>

void emlrtExceptionBridge();
void emlrtExceptionBridge()
{
  throw std::runtime_error("");
}
// Function Definitions
void applyEPIcorrection_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                    int32_T nrhs, const mxArray *prhs[4])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 4) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 4, 4,
                        18, "applyEPIcorrection");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 18,
                        "applyEPIcorrection");
  }
  // Call the function.
  applyEPIcorrection_api(prhs, &outputs);
  // Copy over outputs to the caller.
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexAtExit(&applyEPIcorrection_atexit);
  // Initialize the memory manager.
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&applyEPIcorrection_nestLockGlobal);
  // Module initialization.
  applyEPIcorrection_initialize();
  st.tls = emlrtRootTLSGlobal;
  try {
    // Dispatch the entry-point.
    applyEPIcorrection_mexFunction(nlhs, plhs, nrhs, prhs);
    // Module termination.
    applyEPIcorrection_terminate();
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&applyEPIcorrection_nestLockGlobal);
  } catch (...) {
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&applyEPIcorrection_nestLockGlobal);
    emlrtReportParallelRunTimeError(&st);
    emlrtCleanupOnException((emlrtCTX *)emlrtRootTLSGlobal);
    throw;
  }
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal,
                           &emlrtLockerFunction, omp_get_num_procs(),
                           (void *)&emlrtExceptionBridge, "windows-1252", true);
  return emlrtRootTLSGlobal;
}

// End of code generation (_coder_applyEPIcorrection_mex.cpp)
