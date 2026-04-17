#include "BinaryTree.hpp"

int main()
{
    std::vector<int> level;
    int m,k;
    std::cin >> m;
    for (int i = 0; i < m; i++)
    {
        std::cin >> k;
        level.push_back(k);
    }
    const ds::BinaryTree<int> tree = ds::BinaryTree<int>::buildFromLevel(level);
    tree.inOrderTraversal();
}