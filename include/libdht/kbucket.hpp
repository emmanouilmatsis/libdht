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
            KBucket(int min, int max);

            KBucket(KBucket&&) = default;
            KBucket& operator=(KBucket&&) = default;
            KBucket(const KBucket&) = default;
            KBucket& operator=(const KBucket&) = default;
            ~KBucket() = default;

            bool add(std::shared_ptr<libdht::Node> node);
            bool remove(std::shared_ptr<libdht::Node> node);
            std::shared_ptr<libdht::Node> random();
            int depth();
            bool has(std::shared_ptr<libdht::Node> node);

        private:
            int min_;
            int max_;
            std::chrono::time_point<std::chrono::steady_clock> time_;
            std::list<KBucket> nodes_;
            std::list<KBucket> cache_;
    };

}

#endif // LIBDHT_KBUCKET_H_
