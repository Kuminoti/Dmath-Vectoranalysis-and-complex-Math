#include"../include/basicFunction.hpp"


void Dmath::BasicFunction::createCurve(){
    for(double i = 0; i < this->numberOfElements; i+=this->resolution){
        this->fX.push_back(mainFunc(i));
    }
}

Dmath::BasicFunction::BasicFunction(std::function<double(double)> mainFunc){
    this->numberOfElements = static_cast<size_t>((this->systemStopp - this->systemStart)/this->resolution);
    this->createCurve();
}

Dmath::BasicFunction::BasicFunction(std::function<double(double)> mainFunc, double systemStart,double systemStopp, double resolution){
    this->systemStart = systemStart;
    this->systemStopp = systemStopp;
    this->resolution  = resolution;
    this->numberOfElements = static_cast<size_t>((this->systemStopp - this->systemStart)/this->resolution);
    this->createCurve();
}

size_t Dmath::BasicFunction::numberOfZeroPoints(){
    size_t zeroPoints = 0;
    for(size_t i = 0; i< this->fX.size(); i++){
    if(this->fX[i] == 0){
        zeroPoints++;
    }
    }
    return zeroPoints;
}

double Dmath::BasicFunction::areaXachsis(double start, double stopp){
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



double Dmath::BasicFunction::getMaximum(){
    double maximum = this->fX[0];
    for (size_t i = 0; i < this->fX.size(); i++){
        if(this->fX[i] > maximum){
            maximum = this->fX[i];
        }
    }
    return maximum;
}

double Dmath::BasicFunction::getMinimum(){
    double minimum = this->fX[0];
    for (size_t i = 0; i < this->fX.size(); i++){
      if(this->fX[i] < minimum){
          minimum = this->fX[i];
       }
    }
    return minimum;
 }