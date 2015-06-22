#ifndef LIBDHT_ROUTINGTABLE_H_
#define LIBDHT_ROUTINGTABLE_H_

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

            std::list<libdht::KBucket>::iterator begin();
            std::list<libdht::KBucket>::const_iterator begin() const;
            std::list<libdht::KBucket>::const_iterator cbegin() const;
            std::list<libdht::KBucket>::iterator end();
            std::list<libdht::KBucket>::const_iterator end() const;
            std::list<libdht::KBucket>::const_iterator cend() const;

            // return std::find(data_.begin(), data_.end(), [](){});
            bool add(); // if contains own id or kbucket.depth % b then split bucket and kbucket.add() else kbucket.add()
            std::list<libdht::KBucket>::iterator find(const Node &);
            std::list<libdht::KBucket>::const_iterator find(const Node &) const;
            bool split(std::list<libdht::KBucket>::iterator &kbucket); // const_iterator

        private:
            std::list<KBucket> kbuckets_;
    };

}

#endif // LIBDHT_ROUTINGTABLE_H_
