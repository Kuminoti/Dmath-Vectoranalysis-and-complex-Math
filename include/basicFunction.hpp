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
    virtual void createCurve(){
      for(double i = 0; i < this->numberOfElements; i+=this->resolution){
        this->fX.push_back(mainFunc(i));
      }
    }

    BasicFunction(std::function<double(double)> mainFunc){
      this->numberOfElements = static_cast<size_t>((this->systemStopp - this->systemStart)/this->resolution);
      this->createCurve();
    }

    BasicFunction(std::function<double(double)> mainFunc, double systemStart,double systemStopp, double resolution){
      this->systemStart = systemStart;
      this->systemStopp = systemStopp;
      this->resolution  = resolution;
      this->numberOfElements = static_cast<size_t>((this->systemStopp - this->systemStart)/this->resolution);
      this->createCurve();
    }
  public:

    static BasicFunction createBasicFunctionGraph(std::function<double(double)> mainFunc){
      return BasicFunction(mainFunc);
    }


    static BasicFunction createCustomFunctionGraph(std::function<double(double)> mainFunc, double systemStart, double systemStopp, double resolution){
      return BasicFunction(mainFunc,systemStart,systemStopp,resolution);
    }

    //Returns the number of zero points
    size_t numberOfZeroPoints(){
      size_t zeroPoints = 0;
      for(size_t i = 0; i< this->fX.size(); i++){
        if(this->fX[i] == 0){
          zeroPoints++;
        }
      }
      return zeroPoints;
    }
  
  //Returns the area between the X-achsis and the graph
  double areaXachsis(double start, double stopp){
    double integrationResolution = 0.0001;
    size_t numberOfLoops = static_cast<size_t>((stopp - start)/integrationResolution);
    double area = 0;
    for(size_t i = 0; i < numberOfLoops; i+=integrationResolution){
      //Quasi ein rechteck erzeugen aus dem funktionswert und der auflösung und diese dann aufsummieren.
      //Abs: falls eine kurve ins negative geht
      area+= std::abs(this->mainFunc(i) * integrationResolution);
    }
    return area;
  }

  //Getters:
  inline double getResolution() {return this->resolution;}
  inline double getSystemStart(){return this->systemStart;}
  inline double getSystemStopp(){return this->systemStopp;}
  inline double getNumberOfElements(){return this->numberOfElements;}

  //Returns the largest value of the graph
  double getMaximum(){
    double maximum = this->fX[0];
    for (size_t i = 0; i < this->fX.size(); i++){
      if(this->fX[i] > maximum){
        maximum = this->fX[i];
      }
    }
    return maximum;
  }

  //Returns the smallest value of the graph
  double getMinimum(){
    double minimum = this->fX[0];
    for (size_t i = 0; i < this->fX.size(); i++){
      if(this->fX[i] < minimum){
        minimum = this->fX[i];
      }
    }
    return minimum;
  }

};




NAMESPACEEND

#endif // Include guard