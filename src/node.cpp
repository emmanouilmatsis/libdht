#include "libdht/node.hpp"

namespace libdht
{

    Node::Node() : id_(), address_(kAddress), port_(kPort)
    {
    }

    Node::Node(ID id, std::string address, int port) : id_(id), address_(address), port_(port)
    {
    }

    ID Node::id() const
    {
        return id_;
    }

    std::string Node::address() const
    {
        return address_;
    }

    int Node::port() const
    {
        return port_;
    }

}
