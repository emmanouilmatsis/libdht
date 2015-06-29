#ifndef LIBDHT_ROUTINGTABLE_H_
#define LIBDHT_ROUTINGTABLE_H_

#include <list>

#include "libdht/kbucket.hpp"

#define EXCLUDE
namespace libdht
{

    class RoutingTable
    {
        public:
            RoutingTable();

            RoutingTable(RoutingTable&&) = default;
            RoutingTable& operator=(RoutingTable&&) = default;
            RoutingTable(const RoutingTable&) = default;
            RoutingTable& operator=(const RoutingTable&) = default;
            ~RoutingTable() = default;

            std::list<KBucket>::iterator begin();
            std::list<KBucket>::const_iterator begin() const;
            std::list<KBucket>::const_iterator cbegin() const;
            std::list<KBucket>::iterator end();
            std::list<KBucket>::const_iterator end() const;
            std::list<KBucket>::const_iterator cend() const;

            bool add_contact(Node);

        private:
            void split(std::list<KBucket>::iterator); // const_iterator?

            std::list<KBucket> kbuckets_;
            Node node_;
    };

}

#endif // LIBDHT_ROUTINGTABLE_H_
