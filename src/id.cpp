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

    const std::array<uint8_t, libdht::HASH_LENGTH> ID::data() const
    {
        return data_;
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
