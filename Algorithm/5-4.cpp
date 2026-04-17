#include "Tree.hpp"

int main()
{
    std::vector<char> data;
    std::vector<int> degree;
    std::string str;
    int deg;

    std::cin >> str;
    for (auto i : str)
    {
        data.push_back(i);
    }
    for (int i = 0; i < data.size(); ++i)
    {
        std::cin >> deg;
        degree.push_back(deg);
    }
    ds::Tree<char> tree = ds::Tree<char>::buildFromLevel(data, degree);
    char p,c;
    std::cin >> p >> c;
    tree.insert(p,c);
    tree.levelOrderTraversal();
}