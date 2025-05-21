#pragma once 

#ifndef DMATH_LIST_HPP
#define DMATH_LIST_HPP

#include"../macros.hpp"
#include<iostream>

NAMESPACESTART
template<typename dType>
class Node {
private:
   
    int ID;
    dType data;

public:
    Node* right = nullptr;
    Node* left  = nullptr;
    Node(dType Data, int ID) : data(Data), ID(ID) {}

    dType findFromID(int searchID) {
        if (searchID > this->ID) {
            return (right != nullptr) ? right->findFromID(searchID) : throw std::runtime_error("ID nicht gefunden");
        }
        else if (searchID < this->ID) {
            return (left  != nullptr) ? left ->findFromID(searchID) : throw std::runtime_error("ID nicht gefunden");
        }
        return this->data;
    }

    void addright(dType newData, int newID) {
        if (right == nullptr) {
            right = new Node<dType>(newData, newID);
        }
        else {
            right->addright(newData, newID);
        }
    }

    void addleft (dType newData, int newID) {
        if (left  == nullptr) {
            left  = new Node<dType>(newData, newID);
        }
        else {
            left ->addleft (newData, newID);
        }
    }
};

template<class dType>
class List {
private:
    size_t numberOfElements = 0;
    size_t elementsright = 0;
    size_t elementsleft  = 0;
    

public:
Node<dType>* headNode = nullptr;
    List(dType input) {
        this->numberOfElements = 1;
        this->headNode = new Node<dType>(input, 0);
    }

    void pushright(dType data) {
        this->elementsright++;
        this->numberOfElements++;
        this->headNode->addright(data, elementsright);
    }

    void pushleft (dType data) {
        this->elementsleft ++;
        this->numberOfElements++;
        this->headNode->addleft (data, -elementsleft );
    }

    dType getElementFromID(int ID) {
        return this->headNode->findFromID(ID);
    }

    size_t size() { return this->numberOfElements; }
    size_t leftElements() { return this->elementsleft ; }
    size_t rightElements() { return this->elementsright; }
};

NAMESPACEEND
#endif