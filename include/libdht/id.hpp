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
            ID(std::string);
            ID(std::array<uint8_t, kIDSize> data);

            ID(ID&&) = default;
            ID& operator=(ID&&) = default;
            ID(const ID&) = default;
            ID& operator=(const ID&) = default;
            ~ID() = default;

            std::array<uint8_t, kIDSize> data() const;

            friend bool operator==(const ID& lhs, const ID& rhs);
            friend bool operator!=(const ID& lhs, const ID& rhs);
            friend bool operator<(const ID& lhs, const ID& rhs);
            friend bool operator>(const ID& lhs, const ID& rhs);
            friend bool operator<=(const ID& lhs, const ID& rhs);
            friend bool operator>=(const ID& lhs, const ID& rhs);
            friend std::ostream& operator<<(std::ostream&, const ID&);

            int prefix(const ID&) const;

        private:
            std::array<uint8_t, kIDSize> data_;
    };

}

#endif // LIBDHT_ID_H_
