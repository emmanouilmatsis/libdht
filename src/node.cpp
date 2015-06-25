#include "libdht/node.hpp"

namespace libdht
{

    Node::Node()
    {
    }

    Node::Node(ID id) : id_(id)
    {
    }

    ID Node::id() const
    {
        return id_;
    }


}
