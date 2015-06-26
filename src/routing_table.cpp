#include "libdht/routing_table.hpp"

namespace libdht
{

    RoutingTable::RoutingTable()
    {
    }

    std::list<KBucket>::iterator RoutingTable::begin()
    {
        return kbuckets_.begin();
    }

    std::list<KBucket>::const_iterator RoutingTable::begin() const
    {
        return kbuckets_.cbegin();
    }

    std::list<KBucket>::const_iterator RoutingTable::cbegin() const
    {
        return kbuckets_.cbegin();
    }

    std::list<KBucket>::iterator RoutingTable::end()
    {
        return kbuckets_.end();
    }

    std::list<KBucket>::const_iterator RoutingTable::end() const
    {
        return kbuckets_.cend();
    }

    std::list<KBucket>::const_iterator RoutingTable::cend() const
    {
        return kbuckets_.cend();
    }

    bool RoutingTable::add_contact(Node node)
    {
        auto kbucket = std::find_if(kbuckets_.begin(), kbuckets_.end(),
                [node=node](const KBucket &a) -> bool {
                    return a.covers(node);
                });

        if (kbucket->add(node))
            return true;

        if (kbucket->covers(node_) || kbucket->depth() % kb != 0)
        {
            split(kbucket); // TODO: split bucket
            return add_contact(node);
        }
        else
        {
            // TODO: push node at the fron of cache
            // TODO: ping front node of kbucket
        }

        return false;
    }

    bool RoutingTable::split(std::list<KBucket>::iterator kbucket)
    {
        // 1. find middle new range
        auto min = kbucket->range().first.data();
        std::for_each(min.begin(), min.end(),
                [carry = static_cast<uint8_t>(0)](uint8_t &a) mutable -> void {
		    uint8_t next_carry = (a & 0x01) << 8;
                    a = (a >> 1) | carry;
                    carry  = next_carry;
                });

        auto max = kbucket->range().second.data();
        std::for_each(max.begin(), max.end(),
		 [carry = static_cast<uint8_t>(0)](uint8_t &a) mutable -> void {
		    uint8_t next_carry = (a & 0x01) << 8;
                    a = (a >> 1) | carry;
                    carry = next_carry;
                });

        std::array<uint8_t, kIDSize> sum;
        std::for_each(sum.rbegin(), sum.rend(),
                [carry = static_cast<uint8_t>(0), it_min=min.rbegin(), it_max=max.rbegin()](uint8_t &a) mutable -> void {
                    uint16_t temp_sum = *it_min++ + *it_max++ + carry;
                    carry = static_cast<uint8_t>(temp_sum >> 8) & 0x01;
                    a = static_cast<uint8_t>(temp_sum);
                });


        // 2. create new kbucket
        // 3. insert new kbucket
        // 4. update new kbucket
        // 5. update old kbucket

        return true;
    }

}
