//
//  main.cpp
//  NumAsList
//
//  Created by Victor Rosu on 7/11/15.
//  Copyright (c) 2015 Victor Rosu. All rights reserved.
//

#include <iostream>
#include <time.h>

template<typename T>
class Node
{
public:
    Node(const T value) : _pNext(nullptr), _value(value) {
    }
    const T GetValue() const {
        return _value;
    }
    Node* GetNext() const {
        return _pNext;
    }
    void SetNext(Node* n) {
        _pNext = n;
    }
private:
    Node() {}
    Node*       _pNext;
    const T     _value;
};

template<typename T>
class List
{
public:
    List() : _pHead(nullptr), _count(0) {
    
    }
    
    void AddNew(const T value) {
        Node<T>* p = new Node<T>(value);
        if(_pHead == nullptr) {
            _pHead = p;
        } else {
            p->SetNext(_pHead);
            _pHead = p;
        }
        _count++;
    }
    
    void Remove() {
        Node<T>* p = _pHead;
        if(p != nullptr) {
            _pHead = p->GetNext();
            delete p;
            _count--;
        }
    }
    
    bool IsEmpty() {
        return _pHead == nullptr;
    }
    
    template<typename L>
    void ProcessValues(L lambda) {
        Node<T>* p = _pHead;
        while(p != nullptr) {
            lambda(p->GetValue());
            p = p->GetNext();
        }
    }
    
private:
    Node<T>* _pHead;
    size_t   _count;
};


template<typename T>
void testRandomNumberToList(T printItemAction)
{
    int numberLengthInBytes = 8;
    // take a number and represent it as hex in a linked list
    time_t t;
    time(&t);
    srand(static_cast<int>(t));
    int number = rand(); // % 0xffff;
    std::cout << "Number is: 0x" << std::hex << number << std::endl;
    int shift  = 0;
    List<char> nlist;
    while(true) {
        int value = (number >> (shift*4))& 0xf;
        if(value > 9) {
            value = 'a' + value-10;
        } else {
            value = '0' + value;
        }
        nlist.AddNew(value);
        shift++;
        if(shift == numberLengthInBytes) {
            break;
        }
    }
    std::cout << "List representation: " << std::endl << "0x" << std::endl;
    nlist.ProcessValues(printItemAction);
    
}

int main(int argc, const char * argv[]) {

    auto printItem = [] (char v) {
        std::cout << v << std::endl;
    };

    testRandomNumberToList(printItem);
    
    return 0;
}


