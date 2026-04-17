#include "BinaryTree.hpp"

int main()
{
    int k,m;
    std::vector<int> level;
    std::cin >> k;
    for (int i = 0; i < k; i++)
    {
        std::cin >> m;
        level.push_back(m);
    }
    const ds::BinaryTree<int> tree = ds::BinaryTree<int>::buildFromLevel(level);
    std::cout << ds::BinaryTreeSolution<int>::widthOfBinaryTree(tree) << std::endl;
}