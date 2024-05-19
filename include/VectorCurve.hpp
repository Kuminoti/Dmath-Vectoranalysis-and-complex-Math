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
    
    VectorCurve2D(std::function<double(double)> xFunc,std::function<double(double)> yFunc);
    VectorCurve2D(std::function<double(double)> xFunc,std::function<double(double)> yFunc, double start, double stopp, double res);

    //Constructos for sinmple parametric Vector curves (not fully tested)

    VectorCurve2D(std::function<double(double)> xFunc,std::function<double(double)> yFunc, double start, double stopp, double res, std::vector<Dmath::Vec2D> mainCurve);
    VectorCurve2D(std::function<double(double)> xFunc,std::function<double(double)> yFunc, double start, double stopp, double res, std::vector<Dmath::Vec2D> mainCurve, double rotation);


  public:
    //Create a parametric Vector curve (tested)
    static VectorCurve2D createStandardCurve(std::function<double(double)> funcX,std::function<double(double)> funcY );
    static VectorCurve2D createCustomCurve(std::function<double(double)> funcX, std::function<double(double)> funcY, double start, double stopp, double res );
    
    //Getters (tested)
    Dmath::Vec2D getVectorFromFunction(double vecX, double vecY);   //Returns a vector calculated from the two functions
    Dmath::Vec2D getVectorFromPoint(double point);                  //Returns a vector on the point t
    Dmath::Vec2D getVectorFromStdVec(size_t index);                 //Returns a specific index of the std::vector

    // NEEDS TESTING

    /*
     *The tangential vector at a point of a parameterized curve points in the direction of the tangent
     * to the curve at that point and represents the direction of local change of the curve at that point.
    */ 
    Dmath::Vec2D tangentVector(double t);

    /*
     *The tangent unit vector at a point of a parameterized curve is a vector that points in the same direction
     * as the tangent vector at that point but has a length of 1. It represents the direction of the tangent to the curve at that point,
     * without taking into account the speed of change of the curve.
     */
    Dmath::Vec2D tangetUnitVector(double t);

    /*
     * The principal normal unit vector at a point of a parameterized curve is a vector that is perpendicular to the tangent unit vector
     * at that point and has a length of 1. It represents the direction of maximum curvature of the curve at that point,
     * i.e. the direction in which the curve is curved the most
     */
    Dmath::Vec2D principalNormalUnitVector(double t);


    inline std::vector<Dmath::Vec2D> getMainCurve(){ return this->mainCurve;}

    //operator overloading:
    inline VectorCurve2D operator+ (VectorCurve2D curve){ return addCurve(curve);      }
    inline VectorCurve2D operator- (VectorCurve2D curve){ return subtractCurve(curve); }
    
    double curveLenght();
    double calculateSlopeOnPoint(double t);
    double dotProductVectorCurve(Dmath::VectorCurve2D vec);
    double calculateAreaXAchsis(double tStart, double tEnd);
    double calculateAreaYAchsis(double tStart, double tEnd);
    double getCurvature(double t);
    
    VectorCurve2D addCurve(VectorCurve2D curve);
    VectorCurve2D subtractCurve(VectorCurve2D curve);
    VectorCurve2D rotateCurve(double radiants);

    // NEEDS TESTING

    //Returns the maxima und minima x-points of the given curve
    double maximumY();
    double minimumY();
    double MaximumX();
    double minimumX();

    void moveX(double moveX);
    void moveY(double moveY);
    void moveCurve(double moveX, double moveY);

    void rotateThisCurve(double radiants);
    

    size_t numberOfYZeroPoints();
    size_t numberOfXZeroPoints();

    inline std::vector<Dmath::Vec2D> getCurve(){ return this->mainCurve; }
};
    



class VectorCurve3D : public VectorAnalysis3D{
  private:

    double rotationPhi;
    double rotationTheta;

    std::vector<Dmath::Vec3D> mainCurve;
    std::vector<Dmath::Vec3D> createVectorialCurve();

    VectorCurve3D(std::function<double(double)> xFunc,std::function<double(double)> yFunc, std::function<double(double)> zFunc, double start, double stopp, double res, std::vector<Dmath::Vec3D> mainCurve, double rotationPhi, double rotationTheta);
    VectorCurve3D(std::function<double(double)> xFunc,std::function<double(double)> yFunc, std::function<double(double)> zFunc, double start, double stopp, double res, std::vector<Dmath::Vec3D> mainCurve);
    VectorCurve3D(std::function<double(double)> xFunc,std::function<double(double)> yFunc, std::function<double(double)> zFunc);
    VectorCurve3D(std::function<double(double)> xFunc,std::function<double(double)> yFunc, std::function<double(double)> zFunc, double start, double stopp, double res);

  public:
    static VectorCurve3D createStandardCurve(std::function<double(double)> funcX,std::function<double(double)> funcY, std::function<double(double)> funcZ );
    static VectorCurve3D createCustomCurve  (std::function<double(double)> funcX,std::function<double(double)> funcY, std::function<double(double)> funcZ,double start,double stopp,double res);

    Dmath::Vec3D getVectorFromFunction(double xValue, double yValue, double zValue);
    Dmath::Vec3D getVectorFromPoint(double point);
    Dmath::Vec3D getVectorFromStdVec(size_t index); 
    Dmath::Vec3D tangentVector(double t);

    Dmath::Vec3D tangetUnitVector(double t);
    Dmath::Vec3D principalNormalUnitVector(double t);


    //add() subtract() etc...

    VectorCurve3D rotateCurve(double phi, double theta);

    double dotProductVectorCurve(VectorCurve3D vec);    
    double calculateSlopeXOnPoint(double t);
    double calculateSlopeYOnPoint(double t);
    
    double calculateSlopeOnPoint(double t);
    double calculateAreaXAchsis(double tStart, double tEnd);
    double calculateAreaYAchsis(double tStart, double tEnd);
    double calculateAreaZAchsis(double tStart, double tEnd);
    double curveLenght();
    double getCurvature(double t);

    double maximumY();
    double minimumY();
    double maximumX();
    double minimumX();

    size_t numberOfXZeroPoints();
    size_t numberOfYZeroPoints();
    size_t numberOfZZeroPoints();

    void moveX(double moveX);
    void moveY(double moveY);
    void moveZ(double moveZ);
    void moveCurve(double X, double Y, double Z);
    void rotateThisCurve(double phi, double theta);

};





NAMESPACEEND //Dmath namespace
#endif //include guard