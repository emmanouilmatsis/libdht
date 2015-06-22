#ifndef LIBDHT_KBUCKET_H_
#define LIBDHT_KBUCKET_H_

#include <chrono>
#include <list>
#include <memory>

#include "libdht/node.hpp"

namespace libdht
{

    class KBucket
    {
        public:
            KBucket();
            KBucket(std::pair<unsigned int> range); // range_(std::move(range))

            KBucket(KBucket&&) = default;
            KBucket& operator=(KBucket&&) = default;
            KBucket(const KBucket&) = default;
            KBucket& operator=(const KBucket&) = default;
            ~KBucket() = default;

            std::list<libdht::Node>::iterator begin();
            std::list<libdht::Node>::const_iterator begin() const;
            std::list<libdht::Node>::const_iterator cbegin() const;
            std::list<libdht::Node>::iterator end();
            std::list<libdht::Node>::const_iterator end() const;
            std::list<libdht::Node>::const_iterator cend() const;

            bool add(std::shared_ptr<libdht::Node> node);
            bool remove(std::shared_ptr<libdht::Node> node);
            bool contains(std::shared_ptr<libdht::Node> node);
            bool in_range(std::shared_ptr<libdht::Node> node);
            std::shared_ptr<libdht::Node> pop();
            std::shared_ptr<libdht::Node> random();
            unsigned int depth(); // length of prefix shared by all nodes

        private:
            std::pair<unsigned int, unsigned int> range_;
            std::chrono::time_point<std::chrono::steady_clock> time_;
            std::list<std::shared_ptr<Node>> nodes_;
            std::list<std::shared_ptr<Node>> cache_;
    };

}

#endif // LIBDHT_KBUCKET_H_
