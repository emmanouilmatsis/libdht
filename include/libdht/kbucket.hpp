#ifndef LIBDHT_KBUCKET_H_
#define LIBDHT_KBUCKET_H_

#include <chrono>
#include <list>
#include <memory>
#include <utility>

#include "libdht/node.hpp"

namespace libdht
{

    class KBucket
    {
        public:
            KBucket();
            KBucket(std::pair<ID, ID> range);

            KBucket(KBucket&&) = default;
            KBucket& operator=(KBucket&&) = default;
            KBucket(const KBucket&) = default;
            KBucket& operator=(const KBucket&) = default;
            ~KBucket() = default;

            std::list<Node>::iterator begin();
            std::list<Node>::const_iterator begin() const;
            std::list<Node>::const_iterator cbegin() const;
            std::list<Node>::iterator end();
            std::list<Node>::const_iterator end() const;
            std::list<Node>::const_iterator cend() const;

            bool add(Node);
            bool remove(Node);
            Node random() const;
            bool contains(Node) const;
            bool covers(Node) const;
            bool full() const;
            int depth() const;

        private:
            std::pair<ID, ID> range_;
            std::chrono::time_point<std::chrono::steady_clock> time_;
            std::list<Node> nodes_;
            std::list<Node> cache_;
    };

}

#endif // LIBDHT_KBUCKET_H_
