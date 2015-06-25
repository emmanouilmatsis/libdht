#ifndef LIBDHT_NODE_H_
#define LIBDHT_NODE_H_

#include <sys/socket.h>

#include "libdht/id.hpp"

namespace libdht
{

    class Node
    {
        public:
            Node();
            Node(ID id); // TODO: addr and port

            Node(Node&&) = default;
            Node& operator=(Node&&) = default;
            Node(const Node&) = default;
            Node& operator=(const Node&) = default;
            ~Node() = default;

            ID id() const;

        private:
            ID id_;
            //sockaddr_storage ss; // TODO: seperate addr and port to correct type
    };

}

#endif // LIBDHT_NODE_H_
