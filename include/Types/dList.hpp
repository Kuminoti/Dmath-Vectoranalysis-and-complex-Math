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
 Node* front = nullptr;
    Node* back = nullptr;
    Node(dType Data, int ID) : data(Data), ID(ID) {}

    dType findFromID(int searchID) {
        if (searchID > this->ID) {
            return (front != nullptr) ? front->findFromID(searchID) : throw std::runtime_error("ID nicht gefunden");
        }
        else if (searchID < this->ID) {
            return (back != nullptr) ? back->findFromID(searchID) : throw std::runtime_error("ID nicht gefunden");
        }
        return this->data;
    }

    void addFront(dType newData, int newID) {
        if (front == nullptr) {
            front = new Node<dType>(newData, newID);
        }
        else {
            front->addFront(newData, newID);
        }
    }

    void addBack(dType newData, int newID) {
        if (back == nullptr) {
            back = new Node<dType>(newData, newID);
        }
        else {
            back->addBack(newData, newID);
        }
    }
};

template<class dType>
class List {
private:
    size_t numberOfElements = 0;
    size_t elementsFront = 0;
    size_t elementsBack = 0;
    

public:
Node<dType>* headNode = nullptr;
    List(dType input) {
        this->numberOfElements = 1;
        this->headNode = new Node<dType>(input, 0);
    }

    void pushFront(dType data) {
        this->elementsFront++;
        this->numberOfElements++;
        this->headNode->addFront(data, elementsFront);
    }

    void pushBack(dType data) {
        this->elementsBack++;
        this->numberOfElements++;
        this->headNode->addBack(data, -elementsBack);
    }

    dType getElementFromID(int ID) {
        return this->headNode->findFromID(ID);
    }

    size_t size() { return this->numberOfElements; }
    size_t backElements() { return this->elementsBack; }
    size_t frontElements() { return this->elementsFront; }
};

NAMESPACEEND
#endif