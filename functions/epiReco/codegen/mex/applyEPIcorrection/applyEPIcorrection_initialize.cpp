//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// applyEPIcorrection_initialize.cpp
//
// Code generation for function 'applyEPIcorrection_initialize'
//

// Include files
#include "applyEPIcorrection_initialize.h"
#include "_coder_applyEPIcorrection_mex.h"
#include "applyEPIcorrection_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static void applyEPIcorrection_once();

// Function Definitions
static void applyEPIcorrection_once()
{
  mex_InitInfAndNan();
}

void applyEPIcorrection_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2022b(&st);
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtLicenseCheckR2022a(&st, "EMLRT:runTime:MexFunctionNeedsLicense",
                          "image_toolbox", 2);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    applyEPIcorrection_once();
  }
}

// End of code generation (applyEPIcorrection_initialize.cpp)
