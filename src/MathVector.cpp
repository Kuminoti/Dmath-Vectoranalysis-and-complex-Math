#include "../include/mathVector.hpp"

using namespace Dmath;
// Helper functions:

//Operator overloading

Vec2D Vec2D::operator+(Vec2D &Mathvector) {
  float resultX = this->X + Mathvector.X;
  float resultY = this->Y + Mathvector.Y;

  return Vec2D(resultX, resultY);
}

Vec2D Vec2D::operator-(Vec2D &Mathvector) {
  float resultX = this->X - Mathvector.X;
  float resultY = this->Y - Mathvector.Y;

  return Vec2D(resultX, resultY);
}

float Vec2D::operator*(Vec2D &Mathvector) {
  return this->dotProduct(Mathvector);
}

Vec3D Vec3D::operator+(Vec3D &Mathvector) {
  float resultX = this->X + Mathvector.X;
  float resultY = this->Y + Mathvector.Y;
  float resultZ = this->Z + Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}

Vec3D Vec3D::operator-(Vec3D &Mathvector) {
  float resultX = this->X - Mathvector.X;
  float resultY = this->Y - Mathvector.Y;
  float resultZ = this->Z - Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}

float Vec3D::operator*(Vec3D &Mathvector) {
  return this->dotProduct(Mathvector);
}

// Calculate cosine of the angle between two vectors
float cosAngle(float dotProduct, float absProduct) {
  float result = 0;
  if (absProduct == 0) {
    std::cerr << "Vector abs is Zero" << std::endl;
    result = 0;
  } else {
    result = dotProduct / absProduct;
  }
  return result;
}

float angleFromCos(float cosTheta) {
  float result = 0;
  if (cosTheta > 1 || cosTheta < -1) {
    std::cerr << "Error: cos(theta) wrong value" << std::endl;
    result = 0;
  } else {
    result = std::acos(cosTheta) * 180 / PI;
  }
  return result;
}


void Vec2D::calcAbsXY(){
  if(this->originX != 0 || this->originY != 0){
    this->aX = this->X + this->originX;
    this->aY = this->Y + this->originY;
  }
}





// Vec2D functions:

Vec2D Vec2D::rotateVector(float angle) {
  float newX = this->getX() * std::cos(angle) - this->getY() * std::sin(angle);
  float newY = this->getX() * std::sin(angle) + this->getY() * std::cos(angle);
  return Vec2D(newX, newY);
}

float Vec2D::distance(Vec2D Mathvector){
  
    float dx = std::abs(Mathvector.aX - this->aX);
    float dy = std::abs(Mathvector.aY - this->aY);
    float result =  std::sqrt(dx * dx + dy * dy);
    return result;
}

float Vec2D::calcAngle(Vec2D Mathvector) {
  float product = this->dotProduct(Mathvector);
  float absProduct = this->getAbs() * Mathvector.getAbs();
  float cosTheta = cosAngle(product, absProduct);
  return angleFromCos(cosTheta);
}



float Vec2D::polarSystemArea() {
  float Area = PI * (this->radius * this->radius);
  return Area;
}

float Vec2D::polarSystemCircumfrance() {
  float Area = TWOPI * this->radius;
  return Area;
}

void Vec2D::setX(float value) {
  this->X = value;
  this->cartesianToPolar();
}

void Vec2D::setY(float value) {
  this->Y = value;
  this->cartesianToPolar();
}

void Vec2D::setPhi(float value) {
  this->phi = value;
  this->polarToCartesian();
}

void Vec2D::setRadius(float value) {
  this->radius = value;
  this->polarToCartesian();
}

void Vec2D::setOriginX(float move){
  this->originX = move;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::setOriginY(float move){
  this->originY = move;
  this->calcAbsXY();
  this->calcDZ();
}


void Vec2D::moveVectorX(float move){
  this->originX += move;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::moveVectorY(float move){
  this->originY += move;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::moveVector(float moveX, float moveY){
  this->originX += moveX;
  this->originY += moveY;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::calcAbs() {
  float result = std::sqrt((this->X * this->X) + (this->Y * this->Y));
  this->abs = result;
}


void Vec2D::calcDZ(){
  if(this->originX == 0 && this-> originY == 0){
    this->distanceToZero = 0;
    return;
  }
  else if(this->originX != 0 && this->originY == 0){
    this->distanceToZero = this->originX;
    return;
  }
  else if(this->originY != 0 && this->originX == 0){
    this->distanceToZero = this->originY;
    return;
  }
  float result = 0;
  this->calcAbsXY();
  //AYS absolute Y sqared ...
  float AXS = this->aX * this->aX;
  float AYS = this->aY * this->aY;
  result = std::sqrt(AYS + AYS);
  this->distanceToZero = result;
}


float Vec2D::dotProduct(Vec2D Mathvector) {
  float result = this->X * Mathvector.X + this->Y * Mathvector.Y;
  return result;
}

Vec2D Vec2D::add(Vec2D Mathvector) {
  float resultX = this->X + Mathvector.X;
  float resultY = this->Y + Mathvector.Y;
  return Vec2D(resultX, resultY);
}

Vec2D Vec2D::subtract(Vec2D Mathvector) {
  float resultX = this->X - Mathvector.X;
  float resultY = this->Y - Mathvector.Y;
  return Vec2D(resultX, resultY);
}

Vec2D Vec2D::polarVector(float radius, float angle) {
  float xValue = radius * std::cos(angle);
  float yValue = radius * std::sin(angle);
  return Vec2D(xValue, yValue);
}

float Vec2D::rectangleArea(Vec2D MathVector) {
  float Area = this->getAbs() * MathVector.getAbs();
  return Area;
}

float Vec2D::rectangleCircumfrance(Vec2D MathVector) {
  float Circumfrance = 2 * this->getAbs() + 2 * MathVector.getAbs();
  return Circumfrance;
}


















void Vec3D::calcAXYZ(){
  if(this->originX != 0 || this->originY != 0){
      this->aX = this->X + this->originX;
      this->aY = this->Y + this->originY;
      this->aZ = this->Z + this->originZ;
    }
}

void Vec3D::calcDTZ(){
 if(this->originX == 0 && this->originY == 0 && this->originZ == 0){
    this->distanceToZero = 0;
    return;
  }
  float result = 0;
  this->calcAXYZ();
  //AYS absolute Y sqared ...
  float AXS = this->aX * this->aX;
  float AYS = this->aY * this->aY;
  result = std::sqrt(AYS + AYS);
  this->distanceToZero = result;  
}

void Vec3D::calcAbs() {
  float result = std::sqrt((this->X * this->X) + (this->Y * this->Y) +
                           (this->Z * this->Z));
  this->abs = result;
}

float Vec3D::calcAngle(Vec3D Mathvector) {
  float product = this->dotProduct(Mathvector);
  float absProduct = this->getAbs() * Mathvector.getAbs();
  float cosTheta = cosAngle(product, absProduct);
  return angleFromCos(cosTheta);
}

float Vec3D::dotProduct(Vec3D Mathvector) {
  float result =
      this->X * Mathvector.X + this->Y * Mathvector.Y + this->Z * Mathvector.Z;
  return result;
}

Vec3D Vec3D::vecProduct(Vec3D Mathvector) {
  float resultX = this->Y * Mathvector.Z - this->Z * Mathvector.Y;
  float resultY = this->Z * Mathvector.X - this->X * Mathvector.Z;
  float resultZ = this->X * Mathvector.Y - this->Y * Mathvector.X;
  return Vec3D(resultX, resultY, resultZ);
}


Vec3D Vec3D::add(Vec3D Mathvector) {
  float resultX = this->X + Mathvector.X;
  float resultY = this->Y + Mathvector.Y;
  float resultZ = this->Z + Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}
 

Vec3D Vec3D::subtract(Vec3D Mathvector) {
  float resultX = this->X - Mathvector.X;
  float resultY = this->Y - Mathvector.Y;
  float resultZ = this->Z - Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}


Vec3D Vec3D::sphereVector(float radius, float angleOne, float angleTwo) {
  float Xvalue = radius * std::sin(angleTwo) * std::cos(angleOne);
  float Yvalue = radius * std::sin(angleTwo) * std::sin(angleOne);
  float Zvalue = radius * std::cos(angleTwo);
  return Vec3D(Xvalue, Yvalue, Zvalue);
}

Vec3D Vec3D::cylinderVector(float radius, float angle, float height) {
  float Xvalue = radius * std::cos(angle);
  float Yvalue = radius * std::sin(angle);
  float Zvalue = height;
  return Vec3D(Xvalue, Yvalue, Zvalue);
}

float Vec3D::sphereSystemVolume() {
  // formula: 4/3 π * r³
  float fourThreePi = (4 / 3) * PI;
  float radiusCubed = (this->radius * this->radius * this->radius);
  float result = fourThreePi * radiusCubed;
  return result;
}

float Vec3D::sphereSystemSurface() {
  // formula: 4π * radius²
  float result = FOUR_PI * (this->radius * this->radius);
  return result;
}

float Vec3D::cylinderSystemVolume() {
  // formula B * h
  float baseSide = PI * (this->radius * this->radius);
  return baseSide * this->height;
}

float Vec3D::cylinderSystemSurface() {
  // formula: Baseside * LateralSurface
  float baseSide = PI * (this->radius * this->radius);
  float LateralSurface = this->cylinderSystemLateralSurface();
  return 2 * baseSide * LateralSurface;
}

float Vec3D::cylinderSystemLateralSurface() {
  // formula: 2π * r * h
  float result = TWOPI * this->radius * this->height;
  return result;
}

Vec3D Vec3D::zeroVector() { return Vec3D(0, 0, 0); }

float Vec3D::cuboidVolume(Vec3D MathVector, Vec3D MathVectorTwo) {
  // formula: A*B*C or in this case: |vector1| * |vector2| * |vector3|
  float A = this->getAbs();
  float B = MathVector.getAbs();
  float C = MathVectorTwo.getAbs();
  float result = A * B * C;
  return result;
}

float Vec3D::cuboidSurface(Vec3D MathVector, Vec3D MathVectorTwo) {
  float productOne = this->dotProduct(MathVector);
  float productTwo = this->dotProduct(MathVectorTwo);
  float productThree = MathVector.dotProduct(MathVectorTwo);
  float result = 2 * (productOne + productTwo + productThree);
  return result;
}

float Vec3D::getCylinderRadius(){
    float  result = std::sqrt((this->X*this->X)+(this->Y*this->Y));
    return result;
}

float Vec3D::getSphereRadius(){
    float  result = std::sqrt((this->X*this->X)+(this->Y*this->Y)+(this->Y*this->Y));
    return result;
}

#ifdef CARTESIAN_IS_2D_STANDARD

Vec2D::Vec2D(float XY) : CoordinateSystem2D(XY){
  this->aX = XY;
  this->aY = XY;
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D::Vec2D(float X, float Y) : CoordinateSystem2D(X, Y) {
  this->aX = X;
  this->aY = Y;
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D::Vec2D(float X, float Y, float originX, float originY)
    : CoordinateSystem2D(X, Y, originX, originY) {
  this->calcAbsXY();
  this->calcDZ();
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D Vec2D::zeroVector() { return Vec2D(0, 0); }

#endif

#ifdef POLAR_IS_STANDARD
Vec2D::Vec2D(float radius, float phi) : CoordinateSystem2D(radius, phi) {
  this->calcAbs();
  this->polarToCartesian();
  this->aX = this->X;
  this->aY = this->Y;
}

#endif

#ifdef SPHERE_IS_STANDARD
Vec3D::Vec3D(float radius, float phi, float theta)
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
Vec3D::Vec3D(float radius, float phi, float height)
    : CoordinateSystem3D(radius, phi, height) {

  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->aX = this->X;
  this->aY = this->Y;
  this->aZ = this->Z;
}
#endif

#ifdef CARTESIAN_IS_3D_STANDARD

Vec3D::Vec3D(float XYZ) : CoordinateSystem3D(XYZ) {
  
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();  
  this->aX = XYZ;
  this->aY = XYZ;
  this->aZ = XYZ;
}

Vec3D::Vec3D(float X, float Y, float Z, float originX, float originY, float originZ)
    : CoordinateSystem3D(X, Y, Z, originX, originY, originZ) {
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();
  this->calcAXYZ();
  this->calcDTZ();
}

Vec3D::Vec3D(float X, float Y, float Z) : CoordinateSystem3D(X, Y, Z) {
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();
  this->aX = this->X;
  this->aY = this->Y;
  this->aZ = this->Z;
}
#endif


float Vec3D::getAbs()               { return this->abs; }
float Vec2D::getAbs()               { return this->abs;      }
float Vec2D::lenght()               { return this->getAbs(); }
float Vec2D::getAX()                { return this->aX;       }
float Vec2D::getAY()                { return this->aY;       }
float Vec2D::getDistanceToZero()    { return this->distanceToZero;}
void Vec3D::setX(float X)           { this->X = X; }
void Vec3D::setY(float Y)           { this->Y = Y; }
void Vec3D::setZ(float Z)           { this->Z = Z; }
void Vec3D::setHeight(float height) { this->height = height; }
void Vec3D::setPhi(float phi)       { this->phi = phi; }
void Vec3D::setTheta(float theta)   { this->theta = theta; }