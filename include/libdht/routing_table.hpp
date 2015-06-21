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

        private:
    };

}

#endif // LIBDHT_ROUTINGTABLE_H_
