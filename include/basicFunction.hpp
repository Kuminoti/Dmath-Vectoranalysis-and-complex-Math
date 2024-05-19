#pragma once
#ifndef BASICFUNCTIONS_H
#define BASICFUNCTIONS_H

#include"systems.hpp"

NAMESPACESTART
class BasicFunction {    
  protected: // protected members:
    
    std::function<double(double)> mainFunc;
    std::vector<double> fX;

    double systemStart = ZERO;
    double systemStopp = TWOPI;
    double resolution  = STDRES;

    size_t numberOfElements;

  private: // private methods:
    virtual void createCurve();

    BasicFunction(std::function<double(double)> mainFunc);
    BasicFunction(std::function<double(double)> mainFunc, double resolution); //Constructor for polarfunctions
    BasicFunction(std::function<double(double)> mainFunc, double systemStart,double systemStopp, double resolution);
  public:

    static BasicFunction createBasicFunctionGraph(std::function<double(double)> mainFunc){
      return BasicFunction(mainFunc);
    }


    static BasicFunction createCustomFunctionGraph(std::function<double(double)> mainFunc, double systemStart, double systemStopp, double resolution){
      return BasicFunction(mainFunc,systemStart,systemStopp,resolution);
    }

    // f(phi) =  
    static BasicFunction PolarFunction(std::function<double(double)> mainFunc, double resolution){
        return BasicFunction(mainFunc,resolution);
    }

    //Returns the number of zero points
    size_t numberOfZeroPoints();
  
    //Returns the area between the X-achsis and the graph
    double areaXachsis(double start, double stopp);
    double getSlopeAt(double Value){
        double result = 0;
        double pointXZero = Value - 0.001;
        double xOneValue  = this->mainFunc(Value);
        double xZeroValue = this->mainFunc(pointXZero);

        double resultOne = xOneValue - xZeroValue;
        double resultTwo = Value - pointXZero;

        result = (resultOne/resultTwo);
        return result;
    }


    //Getters:
    inline double getResolution() {return this->resolution;}
    inline double getSystemStart(){return this->systemStart;}
    inline double getSystemStopp(){return this->systemStopp;}
    inline double getNumberOfElements(){return this->numberOfElements;}

    //Maximum and minimum
    double getMaximum();
    double getMinimum();

};




NAMESPACEEND

#endif // Include guard