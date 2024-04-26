#include "../include/systems.hpp"

float pyth2D(float x, float y) { return std::sqrt((x * x) + (y * y)); }

// Pythagorean theorem for 3D vectors
float pyth3D(float x, float y, float z) {
    return std::sqrt((x * x) + (y * y) + (z * z));
}

#ifdef SYSTEM_IS_SET

void CoordinateSystem2D::polarToCartesian() {
    this->X = radius * std::cos(this->phi);
    this->Y = radius * std::sin(this->phi);
}

void CoordinateSystem2D::cartesianToPolar() {
    this->radius = pyth2D(this->X, this->Y);
    this->phi = std::atan2(this->Y, this->X);
}

void CoordinateSystem3D::cartesianToSphere() {
    this->radius = pyth3D(this->X, this->Y, this->Z);
    this->phi = std::atan2(this->Y, this->X);
    this->theta = std::acos((this->Z / pyth3D(this->X, this->Y, this->Z)));
}

void CoordinateSystem3D::cartesianToCylinder() {
    this->radius = pyth2D(this->X, this->Y);
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
    this->radius = pyth2D(this->radius, this->height);
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
}

VectorAnalysis2D::VectorAnalysis2D(std::function<float(float)> xFunc, std::function<float(float)> yFunc){
    this->xFunc = xFunc;
    this->yFunc = yFunc;
    this->systemStart = ZERO;
    this->systemStopp = TWOPI;
    this->resolution  = STDRES;
    this->numberOfElements = static_cast<int>((this->systemStopp-this->systemStart)/resolution);
}


VectorAnalysis2D::VectorAnalysis2D(std::function<float(float)> xFunc, std::function<float(float)> yFunc, float systemStart, float systemStopp, float resolution){
    this->xFunc = xFunc;
    this->yFunc = yFunc;

    this->resolution  = resolution;
    this->systemStart = systemStart;
    this->systemStopp = systemStopp;

    this->numberOfElements = static_cast<int>((this->systemStart - this->systemStopp)/ this->resolution);
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
    return pyth3D(this->X, this->Y, this->Z);
}
float CoordinateSystem3D::getRadiusCylinder() {
    return pyth2D(this->X, this->Y);
}
