#pragma once 

#ifndef DMATH_TYPE_TRAIDS_HPP
#define DMATH_TYPE_TRAIDS_HPP

#include"../mathFunction.hpp"
#include"../complex.hpp"
NAMESPACESTART

template<typename Com>
struct is_Complex{
    static constexpr bool value = std::is_same<Com,Dmath::Complex>::value
};


template<typename Func>
struct is_function_object{
    static constexpr bool value = std::is_same<Func ,Dmath::SingleVarFunction>::value || 
                                  std::is_same<Func ,Dmath::DoubleVarFunction>::value ||
                                  std::is_same<Func ,Dmath::TripleVarFunction>::value;
};


template<typename Vec2>
struct is_vec2{
    static constexpr bool value = std::is_same<Vec2, Dmath::Vec2D >::value ||
                                  std::is_same<Vec2, Dmath::sVec2f>::value ||
                                  std::is_same<Vec2, Dmath::sVec2i>::value;
};


template<typename Vec3>

struct is_vec3{
    static constexpr bool value = std::is_same<Vec2, Dmath::Vec3D >::value ||
                                  std::is_same<Vec2, Dmath::sVec3f>::value ||
                                  std::is_same<Vec2, Dmath::sVec3i>::value;
};




NAMESPACEEND
#endif