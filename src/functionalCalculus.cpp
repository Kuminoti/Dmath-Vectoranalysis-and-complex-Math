#include"../include/functionalCalculus.hpp"



Dmath::Vec3D Dmath::gradientVector(Dmath::TripleVarFunction func, Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z){
    Dmath::Scalar ddx = func.derivativeXAt(x,y,z);
    Dmath::Scalar ddy = func.derivativeYAt(x,y,z);
    Dmath::Scalar ddz = func.derivativeZAt(x,y,z);

    return Dmath::Vec3D(ddx,ddy,ddz);
}


Dmath::Vec2D Dmath::gradientVector(Dmath::DoubleVarFunction func, Dmath::Scalar x, Dmath::Scalar y){
    Dmath::Scalar ddx = func.derivativeXAT(x,y);
    Dmath::Scalar ddy = func.derivativeYAT(x,y);

    return Dmath::Vec2D(ddx,ddy);
}


Dmath::Matrix<Dmath::Scalar> Dmath::getHesseMatrixAt(Dmath::DoubleVarFunction func,  Dmath::Scalar x, Dmath::Scalar y){
    Dmath::Scalar ddxx = func.secondDerivativeXX(x,y);
    Dmath::Scalar ddxy = func.secondDerivativeXY(x,y);
    Dmath::Scalar ddyy = func.secondDerivativeYY(x,y);

    Dmath::Matrix<Dmath::Scalar> mainMatrix(2);

    mainMatrix.setElement(1,1,ddxx);
    mainMatrix.setElement(1,2,ddxy);
    mainMatrix.setElement(2,1,ddxy);
    mainMatrix.setElement(2,2,ddyy);

    return mainMatrix;
}


Dmath::SingleVarFunction Dmath::functionalComposition(Dmath::SingleVarFunction funcOne, Dmath::SingleVarFunction funcTwo){

    auto composed =  [funcOne,funcTwo](double x) mutable  ->double { 
        double innerResult = funcTwo(x);
        double result = funcOne(innerResult);
        return result;
    };

    Dmath::SingleVarFunction mainFunc = composed;

    return mainFunc;
}


