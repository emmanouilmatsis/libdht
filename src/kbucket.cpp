#include "libdht/kbucket.hpp"

namespace libdht
{

    KBucket::KBucket() // TODO
    {
        // prefix default constructor all zero
        // TODO: time_
    }

    KBucket::KBucket(std::bitset<kIDSize> prefix) : prefix_(prefix) // TODO
    {
        // TODO: time_
    }

    std::bitset<kIDSize> KBucket::prefix() const
    {
        return prefix_;
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

    std::list<Node>::reverse_iterator KBucket::rbegin()
    {
        return nodes_.rbegin();
    }

    std::list<Node>::const_reverse_iterator KBucket::rbegin() const
    {
        return nodes_.crbegin();
    }

    std::list<Node>::const_reverse_iterator KBucket::crbegin() const
    {
        return nodes_.crbegin();
    }

    std::list<Node>::reverse_iterator KBucket::rend()
    {
        return nodes_.rend();
    }

    std::list<Node>::const_reverse_iterator KBucket::rend() const
    {
        return nodes_.crend();
    }

    std::list<Node>::const_reverse_iterator KBucket::crend() const
    {
        return nodes_.crend();
    }

    bool KBucket::add(Node node)
    {
        if (contains(node))
        {
            nodes_.splice(nodes_.cend(), nodes_,
                    std::find_if(nodes_.cbegin(), nodes_.cend(),
                        [b=node](const Node &a) -> bool { // TODO: compare address and port
                            return a.id() == b.id();
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

    bool KBucket::remove(Node node) // TODO
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
                [b=node](const Node &a) -> bool {
                    return a.id() == b.id(); // TODO: compare address and port
                }) != nodes_.cend();
    }

    bool KBucket::full() const
    {
        return nodes_.size() >= kK;
    }

    bool KBucket::covers(Node node) const // TODO
    {
        return true;
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
