#pragma once

#include <vector>

namespace ds
{
template<class T>
/// <summary>
/// 一般树的双亲-孩子链表（邻接表）表示法。
/// </summary>
class ListTree
{
    template <class U> friend class TreeSolution;
    /// <summary>
    /// 孩子链表节点，记录孩子索引及后继指针。
    /// </summary>
    struct ChildNode
    {
        /// <summary>
        /// 孩子节点在 nodes 中的索引。
        /// </summary>
        int index;
        /// <summary>
        /// 指向下一个孩子链表节点的指针。
        /// </summary>
        ChildNode* next;

        /// <summary>
        /// 使用孩子索引初始化孩子链表节点。
        /// </summary>
        /// <param name="idx">孩子节点索引。</param>
        explicit ChildNode(const int idx) : index(idx), next(nullptr) {}
    };
    /// <summary>
    /// 树节点，包含数据域与孩子链表头指针。
    /// </summary>
    struct Node
    {
        /// <summary>
        /// 当前节点存储的数据值。
        /// </summary>
        T data;
        /// <summary>
        /// 指向第一个孩子链表节点的指针。
        /// </summary>
        ChildNode* firstChild;

        /// <summary>
        /// 使用给定数据初始化树节点。
        /// </summary>
        /// <param name="data">节点数据值。</param>
        explicit Node(const T& data) : data(data), firstChild(nullptr) {}
    };

    std::vector<Node> nodes;
public:
    /// <summary>
    /// 构造指定容量预留的空树容器。
    /// </summary>
    /// <param name="count">预留的节点数量。</param>
    explicit ListTree(int count) : nodes() { nodes.reserve(count); }
    /// <summary>
    /// 析构函数，释放所有孩子链表动态节点。
    /// </summary>
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

    /// <summary>
    /// 追加一个新树节点。
    /// </summary>
    /// <param name="data">新节点的数据值。</param>
    void addNode(const T& data)
    {
        nodes.emplace_back(data);
    }

    /// <summary>
    /// 为指定父节点追加一个孩子索引。
    /// </summary>
    /// <param name="parentIdx">父节点索引。</param>
    /// <param name="childIdx">孩子节点索引。</param>
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

    /// <summary>
    /// 返回根节点索引。
    /// </summary>
    /// <returns>根节点索引，固定为 0。</returns>
    [[nodiscard]] static int getRootIndex() { return 0; }

    /// <summary>
    /// 返回当前树节点数量。
    /// </summary>
    /// <returns>节点总数。</returns>
    [[nodiscard]] int size() const { return static_cast<int>(nodes.size()); }

    /// <summary>
    /// 按索引获取节点数据。
    /// </summary>
    /// <param name="idx">节点索引。</param>
    /// <returns>对应节点的数据值。</returns>
    T getData(int idx) const { return nodes[idx].data; }

    /// <summary>
    /// 按索引获取节点的第一个孩子链表节点。
    /// </summary>
    /// <param name="idx">节点索引。</param>
    /// <returns>第一个孩子链表节点指针；无孩子时为 nullptr。</returns>
    ChildNode* getFirstChild(int idx) const { return nodes[idx].firstChild; }
};
}
