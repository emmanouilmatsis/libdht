#ifndef LIBDHT_KBUCKET_H_
#define LIBDHT_KBUCKET_H_

#include <chrono>
#include <list>
#include <utility>

#include "libdht/node.hpp"

namespace libdht
{

    class KBucket
    {
        public:
            KBucket();
            KBucket(std::vector<bool> position);

            KBucket(KBucket&&) = default;
            KBucket& operator=(KBucket&&) = default;
            KBucket(const KBucket&) = default;
            KBucket& operator=(const KBucket&) = default;
            ~KBucket() = default;

            std::vector<bool> position() const;

            std::list<Node>::iterator begin();
            std::list<Node>::const_iterator begin() const;
            std::list<Node>::const_iterator cbegin() const;
            std::list<Node>::iterator end();
            std::list<Node>::const_iterator end() const;
            std::list<Node>::const_iterator cend() const;
            std::list<Node>::reverse_iterator rbegin();
            std::list<Node>::const_reverse_iterator rbegin() const;
            std::list<Node>::const_reverse_iterator crbegin() const;
            std::list<Node>::reverse_iterator rend();
            std::list<Node>::const_reverse_iterator rend() const;
            std::list<Node>::const_reverse_iterator crend() const;

            bool add(Node);
            bool contains(Node) const;
            bool covers(Node) const;
            bool full() const;
            int depth() const;

        private:
            std::vector<bool> position_;
            std::chrono::time_point<std::chrono::steady_clock> time_;
            std::list<Node> nodes_;
            std::list<Node> cache_;
    };

}

#endif // LIBDHT_KBUCKET_H_
