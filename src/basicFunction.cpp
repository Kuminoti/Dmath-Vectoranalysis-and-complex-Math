#include"../include/basicFunction.hpp"
#include"../include/macros.hpp"
#include<iostream>

void Dmath::BasicFunction::createCurve(){

    const double start = this->systemStart;
    const double stopp = this->systemStopp;
    const double res   = this->resolution;

    for(double i = start; i < systemStopp; i+=res){
        double currentResult = this->mainFunc(i);
        std::cout << currentResult << std::endl;
        this->fX.push_back(currentResult);
    }
}

Dmath::BasicFunction::BasicFunction(Dmath::singleVarFunction mainFunc){
    
    this->numberOfElements = static_cast<size_t>((this->systemStopp - this->systemStart)/this->resolution);
    this->createCurve();
}

Dmath::BasicFunction::BasicFunction(Dmath::singleVarFunction mainFunc, double systemStart,double systemStopp, double resolution){
    std::cout <<"in constructor" << std::endl;
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

double Dmath::BasicFunction::operator[](size_t index){
    if(index > this->numberOfElements || index < 0){
        
        return 0;
    }

    return this->fX[index];
}

double Dmath::BasicFunction::getSlopeAt(double Value) {
    double result = 0;
    double pointXZero = Value - 0.000001;
    
    double xOneValue = this->mainFunc(Value);
    double xZeroValue = this->mainFunc(pointXZero);

    double resultOne = xOneValue - xZeroValue;
    double resultTwo = Value - pointXZero;

    result = (resultOne / resultTwo);
    return result;
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

bool Dmath::BasicFunction::exsitsIn(double value){
    bool result = false;
    const double num = this->numberOfElements;
    for(size_t i = 0; i < num; i++){
        double CurrentValue = this->fX[i];
        if(value == CurrentValue){  
            result = true;
        }
    }
    return result;
}


double Dmath::BasicFunction::getLength(){
    // const double itt = this->fX.size();

    // bool firstIteration = false;
    // double lenght = 0;
    // for(size_t i = 1; i < itt; i++){
        
    //     lenght += this->mathHelper.pyth(i,);

        
    // }
}