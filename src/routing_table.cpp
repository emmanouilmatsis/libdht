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
            split(kbucket);
            return add_contact(node);
        }
        else
        {
            // TODO: push node at the front of cache
            // TODO: ping front node of kbucket
        }

        return false;
    }

    void RoutingTable::split(std::list<KBucket>::iterator iter_kbucket)
    {
        auto min = iter_kbucket->range().first;
        auto max = iter_kbucket->range().second;

        // 1. find middle of range
        ID min_a(min);
        ID max_a;
        std::for_each(max_a.rbegin(), max_a.rend(),
                [iter_min = min.crbegin(),
                iter_min_crend = min.crend(),
                iter_max = max.crbegin(),
                iter_max_crend = max.crend(),
                carry = static_cast<uint8_t>(0)]
                (uint8_t &a) mutable -> void {

                    auto min = static_cast<uint8_t>((*iter_min >> 1));
                    auto max = static_cast<uint8_t>((*iter_max >> 1));

                    if (++iter_min != iter_min_crend && ++iter_max != iter_max_crend)
                    {
                        min |= *iter_min << 7;
                        max |= *iter_max << 7;
                    }

                    a = min + max + carry;
                    carry = (min + max + carry) >> 8;
                });

        ID min_b(max_a);
        ID max_b(max);
        std::for_each(min_b.rbegin(), min_b.rend(),
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
        auto kbucket_a = KBucket(std::make_pair(min_a, max_a));
        auto kbucket_b = KBucket(std::make_pair(min_b, max_b));

        auto range_a = kbucket_a.range();
        auto range_b = kbucket_b.range();
        std::cout << "a[" << range_a.first << ", " << range_a.second << "]: " << std::endl;
        std::cout << "b[" << range_b.first << ", " << range_b.second << "]: " << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;

        // 3. reassign nodes to new kbuckets
        for (const auto &n : *iter_kbucket)
        {
            if (kbucket_a.covers(n))
            {
                std::cout << "a[" << range_a.first << ", " << range_a.second << "]: " << n.id() << std::endl;
                kbucket_a.add(n);
            }
            else
            {
                std::cout << "b[" << range_b.first << ", " << range_b.second << "]: " << n.id() << std::endl;
                kbucket_b.add(n);
            }
        }
        std::cout << std::endl;

        // 4. insert new kbuckets
        kbuckets_.insert(iter_kbucket, kbucket_a);
        kbuckets_.insert(iter_kbucket, kbucket_b);
        kbuckets_.erase(iter_kbucket);
    }

}
