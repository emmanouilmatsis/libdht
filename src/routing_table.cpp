#include "libdht/routing_table.hpp"

namespace libdht
{

    bool RoutingTable::add()
    {
        auto kbucket = find(node);

        // FIXME: make sure that kbucket.add() will always return true after spliting
        // or in other words than new kbucket won't be full.
        // SECTION 2.4 SAIS THE OPOSITE!
        if (kbucket.contains(node) or !(kbucket.depth() % b))
            split(kbucket);

        return kbucket.add(node); // false because new kbucket could be full so cache node
    }

    bool RoutingTable::split(kbucket)
    {
        // 1. find middle new range
        // 2. create new kbucket
        // 3. insert new kbucket
        // 4. update new kbucket
        // 5. update old kbucket

        auto middle = kbucket.range.second - (kbucket.range.

        kbuckets.insert(std::next(kbucket), KBucket(std::pair<unsigned int, unsigned int>(,)));

        return true;
    }

}
