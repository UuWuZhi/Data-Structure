#pragma once

#include "ListTree.hpp"
#include "Tree.hpp"
#include "BinaryTree.hpp"
#include "ThreadedBinaryTree.hpp"
#include <functional>
namespace ds
{
    template<class T>
    /// <summary>
    /// 树结构存储格式的算法。
    /// </summary>
    class TreeSolution
    {
        using Node = Tree<T>::Node;
        using ListNode = ListTree<T>::Node;
    public:
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
                // 其实理论上来说这条逻辑是不会被触发的
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
                        Node* siblingNode = buildNode(curChild->index);
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
    template <class T>
    class ThreadedBinaryTreeSolution
    {
        using Node = ThreadedBinaryTree<T>::Node;
        using Tree = ThreadedBinaryTree<T>;
    };
}