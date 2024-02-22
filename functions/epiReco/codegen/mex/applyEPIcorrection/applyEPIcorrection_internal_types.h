//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// applyEPIcorrection_internal_types.h
//
// Code generation for function 'applyEPIcorrection'
//

#pragma once

// Include files
#include "applyEPIcorrection_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include "emlrt.h"

// Type Definitions
struct struct_T {
  coder::array<creal_T, 2U> kSpace;
  coder::array<char_T, 2U> method;
  coder::array<real_T, 2U> idxMap;
};

struct rtDesignRangeCheckInfo {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
};

struct rtRunTimeErrorInfo {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
};

// End of code generation (applyEPIcorrection_internal_types.h)
