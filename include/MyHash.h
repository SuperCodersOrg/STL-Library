#pragma once

#include <string>
#include <sstream>
#include <cstddef>
#include <iostream>

template<typename T>
struct MyHash {

    size_t operator()(const T&) const {

        static_assert(sizeof(T) == 0,
            "No hash function defined for this type. "
            "Please specialize MyHash<T>.");

        return 0;
    }
};



/* int specialization */
template<>
struct MyHash<int> {
    
        size_t operator()(int key) const {
            return static_cast<size_t>(key)*2654435761u;
        }    
    };    
    
    
    /* long long specialization */
    template<>
    struct MyHash<long long> {
        
        size_t operator()(long long key) const {
            return static_cast<size_t>(key)*2654435761u;
        }
    };
    
    /* char specialization */
    template<>
    struct MyHash<char> {
        
        size_t operator()(char ch) const {
            return static_cast<size_t>(ch)*2654435761u;
        }
    };
    
    /* string specialization */
    template<>
    struct MyHash<std::string> {
        
        size_t operator()(const std::string& str) const {
            
            size_t hashValue = 0;
            
            for(char ch : str) {
                hashValue = hashValue * 31 + static_cast<unsigned char>(ch);
            }
            
            return hashValue*2654435761u;
        }
    };
    
    /* const char* specialization */
    template<>
    struct MyHash<const char*> {
        
        size_t operator()(const char* str) const {
            
            size_t hashValue = 0;
            
            while(*str) {
                hashValue = hashValue * 31 +
                            static_cast<unsigned char>(*str);
                ++str;
            }
    
            return hashValue * 2654435761u;
        }
    };
    
    
    // Hash Code for linkedlist
    template<typename T>
    struct MyHash<LinkedList<T>> {
    
        size_t operator()(const LinkedList<T>& list) const {
            
            size_t hashValue = 0;
            
            typename LinkedList<T>::Node* curr = list.head;
            
            while (curr) {
                hashValue = hashValue * 31 + MyHash<T>{}(curr->data);
                curr = curr->next;
            }
            
            return hashValue * 2654435761u;
        }
        
    };
    
    // Hash Code for DynamicArray
    template<typename T>
    struct MyHash<DynamicArray<T>> {
        
        size_t operator()(const DynamicArray<T>& arr) const {
            
            size_t hashValue=0;
            
            for(int i=0;i<arr.size();i++){
                hashValue=hashValue * 31 + MyHash<T>{}(arr[i]);
                
            }
            
            return hashValue * 2654435761u;
        }
        
        
    };
    
    
    