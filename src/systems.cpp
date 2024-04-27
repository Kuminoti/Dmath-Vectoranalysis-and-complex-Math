#include "../include/systems.hpp"

#ifdef SYSTEM_IS_SET

//MathHelper methods:

float  MathHelper::calculateDerivativeAt(std::function<float(float)> f, float x) {
    float fx_plus_h = f(x + this->h);
    float fx_minus_h = f(x - this->h);
    float derivative = (fx_plus_h - fx_minus_h) / (2 * this->h);
    return derivative;
}

float MathHelper::calculateDefiniteIntegral(std::function<float(float)> f, float a, float b) {
    float sum = 0.0;
    float dx = (b - a) / this->numSteps;
    for (int i = 0; i < this->numSteps; ++i) {
        float x = a + i * dx;
        sum += f(x) * dx;
    }
    return sum;
}

std::function<float(float)> MathHelper::calculateAntiderivative(std::function<float(float)> f, float x0) {
    float integral = 0.0;
    std::function<float(float)> antiderivative = [f, x0, this, integral](float x) mutable {
        integral += f(x) * this->dx;
        return integral;
    };
    return antiderivative;
}

std::function<float(float)> MathHelper::calculateDerivative(std::function<float(float)> f) {
    float dx = this->dx; // Hier wird dx explizit kopiert, um Rundungsfehler zu vermeiden
    return [f, dx](float x) {
        return (f(x + dx) - f(x)) / dx;
    };
}


void CoordinateSystem2D::polarToCartesian() {
    this->X = radius * std::cos(this->phi);
    this->Y = radius * std::sin(this->phi);
}

void CoordinateSystem2D::cartesianToPolar() {
    this->radius = this->mathHelper.pyth(this->X, this->Y);
    this->phi = std::atan2(this->Y, this->X);
}

void CoordinateSystem3D::cartesianToSphere() {
    this->radius = this->mathHelper.pyth3D(this->X, this->Y, this->Z);
    this->phi = std::atan2(this->Y, this->X);
    this->theta = std::acos((this->Z / radius));
}

void CoordinateSystem3D::cartesianToCylinder() {
    this->radius = this->mathHelper.pyth(this->X, this->Y);
    this->phi = std::atan2(this->Y, this->X);
    this->height = this->Z;
}

void CoordinateSystem3D::sphereToCatesian() {
    this->X = this->radius * std::sin(this->theta) * std::cos(this->phi);
    this->Y = this->radius * std::sin(this->theta) * std::sin(this->phi);
    this->Z = this->radius * std::cos(this->theta);
}

void CoordinateSystem3D::sphereToCylinder() {
    this->radius = this->radius * std::sin(this->theta);
    // this->phi = this->phi;
    this->height = this->radius * std::cos(this->theta);
}

void CoordinateSystem3D::cylinderToCartesian() {
    this->X = this->radius * std::cos(phi);
    this->Y = this->radius * std::sin(phi);
    this->Z = this->height;
}

void CoordinateSystem3D::cylinderToSphere() {
    this->radius = this->mathHelper.pyth(this->radius, this->height);
    // this->phi = this->phi;
    this->theta = std::atan2(this->radius, this->height);
}

#ifdef CARTESIAN_IS_2D_STANDARD

CoordinateSystem2D::CoordinateSystem2D(float XY){
    this->X = XY;
    this->Y = XY;
    this->originX = 0;
    this->originY = 0;
    
}

CoordinateSystem2D::CoordinateSystem2D(float x, float y) {
    this->X = x;
    this->Y = y;
    this->originX = 0;
    this->originY = 0;
}

CoordinateSystem2D::CoordinateSystem2D(float x, float y, float originX,
                                       float originY) {
    this->X = x;
    this->Y = y;
    this->originX = originX;
    this->originY = originY;
}

#endif

#ifdef POLAR_IS_STANDARD
CoordinateSystem2D::CoordinateSystem2D(float radius, float phi, float originX,
                                       float originY) {
    this->radius = radius;
    this->phi = phi;
    this->originX = originX;
    this->originY = originY;
    }

CoordinateSystem2D::CoordinateSystem2D(float radius, float phi) {
    this->radius = radius;
    this->phi = phi;
    this->originX = 0;
    this->originY = 0;
}
#endif

#ifdef CARTESIAN_IS_3D_STANDARD

CoordinateSystem3D::CoordinateSystem3D(float XYZ) : CoordinateSystem2D(XYZ)  {
    this->X = XYZ;
    this->Y = XYZ;
    this->Z = XYZ;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}

CoordinateSystem3D::CoordinateSystem3D(float X, float Y, float Z)
    : CoordinateSystem2D(X, Y) {
    this->Z = Z;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}

CoordinateSystem3D::CoordinateSystem3D(float X, float Y, float Z, float originX, float originY, float originZ)
    : CoordinateSystem2D(X, Y, originX, originY) {
    this->Z = Z;
    this->originZ = originZ;
}
#endif

#ifdef SPHERE_IS_STANDARD
CoordinateSystem3D::CoordinateSystem3D(float radius, float phi, float theta)
    : CoordinateSystem2D(radius, phi) {
    this->theta = theta;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}
CoordinateSystem3D::CoordinateSystem3D(float radius, float phi, float theta,
                                       float originX, float originY,float originZ)
    : CoordinateSystem2D(radius, phi, originX, originY) {
    this->theta = theta;
    this->originZ = originZ;
}
#endif

#ifdef CYLINDER_IS_STANDARD
CoordinateSystem3D::CoordinateSystem3D(float radius, float phi, float height)
    : CoordinateSystem2D(radius, phi) {
    this->height = height;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}
CoordinateSystem3D::CoordinateSystem3D(float radius, float phi, float height,
                                       float originX, float originY, float originZ)
    : CoordinateSystem2D(radius, phi, originX, originY) {
    this->height = height;
    this->originZ = originZ;
}
#endif



#endif


//DIfferential geometry
VectorAnalysis2D::VectorAnalysis2D(float systemStart, float systemStopp, float resolution){
    this->systemStart = systemStart;
    this->systemStopp = systemStopp;
    this->resolution  = resolution;
    this->resolution  = ZERO;
    this->numberOfElements = this->mathHelper.numOfElements(systemStart,systemStopp,resolution);
}

VectorAnalysis2D::VectorAnalysis2D(std::function<float(float)> xFunc, std::function<float(float)> yFunc){
    this->xFunc = xFunc;
    this->yFunc = yFunc;
    this->rotation    = ZERO;
    this->systemStart = ZERO;
    this->systemStopp = TWOPI;
    this->resolution  = STDRES;
    this->numberOfElements = this->mathHelper.numOfElements(ZERO,TWOPI,STDRES);
}


VectorAnalysis2D::VectorAnalysis2D(std::function<float(float)> xFunc, std::function<float(float)> yFunc, float systemStart, float systemStopp, float resolution){
    this->xFunc = xFunc;
    this->yFunc = yFunc;

    this->resolution  = resolution;
    this->systemStart = systemStart;
    this->systemStopp = systemStopp;
    this->rotation    = ZERO;
    this->numberOfElements = this->mathHelper.numOfElements(systemStart,systemStopp,resolution);
}

VectorAnalysis2D::VectorAnalysis2D(std::function<float(float)> xFunc, std::function<float(float)> yFunc, float systemStart, float systemStopp, float resolution, float rotation){
    this->xFunc = xFunc;
    this->yFunc = yFunc;

    this->resolution  = resolution;
    this->systemStart = systemStart;
    this->systemStopp = systemStopp;
    this->rotation    = rotation;

    this->numberOfElements = this->mathHelper.numOfElements(systemStart,systemStopp,resolution);  
}


VectorAnalysis3D::VectorAnalysis3D(float systemStart, float systemStopp, float resolution) :
 VectorAnalysis2D(systemStart,systemStopp,resolution){}
                                

VectorAnalysis3D::VectorAnalysis3D(std::function<float(float)> xFunc, std::function<float(float)> yFunc, std::function<float(float)> zFunc)
: VectorAnalysis2D(xFunc, yFunc){

    this->zFunc = zFunc;
   
}

VectorAnalysis3D::VectorAnalysis3D(std::function<float(float)> xFunc, std::function<float(float)> yFunc,std::function<float(float)> zFunc , float systemStart, float systemStopp, float resolution)
: VectorAnalysis2D(xFunc,yFunc,systemStart,systemStopp,resolution){
    this->zFunc = zFunc;
}

float CoordinateSystem3D::getRadiusSphere() {
    return this->mathHelper.pyth3D(this->X, this->Y, this->Z);
}
float CoordinateSystem3D::getRadiusCylinder() {
    return this->mathHelper.pyth(this->X, this->Y);
}
