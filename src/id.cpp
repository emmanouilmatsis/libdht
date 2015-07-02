#include "libdht/id.hpp"

namespace libdht
{

    ID::ID()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::bernoulli_distribution d;

        for (int i = 0; i < kIDSize; i++)
            data_[i] = d(gen);
    }

    ID::ID(std::string str)
    {
        auto hash = sha1(str); // 160 bits

        std::bitset<4> nibble;

        for (int i = 0; i < std::min(kIDSize, hash.size() * 4); i++)
        {
            if (!(i % 4))
            {
                nibble = std::bitset<4>(std::stoul(std::string(hash.back()), nulptr, 16));
                std::rotate(hash.rbegin(), hash.rbegin() + 1, hash.rend());
            }

            data_[i] = nibble[i % 4];
        }
    }

    ID::ID(std::bitset<kIDSize> data) : data_(data)
    {
    }

    std::array<uint8_t, kIDSize> ID::data() const
    {
        return data_;
    }

    bool operator==(const ID& lhs, const ID& rhs)
    {
        return lhs.data_ == rhs.data_;
    }

    bool operator!=(const ID& lhs, const ID& rhs)
    {
        return lhs.data_ != rhs.data_;
    }

    bool operator<(const ID& lhs, const ID& rhs)
    {
        for (int i = kIDSize-1; i >= 0; i--)
        {
            if (lhs.data_[i] && !rhs.data_[i]) return false;
            if (!lhs.data_[i] && rhs.data_[i]) return true;
        }

        return false;
    }

    bool operator>(const ID& lhs, const ID& rhs)
    {
        return rhs < lhs;
    }

    bool operator<=(const ID& lhs, const ID& rhs)
    {
        return !(lhs > rhs);
    }

    bool operator>=(const ID& lhs, const ID& rhs)
    {
        return !(lhs < rhs);
    }

    std::ostream& operator<<(std::ostream& os, const ID& obj)
    {
        os << std::hex;
        for (int i = kIDSize-1; i >= 0; i--)
            os << std::setfill('0') << std::setw(2) << static_cast<int>(data_[i]);
        os << std::dec;

        return os;
    }

    int ID::prefix(const ID& obj) const
    {
        auto x = data_ ^ obj.data();

        auto pos = 0;

        while (!x.test(kIDSize - 1))
        {
            x <<= 1;
            ++pos;
        }

        return pos;
    }

}
