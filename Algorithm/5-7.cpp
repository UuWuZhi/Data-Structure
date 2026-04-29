#include "ThreadedBinaryTree.hpp"
int main()
{
    std::string str;
    std::cin >> str;
    ds::ThreadedBinaryTree<char> tree = ds::ThreadedBinaryTree<char>::buildFromString(str);
    char parent, child;
    std::cin >> child >> parent;
    tree.insertRight(parent, child);
    tree.printThread();
}