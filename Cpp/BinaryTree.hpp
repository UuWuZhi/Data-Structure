#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <queue>

namespace ds {
template<class T>
class BinaryTree
{
    template <class U> friend class BinaryTreeSolution;
    struct Node
    {
        T data;
        Node* left;
        Node* right;

        explicit Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* buildPreIn(const std::vector<T>& pre, const int preBegin, const int preEnd,
                     const std::vector<T>& in, const int inBegin, const int inEnd)
    {
        if (preBegin > preEnd || inBegin > inEnd) return nullptr;
        if (preEnd - preBegin != inEnd - inBegin) return nullptr;

        T rootVal = pre[preBegin];
        Node* node = new Node(rootVal);

        int pos = inBegin;
        while (pos <= inEnd && in[pos] != rootVal) ++pos;
        if (pos > inEnd) return nullptr;

        // 3 9 20 15 7 -> 9 + 20 15 7
        // 9 3 15 20 7 -> 9 + 15 20 7
        const int leftSize = pos - inBegin;
        node->left = buildPreIn(pre, preBegin + 1, preBegin + leftSize,
                                in, inBegin, pos - 1);
        node->right = buildPreIn(pre, preBegin + leftSize + 1, preEnd,
                                 in, pos + 1, inEnd);
        return node;
    }
    Node* buildInPost(const std::vector<T>& post, const int postBegin, const int postEnd,
                      const std::vector<T>& in, const int inBegin, const int inEnd)
    {
        if (postBegin > postEnd || inBegin > inEnd) return nullptr;
        if (postEnd - postBegin != inEnd - inBegin) return nullptr;

        T rootVal = post[postEnd];
        Node* node = new Node(rootVal);

        int pos = inBegin;
        while (pos <= inEnd && in[pos] != rootVal) ++pos;
        if (pos > inEnd) return nullptr;

        const int leftSize = pos - inBegin;
        node->left = buildInPost(post, postBegin, postBegin + leftSize - 1,
                                 in, inBegin, pos - 1);
        node->right = buildInPost(post, postBegin + leftSize, postEnd - 1,
                                  in, pos + 1, inEnd);
        return node;
    }

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
    void preorder(Node* node) const {
        if (!node) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }
    void clear(Node* node)
    {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        clear(root);
        root = nullptr;
    }
    BinaryTree(const BinaryTree& tree) = delete;
    BinaryTree& operator=(const BinaryTree& tree) = delete;
    BinaryTree(BinaryTree&& other) noexcept : root(other.root)
    {
        other.root = nullptr;
    }
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

    static BinaryTree buildFromPreIn(const std::vector<T>& pre, const std::vector<T>& in)
    {
        BinaryTree tree;
        if (pre.size() != in.size()) return tree;
        if (pre.empty()) return tree;

        tree.root = tree.buildPreIn(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
        return tree;
    }

    static BinaryTree buildFromInPost(const std::vector<T>& in, const std::vector<T>& post)
    {
        BinaryTree tree;
        if (in.size() != post.size()) return tree;
        if (in.empty()) return tree;

        tree.root = tree.buildInPost(post, 0, post.size() - 1, in, 0, in.size() - 1);
        return tree;
    }

    static BinaryTree buildFromLevel(const std::vector<T>& level)
    {
        BinaryTree tree;
        tree.root = tree.buildLevel(level);
        return tree;
    }

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

    void preOrderTraversal() const {
        preorder(root);
        std::cout << std::endl;
    }

    void inOrderTraversal() const
    {
        inorder(root);
        std::cout << std::endl;
    }

    void postOrderTraversal() const
    {
        postorder(root);
        std::cout << std::endl;
    }

};
template <class T>
class BinaryTreeSolution
{
    using Node = BinaryTree<T>::Node;
    using Tree = BinaryTree<T>;
public:
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
