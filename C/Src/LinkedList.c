#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// 链表节点结构体。
/// </summary>
typedef struct Node {
    void* data;         ///< 数据域。
    Node* next;  ///< 指针域，指向下一个节点。
} Node;

/// <summary>
/// 初始化带头节点的链表，创建一个头节点并将其 next 指向 NULL。
/// </summary>
/// <returns>链表头节点指针。</returns>
Node* initList() {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    head->next = NULL;  ///< 头节点不存储数据，仅作为起始标记。
    return head;
}

/// <summary>
/// 头插法：在头节点之后插入新节点（新节点成为第一个实际节点）。
/// </summary>
/// <param name="head">链表头节点。</param>
/// <param name="data">待插入的数据指针。</param>
void insertAtHead(Node* head, void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    newNode->data = data;
    newNode->next = head->next;  ///< 新节点指向原第一个节点。
    head->next = newNode;        ///< 头节点指向新节点。
}

/// <summary>
/// 尾插法：在链表末尾插入新节点。
/// </summary>
/// <param name="head">链表头节点。</param>
/// <param name="data">待插入的数据指针。</param>
void insertAtTail(Node* head, void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    Node* cur = head;
    while (cur->next != NULL) {  ///< 找到最后一个节点。
        cur = cur->next;
    }
    cur->next = newNode;
}

/// <summary>
/// 按位置插入：在第 pos 个位置（1 为第一个实际节点）后插入新节点。
/// </summary>
/// <param name="head">链表头节点。</param>
/// <param name="data">待插入的数据指针。</param>
/// <param name="pos">
/// 插入位置。pos 为 0 时等同于头插法；pos 大于链表长度时插入到末尾。
/// </param>
void insertAtPosition(Node* head, void* data, const int pos) {
    if (pos < 0) {
        printf("位置无效！\n");
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    newNode->data = data;

    Node* cur = head;
    int i = 0;
    /// <remarks>移动到待插入位置的前一个节点。</remarks>
    while (cur != NULL && i < pos) {
        cur = cur->next;
        i++;
    }
    if (cur == NULL) {
        printf("位置超出链表长度，将插入到末尾。\n");
        /// <remarks>此时 cur 为 NULL，需要重新定位到最后一个节点。</remarks>
        cur = head;
        while (cur->next != NULL) cur = cur->next;
        newNode->next = cur->next;
        cur->next = newNode;
    } else {
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

/// <summary>
/// 删除第一个值为 target 的节点（按指针值比较）。
/// </summary>
/// <param name="head">链表头节点。</param>
/// <param name="target">待删除的目标数据指针。</param>
void deleteByValue(Node* head, const void* target) {
    if (head->next == NULL) {
        printf("链表为空，无法删除。\n");
        return;
    }
    Node* prev = head;
    Node* cur = head->next;
    while (cur != NULL) {
        if (cur->data == target) {
            prev->next = cur->next;
            free(cur);
            printf("成功删除节点：%p\n", target);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("未找到值为 %p 的节点。\n", target);
}

/// <summary>
/// 删除第 pos 个节点（1 表示第一个实际节点）。
/// </summary>
/// <param name="head">链表头节点。</param>
/// <param name="pos">待删除节点的位置。</param>
void deleteAtPosition(Node* head, const int pos) {
    if (pos < 1 || head->next == NULL) {
        printf("位置无效或链表为空。\n");
        return;
    }
    Node* prev = head;
    Node* cur = head->next;
    int i = 1;
    while (cur != NULL && i < pos) {
        prev = cur;
        cur = cur->next;
        i++;
    }
    if (cur == NULL) {
        printf("位置 %d 超出链表长度。\n", pos);
        return;
    }
    prev->next = cur->next;
    free(cur);
    printf("成功删除第 %d 个节点。\n", pos);
}

/// <summary>
/// 查找第一个值为 target 的节点（按指针值比较）。
/// </summary>
/// <param name="head">链表头节点。</param>
/// <param name="target">要查找的目标数据指针。</param>
/// <returns>节点位置（从 1 开始），未找到返回 -1。</returns>
int search(const Node* head, const void* target) {
    const Node* cur = head->next;
    int pos = 1;
    while (cur != NULL) {
        if (cur->data == target) {
            return pos;
        }
        cur = cur->next;
        pos++;
    }
    return -1;
}

/// <summary>
/// 遍历链表并打印所有节点的值。
/// </summary>
/// <param name="head">链表头节点。</param>
void printList(const Node* head) {
    if (head->next == NULL) {
        printf("链表为空。\n");
        return;
    }
    const Node* cur = head->next;
    printf("链表内容：");
    while (cur != NULL) {
        printf("%p ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

/// <summary>
/// 释放整个链表（包括头节点）。
/// </summary>
/// <param name="head">头节点指针的地址，用于销毁后置空。</param>
void destroyList(Node** head) {
    Node* cur = *head;
    while (cur != NULL) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
    printf("链表已销毁。\n");
}
