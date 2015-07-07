#include "libdht/kbucket.hpp"

namespace libdht
{

    KBucket::KBucket() : time_(std::chrono::steady_clock::now())
    {
    }

    KBucket::KBucket(std::vector<bool> position) : position_(position), time_(std::chrono::steady_clock::now())
    {
    }

    std::vector<bool> KBucket::position() const
    {
        return position_;
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
                        [b=node](const Node &a) -> bool {
                            return a.id() == b.id(); // TODO: compare address and port
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

    bool KBucket::contains(Node node) const
    {
        return std::find_if(nodes_.cbegin(), nodes_.cend(),
                [b=node](const Node &a) -> bool {
                    return a.id() == b.id(); // TODO: compare address and port
                }) != nodes_.cend();
    }

    bool KBucket::covers(Node node) const
    {
        auto data = node.id().data();

        for (int i = 0; i < position_.size(); i++)
        {
            if (position_[i] != data[data.size() - 1 - i])
                return false;
        }

        return true;
    }

    bool KBucket::full() const
    {
        return nodes_.size() >= kK;
    }

    int KBucket::depth() const
    {
        return position_.size();
    }

}
