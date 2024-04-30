#include "../include/mathVector.hpp"
#include "../include/systemGeometry.hpp"

using namespace Dmath;
// Helper functions:

//Operator overloading

Vec2D Vec2D::operator/(double scalarValue){
  double valueX = this->X / scalarValue;
  double valueY = this->Y / scalarValue;
  return Vec2D(valueX, valueY);
}

Vec2D Vec2D::operator+(Vec2D &Mathvector) {
  double resultX = this->X + Mathvector.X;
  double resultY = this->Y + Mathvector.Y;

  return Vec2D(resultX, resultY);
}

Vec2D Vec2D::operator-(Vec2D &Mathvector) {
  double resultX = this->X - Mathvector.X;
  double resultY = this->Y - Mathvector.Y;

  return Vec2D(resultX, resultY);
}

double Vec2D::operator*(Vec2D &Mathvector) {
  return this->dotProduct(Mathvector);
}

Vec3D Vec3D::operator+(Vec3D &Mathvector) {
  double resultX = this->X + Mathvector.X;
  double resultY = this->Y + Mathvector.Y;
  double resultZ = this->Z + Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}

Vec3D Vec3D::operator-(Vec3D &Mathvector) {
  double resultX = this->X - Mathvector.X;
  double resultY = this->Y - Mathvector.Y;
  double resultZ = this->Z - Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}

Vec3D Vec3D::operator/(double scalarValue){
  double newX = this->X / scalarValue;
  double newY = this->Y / scalarValue;
  double newZ = this->Z / scalarValue;

  Vec3D newVector(newX,newY,newZ);
  if(this->originX != 0 || this->originY != 0 || this->originZ != 0){
    newVector.setOriginX(this->originX);
  }
}

double Vec3D::operator*(Vec3D &Mathvector) {
  return this->dotProduct(Mathvector);
}

// Calculate cosine of the angle between two vectors
double cosAngle(double dotProduct, double absProduct) {
  double result = 0;
  if (absProduct == 0) {
    std::cerr << "Vector abs is Zero" << std::endl;
    result = 0;
  } else {
    result = dotProduct / absProduct;
  }
  return result;
}

double angleFromCos(double cosTheta) {
  double result = 0;
  if (cosTheta > 1 || cosTheta < -1) {
    std::cerr << "Error: cos(theta) wrong value" << std::endl;
    result = 0;
  } else {

#ifdef STANDARD_ANGLE_UNIT_DEG
    result = std::acos(cosTheta) * 180 / PI;
#endif

#ifdef STANDARD_ANGLE_UNIT_RAD
    result = std::acos(cosTheta);
#endif
  }
  return result;
}


// void Vec2D::calcAbsXY(){
//   if(this->originX != 0 || this->originY != 0){
//     this->aX = this->X + this->originX;
//     this->aY = this->Y + this->originY;
//   }
// }





// Vec2D functions:



double Vec2D::distance(Vec2D Mathvector){
  
    double dx = std::abs(Mathvector.aX - this->aX);
    double dy = std::abs(Mathvector.aY - this->aY);
    double result =  std::sqrt(dx * dx + dy * dy);
    return result;
}

double Vec2D::calcAngle(Vec2D Mathvector) {
  double product = this->dotProduct(Mathvector);
  double absProduct = this->getAbs() * Mathvector.getAbs();
  double cosTheta = cosAngle(product, absProduct);
  return angleFromCos(cosTheta);
}



double Vec2D::polarSystemArea() {
  double Area = PI * (this->radius * this->radius);
  return Area;
}

double Vec2D::polarSystemCircumfrance() {
  double Area = TWOPI * this->radius;
  return Area;
}

void Vec2D::setX(double value) {
  this->X = value;
  this->cartesianToPolar();
}

void Vec2D::setY(double value) {
  this->Y = value;
  this->cartesianToPolar();
}

void Vec2D::setPhi(double value) {
  this->phi = value;
  this->polarToCartesian();
}

void Vec2D::setRadius(double value) {
  this->radius = value;
  this->polarToCartesian();
}




void Vec2D::moveVectorX(double move){
  this->originX += move;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::moveVectorY(double move){
  this->originY += move;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::moveVector(double moveX, double moveY){
  this->originX += moveX;
  this->originY += moveY;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::calcAbs() {
  double result = this->mathHelper.pyth(this->X,this->Y);
  this->abs = result;
}

void Vec2D::normalize(){
  this->X = this->X / this->abs;
  this->Y = this->Y / this->abs;
}




double Vec2D::dotProduct(Vec2D Mathvector) {
  double result = this->X * Mathvector.X + this->Y * Mathvector.Y;
  return result;
}

Vec2D Vec2D::add(Vec2D Mathvector) {
  double resultX = this->X + Mathvector.X;
  double resultY = this->Y + Mathvector.Y;
  return Vec2D(resultX, resultY);
}

Vec2D Vec2D::subtract(Vec2D Mathvector) {
  double resultX = this->X - Mathvector.X;
  double resultY = this->Y - Mathvector.Y;
  return Vec2D(resultX, resultY);
}

Vec2D Vec2D::polarVector(double radius, double angle) {
  double xValue = radius * std::cos(angle);
  double yValue = radius * std::sin(angle);
  return Vec2D(xValue, yValue);
}

double Vec2D::rectangleArea(Vec2D MathVector) {
  double Area = this->getAbs() * MathVector.getAbs();
  return Area;
}

double Vec2D::rectangleCircumfrance(Vec2D MathVector) {
  double Circumfrance = 2 * this->getAbs() + 2 * MathVector.getAbs();
  return Circumfrance;
}


void Vec3D::calcAbs() {
  double result = this->mathHelper.pyth3D(this->X,this->Y,this->Z);
  this->abs = result;
}

double Vec3D::calcAngle(Vec3D Mathvector) {
  double product = this->dotProduct(Mathvector);
  double absProduct = this->getAbs() * Mathvector.getAbs();
  double cosTheta = cosAngle(product, absProduct);
  return angleFromCos(cosTheta);
}

double Vec3D::dotProduct(Vec3D Mathvector) {
  double result =
      this->X * Mathvector.X + this->Y * Mathvector.Y + this->Z * Mathvector.Z;
  return result;
}


Vec3D Vec3D::vecProduct(Vec3D Mathvector) {
  double resultX = this->Y * Mathvector.Z - this->Z * Mathvector.Y;
  double resultY = this->Z * Mathvector.X - this->X * Mathvector.Z;
  double resultZ = this->X * Mathvector.Y - this->Y * Mathvector.X;
  return Vec3D(resultX, resultY, resultZ);
}


Vec3D Vec3D::add(Vec3D Mathvector) {
  double resultX = this->X + Mathvector.X;
  double resultY = this->Y + Mathvector.Y;
  double resultZ = this->Z + Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}
 

Vec3D Vec3D::subtract(Vec3D Mathvector) {
  double resultX = this->X - Mathvector.X;
  double resultY = this->Y - Mathvector.Y;
  double resultZ = this->Z - Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}


Vec3D Vec3D::sphereVector(double radius, double angleOne, double angleTwo) {
  double Xvalue = radius * std::sin(angleTwo) * std::cos(angleOne);
  double Yvalue = radius * std::sin(angleTwo) * std::sin(angleOne);
  double Zvalue = radius * std::cos(angleTwo);
  return Vec3D(Xvalue, Yvalue, Zvalue);
}

Vec3D Vec3D::cylinderVector(double radius, double angle, double height) {
  double Xvalue = radius * std::cos(angle);
  double Yvalue = radius * std::sin(angle);
  double Zvalue = height;
  return Vec3D(Xvalue, Yvalue, Zvalue);
}


Vec3D Vec3D::zeroVector() { return Vec3D(0, 0, 0); }


double Vec3D::getCylinderRadius(){
    double  result = std::sqrt((this->X*this->X)+(this->Y*this->Y));
    return result;
}

double Vec3D::getSphereRadius(){
    double  result = std::sqrt((this->X*this->X)+(this->Y*this->Y)+(this->Y*this->Y));
    
    return result;
}





double Vec2D::getAbs()               { return this->abs;      }
double Vec2D::lenght()               { return this->getAbs(); }

double Vec2D::getRotationAngle()     { return this->vectorRotation; }

void Vec3D::setX(double X){
  this->X = X;
  this->cartesianToCylinder();
  this->cartesianToSphere();
}

void Vec3D::moveVectorZ(double moveZ){
  this->originZ += moveZ;
  this->calcAXYZ();
  this->calcDTZ();
}

void Vec3D::moveVectorY(double moveY){
  this->originY += moveY;
  this->calcAXYZ();
  this->calcDTZ();
}


void Vec3D::moveVectorX(double moveX){
  this->originX += moveX;
  this->calcAXYZ();
  this->calcDTZ();
}

void Dmath::Vec3D::moveVector(double moveX, double moveY, double moveZ){
  this->originX += moveX;
  this->originY += moveY;
  this->originZ += moveZ;

  this->calcAXYZ();
  this->calcDTZ();
}

void Vec3D::normalize(){
  this->X = this->X/this->abs;
  this->Y = this->Y/this->abs;
  this->Z = this->Z/this->abs;
}

void Vec3D::setY(double Y)           { this->Y = Y; }
void Vec3D::setZ(double Z)           { this->Z = Z; }
void Vec3D::setHeight(double height) { this->height = height; }
void Vec3D::setPhi(double phi)       { this->phi = phi; }
void Vec3D::setTheta(double theta)   { this->theta = theta; }



//Macro dependent code:

#ifdef SYSTEM_READY

#ifdef POLAR_IS_STANDARD
Vec2D::Vec2D(double radius, double phi) : CoordinateSystem2D(radius, phi) {
  this->calcAbs();
  this->polarToCartesian();
  this->aX = this->X;
  this->aY = this->Y;
}

#endif

#ifdef SPHERE_IS_STANDARD
Vec3D::Vec3D(double radius, double phi, double theta)
    : CoordinateSystem3D(radius, phi, theta) {

  this->calcAbs();
  this->sphereToCatesian();
  this->sphereToCylinder();
  this->aX = this->X;
  this->aY = this->Y;
  this->aZ = this->Z;
}
#endif

#ifdef CYLINDER_IS_STANDARD
Vec3D::Vec3D(double radius, double phi, double height)
    : CoordinateSystem3D(radius, phi, height) {

  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->aX = this->X;
  this->aY = this->Y;
  this->aZ = this->Z;
}
#endif

#ifdef CARTESIAN_IS_3D_STANDARD

Vec3D::Vec3D(double XYZ) : CoordinateSystem3D(XYZ) {
  
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();  
  this->aX = 0;
  this->aY = 0;
  this->aZ = 0;
}

Vec3D::Vec3D(double X, double Y, double Z, double originX, double originY, double originZ)
    : CoordinateSystem3D(X, Y, Z, originX, originY, originZ) {
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();
  this->calcAXYZ();
  this->calcDTZ();
}

Vec3D::Vec3D(double X, double Y, double Z) : CoordinateSystem3D(X, Y, Z) {
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();
  this->aX = this->X;
  this->aY = this->Y;
  this->aZ = this->Z;
}
#endif

#ifdef CARTESIAN_IS_2D_STANDARD

Vec2D::Vec2D(double XY) : CoordinateSystem2D(XY){
  this->aX = XY;
  this->aY = XY;
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D::Vec2D(double X, double Y) : CoordinateSystem2D(X, Y) {
  this->aX = X;
  this->aY = Y;
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D::Vec2D(double X, double Y, double originX, double originY)
    : CoordinateSystem2D(X, Y, originX, originY) {
  this->calcAbsXY();
  this->calcDZ();
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D Vec2D::zeroVector() { return Vec2D(0, 0); }

#endif

#ifdef STANDARD_ANGLE_UNIT_RAD
Dmath::Vec3D Vec3D::rotateVector(double Phi, double Theta) {
    double r = this->radius;
    double theta = this->theta;
    double phi = this->phi;

    double newTheta = theta + Theta;
    double newPhi = phi + Phi;

    double newX = (r * std::sin(newTheta) * std::cos(newPhi));
    double newY = (r * std::sin(newTheta) * std::sin(newPhi));
    double newZ = (r * std::cos(newTheta));

    return Dmath::Vec3D(newX, newY, newZ);
}

#endif

#ifdef STANDARD_ANGLE_UNIT_DEG
Dmath::Vec3D Vec3D::rotateVector(double Phi, double Theta) {
    double r = this->radius;
    double theta = this->theta;
    double phi = this->phi;

    double newTheta = theta + Theta;
    double newPhi = phi + Phi;

    double newX = (r * std::sin(newTheta) * std::cos(newPhi)) * RAD_TO_DEG;
    double newY = (r * std::sin(newTheta) * std::sin(newPhi)) * RAD_TO_DEG ;
    double newZ = (r * std::cos(newTheta))* RAD_TO_DEG;

    return Dmath::Vec3D(newX, newY, newZ);
}

#endif

#ifdef STANDARD_ANGLE_UNIT_DEG

void Vec3D::rotateThisVector(double Phi, double Theta){
    double r = this->radius;
    double theta = this->theta;
    double phi = this->phi;

    double newTheta = theta + Theta;
    double newPhi = phi + Phi;

    this->X = (r * std::sin(newTheta) * std::cos(newPhi)) * RAD_TO_DEG;
    this->Y = (r * std::sin(newTheta) * std::sin(newPhi)) * RAD_TO_DEG;
    this->Z = r * std::cos(newTheta)  * RAD_TO_DEG;
}

#endif 

#ifdef STANDARD_ANGLE_UNIT_RAD

void Vec3D::rotateThisVector(double Phi, double Theta){
    double r = this->radius;
    double theta = this->theta;
    double phi = this->phi;

    double newTheta = theta + Theta;
    double newPhi = phi + Phi;

    this->X = (r * std::sin(newTheta) * std::cos(newPhi)) * RAD_TO_DEG;
    this->Y = (r * std::sin(newTheta) * std::sin(newPhi)) * RAD_TO_DEG;
    this->Z = r * std::cos(newTheta)  * RAD_TO_DEG;
}

#endif 

#ifdef STANDARD_ANGLE_UNIT_RAD
Vec2D Vec2D::rotateVector(double angle) {
  double newX = this->getX() * std::cos(angle) - this->getY() * std::sin(angle);
  double newY = this->getX() * std::sin(angle) + this->getY() * std::cos(angle);
  return Vec2D(newX, newY);
}
#endif

#ifdef STANDARD_ANGLE_UNIT_DEG
Vec2D Vec2D::rotateVector(double vlaue) {
  double newX = this->getX() * std::cos(angle) - this->getY() * std::sin(angle);
  double newY = this->getX() * std::sin(angle) + this->getY() * std::cos(angle);
  newX = newX * RAD_TO_DEG;
  newY = newY * RAD_TO_DEG:
  return Vec2D(newX, newY);
}
#endif

#ifdef STANDARD_ANGLE_UNIT_RAD
void Vec2D::rotateThisVector(double value){
  this->X = this->getX() * std::cos(value) - this->getY() * std::sin(value);
  this->Y = this->getX() * std::sin(value) + this->getY() * std::cos(value);
  this->vectorRotation = value;
}
#endif

#ifdef STANDARD_ANGLE_UNIT_DEG
void Vec2D::rotateThisVectorDEG(double degrees){
  double newX = this->getX() * std::cos(degrees) - this->getY() * std::sin(degrees);
  double newY = this->getX() * std::sin(degrees) + this->getY() * std::cos(degrees);
  this->X    = newX * RAD_TO_DEG;
  this->Y    = newY * RAD_TO_DEG;
  this->vectorRotation = degrees;
}

#endif


#endif