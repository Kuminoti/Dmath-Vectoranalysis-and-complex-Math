#ifndef COMPLEXVECTORMATH_HPP
#define COMPLEXVECTORMATH_HPP

#include<functional>
#include<algorithm>
#include"mathVector.hpp"


NAMESPACESTART

class VectorCurve2D {
  private:
    // createVectorCurve erschafft eine vektoriele parametrisierte kurve
    std::vector<Dmath::Vec2D> createVectorCurve();

    /* createVectorialCurve erschafft eine kurve aus zusammenhängenden vektoren, dessen
     * ursprung der letzte Vektor ist "quasi zusammenhängend" ->->->
     * der ursprung eines vektors ist der wert des letzt (auser beim start 0,0)
     * also z.B:
     * der erste  vektor(0;3)ursprung(0;0)
     * der zweite vektor(1;2)ursprung(0;3) also die koordinatendes letzten Vektors
     * ->->->
    */
    std::vector<Dmath::Vec2D> createVectorialCurve();

  protected:
    std::vector<Dmath::Vec2D> mainCurve;

    std::function<float(float)> mainXFunc;
    std::function<float(float)> mainYFunc;

    float resolution = 0.1;
    float curveStart = 0;
    float curveStopp = TWOPI;

    int numberOfElements;

    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc);
    VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res);

  public:
    static VectorCurve2D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY );
    static VectorCurve2D createCustomCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,float start,float stopp,float res );

    //Getters
    Dmath::Vec2D getVectorFromFunction(float vecX, float vecY);
    Dmath::Vec2D getVectorFromPoint(float point);
};

class VectorCurve3D {
  private:
    std::vector<Dmath::Vec3D> mainCurve;

    std::function<float(float)> mainZFunc;
    std::function<float(float)> mainXFunc;
    std::function<float(float)> mainYFunc;

    float resolution = 0.1;
    float curveStart = 0;
    float curveStopp = TWOPI;

    int numberOfElements;
    std::vector<Dmath::Vec3D> createVectorCurve();
    std::vector<Dmath::Vec3D> createVectorialCurve();

    VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, std::function<float(float)> zFunc);
    VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, std::function<float(float)> zFunc, float start, float stopp, float res);
  public:
    static VectorCurve3D createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY, std::function<float(float)> funcZ );
    static VectorCurve3D createCustomCurve  (std::function<float(float)> funcX,std::function<float(float)> funcY, std::function<float(float)> funcZ,float start,float stopp,float res);

    Dmath::Vec3D getVectorFromFunction(float xValue, float yValue, float zValue);
    Dmath::Vec3D getVectorFromPoint(float point);
};




NAMESPACEEND //Dmath namespace
#endif