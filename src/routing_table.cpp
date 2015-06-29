#include "libdht/routing_table.hpp"

#include <iostream>

namespace libdht
{

    RoutingTable::RoutingTable()
    {
        kbuckets_.push_back(KBucket());
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

    void RoutingTable::split(std::list<KBucket>::iterator iter_kbucket)
    {
        // 1. find middle of range
        std::array<uint8_t, kIDSize> old_kbucket_max;
        std::for_each(old_kbucket_max.rbegin(), old_kbucket_max.rend(),
                [iter_min = iter_kbucket->range().first.data().rbegin(),
                iter_max = iter_kbucket->range().second.data().rbegin(),
                iter_min_end = iter_kbucket->range().first.data().rend(),
                iter_max_end = iter_kbucket->range().second.data().rend(),
                carry = static_cast<uint8_t>(0)](uint8_t &a) mutable -> void {

                    auto min = static_cast<uint8_t>((*iter_min >> 1));
                    auto max = static_cast<uint8_t>((*iter_max >> 1));

                    if (++iter_min != iter_min_end && ++iter_max != iter_max_end)
                    {
                        min |= *iter_min << 7;
                        max |= *iter_max << 7;
                    }

                    a = static_cast<uint8_t>(min + max + carry);
                    carry = static_cast<uint8_t>((min + max + carry) >> 8);
                });

        std::array<uint8_t, kIDSize> new_kbucket_min(old_kbucket_max);
        std::for_each(new_kbucket_min.rbegin(),new_kbucket_min.rend(),
                [carry = static_cast<uint8_t>(1)](uint8_t &a) mutable -> void {
                    if (carry)
                    {
                        auto temp = a + carry;

                        a = static_cast<uint8_t>(temp);
                        carry = static_cast<uint8_t>(temp >> 8);
                    }
                });

        auto old_kbucket_range = std::make_pair(ID(iter_kbucket->range().first.data()), ID(old_kbucket_max));
        auto new_kbucket_range = std::make_pair(ID(new_kbucket_min), ID(iter_kbucket->range().second.data()));;

        // 2. create new kbuckets
        auto old_kbucket = KBucket(old_kbucket_range);
        auto new_kbucket = KBucket(new_kbucket_range);

        // 3. reassign nodes to new kbuckets
        for (const auto &n : *iter_kbucket)
        {
            if (!old_kbucket.covers(n))
                old_kbucket.add(n);
            else
                new_kbucket.add(n);
        }

        // 4. insert new kbuckets
        kbuckets_.insert(iter_kbucket, old_kbucket);
        kbuckets_.insert(iter_kbucket, new_kbucket);
        kbuckets_.erase(iter_kbucket);
    }

}
