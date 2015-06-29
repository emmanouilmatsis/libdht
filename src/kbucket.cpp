#include "libdht/kbucket.hpp"

namespace libdht
{

    KBucket::KBucket()
    {
        std::array<uint8_t, libdht::kIDSize> min;
        min.fill(0);

        std::array<uint8_t, libdht::kIDSize> max;
        max.fill(255);

        range_ = std::make_pair(ID(min), ID(max));
    }

    KBucket::KBucket(std::pair<ID, ID> range) : range_(range)
    {
    }

    std::pair<ID, ID> KBucket::range() const
    {
        return range_;
    }

    std::list<Node>::iterator KBucket::begin()
    {
        return nodes_.begin();
    }

    std::list<Node>::const_iterator KBucket::begin() const
    {
        return nodes_.cbegin();
    }

    std::list<Node>::const_iterator KBucket::cbegin() const
    {
        return nodes_.cbegin();
    }

    std::list<Node>::iterator KBucket::end()
    {
        return nodes_.end();
    }

    std::list<Node>::const_iterator KBucket::end() const
    {
        return nodes_.cend();
    }

    std::list<Node>::const_iterator KBucket::cend() const
    {
        return nodes_.cend();
    }

    bool KBucket::add(Node node)
    {
        if (contains(node))
        {
            nodes_.splice(nodes_.cend(), nodes_,
                    std::find_if(nodes_.cbegin(), nodes_.cend(),
                        [node=node](const Node &a) -> bool {
                            return a.id() == node.id(); // TODO: compare address and port
                        })
                    );
        }
        else if (!full())
        {
            nodes_.push_back(node);
        }
        else
        {
            return false;
        }
        return true;
    }

    bool KBucket::remove(Node node)
    {
        return true;
    }

    Node KBucket::random() const
    {
        return Node();
    }

    bool KBucket::contains(Node node) const
    {
        return std::find_if(nodes_.cbegin(), nodes_.cend(),
                [node=node](const Node &a) -> bool {
                    return a.id() == node.id(); // TODO: compare address and port
                }) != nodes_.cend();
    }

    bool KBucket::full() const
    {
        return nodes_.size() >= kK;
    }

    bool KBucket::covers(Node node) const
    {
        return range_.first <= node.id() && node.id() <= range_.second;
    }

    int KBucket::depth() const
    {
        if (nodes_.empty()) return 0;

        int depth = kK * 8;

        for (auto it = nodes_.begin(); std::next(it) != nodes_.cend(); it++)
            depth = std::min(depth, it->id().prefix(std::next(it)->id()));

        return depth;
    }

}
