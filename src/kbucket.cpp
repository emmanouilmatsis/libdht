#include "libdht/kbucket.hpp"

namespace libdht
{

    bool KBucket::add(Node node)
    {
        if (contains(node))
            nodes_.splice(nodes_.end(), nodes_,
                    std::find_if(nodes_.begin(), nodes_.end(),
                        [node=node](const Node &a) -> bool {
                            return a.id() == node.id(); // TODO: compare address and port
                        })
                    );

        else if (!full())
            nodes_.push_back(node);
        else
            return false;
        return true;
    }

    bool KBucket::contains(Node node)
    {
        return std::find_if(nodes_.begin(), nodes_.end(),
                [node=node](const Node &a) -> bool {
                    return a.id() == node.id(); // TODO: compare address and port
                }) != nodes_.end();
    }

    bool KBucket::full()
    {
        return nodes_.size() >= kK;
    }

    bool KBucket::covers(Node node)
    {
        return range_.first <= node.id() && node.id() <= range_.second;
    }

    int KBucket::depth()
    {
        if (nodes_.empty()) return 0;

        int depth = kK * 8;

        for (auto it = nodes_.begin(); std::next(it) != nodes_.end(); it++)
            depth = std::min(depth, it->id().prefix(std::next(it)->id()));

        return depth;
    }

}
