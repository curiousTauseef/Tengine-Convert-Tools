/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2019, Open AI Lab
 * Author: bzhang@openailab.com
 */
#include "operator/psroipooling.hpp"
#include <math.h>

namespace TEngine {
bool Psroipooling::InferShape(const std::vector<TEngine::TShape>& ishape, std::vector<TEngine::TShape>& oshape,
                              int layout)
{
    const TShape& input = ishape[0];

    int c = param_.output_dim;

    TShape shape;
    // to do : the first dimension should be num_roi
    std::vector<int> dim = {input.GetN(), c, param_.pooled_h, param_.pooled_w};

    // printf("%d %d %d %d \n", input.GetN(), c, param_.pooled_h, param_.pooled_w);
    shape.SetDim(dim);
    shape.SetDataLayout(input.GetDataLayout());

    oshape[0] = shape;

    return true;
}

void Psroipooling::SetSchema(void)
{
    Input({"input:float32"})
        .Output({"output:float32"})
        .SetAttr("spatial_scale", 1.f)
        .SetAttr("output_dim", 1)

        .SetDoc(R"DOC(Psroipooling Layer)DOC");
}

}    // namespace TEngine
