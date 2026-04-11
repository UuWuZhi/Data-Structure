#ifndef DATASTRUCTURE_LINKEDLIST_H
#define DATASTRUCTURE_LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Node Node;
Node* initList();
void insertAtHead(Node* head, void* data);
void insertAtTail(Node* head, void* data);
void insertAtPosition(Node* head, void* data, int pos);
void deleteByValue(Node* head, const void* target);
void deleteAtPosition(Node* head, int pos);
int search(const Node* head, const void* target);
void printList(const Node* head);
void destroyList(Node** head);

#ifdef __cplusplus
}
#endif

#endif //DATASTRUCTURE_LINKEDLIST_H
