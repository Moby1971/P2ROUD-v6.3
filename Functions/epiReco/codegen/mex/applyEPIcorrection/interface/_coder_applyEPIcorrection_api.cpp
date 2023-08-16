//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_applyEPIcorrection_api.cpp
//
// Code generation for function '_coder_applyEPIcorrection_api'
//

// Include files
#include "_coder_applyEPIcorrection_api.h"
#include "applyEPIcorrection.h"
#include "applyEPIcorrection_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Declarations
static void b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<creal_T, 2U> &ret);

static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static void b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<char_T, 2U> &ret);

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *kSpaceGhost,
                             const char_T *identifier,
                             coder::array<creal_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<creal_T, 2U> &y);

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *kCenter,
                               const char_T *identifier);

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *method,
                             const char_T *identifier,
                             coder::array<char_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<char_T, 2U> &y);

static const mxArray *emlrt_marshallOut(const emlrtStack &sp,
                                        const coder::array<creal_T, 2U> &u);

// Function Definitions
static void b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<creal_T, 2U> &ret)
{
  static const int32_T dims[2]{-1, -1};
  int32_T iv[2];
  boolean_T bv[2]{true, true};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", true, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret.set_size(static_cast<emlrtRTEInfo *>(nullptr), &sp, iv[0], iv[1]);
  emlrtImportArrayR2015b((emlrtConstCTX)&sp, src, &ret[0], 8, true);
  emlrtDestroyArray(&src);
}

static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<real_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

static void b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<char_T, 2U> &ret)
{
  static const int32_T dims[2]{1, -1};
  int32_T iv[2];
  boolean_T bv[2]{false, true};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "char", false, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret.set_size(static_cast<emlrtRTEInfo *>(nullptr), &sp, iv[0], iv[1]);
  emlrtImportArrayR2015b((emlrtConstCTX)&sp, src, &ret[0], 1, false);
  emlrtDestroyArray(&src);
}

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *kSpaceGhost,
                             const char_T *identifier,
                             coder::array<creal_T, 2U> &y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(kSpaceGhost), &thisId, y);
  emlrtDestroyArray(&kSpaceGhost);
}

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<creal_T, 2U> &y)
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *kCenter,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(kCenter), &thisId);
  emlrtDestroyArray(&kCenter);
  return y;
}

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = b_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *method,
                             const char_T *identifier,
                             coder::array<char_T, 2U> &y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(method), &thisId, y);
  emlrtDestroyArray(&method);
}

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<char_T, 2U> &y)
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *emlrt_marshallOut(const emlrtStack &sp,
                                        const coder::array<creal_T, 2U> &u)
{
  const mxArray *m;
  const mxArray *y;
  int32_T iv[2];
  y = nullptr;
  iv[0] = u.size(0);
  iv[1] = u.size(1);
  m = emlrtCreateNumericArray(2, &iv[0], mxDOUBLE_CLASS, mxCOMPLEX);
  emlrtExportNumericArrayR2013b((emlrtConstCTX)&sp, m, &u[0], 8);
  emlrtAssign(&y, m);
  return y;
}

void applyEPIcorrection_api(const mxArray *const prhs[4], const mxArray **plhs)
{
  coder::array<creal_T, 2U> kSpaceCorrected;
  coder::array<creal_T, 2U> kSpaceGhost;
  coder::array<char_T, 2U> method;
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T kCenter;
  real_T pCenter;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  // Marshall function inputs
  emlrt_marshallIn(st, emlrtAliasP(prhs[0]), "kSpaceGhost", kSpaceGhost);
  kCenter = emlrt_marshallIn(st, emlrtAliasP(prhs[1]), "kCenter");
  pCenter = emlrt_marshallIn(st, emlrtAliasP(prhs[2]), "pCenter");
  emlrt_marshallIn(st, emlrtAliasP(prhs[3]), "method", method);
  // Invoke the target function
  applyEPIcorrection(&st, kSpaceGhost, kCenter, pCenter, method,
                     kSpaceCorrected);
  // Marshall function outputs
  *plhs = emlrt_marshallOut(st, kSpaceCorrected);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

// End of code generation (_coder_applyEPIcorrection_api.cpp)
