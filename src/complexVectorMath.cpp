#include"../include/complexVectorMath.hpp"



//2D curves

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

Dmath::VectorCurve2D Dmath::VectorCurve2D::createCustomCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,float start,float stopp,float res ){
    return Dmath::VectorCurve2D(funcX,funcY,start,stopp,res);
}

Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromPoint(float point){
    if(point > this->curveStopp || point < this->curveStart){
        std::cerr << "Error index out of limit! \n Returning a null vector \n" ;
            return Dmath::Vec2D::zeroVector();
        }
    int foundPoint = static_cast<int> (point/this->resolution);
    Dmath::Vec2D outputVector = this->mainCurve[foundPoint];
    return outputVector;
}

Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromFunction(float vecX, float vecY){
    float xValue = this->mainXFunc(vecX);
    float yValue = this->mainYFunc(vecY);
    Dmath::Vec2D outputVector(xValue, yValue);
    return outputVector;
}







//3D curves
std::vector<Dmath::Vec3D> Dmath::VectorCurve3D::createVectorCurve(){
    std::vector<Dmath::Vec3D> output;
    for(double i = 0; i<this->numberOfElements; i+= this->resolution){
        output.push_back(Dmath::Vec3D(this->mainXFunc(i),this->mainYFunc(i),this->mainZFunc(i)));
    }
    return output;
}

Dmath::VectorCurve3D::VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc,std::function<float(float)> zFunc){
    this->mainXFunc = xFunc;
    this->mainYFunc = yFunc;
    this->mainZFunc = zFunc;
    this->numberOfElements = static_cast<int>((this->curveStopp - this->curveStart) / this->resolution);
    this->mainCurve = this->createVectorCurve();
}

Dmath::VectorCurve3D::VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc,std::function<float(float)> zFunc, float start, float stopp, float res){
    this->mainXFunc = xFunc;
    this->mainYFunc = yFunc;
    this->mainZFunc = zFunc;
    this->curveStart = start;
    this->curveStopp = stopp;
    this->resolution = res;
    this->numberOfElements = static_cast<int>((this->curveStopp - this->curveStart) / this->resolution);
    this->mainCurve = this->createVectorCurve();
}

Dmath::VectorCurve3D Dmath::VectorCurve3D::createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,std::function<float(float)> zFunc ){
    return Dmath::VectorCurve3D(funcX,funcY,zFunc);
}

Dmath::VectorCurve3D Dmath::VectorCurve3D::createCustomCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,std::function<float(float)> zFunc, float start,float stopp,float res ){
    return Dmath::VectorCurve3D(funcX,funcY,zFunc,start,stopp,res);
}

Dmath::Vec3D  Dmath::VectorCurve3D::getVectorFromFunction(float xValue, float yValue, float zValue){
    float vecX = this->mainXFunc(xValue);
    float vecY = this->mainYFunc(yValue);
    float vecZ = this->mainZFunc(zValue);
    Dmath::Vec3D outputVector(vecX,vecY,vecZ);
    return outputVector;
}

Dmath::Vec3D Dmath::VectorCurve3D::getVectorFromPoint(float point){
    if(point > this->curveStopp || point < this->curveStart){
        std::cerr << "Error index out of limit! \n Returning a null vector \n" ;
        return Dmath::Vec3D::zeroVector();
    }
    int foundPoint = static_cast<int> (point/this->resolution);
    Dmath::Vec3D outputVector = this->mainCurve[foundPoint];
    return outputVector;
}