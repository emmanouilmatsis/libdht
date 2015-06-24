#include "libdht/routing_table.hpp"

#ifndef EXCLUDE

namespace libdht
{

    RoutingTable::RoutingTable()
    {
    }

    bool RoutingTable::add_contact(Node node)
    {
        auto kbucket = std::find_if(kbuckets_.begin(), kbuckets_.end(),
                [node=node](const KBucket &a) -> bool{
                    return a.covers(node);
                });

        if (kbucket->add(node))
            return true;

        if (kbucket->covers(node_) || kbucket->depth() % kb != 0)
        {
            //split(kbucket); // TODO
            return add_contact(node);
        }

        return false;
    }

    bool RoutingTable::split()
    {
        // 1. find middle new range
        // 2. create new kbucket
        // 3. insert new kbucket
        // 4. update new kbucket
        // 5. update old kbucket

        return true;
    }

}

#endif
