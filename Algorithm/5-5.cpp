#include "Tree.hpp"
#include "ListTree.hpp"

int main()
{
    int n;
    std::cin >> n;
    ds::ListTree<char> list_tree(n);
    for (int i = 0; i < n; i++)
    {
        char c;
        std::cin >> c;
        list_tree.addNode(c);
    }
    for (int i = 0; i < n; i++)
    {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; j++)
        {
            int child_idx;
            std::cin >> child_idx;
            list_tree.addChild(i,child_idx);
        }
    }
    ds::Tree<char> child_sibling_tree = ds::TreeSolution<char>::convertToChildSibling(list_tree);
    child_sibling_tree.preOrderTraversal();
}