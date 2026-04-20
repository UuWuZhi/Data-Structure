#pragma once

namespace ds
{
    template <class T>
    /// <summary>
    /// 带头结点的中序线索二叉树。
    /// </summary>
    class ThreadedBinaryTree
    {
        template <class U> friend class TreeSolution;
        /// <summary>
        /// 线索二叉树结点定义。
        /// </summary>
        struct Node
        {
            T data;                 // 数据域
            Node* left;             // 左指针（左孩子或前驱线索）
            Node* right;            // 右指针（右孩子或后继线索）
            bool ltag;              // true: 左指针为线索; false: 左指针指向左孩子
            bool rtag;              // true: 右指针为线索; false: 右指针指向右孩子

            /// <summary>
            /// 构造一个叶子结点，左右各指针均为空，标志均为 false。
            /// </summary>
            /// <param name="val">结点数据。</param>
            explicit Node(const T& val)
                : data(val), left(nullptr), right(nullptr), ltag(false), rtag(false) {}
        };

        Node* head;   // 头结点（不存储有效数据）

        /// <summary>
        /// 递归释放所有结点（包括头结点）。
        /// </summary>
        /// <param name="node">当前待释放子树的根。</param>
        void clear(Node* node)
        {
            if (node == nullptr) return;
            // 只有当指针指向孩子时才递归释放
            if (!node->ltag) clear(node->left);
            if (!node->rtag) clear(node->right);
            delete node;
        }

        /// <summary>
        /// 递归中序遍历对二叉树进行线索化。
        /// </summary>
        /// <param name="cur">当前遍历的结点。</param>
        /// <param name="prev">前驱指针的引用（指向中序遍历中上一个访问的结点）。</param>
        void inOrderThread(Node* cur, Node*& prev)
        {
            if (cur == nullptr) return;

            // 线索化左子树
            if (cur->ltag == false) inOrderThread(cur->left, prev);

            // 处理当前结点的前驱线索
            if (cur->left == nullptr)
            {
                cur->left = prev;
                cur->ltag = true;
            }
            // 处理前驱结点的后继线索
            if (prev != nullptr && prev->right == nullptr)
            {
                prev->right = cur;
                prev->rtag = true;
            }
            prev = cur;

            // 线索化右子树
            if (cur->rtag == false) inOrderThread(cur->right, prev);
        }
    };
}