#pragma once

#ifndef DK_MACROS_HPP
    #define DK_MACROS_HPP

    #include <cmath>
    #include <vector>
    #include <functional>
    #include <stdint.h>


    #define STDRES 0.1f               //The standard resolution for more dimensional vector systems
    #define ZERO 0                    //Standard zero used as a constant for the startpoint in more dimensional vector systems
    #define PI 3.14159265358979323846
    #define EULER 2.718281828459045
    #define TWOPI 2 * PI
    #define FOUR_PI 2 * PI
    #define RAD_TO_DEG 180.f/PI
    #define DEG_TO_RAD PI/180.f
    #define CNULL ((void *)0)
    #define NAMESPACESTART namespace Dmath {
    #define NAMESPACEEND }

    #ifdef WORKING
        #include <iostream>
        #define LOGGER(info){ std::cout<< __FILE__ << " " << __LINE__ << " " << info <<std::endl;}
    #endif //WORKING
    



#endif //DK_MACROS_HPP