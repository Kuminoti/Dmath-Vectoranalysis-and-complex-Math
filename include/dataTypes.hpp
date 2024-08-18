#pragma once

#ifndef DMATH_DATA_TYPES_HPP
#define DMATH_DATA_TYPES_HPP

#include"macros.hpp"


NAMESPACESTART

template<typename d_type_one, typename d_type_two>
struct Duo {
    d_type_one one;
    d_type_two two;

    // Constructor using initializer list
    Duo(d_type_one one, d_type_two two)
        : one(one), two(two) {}

    // Default constructor
    Duo() : one(), two() {}

    template<typename T = d_type_one, typename std::enable_if<std::is_same<T, d_type_two>::value, int>::type = 0>
    constexpr void swap() {
        d_type_one val = this->two;
        this->two = this->one;
        this->one = val;
    }
    
};


template<typename d_type_one, typename d_type_two, typename d_type_three>
struct Trio{

  d_type_one   one;
  d_type_two   two;
  d_type_three three;

  Trio(d_type_one one, d_type_two two, d_type_three three) 
      : one(one), two(two), three(three) {}


  Trio(): one(), two(), three() {}

  template<typename T = d_type_one, typename std::enable_if<std::is_same<T,d_type_two>::value, int>::type = 0>
  constexpr void swapOneAndTwo(){
    d_type_one val = this->two;
    this->two = this->one;
    this->one = val;
  }
  template<typename T = d_type_one, typename std::enable_if<std::is_same<T,d_type_three>::value, int>::type = 0>
  constexpr void swapOneAndThree(){
    d_type_one val = this->three;
    this->three = this->one;
    this->one = val;
  }

  template<typename T = d_type_two, typename std::enable_if<std::is_same<T,d_type_three>::value, int>::type = 0>
  constexpr void swapTwoAndThree(){
    d_type_three val = this->three;
    this->three = this->two;
    this->two = val;
  }
};






NAMESPACEEND


#endif