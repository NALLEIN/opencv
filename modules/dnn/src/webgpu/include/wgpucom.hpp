// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Copyright (C) 2020, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.

#ifndef OPENCV_DNN_WEBGPU_HPP
#define OPENCV_DNN_WEBGPU_HPP

#include <vector>

namespace cv { namespace dnn { namespace webgpu {
#ifdef HAVE_WEBGPU

enum Format
{
    wFormatInvalid = -1,
    wFormatFp16,
    wFormatFp32,
    wFormatFp64,
    wFormatInt32,
    wFormatNum
};

enum OpType
{
    wOpTypeConv,
    wOpTypePool,
    wOpTypeDWConv,
    wOpTypeLRN,
    wOpTypeConcat,
    wOpTypeSoftmax,
    wOpTypeReLU,
    wOpTypePriorBox,
    wOpTypePermute,
    wOpTypeNum
};

enum PaddingMode
{
    wPaddingModeSame,
    wPaddingModeValid,
    wPaddingModeCaffe,
    wPaddingModeNum
};

enum FusedActivationType
{
    wNone,
    wRelu,
    wRelu1,
    wRelu6,
    wActivationNum
};

typedef std::vector<int> Shape;
bool isAvailable();
#endif  // HAVE_WEBGPU

}}} //namespace cv::dnn::webgpu

#include "buffer.hpp"
#include "tensor.hpp"
#include "op_base.hpp"
#include "op_concat.hpp"
#include "op_conv.hpp"
#include "op_lrn.hpp"
#include "op_softmax.hpp"
#include "op_relu.hpp"
#include "op_pool.hpp"
#include "op_prior_box.hpp"
#include "op_permute.hpp"

#endif//    OPENCV_DNN_WEBGPU_HPP