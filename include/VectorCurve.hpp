#pragma once

#ifndef COMPLEXVECTORMATH_HPP
#define COMPLEXVECTORMATH_HPP

#include<functional>
#include<algorithm>
#include"mathVector.hpp"

NAMESPACESTART

class VectorCurve2D : public VectorAnalysis2D{
  private:
    
    std::vector<Dmath::Vec2D> createVectorialCurve();

  protected:
    std::vector<Dmath::Vec2D> mainCurve;

    //Constructos for sinmple parametric Vector curves (tested)
    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc);
    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res);

  public:
    //Create a parametric Vector curve (tested)
    static VectorCurve2D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY );
    static VectorCurve2D createCustomCurve(std::function<float(float)> funcX, std::function<float(float)> funcY, float start, float stopp, float res );
    
    //Getters (tested)
    Dmath::Vec2D getVectorFromFunction(float vecX, float vecY);
    Dmath::Vec2D getVectorFromPoint(float point);
    Dmath::Vec2D tangentVector(float t);

    // NEEDS TESTING


    //operator overloading:
    inline VectorCurve2D operator+ (VectorCurve2D curve){ return addCurve(curve);      }
    inline VectorCurve2D operator- (VectorCurve2D curve){ return subtractCurve(curve); }
    
    float curveLenght();
    float calculateSlopeOnPoint(float t);
    float dotProductVectorCurve(Dmath::VectorCurve2D vec);
    float calculateAreaXAchsis(float tStart, float tEnd);


    
    //VectorCurve2D curveFusion(){}
    VectorCurve2D addCurve(VectorCurve2D curve);
    VectorCurve2D subtractCurve(VectorCurve2D curve);

    // NEEDS TESTING
    float maximumY();
    float minimumY();
    float MaximumX();
    float minimumX();

    size_t numberOfZeroPoints();
};
    

class VectorCurve3D : public VectorAnalysis3D{
  private:
    std::vector<Dmath::Vec3D> mainCurve;
    std::vector<Dmath::Vec3D> createVectorialCurve();
    VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, std::function<float(float)> zFunc);
    VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, std::function<float(float)> zFunc, float start, float stopp, float res);
  public:
    static VectorCurve3D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY, std::function<float(float)> funcZ );
    static VectorCurve3D createCustomCurve  (std::function<float(float)> funcX,std::function<float(float)> funcY, std::function<float(float)> funcZ,float start,float stopp,float res);

    Dmath::Vec3D getVectorFromFunction(float xValue, float yValue, float zValue);
    Dmath::Vec3D getVectorFromPoint(float point);

    Vec3D tangentVector(float t);

    float dotProductVectorCurve(VectorCurve3D vec);    
    float calculateSlopeXOnPoint(float t);
    float calculateSlopeYOnPoint(float t);
    float curveLenght();

    float maximumY();
    float minimumY();
    float maximumX();
    float minimumX();

};




NAMESPACEEND //Dmath namespace
#endif //include guard