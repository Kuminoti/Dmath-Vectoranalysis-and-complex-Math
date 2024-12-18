#pragma once

#ifndef D_FUNCTIONS_HPP
#define D_FUNCTIONS_HPP

#include"dataTypes.hpp" 


NAMESPACESTART



//Mathmatical operations:

 auto sec  = [](double x) ->double {return 1/std::cos(x); };
 auto cec  = [](double x) ->double {return 1/std::sin(x); };
 auto cot  = [](double x) ->double {return 1/std::tan(x); };
 auto cosh = [](double x) ->double { return (std::exp(x) + std::exp(-x)) / 2; };    

auto greaterThan = [](double greater,double than)->bool {
    if(greater > than){
        return true;
    }
    return false;
};

auto smallerThan = [](double smaller, double than)->bool {
    if(smaller < than){
        return true;
    }
    return false;
};



auto sleep = [](size_t millis) ->void { std::this_thread::sleep_for(std::chrono::milliseconds(millis));};

auto sleepMicros = [](size_t micros) -> void { std::this_thread::sleep_for(std::chrono::microseconds(micros)); };

SHARED_LIB double pyth2(double a, double b);

SHARED_LIB double pyth3(double x, double y, double z);


    //simples summenzeichen
SHARED_LIB double SigmaAdd(size_t start, size_t end);

    //Summenzeichen mit term. singleVarFunction = lambda (quasi)
SHARED_LIB double sigmaAddFunc(size_t start, size_t end, Dmath::singleVarFunction mainFunc);


SHARED_LIB size_t numberOfElements(Dmath::Parameters params);


SHARED_LIB bool checkParams(Dmath::Parameters params);


SHARED_LIB double kelvinToCelsius(double Kelvin);

SHARED_LIB double CelsiusToKelvin(double celsius);

SHARED_LIB double fahrenheitToCelsius(double fahrenheit);

SHARED_LIB double celsiusToFahrenheit(double celsius);


SHARED_LIB double radiansToDegrees(double radiants);

SHARED_LIB double degreesToRadians(double degrees);

SHARED_LIB double fDotPruduct(Dmath::sVec2f vecOne, Dmath::sVec2f);

SHARED_LIB size_t iDotPruduct(Dmath::sVec2i vecOne, Dmath::sVec2i vecTwo);

SHARED_LIB double fDotPruduct(Dmath::sVec3f vecOne, Dmath::sVec3f vecTwo);

SHARED_LIB size_t binomialCoefficient(size_t n, size_t k);

SHARED_LIB double gammaFunction(double x);

SHARED_LIB double psiFunction(double x);

SHARED_LIB double average(std::vector<double> input);

SHARED_LIB int digitSum(int number);

NAMESPACEEND

#endif 