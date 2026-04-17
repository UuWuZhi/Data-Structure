#include "BinaryTree.hpp"

int main()
{
    std::vector<int> pre;
    std::vector<int> in;
    int m, k;
    std::cin >> m;
    for (int i = 0; i < m; i++)
    {
        std::cin >> k;
        pre.push_back(k);
    }
    std::cin >> m;
    for (int i = 0; i < m; i++)
    {
        std::cin >> k;
        in.push_back(k);
    }

    const ds::BinaryTree<int> tree = ds::BinaryTree<int>::buildFromPreIn(pre, in);
    tree.levelOrderTraversal();
}
