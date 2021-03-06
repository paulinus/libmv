// Copyright (c) 2009 libmv authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#ifndef LIBMV_MULTIVIEW_HOMOGRAPHY_KERNEL_H_
#define LIBMV_MULTIVIEW_HOMOGRAPHY_KERNEL_H_

#include "libmv/base/vector.h"
#include "libmv/multiview/conditioning.h"
#include "libmv/multiview/homography_error.h"
#include "libmv/multiview/two_view_kernel.h"
#include "libmv/numeric/numeric.h"

namespace libmv {
namespace homography {
namespace homography2D {
namespace kernel {

struct FourPointSolver {
  enum { MINIMUM_SAMPLES = 4 };
  /**
   * Computes the homography that transforms x to y with the direct linear
   * transform (DLT).
   *
   * \param x  A 2xN matrix of column vectors.
   * \param y  A 2xN matrix of column vectors.
   * \param Hs A vector into which the computed homography is stored.
   *
   * The estimated homography should approximatelly hold the condition y = H x.
   *
   * \see HomographyFromCorrespondencesLinearRobust
   */
  // TODO(keir): Fix \see above.
  static void Solve(const Mat &x, const Mat &y, vector<Mat3> *Hs);
};

typedef two_view::kernel::Kernel<FourPointSolver, AsymmetricError, Mat3>
  UnnormalizedKernel;

//! Isotopic normalized solver
typedef two_view::kernel::Kernel<
    two_view::kernel::IsotropicNormalizedSolver<FourPointSolver, UnnormalizerI>,
    AsymmetricError,
    Mat3>
  IsotropicNormalizedKernel;

// By default use the normalized version for increased robustness.
typedef two_view::kernel::Kernel<
    two_view::kernel::NormalizedSolver<FourPointSolver, UnnormalizerI>,
    AsymmetricError,
    Mat3>
  Kernel;

}  // namespace kernel
}  // namespace homography2D
}  // namespace homography
}  // namespace libmv

#endif  // LIBMV_MULTIVIEW_HOMOGRAPHY_H_
