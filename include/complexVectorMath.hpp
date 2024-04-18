#ifndef COMPLEXVECTORMATH_HPP
#define COMPLEXVECTORMATH_HPP

#include<functional>
#include<algorithm>
#include"mathVector.hpp"


NAMESPACESTART

class VectorCurve2D {
  protected:
    std::vector<Dmath::Vec2D> mainCurve;

    std::function<float(float)> mainXFunc;
    std::function<float(float)> mainYFunc;

    float resolution = 0.1;
    float curveStart = 0;
    float curveStopp = TWOPI;

    int numberOfElements;

    std::vector<Dmath::Vec2D> createVectorCurve();

    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc);
    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res);

  public:
    static VectorCurve2D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY );
    static VectorCurve2D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,float start,float stopp,float res );

    Dmath::Vec2D getVectorFromFunction(float vecX, float vecY){
        float xValue = this->mainXFunc(vecX);
        float yValue = this->mainYFunc(vecY);
        Dmath::Vec2D outputVector(xValue, yValue);
        return outputVector;
    }

    Dmath::Vec2D getVectorFromPoint(float point){
        if(point > curveStopp || point < curveStart){
            std::cerr << "Error index out of limit! \n Returning a null vector \n" ;
            return Dmath::Vec2D::zeroVector();
        }
        int foundPoint = static_cast<int> (point/resolution);
        Dmath::Vec2D outputVector = mainCurve[foundPoint];
        return outputVector;
    }
};



NAMESPACEEND //Dmath namespace
#endif