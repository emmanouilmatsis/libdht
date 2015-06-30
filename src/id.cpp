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

    ID::ID(std::string str)
    {
        auto hash = sha1(str);

        std::transform(data_.begin(), data_.end(), data_.begin(),
                [it = hash.begin()](const uint &a) mutable -> uint8_t {
                    return static_cast<uint8_t>(std::stoul(std::string{*it++, *it++}, nullptr, 16));
                });
    }

    ID::ID(std::array<uint8_t, kIDSize> data) : data_(data)
    {
    }

    std::array<uint8_t, kIDSize>::iterator ID::begin()
    {
        return data_.begin();
    }

    std::array<uint8_t, kIDSize>::const_iterator ID::begin() const
    {
        return data_.cbegin();
    }

    std::array<uint8_t, kIDSize>::const_iterator ID::cbegin() const
    {
        return data_.cbegin();
    }

    std::array<uint8_t, kIDSize>::iterator ID::end()
    {
        return data_.end();
    }

    std::array<uint8_t, kIDSize>::const_iterator ID::end() const
    {
        return data_.cend();
    }

    std::array<uint8_t, kIDSize>::const_iterator ID::cend() const
    {
        return data_.cend();
    }

    std::array<uint8_t, kIDSize>::reverse_iterator ID::rbegin()
    {
        return data_.rbegin();
    }

    std::array<uint8_t, kIDSize>::const_reverse_iterator ID::rbegin() const
    {
        return data_.crbegin();
    }

    std::array<uint8_t, kIDSize>::const_reverse_iterator ID::crbegin() const
    {
        return data_.crbegin();
    }

    std::array<uint8_t, kIDSize>::reverse_iterator ID::rend()
    {
        return data_.rend();
    }

    std::array<uint8_t, kIDSize>::const_reverse_iterator ID::rend() const
    {
        return data_.crend();
    }

    std::array<uint8_t, kIDSize>::const_reverse_iterator ID::crend() const
    {
        return data_.crend();
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
