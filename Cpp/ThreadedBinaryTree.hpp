#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <stack>
#include <string>

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
            if (node->ltag == false) clear(node->left);
            if (node->rtag == false) clear(node->right);
            delete node;
        }

        /// <summary>
        /// 对当前二叉树（头结点已正确连接根结点）重新进行中序线索化。
        /// </summary>
        void reThread()
        {
            if (head == nullptr) return;
            // 获取真实的根结点（如果左指针为线索则树为空）
            Node* rootNode = head->ltag == true ? nullptr : head->left;

            // 初始化头结点的左右指针及标志
            head->left = rootNode;
            head->ltag = rootNode == nullptr ? true : false;
            head->right = head;
            head->rtag = true;

            if (rootNode != nullptr)
            {

                // 中序线索化：cur 按值传递，prev 按引用传递以便更新
                std::function<void(Node*, Node*&)> inOrderThread = [&](Node* cur, Node*& prev)
                {
                    if (cur == nullptr) return;

                    // 线索化左子树（如果不是线索）
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

                    // 线索化右子树（如果不是线索）
                    if (cur->rtag == false) inOrderThread(cur->right, prev);
                };

                Node* prev = head;   // 前驱指针，初始指向头结点
                inOrderThread(rootNode, prev);   // 从根结点开始线索化

                // 处理最后一个结点的后继线索指向头结点
                if (prev != nullptr && prev->right == nullptr)
                {
                    prev->right = head;
                    prev->rtag = true;
                }
                // 头结点的右指针指向中序最后一个结点
                head->right = prev;
                head->rtag = false;
            }
            else
            {
                // 空树：头结点左右指针均指向自身
                head->left = head;
                head->right = head;
            }
        }

    public:
        /// <summary>
        /// 禁用拷贝构造。
        /// </summary>
        ThreadedBinaryTree(const ThreadedBinaryTree&) = delete;
        /// <summary>
        /// 禁用拷贝赋值。
        /// </summary>
        ThreadedBinaryTree& operator=(const ThreadedBinaryTree&) = delete;

        /// <summary>
        /// 输出结点指针的辅助友元（用于调试）。
        /// </summary>
        friend std::ostream& operator<<(std::ostream& os, const Node* node)
        {
            if (node != nullptr)
                if (node->data == NULL)
                    os << "0";
                else
                    os << node->data;
            else
                os << "null";
            return os;
        }

        /// <summary>
        /// 构造一棵空的中序线索二叉树（只有头结点）。
        /// </summary>
        ThreadedBinaryTree() : head(new Node(T()))
        {
            head->left = head;   // 空树：左指针指向自身
            head->right = head;  // 右指针指向自身
            head->ltag = false;  // 左指针为孩子（实际指向自身）
            head->rtag = true;   // 右指针为线索（指向自身）
        }

        /// <summary>
        /// 从已有的根结点构造二叉树并自动进行中序线索化（头结点由内部创建）。
        /// </summary>
        /// <param name="rootNode">二叉树根结点指针（将被接管）。</param>
        explicit ThreadedBinaryTree(Node* rootNode) : head(new Node(T()))
        {
            head->left = rootNode;
            head->ltag = (rootNode == nullptr);
            head->right = head;
            head->rtag = true;
            reThread();          // 统一进行线索化，避免重复代码
        }

        /// <summary>
        /// 析构函数，释放所有结点（包括头结点）。
        /// </summary>
        ~ThreadedBinaryTree()
        {
            if (head != nullptr)
            {
                Node* root = head->ltag == true ? nullptr : head->left;
                clear(root);
                delete head;
                head = nullptr;
            }
        }

        /// <summary>
        /// 移动构造函数。
        /// </summary>
        /// <param name="other">源树对象。</param>
        ThreadedBinaryTree(ThreadedBinaryTree&& other) noexcept : head(other.head)
        {
            other.head = nullptr;
        }

        /// <summary>
        /// 移动赋值运算符。
        /// </summary>
        /// <param name="other">源树对象。</param>
        /// <returns>当前树对象。</returns>
        ThreadedBinaryTree& operator=(ThreadedBinaryTree&& other) noexcept
        {
            if (this != &other)
            {
                clear(head->left);
                delete head;
                head = other.head;
                other.head = nullptr;
            }
            return *this;
        }

        /// <summary>
        /// 根据先序和中序遍历序列递归构建二叉树。
        /// </summary>
        /// <param name="pre">先序序列。</param>
        /// <param name="in">中序序列。</param>
        /// <returns>构建好的线索二叉树。</returns>
        static ThreadedBinaryTree buildFromPreIn(const std::vector<T>& pre, const std::vector<T>& in)
        {
            ThreadedBinaryTree tree;
            if (pre.size() != in.size() || pre.empty()) return tree;

            std::function<Node*(int, int, int, int)> buildNode = [&](int preBegin, int preEnd, int inBegin, int inEnd) -> Node*
            {
                if (preBegin > preEnd || inBegin > inEnd) return nullptr;
                if (preEnd - preBegin != inEnd - inBegin) return nullptr;

                T rootVal = pre[preBegin];
                Node* rootNode = new Node(rootVal);

                int rootIndex = inBegin;
                while (rootIndex <= inEnd && in[rootIndex] != rootVal) ++rootIndex;
                if (rootIndex > inEnd) return nullptr;

                const int leftSize = rootIndex - inBegin;
                rootNode->left = buildNode(preBegin + 1, preBegin + leftSize, inBegin, rootIndex - 1);
                rootNode->right = buildNode(preBegin + leftSize + 1, preEnd, rootIndex + 1, inEnd);
                return rootNode;
            };

            Node* rootNode = buildNode(0, pre.size() - 1, 0, pre.size() - 1);
            tree.head->left = rootNode;
            tree.head->ltag = (rootNode == nullptr);
            tree.reThread();
            return tree;
        }

        /// <summary>
        /// 根据先序扩展序列构建带头结点的中序线索二叉树。
        /// 序列中的空结点由 emptyMark 表示。
        /// </summary>
        /// <param name="preExpanded">先序扩展序列。</param>
        /// <param name="emptyMark">空结点值标记。</param>
        /// <returns>构建好的线索二叉树。</returns>
        static ThreadedBinaryTree buildFromPreExpanded(const std::vector<T>& preExpanded, const T& emptyMark)
        {
            ThreadedBinaryTree tree;
            if (preExpanded.empty()) return tree;

            size_t index = 0;
            (void)index;    // 没屁用，只是为了让编译器不报Warning
            std::function<Node*()> buildNode = [&]() -> Node*
            {
                if (index >= preExpanded.size()) return nullptr;
                T val = preExpanded[index++];
                if (val == emptyMark) return nullptr;
                Node* node = new Node(val);
                node->left = buildNode();
                node->right = buildNode();
                return node;
            };

            Node* rootNode = buildNode();
            tree.head->left = rootNode;
            tree.head->ltag = (rootNode == nullptr);
            tree.reThread();
            return tree;
        }

        /// <summary>
        /// 从字符串构建（针对 char 类型的便捷版本）。
        /// </summary>
        static ThreadedBinaryTree buildFromString(const std::string& str)
        {
            std::vector<char> vec(str.begin(), str.end());
            return buildFromPreExpanded(vec, '#');
        }

        /// <summary>
        /// 按值查找结点，返回结点指针，未找到返回 nullptr。
        /// </summary>
        Node* findNode(const T& val)
        {
            if (head == nullptr || head->left == head) return nullptr;
            Node* curNode = head->left;
            while (curNode->ltag == false) curNode = curNode->left;
            while (curNode != head)
            {
                if (curNode->data == val) return curNode;
                if (curNode->rtag == true)
                    curNode = curNode->right;
                else
                {
                    curNode = curNode->right;
                    while (curNode->ltag == false) curNode = curNode->left;
                }
            }
            return nullptr;
        }

        /// <summary>
        /// 在指定结点右侧插入新结点（作为右孩子），并重新线索化。
        /// </summary>
        void insertRight(const T& rootVal, const T& childVal)
        {
            Node* childNode = new Node(childVal);
            Node* parentNode = findNode(rootVal);
            if (parentNode == nullptr)
            {
                delete childNode;
                return;
            }

            if (parentNode->rtag == true)
            {
                // 原右指针为线索，直接插入为右孩子
                parentNode->right = childNode;
                parentNode->rtag = false;
            }
            else
            {
                // 原右指针有右子树，将原右子树变成新结点的右子树
                Node* originalRight = parentNode->right;
                parentNode->right = childNode;
                childNode->right = originalRight;
                childNode->rtag = false;   // 原右子树成为右孩子，而非线索
            }
            // 重新线索化整个树（简单但正确）
            reThread();
        }

        /// <summary>
        /// 递归方式中序遍历（基于孩子指针）。
        /// </summary>
        void inOrderTraversalRecursion() const
        {
            std::function<void(Node*)> inOrderPrint = [&](Node* curNode)
            {
                if (curNode == nullptr) return;
                if (curNode->ltag == false) inOrderPrint(curNode->left);
                std::cout << curNode->data << " ";
                if (curNode->rtag == false) inOrderPrint(curNode->right);
            };
            inOrderPrint(head->left);
            std::cout << std::endl;
        }

        /// <summary>
        /// 利用线索进行中序遍历（效率更高）。
        /// </summary>
        void inOrderTraversalThread() const
        {
            if (head == nullptr || head->left == head) return;
            Node* curNode = head->left;
            while (curNode->ltag == false) curNode = curNode->left;

            while (curNode != head)
            {
                std::cout << curNode->data << " ";
                if (curNode->rtag == true)
                    curNode = curNode->right;
                else
                {
                    curNode = curNode->right;
                    while (curNode->ltag == false) curNode = curNode->left;
                }
            }
            std::cout << std::endl;
        }

        /// <summary>
        /// 后序遍历输出（基于孩子指针，单函数迭代实现）。
        /// </summary>
        void postOrderTraversal() const
        {
            if (head == nullptr || head->left == head) return;

            std::stack<Node*> nodeStack;
            Node* curNode = head->left;
            Node* lastVisited = nullptr;

            while (curNode != nullptr || !nodeStack.empty())
            {
                while (curNode != nullptr)
                {
                    nodeStack.push(curNode);
                    curNode = (curNode->ltag == false) ? curNode->left : nullptr;
                }

                Node* peekNode = nodeStack.top();
                Node* rightChild = (peekNode->rtag == false) ? peekNode->right : nullptr;

                if (rightChild != nullptr && rightChild != lastVisited)
                {
                    curNode = rightChild;
                }
                else
                {
                    std::cout << peekNode->data << " ";
                    lastVisited = peekNode;
                    nodeStack.pop();
                }
            }
            std::cout << std::endl;
        }
        /// <summary>
        /// 递归方式后序遍历（基于孩子指针）。
        /// </summary>
        void postOrderTraversalRecursion() const
        {
            std::function<void(Node*)> inOrderPrint = [&](Node* curNode)
            {
                if (curNode == nullptr) return;
                if (curNode->ltag == false) inOrderPrint(curNode->left);
                if (curNode->rtag == false) inOrderPrint(curNode->right);
                std::cout << curNode->data << " ";
            };
            inOrderPrint(head->left);
            std::cout << std::endl;
        }

        /// <summary>
        /// 调试用：打印每个结点的数据以及 ltag/rtag 标志。
        /// </summary>
        void printThread() const
        {
            if (head == nullptr || head->left == head) return;
            Node* curNode = head->left;
            while (curNode->ltag == false) curNode = curNode->left;

            while (curNode != head)
            {
                std::cout << curNode->data << " " << curNode->ltag << " " << curNode->rtag << std::endl;
                if (curNode->rtag == true)
                    curNode = curNode->right;
                else
                {
                    curNode = curNode->right;
                    while (curNode->ltag == false) curNode = curNode->left;
                }
            }
            std::cout << std::endl;
        }

        /// <summary>
        /// 查找指定结点的中序前驱。
        /// </summary>
        Node* findPrev(const T& val)
        {
            Node* curNode = findNode(val);
            if (curNode == nullptr) return nullptr;
            if (curNode->ltag == true)
                return curNode->left;
            else
            {
                curNode = curNode->left;
                while (curNode->rtag == false) curNode = curNode->right;
                return curNode;
            }
        }

        /// <summary>
        /// 查找指定结点的中序后继。
        /// </summary>
        Node* findNext(const T& val)
        {
            Node* curNode = findNode(val);
            if (curNode == nullptr) return nullptr;
            if (curNode->rtag == true)
                return curNode->right;
            else
            {
                curNode = curNode->right;
                while (curNode->ltag == false) curNode = curNode->left;
                return curNode;
            }
        }
    };
}
