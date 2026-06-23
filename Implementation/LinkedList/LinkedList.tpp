#include "LinkedList.h"
#include <iostream>





// LinkedList Constructor
template<typename T> LinkedList<T> :: LinkedList(){
    head=nullptr;
    tail=nullptr;
    size=0;
}

// LinkedList Copy Conststructor
template<typename T>LinkedList<T> :: LinkedList(const LinkedList&others){
    head=nullptr;
    tail=nullptr;
    size=0;
    Node*cur=others.head;
    
    while(cur){
        this->append(cur->data);
        cur=cur->next;
    }
}


// LinkedList Destructor
template<typename T> LinkedList<T> :: ~LinkedList(){
    Node* temp=head;
    while(head){
        head=head->next;
        delete temp;
        temp=head;
    }
    head=nullptr;
    tail=nullptr;
    size=0;
}


//Node Constructor
template<typename T>
LinkedList<T> :: Node :: Node(T val){
        data=val;
        next=nullptr;
};

// Append
template<typename T>void 
LinkedList<T> :: append(T val){
    Node* node = new Node(val);
        if(head==nullptr){
            head=node;
            tail=node;
        }
        else{
            tail->next=node;
            tail=node;
        }
        size++;

};

// pop()
template<typename T> void 
LinkedList<T> :: pop(){
    if(size==0) return;
    Node*temp=head;
    size--;
    if(head->next==nullptr){
        head=nullptr;
        tail=nullptr;
        delete temp;
        return;
    }

    while(temp->next!=tail){
        temp=temp->next;
    }
    temp->next=nullptr;
    delete tail;
    tail=temp;

};

//InsertHead
template <typename T> void 
LinkedList<T> :: insertHead(T val){
    Node*node=new Node(val);
    size++;
    if(head==nullptr){
        head=node;
        tail=head;
        return;
    }
    node->next=head;
    head=node;
};

// insert at random pos
template<typename T> 
// pos between 1 to size
void LinkedList<T> :: insert(int pos,T val){

    // pos>size || pos<1
    if(size+1<pos || pos<1){ 
        std::cout<<"Invalid Size";
        return;
    }
    // Last insertion
    if(size+1==pos){
        append(val);
        return;
    }
    
    // Insert at head (or Head is nullptr)
    if(pos==1 ){
        insertHead(val);
        return;
    }

    // Insert in Between Head and Tail
    Node * node= new Node(val);
    size++;
    Node*prev=head;
    for(int i=0;i<pos-2;i++){
        prev=prev->next;
    }
    node->next=prev->next;
    prev->next=node;

};


//print()
template<typename T> void 
LinkedList<T> :: print(){
    if(!size){
        std::cout<<"No linked List\n";
        return;
    }
    Node*node=head;
    while(node){
        std::cout<<node->data<<" ";
        node=node->next;
    }
    std::cout<<std::endl;
};

//length()
template<typename T>
int LinkedList<T> :: length(){
    return size;
}


//exists()
template<typename T> bool
LinkedList<T>::exists(T val){
    Node*temp=head;
    while(temp){
        if(temp->data==val)return true;
        temp=temp->next;
    }
    return false;
}

//reverse()
template <typename T> void
LinkedList<T>::reverse(){

    Node* prev=nullptr;
    Node* cur=head;
    tail=head;

    while(cur){
        Node*next=cur->next;
        cur->next=prev;
        prev=cur;
        cur=next;
    }
    head=prev;

    

}

// remove by value
template<typename T>void
LinkedList<T>::remove(T val){
    Node*prev=head;
    Node*nxt=head;

    while(nxt){
        if(nxt->data==val)break;
        prev=nxt;
        nxt=nxt->next;
    }

    if(nxt==nullptr){
        std::cout<<"Data not Found!";
        return;
    }
    
    if(nxt==tail){
        pop();
        return;
    }

    size--;

    if(nxt==prev){

        if(head==tail){
            tail=nullptr;
        }
        head=nxt->next;
        delete nxt;
        return;
    }

    prev->next=nxt->next;
    delete nxt;

}