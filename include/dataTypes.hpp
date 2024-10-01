#pragma once

//FILE: include/dataTypes.hpp   |   no corosponding .cpp file

/* This File is used for defining smaller library specific (helper) data types and typedef's
 * */

#ifndef DMATH_DATA_TYPES_HPP //include guard 
#define DMATH_DATA_TYPES_HPP
#include"macros.hpp"


NAMESPACESTART

typedef std::function<double(double)>                 singleVarFunction;
typedef std::function<double(double, double)>         doubleVarFunction;
typedef std::function<double(double, double, double)> tripleVarFunction;

typedef std::vector<double> doubleVector;


/*Calculating a mathmatical function is this library works by defining start and an end point 
  and calculating the value of a given function in specific small intervalls (resolution)
  and since passing all the data in a constructor or function will create big and ugly "oneliners"
  I build this struct wich encapsulates all data in one.
  The template needs a singleVarFunction, doubleVarFunction or tripleVarFunction
  wich are typedefs for specific std::function-objects.
  (defined in this file starting at line 11)
  */
template<typename Func, typename = typename std::enable_if<
    std::is_same<Func, singleVarFunction>::value ||
    std::is_same<Func, doubleVarFunction>::value ||
    std::is_same<Func, tripleVarFunction>::value
    >::type>
struct FunctionalParameters
{
    double functionStart;
    double functionEnd;
    double resolution;

    Func mainFunction;
};



//Since some mathmatical operations needs to claculate or return 2 values
//I made a Duo and trio struct the Duo behaves lake a std::pair<>
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
    virtual ~Duo();
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


/*
  I made a more powefull and complex vector-class in the file: 
  /include/mathVector.hpp file (Dmath::Vec2D, Dmath::Vec3D)
  but for more simple and minnimalistic purpuses I made simple vector-structs
  for int, float and a template one in 2D and 3D.
  Wich all just contain an X, Y (and Z) value and a constructor. 
*/
struct sVec2i{
  int X;
  int Y;
  sVec2i(int X, int Y) : X(X), Y(Y) {}
};

struct sVec2f{
  float X;
  float Y;
  sVec2f(float X, float Y) : X(X), Y(Y){}
};

template<typename math>
struct sVec2{
  math X;
  math Y;
  sVec2(math X, math Y) : X(X) , Y(Y){}
};

struct sVec3i{
  int X;
  int Y;
  int Z;

  sVec3i(int X, int Y, int Z) : X(X), Y(Y), Z(Z){}
};

struct sVec3f{
  float X;
  float Y;
  float Z;

  sVec3f(float X, float Y, float Z) : X(X), Y(Y), Z(Z) {}
};

template<typename math>
struct sVec3{
  math X;
  math Y; 
  math Z;
  sVec3(math X, math Y, math Z) : X(X), Y(Y), Z(Z){}
};
NAMESPACEEND //DMATH_DATA_TYPES_HPP


#endif