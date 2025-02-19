#include "../include/vectorfunction.hpp"


Dmath::SingleVectorFunction::SingleVectorFunction(Dmath::SingleVarFunction xOfT, Dmath::SingleVarFunction yOfT){
    this->xOfT = xOfT;
    this->yOfT = yOfT;
    this->zOfT = [](double t){ return 0; };
    
}

Dmath::SingleVectorFunction::SingleVectorFunction(Dmath::SingleVarFunction xOfT, Dmath::SingleVarFunction yOfT, Dmath::SingleVarFunction zOfT){
    this->xOfT = xOfT;
    this->yOfT = yOfT;
    this->zOfT = zOfT;
    
}

Dmath::Vec2D Dmath::SingleVectorFunction::call2D(double t){
    return Dmath::Vec2D(xOfT(t), yOfT(t));
}

Dmath::Vec3D Dmath::SingleVectorFunction::operator ()(double t){
    const Dmath::Scalar currentX = this->xOfT(t);
    const Dmath::Scalar currentY = this->yOfT(t);
    const Dmath::Scalar currentZ = this->zOfT(t);
    
    return Dmath::Vec3D(currentX, currentY, currentZ);
}