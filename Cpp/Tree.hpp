#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#include "ListTree.hpp"

namespace ds
{
template<class T>
class Tree
{
    template <class U> friend class TreeSolution;
    struct Node
    {
        T data;
        Node* child;
        Node* sibling;

        explicit Node(const T& data) : data(data), child(nullptr), sibling(nullptr) {}
    };

    Node* root;

    void clear(Node* rootNode)
    {
        if (rootNode == nullptr) return;
        clear(rootNode->child);
        clear(rootNode->sibling);
        delete rootNode;
    }

    Node* findNode(Node* node, const T& data) const
    {
        if (node == nullptr) return nullptr;
        if (node->data == data) return node;
        Node* foundNode = findNode(node->child, data);
        if (foundNode != nullptr) return foundNode;
        return findNode(node->sibling, data);
    }

    void preOrder(Node* rootNode)
    {
        if (rootNode == nullptr) return;
        std::cout << rootNode->data << ' ';
        preOrder(rootNode->child);
        preOrder(rootNode->sibling);
    }

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
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;
    Tree() : root(nullptr) {}
    explicit Tree(Node* rootNode) : root(rootNode) {}
    ~Tree() {clear(root); root = nullptr;}
    Tree(Tree&& other) noexcept : root(other.root)
    {
        other.root = nullptr;
    }
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
    void preOrderTraversal() const {
        preOrder(root);
        std::cout << std::endl;
    }

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
class TreeSolution
{
    using Node = Tree<T>::Node;
    using ListNode = ListTree<T>::Node;

    static Tree<T> convertToChildSibling(const ListTree<T>& src)
    {
        const int num = src.size();
        if (num == 0) return Tree<T>(nullptr);

        std::vector<Node*> mapping(num, nullptr);

        std::function<Node*(int)> buildNode = [&](int idx) -> Node*
        {
            if (idx < 0 || idx >= num) return nullptr;
            if (mapping[idx] != nullptr) return mapping[idx];
        };

        int rootIdx = src.getRootIndex();
        Node* rootNode = buildNode(rootIdx);
        return Tree<T>(rootNode);

    }
};
}
