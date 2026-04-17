#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <functional>

namespace ds {
template<class T>
/// <summary>
/// 二叉树结构及常用构建与遍历功能。
/// </summary>
class BinaryTree
{
    template <class U> friend class BinaryTreeSolution;
    /// <summary>
    /// 二叉树节点定义。
    /// </summary>
    struct Node
    {
        /// <summary>
        /// 当前节点存储的数据值。
        /// </summary>
        T data;
        /// <summary>
        /// 指向左孩子节点的指针。
        /// </summary>
        Node* left;
        /// <summary>
        /// 指向右孩子节点的指针。
        /// </summary>
        Node* right;

        /// <summary>
        /// 使用给定值初始化节点。
        /// </summary>
        /// <param name="val">节点数据值。</param>
        explicit Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    /// <summary>
    /// 根据层序序列构建二叉树，-1 表示空节点。
    /// </summary>
    /// <param name="level">层序节点值序列。</param>
    /// <returns>构建后的根节点指针。</returns>
    Node* buildLevel(const std::vector<T>& level)
    {
        if (level.empty()) return nullptr;

        std::queue<Node*> q;
        Node* rootNode = new Node(level[0]);
        q.push(rootNode);
        size_t i = 1;

        while (!q.empty() && i < level.size())
        {
            Node* curNode = q.front();
            q.pop();
            if (i < level.size())
            {
                if (level[i] != -1)
                {
                    curNode->left = new Node(level[i]);
                    q.push(curNode->left);
                }
                ++i;
            }
            if (i < level.size())
            {
                if (level[i] != -1)
                {
                    curNode->right = new Node(level[i]);
                    q.push(curNode->right);
                }
                ++i;
            }
        }
        return rootNode;
    }
    /// <summary>
    /// 递归先序遍历。
    /// </summary>
    /// <param name="node">当前遍历节点。</param>
    void preorder(Node* node) const {
        if (!node) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    /// <summary>
    /// 递归中序遍历。
    /// </summary>
    /// <param name="node">当前遍历节点。</param>
    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    /// <summary>
    /// 递归后序遍历。
    /// </summary>
    /// <param name="node">当前遍历节点。</param>
    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }
    /// <summary>
    /// 递归释放以指定节点为根的子树。
    /// </summary>
    /// <param name="node">待释放子树根节点。</param>
    void clear(Node* node)
    {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
public:
    /// <summary>
    /// 构造空二叉树。
    /// </summary>
    BinaryTree() : root(nullptr) {}
    /// <summary>
    /// 析构函数，释放整棵树。
    /// </summary>
    ~BinaryTree()
    {
        clear(root);
        root = nullptr;
    }
    /// <summary>
    /// 禁用拷贝构造。
    /// </summary>
    BinaryTree(const BinaryTree& tree) = delete;
    /// <summary>
    /// 禁用拷贝赋值。
    /// </summary>
    BinaryTree& operator=(const BinaryTree& tree) = delete;
    /// <summary>
    /// 移动构造函数。
    /// </summary>
    /// <param name="other">源树对象。</param>
    BinaryTree(BinaryTree&& other) noexcept : root(other.root)
    {
        other.root = nullptr;
    }
    /// <summary>
    /// 移动赋值运算符。
    /// </summary>
    /// <param name="other">源树对象。</param>
    /// <returns>当前树对象。</returns>
    BinaryTree& operator=(BinaryTree&& other) noexcept
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
    /// 由先序与中序序列构建二叉树。
    /// </summary>
    /// <param name="pre">先序序列。</param>
    /// <param name="in">中序序列。</param>
    /// <returns>构建后的二叉树实例。</returns>
    static BinaryTree buildFromPreIn(const std::vector<T>& pre, const std::vector<T>& in)
    {
        BinaryTree tree;
        if (pre.size() != in.size()) return tree;
        if (pre.empty()) return tree;

        std::function<Node*(int, int, int, int)> build = [&](int preBegin,int preEnd, int inBegin, int inEnd) -> Node*
        {
            if (preBegin > preEnd || inBegin > inEnd) return nullptr;
            if (preEnd - preBegin != inEnd - inBegin) return nullptr;

            T rootVal = pre[preBegin];
            Node* node = new Node(rootVal);

            int pos = inBegin;
            while (pos <= inEnd && in[pos] != rootVal) ++pos;
            if (pos > inEnd) return nullptr;

            const int leftSize = pos - inBegin;
            node->left = build(preBegin + 1, preBegin + leftSize, inBegin, pos - 1);
            node->right = build(preBegin + leftSize + 1, preEnd, pos + 1, inEnd);
            return node;
        };

        tree.root = build(0, static_cast<int>(pre.size()) - 1, 0, static_cast<int>(in.size()) - 1);
        return tree;
    }

    /// <summary>
    /// 由中序与后序序列构建二叉树。
    /// </summary>
    /// <param name="in">中序序列。</param>
    /// <param name="post">后序序列。</param>
    /// <returns>构建后的二叉树实例。</returns>
    static BinaryTree buildFromInPost(const std::vector<T>& in, const std::vector<T>& post)
    {
        BinaryTree tree;
        if (in.size() != post.size()) return tree;
        if (in.empty()) return tree;

        std::function<Node*(int, int, int, int)> build = [&](int inBegin,int inEnd, int postBegin, int postEnd) -> Node*
        {
            if (postBegin > postEnd || inBegin > inEnd) return nullptr;
            if (postEnd - postBegin != inEnd - inBegin) return nullptr;

            T rootVal = post[postEnd];
            Node* node = new Node(rootVal);

            int pos = inBegin;
            while (pos <= inEnd && in[pos] != rootVal) ++pos;
            if (pos > inEnd) return nullptr;

            const int leftSize = pos - inBegin;
            node->left = build(inBegin, pos - 1, postBegin, postBegin + leftSize - 1);
            node->right = build(pos + 1, inEnd, postBegin + leftSize, postEnd - 1);
            return node;
        };

        tree.root = build(0, static_cast<int>(in.size()) - 1, 0, static_cast<int>(post.size()) - 1);
        return tree;
    }

    /// <summary>
    /// 由层序序列构建二叉树，-1 表示空节点。
    /// </summary>
    /// <param name="level">层序节点值序列。</param>
    /// <returns>构建后的二叉树实例。</returns>
    static BinaryTree buildFromLevel(const std::vector<T>& level)
    {
        BinaryTree tree;
        tree.root = tree.buildLevel(level);
        return tree;
    }

    /// <summary>
    /// 输出层序遍历结果（包含必要的空节点占位 -1）。
    /// </summary>
    void levelOrderTraversal() const
    {
        if (root == nullptr) return;
        std::deque<Node*> q;
        q.push_back(root);
        while (!q.empty())
        {
            Node* cur = q.front();
            q.pop_front();
            if (cur != nullptr)
            {
                std::cout << cur->data << ' ';
                q.push_back(cur->left);
                q.push_back(cur->right);
            } else
            {
                bool hasNonNull = false;
                for (Node* node : q)
                {
                    if (node != nullptr)
                    {
                        hasNonNull = true;
                        break;
                    }
                }
                if (hasNonNull)
                {
                    std::cout << "-1 ";
                }
                else
                {
                    break;
                }
            }
        }
        std::cout << std::endl;
    }

    /// <summary>
    /// 输出先序遍历结果。
    /// </summary>
    void preOrderTraversal() const {
        preorder(root);
        std::cout << std::endl;
    }

    /// <summary>
    /// 输出中序遍历结果。
    /// </summary>
    void inOrderTraversal() const
    {
        inorder(root);
        std::cout << std::endl;
    }

    /// <summary>
    /// 输出后序遍历结果。
    /// </summary>
    void postOrderTraversal() const
    {
        postorder(root);
        std::cout << std::endl;
    }

};
template <class T>
/// <summary>
/// 二叉树相关算法集合。
/// </summary>
class BinaryTreeSolution
{
    using Node = BinaryTree<T>::Node;
    using Tree = BinaryTree<T>;
public:
    /// <summary>
    /// 计算二叉树的最大宽度（按完全二叉树索引位置计）。
    /// </summary>
    /// <param name="tree">目标二叉树。</param>
    /// <returns>二叉树最大宽度。</returns>
    static int widthOfBinaryTree(const Tree& tree)
    {
        const Node* root = tree.root;
        if (root == nullptr) return 0;
        int maxWidth = 0;
        std::queue<std::pair<const Node*, int>> q;
        q.push({root, 0});

        while (!q.empty())
        {
            const size_t levelSize = q.size();
            const int left = q.front().second;
            int right = left;
            for (size_t i = 0; i < levelSize; ++i)
            {
                auto [node, idx] = q.front();
                q.pop();
                right = idx;
                if (node->left != nullptr) q.push({node->left, 2 * idx});
                if (node->right != nullptr) q.push({node->right, 2 * idx + 1});
            }
            maxWidth = std::max(maxWidth, right - left + 1);
        }
        return maxWidth;
    }
};
} // namespace ds
