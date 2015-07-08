#ifndef LIBDHT_PROTOCOL_H_
#define LIBDHT_PROTOCOL_H_

#include "libdht/constants.hpp"

namespace libdht
{

    class Protocol
    {
        public:
            Protocol();

            Protocol(Protocol&&) = default;
            Protocol& operator=(Protocol&&) = default;
            Protocol(const Protocol&) = default;
            Protocol& operator=(const Protocol&) = default;
            ~Protocol() = default;

        private:
    };

}

#endif // LIBDHT_PROTOCOL_H_
