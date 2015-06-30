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

            std::array<uint8_t, kIDSize>::iterator begin();
            std::array<uint8_t, kIDSize>::const_iterator begin() const;
            std::array<uint8_t, kIDSize>::const_iterator cbegin() const;
            std::array<uint8_t, kIDSize>::iterator end();
            std::array<uint8_t, kIDSize>::const_iterator end() const;
            std::array<uint8_t, kIDSize>::const_iterator cend() const;
            std::array<uint8_t, kIDSize>::reverse_iterator rbegin();
            std::array<uint8_t, kIDSize>::const_reverse_iterator rbegin() const;
            std::array<uint8_t, kIDSize>::const_reverse_iterator crbegin() const;
            std::array<uint8_t, kIDSize>::reverse_iterator rend();
            std::array<uint8_t, kIDSize>::const_reverse_iterator rend() const;
            std::array<uint8_t, kIDSize>::const_reverse_iterator crend() const;

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
