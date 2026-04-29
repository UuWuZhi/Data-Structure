#include "ThreadedBinaryTree.hpp"
int main()
{
    std::string str;
    std::cin >> str;
    char val;
    std::cin >> val;
    ds::ThreadedBinaryTree<char> tree = ds::ThreadedBinaryTree<char>::buildFromString(str);
    std::cout << tree.findPrev(val) << " " << tree.findNext(val) << std::endl;
}