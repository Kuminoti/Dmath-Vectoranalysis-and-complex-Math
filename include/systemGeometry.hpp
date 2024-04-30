#pragma once

#ifndef SYSTEMGEOMETRY_HPP
#define SYSTEMGEOMETRY_HPP

#include"mathVector.hpp"

#ifdef SYSTEM_READY



NAMESPACESTART

class Vec3D;

class SystemGeometry{
public:
  double cylinderSystemVolume(Dmath::Vec3D vector);
  double cylinderSystemSurface(Dmath::Vec3D vector);
  double cylinderSystemLateralSurface(Dmath::Vec3D vector);

  double sphereSystemVolume(Dmath::Vec3D vector);
  double sphereSystemSurface(Dmath::Vec3D vector);

  double cuboidVolume(Dmath::Vec3D mainVector, Dmath::Vec3D MathVector, Dmath::Vec3D MathVectorTwo);
  double cuboidSurface(Dmath::Vec3D mainVector, Dmath::Vec3D MathVector, Dmath::Vec3D MathVectorTwo);
};
NAMESPACEEND

#endif//SYSTEM_READY

#endif//SYSTEMGEOMETRY_HPP