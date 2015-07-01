#include "libdht/id.hpp"

namespace libdht
{

    ID::ID()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::bernoulli_distribution d;

        for (int i = 0; i < kIDSize; i++)
            data[i] = d(gen);
    }

    ID::ID(std::string str)
    {
        auto hash = sha1(str); // 160 bits
        auto hash_size = hash.size() * 4; // in bits

        std::bitset<4> nibble;

        for (int i = 0; i < std::min(kIDSize, hash_size); i++)
        {
            if (!(i % 4))
            {
                nibble = std::bitset<4>(std::stoul(std::string(hash.back()), nulptr, 16));
                hash.pop_back();
            }

            data_[i] = nibble[i % 4];
        }

        /*
        for (int i = 0; i < kIDSize; i++)
        {
            if (!(i % 4))
            {
                if (hash.empty())
                    break;

                nibble = std::bitset<4>(std::stoul(std::string(hash.back()), nulptr, 16));
                hash.pop_back();
            }

            data_[i] = nibble[i % 4];
        }
        */
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
        auto pair = std::mismatch(lhs.data_.cbegin(), lhs.data_.cend(), rhs.data_.cbegin(), rhs.data_.cend());

        if (pair.first != lhs.data_.cend() && pair.second != rhs.data_.cend())
            return false;
        return true;
    }

    bool operator!=(const ID& lhs, const ID& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const ID& lhs, const ID& rhs)
    {
        auto pair = std::mismatch(lhs.data_.cbegin(), lhs.data_.cend(), rhs.data_.cbegin(), rhs.data_.cend());

        if (pair.first != lhs.data_.cend() && pair.second != rhs.data_.cend())
            return *pair.first < *pair.second;
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
        for (const auto& element : obj.data_)
            os << std::setfill('0') << std::setw(2) << static_cast<int>(element);
        os << std::dec;

        return os;
    }

    int ID::prefix(const ID& obj) const
    {
        auto pair = std::mismatch(data_.cbegin(), data_.cend(), obj.data_.cbegin(), obj.data_.cend());

        auto position = static_cast<int>(std::distance(data_.cbegin(), pair.first)) * 8;

        if (pair.first != data_.cend() && pair.second != obj.data_.cend())
        {
            auto x = *pair.first ^ *pair.second;

            while((x & 0x80) == 0)
            {
                ++position;
                x <<= 1;
            }
        }

        return position;
    }

}
