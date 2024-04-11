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

CoordinateSystem2D::CoordinateSystem2D(float x, float y) {
  this->X = x;
  this->Y = y;
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
  this->abs = pyth2D(this->X, this->Y);
}

CoordinateSystem2D::CoordinateSystem2D(float radius, float phi) {
  this->radius = radius;
  this->phi = phi;
  this->abs = pyth2D(this->X, this->Y);
}
#endif

#ifdef CARTESIAN_IS_3D_STANDARD
CoordinateSystem3D::CoordinateSystem3D(float X, float Y, float Z)
    : CoordinateSystem2D(X, Y) {
  this->Z = Z;
  this->abs = pyth3D(this->X, this->Y, this->Z);
}

CoordinateSystem3D::CoordinateSystem3D(float X, float Y, float Z, float originX,
                                       float originY)
    : CoordinateSystem2D(X, Y, originX, originY) {
  this->Z = Z;
  this->abs = pyth3D(this->X, this->Y, this->Z);
}
#endif

#ifdef SPHERE_IS_STANDARD
CoordinateSystem3D::CoordinateSystem3D(float radius, float phi, float theta)
    : CoordinateSystem2D(radius, phi) {
  this->theta = theta;
}
CoordinateSystem3D::CoordinateSystem3D(float radius, float phi, float theta,
                                       float originX, float originY)
    : CoordinateSystem2D(radius, phi, originX, originY) {
  this->theta = theta;
}
#endif

#ifdef CYLINDER_IS_STANDARD
CoordinateSystem3D::CoordinateSystem3D(float radius, float phi, float height)
    : CoordinateSystem2D(radius, phi) {
  this->height = height;
}
CoordinateSystem3D::CoordinateSystem3D(float radius, float phi, float height,
                                       float originX, float originY)
    : CoordinateSystem2D(radius, phi, originX, originY) {
  this->height = height;
}
#endif
float CoordinateSystem2D::getX() { return this->X; }
float CoordinateSystem2D::getY() { return this->Y; }
float CoordinateSystem2D::getPhi() { return this->phi; }
float CoordinateSystem2D::getRadius() { return this->radius; }
float CoordinateSystem3D::getTheta() { return this->theta; }
float CoordinateSystem3D::getHeight() { return this->height; }
float CoordinateSystem3D::getZ() { return this->Z; }
float CoordinateSystem3D::getRadiusSphere() {
  return pyth3D(this->X, this->Y, this->Z);
}
float CoordinateSystem3D::getRadiusCylinder() {
  return pyth2D(this->X, this->Y);
}

#endif