#include "../include/systems.hpp"
#include "../include/macros.hpp"
#ifdef SYSTEM_IS_SET

//MathHelper methods:

double  MathHelper::calculateDerivativeAt(std::function<double(double)> f, double x) {
    double fx_plus_h = f(x + this->h);
    double fx_minus_h = f(x - this->h);
    double derivative = (fx_plus_h - fx_minus_h) / (2 * this->h);
    return derivative;
}

double MathHelper::calculateDefiniteIntegral(std::function<double(double)> f, double a, double b) {
    double sum = 0.0;
    double dx = (b - a) / this->numSteps;
    for (int i = 0; i < this->numSteps; ++i) {
        double x = a + i * dx;
        sum += f(x) * dx;
    }
    return sum;
}

std::function<double(double)> MathHelper::calculateAntiderivative(std::function<double(double)> f, double x0) {
    double integral = 0.0;
    std::function<double(double)> antiderivative = [f, x0, this, integral](double x) mutable {
        integral += f(x) * this->dx;
        return integral;
    };
    return antiderivative;
}

std::function<double(double)> MathHelper::calculateDerivative(std::function<double(double)> f) {
    double dx = this->dx; // Hier wird dx explizit kopiert, um Rundungsfehler zu vermeiden
    return [f, dx](double x) {
        return (f(x + dx) - f(x)) / dx;
    };
}

double MathHelper::piMultiply(std::function<double(double)> mainFunc,size_t start, size_t end){
    double result = 0;
    if(start >= end){
    return 0;
    }
    for(int i = start; i<end; i++){
    result+= mainFunc(i);
    }
    return result;
}


double MathHelper::sigmaAdd(std::function<double(double)> mainFunc,size_t start, size_t end){
    double result = 0;
    if(start >= end){
    return 0;
    }
    for(int i = start; i<end; i++){
    result += mainFunc(i);
    }
    return result;
}



void CoordinateSystem2D::polarToCartesian() {
    this->X = radius * std::cos(this->phi);
    this->Y = radius * std::sin(this->phi);
}

void CoordinateSystem2D::cartesianToPolar() {
    this->radius = this->mathHelper.pyth(this->X, this->Y);
    this->phi = std::atan2(this->Y, this->X);
    
}



void CoordinateSystem2D::calcAbsXY() {
    if(this->originX != 0 || this->originY != 0){
        this->aX = this->X + this->originX;
        this->aY = this->Y + this->originY;
    }
}


void CoordinateSystem2D::setOriginX(double move){
  this->originX = move;
  this->calcAbsXY();
  this->calcDZ();
}

void CoordinateSystem2D::setOriginY(double move){
  this->originY = move;
  this->calcAbsXY();
  this->calcDZ();
}




void CoordinateSystem3D::cartesianToSphere() {
    this->radius = this->mathHelper.pyth3D(this->X, this->Y, this->Z);
    this->phi =  std::atan2(this->Y, this->X);
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

void CoordinateSystem3D::setOriginX(double Value){
  this->originX = Value;
  this->calcAXYZ();
  this->calcDTZ();
}

void CoordinateSystem3D::setOriginY(double Value){
  this->originY = Value;
  this->calcAXYZ();
  this->calcDTZ();
}

void CoordinateSystem3D::setOriginZ(double Value){
  this->originZ = Value;
  this->calcAXYZ();
  this->calcDTZ();
}

void CoordinateSystem3D::calcAXYZ(){
    if(this->originX != 0 || this->originY != 0 || this->originZ != 0){
        this->aX = this->originX + this->X;
        this->aY = this->originY + this->Y; 
        this->aZ = this->originZ + this->Z;
    }
}

void CoordinateSystem3D::calcDTZ(){
 if(this->originX == 0 && this->originY == 0 && this->originZ == 0){
    this->distanceToZero = 0;
    return;
  }
  double result = 0;
  this->calcAXYZ();
  //AYS absolute Y sqared ...
  double AXS = this->aX * this->aX;
  double AYS = this->aY * this->aY;
  double AZS = this->aZ * this->aZ;
  result = std::sqrt(AYS + AYS);
  this->distanceToZero = result;  
}

void CoordinateSystem2D::calcDZ(){
    float result = 0;
    if(this->originX != 0 || this->originY != 0){
        result = this->mathHelper.pyth(this->aX,this->aY);
    }
    else { result = 0;}
  this->distanceToZero = result;
}

#ifdef CARTESIAN_IS_2D_STANDARD

CoordinateSystem2D::CoordinateSystem2D(double XY){
    this->X = XY;
    this->Y = XY;
    this->originX = 0;
    this->originY = 0;
    this->aX = 0;
    this->aY = 0;
    
}

CoordinateSystem2D::CoordinateSystem2D(double x, double y) {
    this->X = x;
    this->Y = y;
    this->originX = 0;
    this->originY = 0;
}

CoordinateSystem2D::CoordinateSystem2D(double x, double y, double originX,
                                       double originY) {
    this->X = x;
    this->Y = y;
    this->originX = originX;
    this->originY = originY;
    this->calcAbsXY();
    this->calcDZ();
}

#endif

#ifdef POLAR_IS_STANDARD
CoordinateSystem2D::CoordinateSystem2D(double radius, double phi, double originX,
                                       double originY) {
    this->radius = radius;
    this->phi = phi;
    this->originX = originX;
    this->originY = originY;
    this->calcAbsXY();
    }


CoordinateSystem2D::CoordinateSystem2D(double radius, double phi) {
    this->radius = radius;
    this->phi = phi;
    this->originX = 0;
    this->originY = 0;
}
#endif

#ifdef CARTESIAN_IS_3D_STANDARD

CoordinateSystem3D::CoordinateSystem3D(double XYZ) : CoordinateSystem2D(XYZ)  {
    this->X = XYZ;
    this->Y = XYZ;
    this->Z = XYZ;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}

CoordinateSystem3D::CoordinateSystem3D(double X, double Y, double Z)
    : CoordinateSystem2D(X, Y) {
    this->Z = Z;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}

CoordinateSystem3D::CoordinateSystem3D(double X, double Y, double Z, double originX, double originY, double originZ)
    : CoordinateSystem2D(X, Y, originX, originY) {
    this->Z = Z;
    this->originZ = originZ;
}
#endif

#ifdef SPHERE_IS_STANDARD
CoordinateSystem3D::CoordinateSystem3D(double radius, double phi, double theta)
    : CoordinateSystem2D(radius, phi) {
    this->theta = theta;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}
CoordinateSystem3D::CoordinateSystem3D(double radius, double phi, double theta,
                                       double originX, double originY,double originZ)
    : CoordinateSystem2D(radius, phi, originX, originY) {
    this->theta = theta;
    this->originZ = originZ;
}
#endif

#ifdef CYLINDER_IS_STANDARD
CoordinateSystem3D::CoordinateSystem3D(double radius, double phi, double height)
    : CoordinateSystem2D(radius, phi) {
    this->height = height;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}
CoordinateSystem3D::CoordinateSystem3D(double radius, double phi, double height,
                                       double originX, double originY, double originZ)
    : CoordinateSystem2D(radius, phi, originX, originY) {
    this->height = height;
    this->originZ = originZ;
}
#endif



#endif


//DIfferential geometry

VectorAnalysis2D::VectorAnalysis2D(std::function<Dmath::Duo<double,double>(double, double)> paramOne, std::function<Dmath::Duo<double,double>(double,double)> paramTwo){
    this->resolution = STDRES;
    this->systemStart = 0;
    this->systemStopp = TWOPI;
    this->numberOfElements = this->mathHelper.numOfElements(this->systemStart,this->systemStopp,this->resolution);

    this->funcOne = paramOne;
    this->funcTwo = paramTwo;
}


VectorAnalysis2D::VectorAnalysis2D(double systemStart, double systemStopp, double resolution){
    this->systemStart = systemStart;
    this->systemStopp = systemStopp;
    this->resolution  = resolution;
    
    this->numberOfElements = this->mathHelper.numOfElements(systemStart,systemStopp,resolution);
}

VectorAnalysis2D::VectorAnalysis2D(std::function<double(double)> xFunc, std::function<double(double)> yFunc){
    this->xFunc = xFunc;
    this->yFunc = yFunc;
    this->rotation    = ZERO;
    this->systemStart = ZERO;
    this->systemStopp = TWOPI;
    this->resolution  = STDRES;
    this->numberOfElements = this->mathHelper.numOfElements(ZERO,TWOPI,STDRES);
}

VectorAnalysis2D::VectorAnalysis2D(std::function<double(double,double)> mainFunc, double start, double stopp, double resolution){
    this->mainFunc = mainFunc;
    this->systemStart = start;
    this->systemStopp = stopp;
    this->resolution  = resolution;
    this->numberOfElements = this->mathHelper.numOfElements(start,stopp,resolution);
}

VectorAnalysis2D::VectorAnalysis2D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, double systemStart, double systemStopp, double resolution){
    this->xFunc = xFunc;
    this->yFunc = yFunc;

    this->resolution  = resolution;
    this->systemStart = systemStart;
    this->systemStopp = systemStopp;
    this->rotation    = ZERO;
    this->numberOfElements = this->mathHelper.numOfElements(systemStart,systemStopp,resolution);
}

VectorAnalysis2D::VectorAnalysis2D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, double systemStart, double systemStopp, double resolution, double rotation){
    this->xFunc = xFunc;
    this->yFunc = yFunc;

    this->resolution  = resolution;
    this->systemStart = systemStart;
    this->systemStopp = systemStopp;
    this->rotation    = rotation;

    this->numberOfElements = this->mathHelper.numOfElements(systemStart,systemStopp,resolution);  
}


VectorAnalysis3D::VectorAnalysis3D(double systemStart, double systemStopp, double resolution) :
 VectorAnalysis2D(systemStart,systemStopp,resolution){}
                                

VectorAnalysis3D::VectorAnalysis3D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, std::function<double(double)> zFunc)
: VectorAnalysis2D(xFunc, yFunc){

    this->zFunc = zFunc;
   
}

VectorAnalysis3D::VectorAnalysis3D(std::function<double(double)> xFunc, std::function<double(double)> yFunc,std::function<double(double)> zFunc , double systemStart, double systemStopp, double resolution)
: VectorAnalysis2D(xFunc,yFunc,systemStart,systemStopp,resolution){
    this->zFunc = zFunc;
}

double CoordinateSystem3D::getRadiusSphere() {
    return this->mathHelper.pyth3D(this->X, this->Y, this->Z);
}
double CoordinateSystem3D::getRadiusCylinder() {
    return this->mathHelper.pyth(this->X, this->Y);
}



