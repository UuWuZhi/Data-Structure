/// <summary>
/// 重要说明：使用void*存储数据时，应使用函数指针传递比较，查找，打印等函数的逻辑
/// 此处仅作教学目的，故没有添加
/// </summary>
#include "LinkedList.h"
#include <string>
#include <iostream>

typedef struct Book
{
    size_t Index = -1;
    std::string Name;
    double Price = 0.0;
} Book ;

int main()
{
    Node* head = initList();
    size_t choice = -1;
    int pos;
    Book book;
    while (std::cin >> choice)
    {
        switch (choice)
        {
            case 1:
                std::cout << "输入指定位置，编号，书名，价格：";
                std::cin >> pos >> book.Index >> book.Name >> book.Price;
                insertAtPosition(head, &book, pos);
            break;
            case 2:
                std::cout << "输入位置";
                std::cin >> pos;
                deleteAtPosition(head, pos);
            break;
            case 3:
                printList(head);
            break;
        default:
                std::cout << "Err Input" << std::endl;
        }
    }
}