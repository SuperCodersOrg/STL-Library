#pragma once

template<typename T>class LinkedList{

    private:
    struct Node{
        T data;
        Node*next;
        Node(T val);
    };
    public:
    Node*head=nullptr;
    Node*tail=nullptr;
    int size;
    LinkedList(); //Constructor
    ~LinkedList(); // Destructor
    LinkedList(const LinkedList& other); // Copy Constructor
    //LinkedList& operator=(const LinkedList& other); // Handling assignment operator
    void insertHead(T value); //Insert value at front
    void remove(T val); // Delete value
    void insert(int pos, T value); //Insert value at given position
    void append(T value); 
    void pop();//
    void reverse();
    bool exists(T value); //returns true of value exists otherwise returns false 
    int length(); //return size of the linkedlist
    void print(); // print the linkedlist


};

#include "LinkedList.tpp"
