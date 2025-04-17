#pragma once 

#ifndef DMATH_TYPE_TRAIDS_HPP
#define DMATH_TYPE_TRAIDS_HPP

#include"../mathFunction.hpp"
#include"../complex.hpp"
NAMESPACESTART

template<typename T>
struct is_Complex{
    static constexpr bool value = std::is_same<t,Dmath::Complex>::value
};

NAMESPACEEND
#endif