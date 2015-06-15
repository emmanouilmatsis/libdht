#ifndef LIBDHT_ID_H_
#define LIBDHT_ID_H_

#include <algorithm>
#include <array>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

#include "libdht/constants.hpp"
#include "libdht/sha1.hpp"

namespace libdht
{

    class ID
    {
        public:
            ID();
            ID(const std::string &);

            ID(ID&&) = default;
            ID& operator=(ID&&) = default;
            ID(const ID&) = default;
            ID& operator=(const ID&) = default;
            ~ID() = default;

            const std::array<uint8_t, libdht::HASH_LENGTH> data() const;
            friend std::ostream& operator<<(std::ostream&, const ID&);

        private:
            std::array<uint8_t, libdht::HASH_LENGTH> data_;
    };

}

#endif // LIBDHT_ID_H_
