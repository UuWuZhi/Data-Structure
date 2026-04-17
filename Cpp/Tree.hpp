#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#include "ListTree.hpp"

namespace ds
{
template<class T>
/// <summary>
/// 一般树的孩子-兄弟表示法。
/// </summary>
class Tree
{
    template <class U> friend class TreeSolution;
    /// <summary>
    /// 孩子-兄弟存储结构使用的内部节点定义。
    /// </summary>
    struct Node
    {
        /// <summary>
        /// 当前节点存储的数据值。
        /// </summary>
        T data;
        /// <summary>
        /// 指向第一个孩子节点的指针。
        /// </summary>
        Node* child;
        /// <summary>
        /// 指向下一个兄弟节点的指针。
        /// </summary>
        Node* sibling;

        /// <summary>
        /// 使用给定数据初始化节点。
        /// </summary>
        /// <param name="data">节点数据值。</param>
        explicit Node(const T& data) : data(data), child(nullptr), sibling(nullptr) {}
    };

    Node* root;

    /// <summary>
    /// 递归释放孩子链与兄弟链上的所有节点。
    /// </summary>
    /// <param name="rootNode">当前待清理的节点。</param>
    void clear(Node* rootNode)
    {
        if (rootNode == nullptr) return;
        clear(rootNode->child);
        clear(rootNode->sibling);
        delete rootNode;
    }

    /// <summary>
    /// 查找数据等于目标值的第一个节点。
    /// </summary>
    /// <param name="node">当前遍历起始节点。</param>
    /// <param name="data">目标值。</param>
    /// <returns>匹配到的节点指针；未找到则返回 nullptr。</returns>
    Node* findNode(Node* node, const T& data) const
    {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        Node* foundNode = findNode(node->child, data);
        if (foundNode != nullptr) return foundNode;
        return findNode(node->sibling, data);
    }

    /// <summary>
    /// 对孩子-兄弟结构执行递归先序遍历。
    /// </summary>
    /// <param name="rootNode">遍历起始节点。</param>
    void preOrder(Node* rootNode)
    {
        if (rootNode == nullptr) return;
        std::cout << rootNode->data << ' ';
        preOrder(rootNode->child);
        preOrder(rootNode->sibling);
    }

    /// <summary>
    /// 根据层序节点值与节点度数构建树。
    /// </summary>
    /// <param name="nodeData">按层序排列的节点值。</param>
    /// <param name="degrees">层序下每个节点对应的孩子数量。</param>
    /// <returns>构建后的根节点指针。</returns>
    Node* buildLevel(const std::vector<T>& nodeData, const std::vector<int>& degrees)
    {
        if (nodeData.empty() || degrees.empty()) return nullptr;
        if (nodeData.size() != degrees.size()) return nullptr;
        clear(root);
        root = new Node(nodeData[0]);
        if (nodeData.size() == 1) return root;

        std::queue<std::pair<Node*, size_t>> q;
        q.push({root, 0});
        size_t nextIdx = 1;

        while (!q.empty() && nextIdx < nodeData.size())
        {
            auto [parent, parentIdx] = q.front();
            q.pop();
            int childCount = degrees[parentIdx];
            Node* prevChild = nullptr;

            for (size_t i = 0; i < childCount && nextIdx < nodeData.size(); ++i)
            {
                Node* child = new Node(nodeData[nextIdx]);
                if (prevChild == nullptr)
                {
                    parent->child = child;
                } else
                {
                    prevChild->sibling = child;
                }
                prevChild = child;
                q.push({child, nextIdx});
                nextIdx++;
            }
        }
        return root;
    }
public:
    /// <summary>
    /// 禁用拷贝构造。
    /// </summary>
    Tree(const Tree&) = delete;
    /// <summary>
    /// 禁用拷贝赋值。
    /// </summary>
    Tree& operator=(const Tree&) = delete;
    /// <summary>
    /// 构造空树。
    /// </summary>
    Tree() : root(nullptr) {}
    /// <summary>
    /// 使用已有根节点指针构造树。
    /// </summary>
    /// <param name="rootNode">根节点指针。</param>
    explicit Tree(Node* rootNode) : root(rootNode) {}
    /// <summary>
    /// 析构树并释放所有节点。
    /// </summary>
    ~Tree() {clear(root); root = nullptr;}
    /// <summary>
    /// 移动构造函数。
    /// </summary>
    /// <param name="other">源树对象。</param>
    Tree(Tree&& other) noexcept : root(other.root)
    {
        other.root = nullptr;
    }
    /// <summary>
    /// 移动赋值运算符。
    /// </summary>
    /// <param name="other">源树对象。</param>
    /// <returns>当前树对象。</returns>
    Tree& operator=(Tree&& other) noexcept
    {
        if (this != &other)
        {
            clear(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }
    /// <summary>
    /// 将先序遍历结果输出到标准输出。
    /// </summary>
    void preOrderTraversal() const {
        preOrder(root);
        std::cout << std::endl;
    }

    /// <summary>
    /// 将层序遍历结果及每个节点度数输出到标准输出。
    /// </summary>
    void levelOrderTraversal() const
    {
        if (root == nullptr) return;
        std::queue<Node*> q;
        std::vector<size_t> degrees;
        q.push(root);
        while (!q.empty())
        {
            const size_t levelSize = q.size();
            for (size_t i = 0; i < levelSize; ++i)
            {
                Node* curNode = q.front();
                size_t degree = 0;
                q.pop();
                std::cout << curNode->data << ' ';
                Node* child = curNode->child;
                while (child != nullptr)
                {
                    q.push(child);
                    child = child->sibling;
                    degree++;
                }
                degrees.push_back(degree);
            }
        }
        std::cout << std::endl;
        for (const size_t i : degrees)
        {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }

    /// <summary>
    /// 在指定父节点下插入新节点，位置为最后一个孩子。
    /// </summary>
    /// <param name="parentData">父节点的数据值。</param>
    /// <param name="data">新插入孩子节点的数据值。</param>
    void insert(const T& parentData, const T& data)
    {
        Node* parentNode = findNode(root, parentData);
        if (parentNode == nullptr) return;

        Node* newNode = new Node(data);
        if (parentNode->child == nullptr)
        {
            parentNode->child = newNode;
        }
        else
        {
            Node* child = parentNode->child;
            while (child->sibling != nullptr)
            {
                child = child->sibling;
            }
            child->sibling = newNode;
        }
    }

    /// <summary>
    /// 工厂方法：根据层序值和度数构建树。
    /// </summary>
    /// <param name="nodeData">按层序排列的节点值。</param>
    /// <param name="degrees">层序下每个节点对应的孩子数量。</param>
    /// <returns>构建完成的树实例。</returns>
    static Tree buildFromLevel(const std::vector<T>& nodeData, const std::vector<int>& degrees)
    {
        Tree tree;
        if (nodeData.empty() || degrees.empty()) return tree;
        if (nodeData.size() != degrees.size()) return tree;

        tree.root = tree.buildLevel(nodeData, degrees);
        return tree;
    }
};
template<class T>
/// <summary>
/// 树结构存储格式之间的转换算法。
/// </summary>
class TreeSolution
{
    using Node = Tree<T>::Node;
    using ListNode = ListTree<T>::Node;

    /// <summary>
    /// 将邻接表树格式转换为孩子-兄弟格式。
    /// </summary>
    /// <param name="src">源列表树。</param>
    /// <returns>转换后的孩子-兄弟树。</returns>
    static Tree<T> convertToChildSibling(const ListTree<T>& src)
    {
        const int num = src.size();
        if (num == 0) return Tree<T>(nullptr);

        // mapping[i] 缓存源树中索引 i 对应的已转换节点。
        // 这样可以避免重复分配，并保证一一映射关系。
        std::vector<Node*> mapping(num, nullptr);

        std::function<Node*(int)> buildNode = [&](int idx) -> Node*
        {
            // 对非法索引做保护，避免异常输入导致越界访问。
            if (idx < 0 || idx >= num) return nullptr;
            // 若该节点已构建则直接复用，保持节点身份一致并避免重复构建。
            if (mapping[idx] != nullptr) return mapping[idx];

            // 1) 根据源树数据创建当前节点，并立即写入缓存。
            Node* curNode = new Node(src.getData(idx));
            mapping[idx] = curNode;

            auto* firstChild = src.getFirstChild(idx);
            if (firstChild != nullptr)
            {
                // 2) 先转换第一个孩子，并挂接到 child 指针。
                Node* firstChildNode = buildNode(firstChild->index);
                curNode->child = firstChildNode;

                // 3) 依次转换其余孩子，并通过 sibling 指针串成兄弟链。
                Node* prevSibling = firstChildNode;
                auto* curChild = firstChild->next;
                while (curChild != nullptr)
                {
                    // 构建当前孩子子树，然后追加到兄弟链末尾。
                    Node* siblingNode = buildNode(curChild->childIndex);
                    prevSibling->sibling = siblingNode;
                    prevSibling = siblingNode;
                    curChild = curChild->next;
                }
            }
            return curNode;
        };

        // 从源树根节点开始转换，并将结果封装为 Tree 返回。
        int rootIdx = src.getRootIndex();
        Node* rootNode = buildNode(rootIdx);
        return Tree<T>(rootNode);

    }
};
}
