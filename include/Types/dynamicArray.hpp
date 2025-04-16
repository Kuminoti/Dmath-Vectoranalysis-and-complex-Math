#pragma once



#ifndef DMATH_DYNAMIC_ARRAY_HPP
#define DMATH_DYNAMIC_ARRAY_HPP

#include"../dataTypes.hpp"

NAMESPACESTART

template<class math>

class DArray{

    math* arr;
    size_t elements = 0;
    size_t capacity = 10;


public:
    DArray() = default;


    DArray(){
        this->arr = new math[capacity] ;
    }
    ~DArray(){
        delete[] this->arr;
        this->arr = nullptr;
    }

    DArray(size_t numberOfElements){
        this->arr = new math[numberOfElements];
        this->elements = numberOfElements;
    }

    void push_back(math element) {
        if (elements == capacity) {
            capacity *= 2;
            math* newArray = new math[capacity];
            for (size_t i = 0; i < elements; ++i) {
                newArray[i] = arr[i];
            }
            delete[] arr;
            arr = newArray;
        }

        // Add Element 
        arr[elements] = element;
        ++elements;
    }

    // Remove element 
    void pop_back() {
        if (elements > 0) {
            --elements;
        }
    }


    size_t size(){
        return this->elements;
    }

    math operator[](size_t index){
        if(index > elements){
            return 0;
        }
        return this->arr[index];
    }

};

NAMESPACEEND

#endif //DMATH_DYNAMIC_ARRAY_HPP