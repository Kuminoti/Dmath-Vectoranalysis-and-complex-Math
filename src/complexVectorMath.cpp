#include"../include/complexVectorMath.hpp"


std::vector<Dmath::Vec2D> Dmath::VectorCurve2D::createVectorCurve(){
    std::vector<Dmath::Vec2D> output;
    for(double i = 0; i<this->numberOfElements; i+= resolution){
        output.push_back(Dmath::Vec2D(this->mainXFunc(i),mainYFunc(i)));
    }
    return output;
}

Dmath::VectorCurve2D::VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc){
    this->mainXFunc = xFunc;
    this->mainYFunc = yFunc;
    this->numberOfElements = static_cast<int>((this->curveStopp - this->curveStart) / this->resolution);
    this->mainCurve = this->createVectorCurve();
}

Dmath::VectorCurve2D::VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res){
    this->mainXFunc = xFunc;
    this->mainYFunc = yFunc;
    this->curveStart = start;
    this->curveStopp = stopp;
    this->resolution = res;
    this->numberOfElements = static_cast<int>((this->curveStopp - this->curveStart) / this->resolution);
    this->mainCurve = this->createVectorCurve();
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY ){
    return Dmath::VectorCurve2D(funcX,funcY);
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,float start,float stopp,float res ){
    return Dmath::VectorCurve2D(funcX,funcY,start,stopp,res);
}