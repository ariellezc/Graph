class node{
public:
    int data;
    node* next;
    int weight;
};

class list{
public:
    node* head=nullptr;
    node* tail=nullptr;
    void createNode(int data, int weight);
};

void list::createNode(int data, int weight){
    node* nNode = new node();
    nNode->data = data;
    nNode->weight = weight;
    nNode->next = nullptr;

    if(head == nullptr){
        head = nNode;
        tail = nNode;
    }
    else{
        tail->next = nNode;
        tail = nNode;
    }
}
