#pragma once

#include <iostream>
#include <vector>
#include <deque>

namespace ds {

template<class T>
class BinaryTree
{
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

        if (pos == inEnd && in[pos] != rootVal) return nullptr;

        // 3 9 20 15 7 -> 9 + 20 15 7
        // 9 3 15 20 7 -> 9 + 15 20 7
        const int leftSize = pos - inBegin;
        node->left = buildPreIn(pre, preBegin + 1, preBegin + leftSize,
                                in, inBegin, pos - 1);
        node->right = buildPreIn(pre, preBegin + leftSize + 1, preEnd,
                                 in, pos + 1, inEnd);
        return node;
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

    void clear(Node* node)
    {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    static BinaryTree buildFromPreIn(std::vector<T> pre, std::vector<T> in)
    {
        BinaryTree tree;
        if (pre.size() != in.size()) return tree;
        if (pre.empty()) return tree;

        tree.root = tree.buildPreIn(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
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
};

} // namespace ds
