#pragma once

#include <vector>

namespace ds
{
template<class T>
class ListTree
{
    template <class U> friend class BinaryTreeSolution;
    struct ChildNode
    {
        int index;
        ChildNode* next;

        explicit ChildNode(const int idx) : index(idx), next(nullptr) {}
    };
    struct Node
    {
        T data;
        ChildNode* firstChild;

        explicit Node(const T& data) : data(data), firstChild(nullptr) {}
    };

    std::vector<Node> nodes;
public:
    explicit ListTree(int count) : nodes() { nodes.reserve(count); }
    ~ListTree()
    {
        for (auto &node : nodes)
        {
            ChildNode* curChildNode = node.firstChild;
            while (curChildNode != nullptr)
            {
                const ChildNode* toDelete = curChildNode;
                curChildNode = curChildNode->next;
                delete toDelete;
            }
        }
    }

    void addNode(const T& data)
    {
        nodes.emplace_back(data);
    }

    void addChild(int parentIdx, int childIdx)
    {
        if (parentIdx < 0 || parentIdx >= static_cast<int>(nodes.size())) return;
        auto* newChildNode = new ChildNode(childIdx);
        if (nodes[parentIdx].firstChild == nullptr)
        {
            nodes[parentIdx].firstChild = newChildNode;
        }
        else
        {
            ChildNode* curChildNode = nodes[parentIdx].firstChild;
            while (curChildNode->next != nullptr) curChildNode = curChildNode->next;
            curChildNode->next = newChildNode;
        }
    }

    [[nodiscard]] static int getRootIndex() { return 0; }

    [[nodiscard]] int size() const { return static_cast<int>(nodes.size()); }

    T getData(int idx) const { return nodes[idx].data; }

    ChildNode* getFirstChild(int idx) const { return nodes[idx].firstChild; }
};
}