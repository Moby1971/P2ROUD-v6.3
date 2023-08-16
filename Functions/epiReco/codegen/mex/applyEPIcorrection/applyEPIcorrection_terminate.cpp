//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// applyEPIcorrection_terminate.cpp
//
// Code generation for function 'applyEPIcorrection_terminate'
//

// Include files
#include "applyEPIcorrection_terminate.h"
#include "_coder_applyEPIcorrection_mex.h"
#include "applyEPIcorrection_data.h"
#include "rt_nonfinite.h"

// Function Definitions
void applyEPIcorrection_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void applyEPIcorrection_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (applyEPIcorrection_terminate.cpp)
