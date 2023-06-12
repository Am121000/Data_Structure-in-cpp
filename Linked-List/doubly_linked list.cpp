/// major benefit of Doubly linked list is the bidirectional traversal
/// another is backward iteration which is tough using singly linked list

#include <iostream>
using namespace std;
///Firstly we make a class named node for declaring our data structure.
/// you can also use structures and make use of the keyword struct.
///and the reason i do so because I can always use the constructor to directly assign the value rather than making a new function
class Node {
    public:
    int data;
    Node* prev;
    Node* next;

    Node(int val){
        data=val;
        prev=NULL;
        next=NULL;
    }

};
/// the below function will insert the data into end of the list
/// you can use how I have used the NODE(data) which directly provide me my ready to move variable into the list
void insert_at_tail(Node* &head, int data)
{
    Node* newnode= new Node(data);
    if( head==NULL)
    {
        head=newnode;
        return;
    }
    Node* curr=head;
    while(curr->next!=NULL)/// we here traverse to the end of the whole list and add the block to the end
    {
        curr=curr->next;
    }
    curr->next=newnode;/// the next travesed variables next value will indicate to the new valued variable
    newnode->prev=curr;/// the newnode variable previous pointer should also point to the current existing list to call it a doubly linked list;
}
void insert_at_head(Node* &head, int data){
    Node* newnode=new Node(data);
    if(head==NULL){
        head=newnode;
    }
    else{
        head->prev=newnode;
        newnode->next=head;
        head=newnode;
    }
}
void display(Node* head)
{
    if(head==NULL){
        cout<<"empty list"<< endl;
    }
    Node* temp=head;
    while(temp->next!=NULL)
    {
        cout<<temp->data;
        temp=temp->next;
    }


        cout<<temp->data;


    cout<<endl;
}
void delete_at_tail(Node* &head)
{
    if(head==NULL)
    {
        cout<<"empty list"<<endl;
        return;
    }
    Node* curr=head;
    while(curr->next!=NULL)
    {
        curr=curr->next;

    }
    curr->prev->next=NULL;

    delete curr;
}
void delete_at_head(Node* &head){
    if(head==NULL){
        cout<<"Empty list"<<endl;
    }
   Node* temp = head;
        head = head->next;
        if(head != NULL) {
            head->prev = NULL;
        }
       delete temp;

}

int main() {
   Node* head=NULL;

   insert_at_tail(head,10);
   insert_at_tail(head,20);
   insert_at_tail(head,30);
   display(head);
   insert_at_head(head,50);
   insert_at_head(head,60);
    display(head);
   delete_at_tail(head);
   delete_at_head(head);
   display(head);



    return 0;
}
