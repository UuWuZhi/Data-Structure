
struct Node
{
    // 数据域
    int data;
    // 指针域
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

Node* initList()
{
    Node* head = new Node(0); // 0x0000 = 0
    return head;
}

void pushBack(Node* &head, int val)
{
    Node* newNode = new Node(val);
    Node* curNode = head;
    while(curNode->next != nullptr)
    {
        curNode = curNode->next;
    }
    curNode->next = newNode;
}


void deleteNode(Node* head, int val)
{
    Node* prevNode = head;
    Node* curNode = prevNode->next;
    while (curNode != nullptr)

    {
        if (curNode->data == val)
        {

            prevNode->next = curNode->next;
            delete curNode;
            break;
        }

        prevNode = curNode;
        curNode = curNode->next;
    }
}
int main()
{

}