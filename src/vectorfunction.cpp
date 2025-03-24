#include "../include/vectorfunction.hpp"
#pragma region single

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

Dmath::Vec2D Dmath::SingleVectorFunction::call2D(Dmath::Scalar t){
    return Dmath::Vec2D(xOfT(t), yOfT(t));
}

Dmath::Vec3D Dmath::SingleVectorFunction::operator ()(Dmath::Scalar t){
    const Dmath::Scalar currentX = this->xOfT(t);
    const Dmath::Scalar currentY = this->yOfT(t);
    const Dmath::Scalar currentZ = this->zOfT(t);
    
    return Dmath::Vec3D(currentX, currentY, currentZ);
}


Dmath::Vec3D Dmath::SingleVectorFunction::getTangentialVectorAt(Dmath::Scalar t){
    const Dmath::Scalar dx = this->xOfT.getDerivativeAt(t);
    const Dmath::Scalar dy = this->yOfT.getDerivativeAt(t);
    const Dmath::Scalar dz = this->zOfT.getDerivativeAt(t);

    return Dmath::Vec3D(dx,dy,dz);
}

#pragma endregion


#pragma region Double 
Dmath::Vec3D Dmath::DoubleVectorFunction::operator ()(Dmath::Scalar U, Dmath::Scalar V){
    const Dmath::Scalar currentX = this->xOfUV(U,V);
    const Dmath::Scalar currentY = this->yOfUV(U,V);
    const Dmath::Scalar currentZ = this->zOfUV(U,V);

    return Dmath::Vec3D(currentX,currentY, currentZ);
}

Dmath::DoubleVectorFunction::DoubleVectorFunction(Dmath::DoubleVarFunction xOfUV, Dmath::DoubleVarFunction yOfUV, Dmath::DoubleVarFunction zOfUV){
    this->xOfUV = xOfUV;
    this->yOfUV = yOfUV;
    this->zOfUV = zOfUV;

}

Dmath::Vec3D Dmath::DoubleVectorFunction::getPartialUAt(Dmath::Scalar u, Dmath::Scalar v){
    const Dmath::Scalar du_x = (this->xOfUV(u + 0.0001, v) - this->xOfUV(u - 0.0001, v)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUV(u + 0.0001, v) - this->yOfUV(u - 0.0001, v)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUV(u + 0.0001, v) - this->zOfUV(u - 0.0001, v)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x,du_y,du_z);
}


Dmath::Vec3D Dmath::DoubleVectorFunction::getPartialVAt(Dmath::Scalar u, Dmath::Scalar v){
    const Dmath::Scalar du_x = (this->xOfUV(u, v + 0.0001) - this->xOfUV(u, v - 0.0001)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUV(u, v + 0.0001) - this->yOfUV(u, v - 0.0001)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUV(u, v + 0.0001) - this->zOfUV(u, v - 0.0001)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x,du_y,du_z);
}

Dmath::Vec3D Dmath::DoubleVectorFunction::normVectorAt(Dmath::Scalar u, Dmath::Scalar v){
    Dmath::Vec3D du = this->getPartialUAt(u,v);
    Dmath::Vec3D dv = this->getPartialVAt(u,v);

    Dmath::Vec3D normVec = du.vecProduct(dv);

    return normVec;
}

#pragma endregion

#pragma region Triple

Dmath::TripleVectorFunction::TripleVectorFunction(Dmath::TripleVarFunction xOfUVW, Dmath::TripleVarFunction yOfUVW, Dmath::TripleVarFunction zOfUVW){
    this->xOfUVW = xOfUVW;
    this->yOfUVW = yOfUVW;
    this->zOfUVW = zOfUVW;
}

Dmath::Vec3D Dmath::TripleVectorFunction::operator()(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar currentX = this->xOfUVW(u,v,w);
    const Dmath::Scalar currentY = this->yOfUVW(u,v,w);
    const Dmath::Scalar currentz = this->zOfUVW(u,v,w);

    return Dmath::Vec3D(currentX, currentY, currentz);
}


Dmath::Vec3D Dmath::TripleVectorFunction::getPartialUAt(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar du_x = (this->xOfUVW(u + 0.0001, v, w) - this->xOfUVW(u - 0.0001, v, w)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUVW(u + 0.0001, v, w) - this->yOfUVW(u - 0.0001, v, w)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUVW(u + 0.0001, v, w) - this->zOfUVW(u - 0.0001, v, w)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x, du_y,du_z);
}

Dmath::Vec3D Dmath::TripleVectorFunction::getPartialVAt(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar du_x = (this->xOfUVW(u, v + 0.0001, w) - this->xOfUVW(u, v - 0.0001, w)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUVW(u, v + 0.0001, w) - this->yOfUVW(u, v - 0.0001, w)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUVW(u, v + 0.0001, w) - this->zOfUVW(u, v - 0.0001, w)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x, du_y,du_z);
}

Dmath::Vec3D Dmath::TripleVectorFunction::getPartialWAt(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar du_x = (this->xOfUVW(u, v, w + 0.0001) - this->xOfUVW(u, v, w - 0.0001)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUVW(u, v, w + 0.0001) - this->yOfUVW(u, v, w + 0.0001)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUVW(u, v, w + 0.0001) - this->zOfUVW(u, v, w + 0.0001)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x, du_y,du_z);
}

Dmath::Scalar Dmath::TripleVectorFunction::callX(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    return this->xOfUVW(u,v,w);
}

Dmath::Scalar Dmath::TripleVectorFunction::callY(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    return this->yOfUVW(u,v,w);
}

Dmath::Scalar Dmath::TripleVectorFunction::callZ(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    return this->zOfUVW(u,v,w);
}

Dmath::Scalar Dmath::TripleVectorFunction::callXPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar dx = this->callX(u + 0.0001, v, w) - this->callX(u - 0.0001, v, w) / (2 * 0.0001);
    return dx;
}


Dmath::Scalar Dmath::TripleVectorFunction::callYPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar dx = this->callX(u + 0.0001, v, w) - this->callX(u - 0.0001, v, w) / (2 * 0.0001);
    return dx;
}

#pragma endregion