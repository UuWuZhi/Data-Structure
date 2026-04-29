#pragma once
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>

namespace ds {

/// <summary>
/// 哈夫曼树类，支持根据叶子权值构建最优二叉树，并生成哈夫曼编码。
/// </summary>
/// <typeparam name="T">叶子结点值的类型。</typeparam>
template <typename T>
class HuffmanTree {
    /// <summary>
    /// 哈夫曼树结点定义。
    /// </summary>
    struct Node {
        T data;                 // 叶子结点的值（非叶子结点为默认构造值）
        int weight;             // 权值
        Node* left;             // 左孩子
        Node* right;            // 右孩子
        size_t minLeafIndex;    // 子树中最小叶子输入下标（稳定排序次关键字）
        size_t createId;        // 结点创建序号（最终打破平局）

        /// <summary>
        /// 构造叶子结点。
        /// </summary>
        /// <param name="d">结点值。</param>
        /// <param name="w">权值。</param>
        Node(const T& d, const int w, const size_t leafIndex, const size_t id)
            : data(d), weight(w), left(nullptr), right(nullptr), minLeafIndex(leafIndex), createId(id) {}

        /// <summary>
        /// 构造内部合并结点（非叶子）。
        /// </summary>
        /// <param name="w">权值（左右孩子权值之和）。</param>
        /// <param name="l">左孩子。</param>
        /// <param name="r">右孩子。</param>
        Node(const int w, Node* l, Node* r, const size_t id)
            : data(T()),
              weight(w),
              left(l),
              right(r),
              minLeafIndex(std::min(l->minLeafIndex, r->minLeafIndex)),
              createId(id) {}
    };

    Node* root;                                 // 哈夫曼树根结点
    std::unordered_map<T, std::string> codeMap; // 叶子值 → 哈夫曼编码

    /// <summary>
    /// 递归释放子树内存。
    /// </summary>
    /// <param name="node">当前子树的根。</param>
    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    /// <summary>
    /// 递归生成所有叶子结点的哈夫曼编码。
    /// </summary>
    /// <param name="node">当前结点。</param>
    /// <param name="code">到达当前结点时的累积编码。</param>
    void buildCodeMap(Node* node, const std::string& code) {
        if (node == nullptr) return;
        // 叶子结点：左右孩子均为空
        if (node->left == nullptr && node->right == nullptr) {
            codeMap[node->data] = code;
            return;
        }
        // 递归左子树（编码追加 '0'）
        buildCodeMap(node->left, code + '0');
        // 递归右子树（编码追加 '1'）
        buildCodeMap(node->right, code + '1');
    }

public:
    /// <summary>
    /// 禁用拷贝构造。
    /// </summary>
    HuffmanTree(const HuffmanTree&) = delete;
    /// <summary>
    /// 禁用拷贝赋值。
    /// </summary>
    HuffmanTree& operator=(const HuffmanTree&) = delete;

    /// <summary>
    /// 构造哈夫曼树。
    /// </summary>
    /// <param name="values">叶子结点的值列表，与权值一一对应。</param>
    /// <param name="weights">叶子结点的权值列表。</param>
    /// <remarks>要求 values 与 weights 长度相同且至少为1。</remarks>
    HuffmanTree(const std::vector<T>& values, const std::vector<int>& weights)
        : root(nullptr) {
        if (values.empty() || values.size() != weights.size()) {
            return; // 非法输入，空树
        }

        // 自定义比较器：稳定最小堆（weight, minLeafIndex, createId）
        auto cmp = [](Node* a, Node* b) {
            if (a->weight != b->weight) return a->weight > b->weight;
            if (a->minLeafIndex != b->minLeafIndex) return a->minLeafIndex > b->minLeafIndex;
            return a->createId > b->createId;
        };
        std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> minHeap(cmp);
        size_t createIdCounter = 0;

        // 创建叶子结点并入堆
        for (size_t i = 0; i < values.size(); ++i) {
            minHeap.push(new Node(values[i], weights[i], i, createIdCounter++));
        }

        // 贪心合并直到堆中只剩一个结点
        while (minHeap.size() > 1) {
            Node* left = minHeap.top(); minHeap.pop();
            Node* right = minHeap.top(); minHeap.pop();

            // 保证左右孩子在同一稳定规则下有确定顺序：左 <= 右
            const bool leftGreaterThanRight =
                (left->weight > right->weight) ||
                (left->weight == right->weight && left->minLeafIndex > right->minLeafIndex) ||
                (left->weight == right->weight && left->minLeafIndex == right->minLeafIndex &&
                 left->createId > right->createId);
            if (leftGreaterThanRight) std::swap(left, right);

            Node* parent = new Node(left->weight + right->weight, left, right, createIdCounter++);
            minHeap.push(parent);
        }

        root = minHeap.top(); // 树根
        // 生成编码映射表
        buildCodeMap(root, "");
    }

    /// <summary>
    /// 析构函数，释放所有结点内存。
    /// </summary>
    ~HuffmanTree() {
        clear(root);
    }

    /// <summary>
    /// 移动构造函数。
    /// </summary>
    HuffmanTree(HuffmanTree&& other) noexcept
        : root(other.root), codeMap(std::move(other.codeMap)) {
        other.root = nullptr;
    }

    /// <summary>
    /// 移动赋值运算符。
    /// </summary>
    HuffmanTree& operator=(HuffmanTree&& other) noexcept {
        if (this != &other) {
            clear(root);
            root = other.root;
            codeMap = std::move(other.codeMap);
            other.root = nullptr;
        }
        return *this;
    }

    /// <summary>
    /// 获取指定叶子结点的哈夫曼编码。
    /// </summary>
    /// <param name="value">叶子结点的值。</param>
    /// <returns>对应的哈夫曼编码（如 "101"），若不存在则返回空字符串。</returns>
    std::string getCode(const T& value) const {
        auto it = codeMap.find(value);
        if (it != codeMap.end())
            return it->second;
        return "";
    }
};

} // namespace ds
