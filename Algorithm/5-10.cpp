#include <iostream>
#include "HuffmanTree.hpp"

int main() {
    int n;
    std::cin >> n;
    std::vector<char> data(n);
    std::vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> data[i] >> weights[i];
    }

    ds::HuffmanTree<char> huffman(data, weights);

    char target;
    std::cin >> target;
    std::string code = huffman.getCode(target);
    if (!code.empty())
    {
        std::cout << code << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
    return 0;
}