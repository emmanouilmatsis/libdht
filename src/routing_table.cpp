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
        auto iter_kbucket = std::find_if(kbuckets_.begin(), kbuckets_.end(),
                [node=node](const KBucket &a) -> bool {
                    return a.covers(node);
                });

        if (iter_kbucket->add(node))
            return true;

        if (iter_kbucket->covers(node_) || iter_kbucket->depth() % kb)
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

    void RoutingTable::split(std::list<KBucket>::iterator iter_old_kbucket)
    {
        auto new_left_position = iter_old_kbucket->position();
        new_left_position.push_back(1);
        auto new_left_kbucket = KBucket(new_left_position);

        auto new_right_position = iter_old_kbucket->position();
        new_right_position.push_back(0);
        auto new_right_kbucket = KBucket(new_right_position);

        for (const auto &n : *iter_old_kbucket)
        {
            if (new_left_kbucket.covers(n))
                new_left_kbucket.add(n);
            else
                new_right_kbucket.add(n);
        }

        kbuckets_.insert(iter_old_kbucket, new_left_kbucket);
        kbuckets_.insert(iter_old_kbucket, new_right_kbucket);

        kbuckets_.erase(iter_old_kbucket);
    }

}
