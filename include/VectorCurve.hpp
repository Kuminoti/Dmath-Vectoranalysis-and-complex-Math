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

    //Constructos for sinmple parametric Vector curves (not fully tested)

    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res, std::vector<Dmath::Vec2D> mainCurve);
    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res, std::vector<Dmath::Vec2D> mainCurve, float rotation);


  public:
    //Create a parametric Vector curve (tested)
    static VectorCurve2D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY );
    static VectorCurve2D createCustomCurve(std::function<float(float)> funcX, std::function<float(float)> funcY, float start, float stopp, float res );
    
    //Getters (tested)
    Dmath::Vec2D getVectorFromFunction(float vecX, float vecY);   //Returns a vector calculated from the two functions
    Dmath::Vec2D getVectorFromPoint(float point);                 //Returns a vector on the point t
    Dmath::Vec2D getVectorFromStdVec(size_t index);                //Returns a specific index of the std::vector

    Dmath::Vec2D tangentVector(float t);
    Dmath::Vec2D tangetUnitVector(float t);
    Dmath::Vec2D principalNormalUnitVector(float t);
    inline std::vector<Dmath::Vec2D> getMainCurve(){ return this->mainCurve;}


    // NEEDS TESTING


    //operator overloading:
    inline VectorCurve2D operator+ (VectorCurve2D curve){ return addCurve(curve);      }
    inline VectorCurve2D operator- (VectorCurve2D curve){ return subtractCurve(curve); }
    
    float curveLenght();
    float calculateSlopeOnPoint(float t);
    float dotProductVectorCurve(Dmath::VectorCurve2D vec);
    float calculateAreaXAchsis(float tStart, float tEnd);
    float getCurvature(float t);
    float getT(float originX, float originY){
      
    }
    
    //VectorCurve2D curveFusion(){}
    VectorCurve2D addCurve(VectorCurve2D curve);
    VectorCurve2D subtractCurve(VectorCurve2D curve);
    //VectorCurve2D rotateCurve(float radiants);

    // NEEDS TESTING
    float maximumY();
    float minimumY();
    float MaximumX();
    float minimumX();

    void moveX(float moveX);
    void moveY(float moveY);
    void moveCurve(float moveX, float moveY);

    void rotateThisCurve(float radiants);
    

    size_t numberOfYZeroPoints();
    size_t numberOfXZeroPoints();
};
    

class VectorCurve3D : public VectorAnalysis3D{
  private:

    float rotationPhi;
    float rotationTheta;

    std::vector<Dmath::Vec3D> mainCurve;
    std::vector<Dmath::Vec3D> createVectorialCurve();

    VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, std::function<float(float)> zFunc, float start, float stopp, float res, std::vector<Dmath::Vec3D> mainCurve, float rotationPhi, float rotationTheta);
    VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, std::function<float(float)> zFunc, float start, float stopp, float res, std::vector<Dmath::Vec3D> mainCurve);
    VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, std::function<float(float)> zFunc);
    VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, std::function<float(float)> zFunc, float start, float stopp, float res);

  public:
    static VectorCurve3D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY, std::function<float(float)> funcZ );
    static VectorCurve3D createCustomCurve  (std::function<float(float)> funcX,std::function<float(float)> funcY, std::function<float(float)> funcZ,float start,float stopp,float res);

    Dmath::Vec3D getVectorFromFunction(float xValue, float yValue, float zValue);
    Dmath::Vec3D getVectorFromPoint(float point);
    Dmath::Vec3D getVectorFromStdVec(size_t index); 
    Dmath::Vec3D tangentVector(float t);

    Dmath::Vec3D tangetUnitVector(float t);
    Dmath::Vec3D principalNormalUnitVector(float t);


    //add() subtract() etc...

    VectorCurve3D rotateCurve(float phi, float theta);

    float dotProductVectorCurve(VectorCurve3D vec);    
    float calculateSlopeXOnPoint(float t);
    float calculateSlopeYOnPoint(float t);
    float calculateArea();
    float calculateSpecificArea(float start, float stopp);
    float curveLenght();
    float getCurvature(float t);

    float maximumY();
    float minimumY();
    float maximumX();
    float minimumX();

    size_t numberOfXZeroPoints();
    size_t numberOfYZeroPoints();
    size_t numberOfZZeroPoints();

    void moveX(float moveX);
    void moveY(float moveY);
    void moveZ(float moveZ);
    void moveCurve(float X, float Y, float Z);
    void rotateThisCurve(float phi, float theta);

};




NAMESPACEEND //Dmath namespace
#endif //include guard