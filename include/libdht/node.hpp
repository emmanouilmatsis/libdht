#ifndef LIBDHT_NODE_H_
#define LIBDHT_NODE_H_

#include <string>

#include "libdht/id.hpp"

namespace libdht
{

    class Node
    {
        public:
            Node();
            Node(ID id, std::string address, int port);

            Node(Node&&) = default;
            Node& operator=(Node&&) = default;
            Node(const Node&) = default;
            Node& operator=(const Node&) = default;
            ~Node() = default;

            ID id() const;
            std::string address() const;
            int port() const;

        private:
            ID id_;
            std::string address_;
            int port_;
    };

}

#endif // LIBDHT_NODE_H_
