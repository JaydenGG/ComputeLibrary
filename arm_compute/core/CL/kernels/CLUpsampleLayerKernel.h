/*
 * Copyright (c) 2018 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __ARM_COMPUTE_CLUPSAMPLELAYERKERNEL_H__
#define __ARM_COMPUTE_CLUPSAMPLELAYERKERNEL_H__

#include "arm_compute/core/CL/ICLKernel.h"

namespace arm_compute
{
class ICLTensor;

/** Interface for the UpsampleLayer kernel on OpenCL. */
class CLUpsampleLayerKernel : public ICLKernel
{
public:
    /** Constructor */
    CLUpsampleLayerKernel();
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    CLUpsampleLayerKernel(const CLUpsampleLayerKernel &) = delete;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    CLUpsampleLayerKernel &operator=(const CLUpsampleLayerKernel &) = delete;
    /** Default Move Constructor. */
    CLUpsampleLayerKernel(CLUpsampleLayerKernel &&) = default;
    /** Default move assignment operator */
    CLUpsampleLayerKernel &operator=(CLUpsampleLayerKernel &&) = default;
    /** Default destructor */
    ~CLUpsampleLayerKernel() = default;

    /** Initialise the kernel's input and output.
     *
     * @param[in]  input             Source tensor. Data types supported: U8/S8/QASYMM8/U16/S16/F16/U32/S32/F32.
     * @param[out] output            Destination tensor. Data types supported: same as @p input.
     * @param[in]  info              Contains stride information described in @ref Size2D.
     * @param[in]  upsampling_policy Defines the policy to fill the intermediate pixels.
     */
    void configure(const ICLTensor *input, ICLTensor *output, const Size2D &info, const InterpolationPolicy upsampling_policy);
    /** Static function to check if given info will lead to a valid configuration of @ref CLUpsampleLayerKernel
     *
     * @param[in] input             Source tensor info. Data types supported: U8/S8/QASYMM8/U16/S16/F16/U32/S32/F32.
     * @param[in] output            Destination tensor info. Data types supported: same as @p input.
     * @param[in] info              Contains  stride information described in @ref Size2D.
     * @param[in] upsampling_policy Defines the policy to fill the intermediate pixels.
     *
     * @return a status
     */
    static Status validate(const ITensorInfo *input, const ITensorInfo *output, const Size2D &info, const InterpolationPolicy upsampling_policy);

    // Inherited methods overridden:
    void run(const Window &window, cl::CommandQueue &queue) override;

private:
    const ICLTensor *_input;
    ICLTensor       *_output;
    Size2D           _info;
    unsigned int     _num_elems_processed_per_iteration_input_x;
};
} // namespace arm_compute
#endif /*__ARM_COMPUTE_CLUPSAMPLELAYERKERNEL_H__ */
