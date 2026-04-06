#include <stdio.h>
#include <stdlib.h>

// 链表节点结构体
typedef struct Node {
    int data;           // 数据域
    struct Node* next;  // 指针域，指向下一个节点
} Node;

// 初始化带头节点的链表：创建一个头节点，其next指向NULL
Node* initList() {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    head->next = NULL;  // 头节点不存储数据，仅作为起始标记
    return head;
}

// 头插法：在头节点之后插入新节点（新节点成为第一个实际节点）
void insertAtHead(Node* head, const int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    newNode->data = data;
    newNode->next = head->next;  // 新节点指向原第一个节点
    head->next = newNode;        // 头节点指向新节点
}

// 尾插法：在链表末尾插入新节点
void insertAtTail(Node* head, const int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    Node* cur = head;
    while (cur->next != NULL) {  // 找到最后一个节点
        cur = cur->next;
    }
    cur->next = newNode;
}

// 按位置插入：在第pos个位置（1为第一个实际节点）后插入新节点
// 若pos为0，等同于头插法；若pos大于链表长度，则插入到末尾
void insertAtPosition(Node* head, const int data, const int pos) {
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
    // 移动到待插入位置的前一个节点
    while (cur != NULL && i < pos) {
        cur = cur->next;
        i++;
    }
    if (cur == NULL) {
        printf("位置超出链表长度，将插入到末尾。\n");
        // 此时cur为NULL，需要重新定位到最后一个节点
        cur = head;
        while (cur->next != NULL) cur = cur->next;
        newNode->next = cur->next;
        cur->next = newNode;
    } else {
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

// 删除第一个值为target的节点
void deleteByValue(Node* head, const int target) {
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
            printf("成功删除节点：%d\n", target);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("未找到值为 %d 的节点。\n", target);
}

// 删除第pos个节点（1表示第一个实际节点）
void deleteAtPosition(Node* head, int pos) {
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

// 查找第一个值为target的节点，返回其位置（1起始），未找到返回-1
int search(const Node* head, const int target) {
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

// 遍历链表并打印所有节点的值
void printList(const Node* head) {
    if (head->next == NULL) {
        printf("链表为空。\n");
        return;
    }
    const Node* cur = head->next;
    printf("链表内容：");
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

// 释放整个链表（包括头节点）
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
