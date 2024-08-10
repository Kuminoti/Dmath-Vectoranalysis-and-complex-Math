#pragma once

#ifndef DK_MACROS_HPP
    #define DK_MACROS_HPP

    #include <cmath>
    #include <vector>
    #include <functional>
    #include <stdint.h>
    #include <algorithm>
    #include <thread>
    #include <chrono>
    #include <type_traits>


    #define ZERO_KELVINK -273.17
    #define ZERO_KELVINC  273.17
    #define ANALYSIS_RES 0.0001          //the standard resolution for clculating the area or slope aof a function
    #define STDRES 0.05f                //The standard resolution for more dimensional vector systems
    #define ZERO 0                     //Standard zero used as a constant for the startpoint in more dimensional vector systems
    #define PI 3.14159265358979323846
    #define EULER 2.718281828459045
    #define TWOPI 2 * PI
    #define FOUR_PI 2 * PI
    #define RAD_TO_DEG 180.f/PI
    #define DEG_TO_RAD PI/180.f
    #define CNULL ((void *)0)

    #define NAMESPACETEST       namespace Testing {
    #define NAMESPACEWORKING    namespace Working{
    #define NAMESPACESTART      namespace Dmath {
    #define NAMESPACEEND        }

    


    #define  byte uint8_t
    #define CARTESIAN_IS_3D_STANDARD
    #define CARTESIAN_IS_2D_STANDARD
 #if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD)) &&                              \
        defined(CARTESIAN_IS_3D_STANDARD)
        #warning "Warning: More than one system is defined!"
        #define COORDINATES_READY
        #undef CARTESIAN_IS_STANDARD

        #ifdef SPHERE_IS_STANDARD
            #undef CYLINDER_IS_STANDARD
            #warning "Sphere system will be standart!"
            #define COORDINATES_READY
        #endif
        
        #else
        #define COORDINATES_READY
        

    #endif



    #if (defined(CARTESIAN_IS_2D_STANDARD) && defined(POLAR_IS_STANDARD))
        #undef POLAR_IS_STANDARD
#
    #elif defined(CARTESIAN_IS_2D_STANDARD)
        #define COORDINATES_READY

    #endif //defined(CARTESIAN_IS_2D_STANDARD) && defined(POLAR_IS_STANDARD)

    #if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD) ||                               \
        defined(CARTESIAN_IS_3D_STANDARD) || defined(POLAR_IS_STANDARD) ||                            \
        defined(CARTESIAN_IS_2D_STANDARD))
        #define COORDINATES_READY
        #else

    #endif

    #ifdef WORKING
        #warning "DEBUGMODE"
        #ifdef RELEASE
            #undef RELEASE
        #endif

        #include <iostream>
        #include <fstream>

        #ifdef DEBUG_TOOLS
            #define LOGGER(info){ std::cout<< __FILE__ << " " << __LINE__ << " " << info <<std::endl;}
        #endif //DEBUG_TOOLS

      
     
    #endif //WORKING
    
    
  
//Choose your prefered angle unit with (un)commenting the fitting macro
#define STANDARD_ANGLE_UNIT_DEG
//#define STANDARD_ANGLE_UNIT_RAD
#if(defined(STANDARD_ANGLE_UNIT_DEG) || defined(STANDARD_ANGLE_UNIT_RAD))
#define ANGLE_UNIT_SET
#else
#if(defined(STANDARD_ANGLE_UNIT_DEG) && defined(STANDARD_ANGLE_UNIT_RAD))
#warning "Both angle units are set standard will be radiants!"
#undef STANDARD_ANGLE_UNIT_DEG
#define ANGLE_UNIT_SET
#endif
#endif

//Uncomment to choose your standard coordinate system

#define CARTESIAN_IS_2D_STANDARD   // Cartesian system: X,Y
//#define POLAR_IS_STANDARD        //Polar system: Radius, phi

#define CARTESIAN_IS_3D_STANDARD   //Cartesian system: X,Y,Z
//#define SPHERE_IS_STANDARD       // Sphere system: Radius, phi, phi
//#define CYLINDER_IS_STANDARD     //Cylinder system: Radius, phi, height

#if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD)) &&                              \
    defined(CARTESIAN_IS_3D_STANDARD)
#warning "Warning: More than one system is defined!"
#undef CARTESIAN_IS_STANDARD
#ifdef SPHERE_IS_STANDARD
#undef CYLINDER_IS_STANDARD
#warning "Sphere system will be standart!"
#endif
#warning "Cylinder system will be standart!"

#endif

#ifdef POLAR_IS_STANDARD
#ifdef CARTESIAN_IS_2D_STANDARD
#undef CARTESIAN_IS_2D_STANDARD
#warning                                                                                           \
    "Warning: You defined polar coordinates as standard and cartesian as 2D standard. Polar will be standard."
#endif
#endif

#if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD) ||                               \
     defined(CARTESIAN_IS_3D_STANDARD) || defined(POLAR_IS_STANDARD) ||                            \
     defined(CARTESIAN_IS_2D_STANDARD))
#define SYSTEM_IS_SET
#else
#error "FATAL ERROR NO SYSTEM SET"
#endif

#if (defined(SYSTEM_IS_SET) && defined(ANGLE_UNIT_SET))
#define SYSTEM_READY

#endif


   
  


#endif //DK_MACROS_HPP