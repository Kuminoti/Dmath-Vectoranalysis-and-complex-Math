#ifndef COMPLEXVECTORMATH_HPP
#define COMPLEXVECTORMATH_HPP

#include<functional>
#include<algorithm>
#include"mathVector.hpp"


NAMESPACESTART

class VectorCurve2D : public VectorialDifferentialGeometry2D {
  private:
    
    std::vector<Dmath::Vec2D> createVectorialCurve();

  protected:
    std::vector<Dmath::Vec2D> mainCurve;

    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc);
    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res);

  public:
    static VectorCurve2D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY );
    static VectorCurve2D createCustomCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,float start,float stopp,float res );
    //Getters
    Dmath::Vec2D getVectorFromFunction(float vecX, float vecY);
    Dmath::Vec2D getVectorFromPoint(float point);

    Vec2D tangentVector(float t);

    float curveLenght();
};
    

class VectorCurve3D : public VectorialDifferentialGeometry3D{
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
    float curveLenght();
};




NAMESPACEEND //Dmath namespace
#endif