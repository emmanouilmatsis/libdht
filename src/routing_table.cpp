#include "libdht/routing_table.hpp"

#include <iostream>

#define EXCLUDE

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

    std::list<KBucket>::reverse_iterator RoutingTable::rbegin()
    {
        return kbuckets_.rbegin();
    }

    std::list<KBucket>::const_reverse_iterator RoutingTable::rbegin() const
    {
        return kbuckets_.crbegin();
    }

    std::list<KBucket>::const_reverse_iterator RoutingTable::crbegin() const
    {
        return kbuckets_.crbegin();
    }

    std::list<KBucket>::reverse_iterator RoutingTable::rend()
    {
        return kbuckets_.rend();
    }

    std::list<KBucket>::const_reverse_iterator RoutingTable::rend() const
    {
        return kbuckets_.crend();
    }

    std::list<KBucket>::const_reverse_iterator RoutingTable::crend() const
    {
        return kbuckets_.crend();
    }


#ifndef EXCLUDE
    bool RoutingTable::covers(std::list<KBucket>::iterator iter_kbucket)
    {
        return iter_kbucket->position <= node.id
            && std::next(iter_kbucket)->position > node.id
            || std::next(iter_kbucket) == kbuckets_.end();
    }
#endif

    bool RoutingTable::add_contact(Node node) // TODO
    {
        auto iter_kbucket = std::find_if(kbuckets_.begin(), kbuckets_.end(),
                [node=node](const KBucket &a) -> bool {
                    return a.covers(node);
                });

        if (iter_kbucket->add(node))
            return true;

        if (iter_kbucket->covers(node_) || iter_kbucket->depth() % kb != 0)
        {
            split(iter_kbucket);
            return add_contact(node);
        }
        else
        {
            // TODO: push node at the front of cache
            // TODO: ping front node of kbucket
        }

        return false;
    }

    void RoutingTable::split(std::list<KBucket>::iterator iter_old_kbucket) // TODO
    {

#ifndef EXCLUDE
        auto old_range = iter_old_kbucket->range();
        auto old_min = old_range.first;
        auto old_max = old_range.second;

        // 1. find middle of range
        ID new_left_min(old_min);
        ID new_left_max;
        std::for_each(new_left_max.rbegin(), new_left_max.rend(),
                [iter_old_min = old_min.crbegin(),
                iter_old_min_crend = old_min.crend(),
                iter_old_max = old_max.crbegin(),
                iter_old_max_crend = old_max.crend(),
                carry = static_cast<uint8_t>(0)]
                (uint8_t &a) mutable -> void {

                    auto byte_min = static_cast<uint8_t>((*iter_old_min >> 1));
                    auto byte_max = static_cast<uint8_t>((*iter_old_max >> 1));

                    if (++iter_old_min != iter_old_min_crend && ++iter_old_max != iter_old_max_crend)
                    {
                        byte_min |= *iter_old_min << 7;
                        byte_max |= *iter_old_max << 7;
                    }

                    a = byte_min + byte_max + carry;
                    carry = (byte_min + byte_max + carry) >> 8;
                });

        ID new_right_min(new_left_max);
        ID new_right_max(old_max);
        std::for_each(new_right_min.rbegin(), new_right_min.rend(),
                [carry = static_cast<uint8_t>(1)]
                (uint8_t &a) mutable -> void {
                    if (carry)
                    {
                        auto temp = a + carry;

                        a = static_cast<uint8_t>(temp);
                        carry = static_cast<uint8_t>(temp >> 8);
                    }
                });

        // 2. create new kbuckets
        auto new_left_kbucket = KBucket(std::make_pair(new_left_min, new_left_max));
        auto new_right_kbucket = KBucket(std::make_pair(new_right_min, new_right_max));

        // 3. reassign nodes to new kbuckets
        for (const auto &n : *iter_old_kbucket)
        {
            if (new_left_kbucket.covers(n))
                new_left_kbucket.add(n);
            else
                new_right_kbucket.add(n);
        }

        // 4. insert new kbuckets
        kbuckets_.insert(iter_old_kbucket, new_left_kbucket);
        kbuckets_.insert(iter_old_kbucket, new_right_kbucket);
        kbuckets_.erase(iter_old_kbucket);
#endif
    }

}
