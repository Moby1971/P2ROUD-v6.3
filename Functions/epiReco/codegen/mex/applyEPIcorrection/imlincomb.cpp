//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// imlincomb.cpp
//
// Code generation for function 'imlincomb'
//

// Include files
#include "imlincomb.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"

// Variable Definitions
static emlrtBCInfo j_emlrtBCI{
    -1,                    // iFirst
    -1,                    // iLast
    199,                   // lineNo
    55,                    // colNo
    "",                    // aName
    "lincombPortableCode", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imlincomb.m", // pName
    0 // checkKind
};

static emlrtBCInfo k_emlrtBCI{
    -1,                    // iFirst
    -1,                    // iLast
    204,                   // lineNo
    11,                    // colNo
    "",                    // aName
    "lincombPortableCode", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imlincomb.m", // pName
    0 // checkKind
};

static emlrtRTEInfo wb_emlrtRTEI{
    190,         // lineNo
    20,          // colNo
    "imlincomb", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2023a\\toolbox\\images\\images\\eml\\imlincomb.m" // pName
};

// Function Definitions
namespace coder {
void lincombPortableCode(const emlrtStack &sp, real_T varargin_1,
                         const ::coder::array<real_T, 2U> &varargin_2,
                         real_T varargin_3, ::coder::array<real_T, 2U> &Z)
{
  emlrtStack st;
  real_T val;
  int32_T i;
  int32_T k;
  int32_T lincombPortableCode_numThreads;
  int32_T ub_loop;
  int32_T ub_loop_tmp;
  boolean_T emlrtHadParallelError{false};
  Z.set_size(&wb_emlrtRTEI, &sp, varargin_2.size(0), varargin_2.size(1));
  ub_loop_tmp = varargin_2.size(0) * varargin_2.size(1);
  ub_loop = ub_loop_tmp - 1;
  emlrtEnterParallelRegion((emlrtCTX)&sp,
                           static_cast<boolean_T>(omp_in_parallel()));
  lincombPortableCode_numThreads =
      emlrtAllocRegionTLSs(sp.tls, static_cast<boolean_T>(omp_in_parallel()),
                           omp_get_max_threads(), omp_get_num_procs());
#pragma omp parallel num_threads(lincombPortableCode_numThreads) private(      \
    val, st, i) firstprivate(ub_loop_tmp, emlrtHadParallelError)
  {
    try {

      st.prev = &sp;
      st.tls = emlrtAllocTLS((emlrtCTX)&sp, omp_get_thread_num());
      st.site = nullptr;
    } catch (...) {
      emlrtHadParallelError = true;
    }
#pragma omp for nowait
    for (k = 0; k <= ub_loop; k++) {
      if (emlrtHadParallelError) {
        continue;
      }
      try {

        if ((k + 1 < 1) || (k + 1 > ub_loop_tmp)) {
          emlrtDynamicBoundsCheckR2012b(k + 1, 1, ub_loop_tmp, &j_emlrtBCI,
                                        &st);
        }
        val = varargin_1 * varargin_2[k] + varargin_3;
        i = Z.size(0) * Z.size(1);
        if ((static_cast<int32_T>(static_cast<uint32_T>(k) + 1U) < 1) ||
            (static_cast<int32_T>(static_cast<uint32_T>(k) + 1U) > i)) {
          emlrtDynamicBoundsCheckR2012b(
              static_cast<int32_T>(static_cast<uint32_T>(k) + 1U), 1, i,
              &k_emlrtBCI, &st);
        }
        Z[k] = val;
      } catch (...) {
        emlrtHadParallelError = true;
      }
    }
  }
  emlrtExitParallelRegion((emlrtCTX)&sp,
                          static_cast<boolean_T>(omp_in_parallel()));
}

} // namespace coder

// End of code generation (imlincomb.cpp)
