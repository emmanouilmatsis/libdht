#include "libdht/id.hpp"

namespace libdht
{

    ID::ID()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<uint8_t> uniform_dist;

        std::transform(data_.begin(), data_.end(), data_.begin(),
                [mt, uniform_dist] (const uint8_t &a) mutable -> uint8_t {
                    return uniform_dist(mt);
                });
    }

    ID::ID(const std::string& str)
    {
        auto hash = libdht::sha1(str);

        std::transform(data_.begin(), data_.end(), data_.begin(),
                [it = hash.begin()](const uint &a) mutable -> uint8_t {
                    return static_cast<uint8_t>(std::stoul(std::string{*it++, *it++}, nullptr, 16));
                });
    }

    const std::array<uint8_t, libdht::kIDSize> ID::data() const
    {
        return data_;
    }

    unsigned int ID::prefix(const ID& obj)
    {
        auto pair = std::mismatch(data_.cbegin(), data_.cend(), obj.data_.cbegin(), obj.data_.cend());

        auto position = std::distance(data_.cbegin(), pair.first) * 8;

        if (pair.first != data_.cend() && pair.second != obj.data_.cend())
        {
            auto x = *pair.first ^ *pair.second;

            while((x & 0x80) == 0)
            {
                ++position;
                x <<= 1;
            }
        }

        return static_cast<unsigned int>(position);
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
            return static_cast<int>(*pair.first) < static_cast<int>(*pair.second);
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
            os << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(element);
        os << std::dec;

        return os;
    }

}
