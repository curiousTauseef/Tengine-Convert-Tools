#include "operator/logical.hpp"
#include "operator/logical_param.hpp"
#include "static_graph.hpp"
#include <cmath>

namespace TEngine {

bool Logical::InferShape(const std::vector<TShape>& ishape, std::vector<TShape>& oshape, int layout)
{
    if (ishape.size() == 1)
    {
        oshape = ishape;
        return true;
    }

    if (ishape.size() != 2)
    {
        return false;
    }

    int i0_size = ishape[0].GetSize();
    int i1_size = ishape[1].GetSize();

    if (i0_size >= i1_size)
    {
        oshape[0] = ishape[0];
    }
    else if (i0_size < i1_size)
    {
        oshape[0] = ishape[1];
    }

    return true;
}

void Logical::SetSchema(void)
{
    Input({"input:float32"}).Output({"output:float32"}).SetAttr("type", 0).SetDoc(R"DOC(Logical Layer)DOC");
}

}    // namespace TEngine