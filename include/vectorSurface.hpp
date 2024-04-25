#pragma once

#ifndef VECTOR_SURFACE_HPP
#define VECTOR_SURFACE_HPP

#include"VectorCurve.hpp"

NAMESPACESTART
class VectorSurface : public VectorAnalysis3D{
  private:
    std::function<float(float, float)> xFunc;
    std::function<float(float, float)> yFunc;
    std::function<float(float, float)> zFunc;

    std::vector<Dmath::Vec3D> mainSurface;
    std::vector<Dmath::Vec3D> surfaceNormals;


    Dmath::Vec3D calculatePartialDerivativeU(float u, float v) {
        // Hier berechnest du die partielle Ableitung nach u
        float epsilon = 0.001; // Kleiner Wert für die numerische Ableitung
        float du_x = (xFunc(u + epsilon, v) - xFunc(u - epsilon, v)) / (2 * epsilon);
        float du_y = (yFunc(u + epsilon, v) - yFunc(u - epsilon, v)) / (2 * epsilon);
        float du_z = (zFunc(u + epsilon, v) - zFunc(u - epsilon, v)) / (2 * epsilon);

        return Dmath::Vec3D(du_x, du_y, du_z);
    }

    Dmath::Vec3D calculatePartialDerivativeV(float u, float v) {
        // Hier berechnest du die partielle Ableitung nach v
        float epsilon = 0.001; // Kleiner Wert für die numerische Ableitung
        float dv_x = (xFunc(u, v + epsilon) - xFunc(u, v - epsilon)) / (2 * epsilon);
        float dv_y = (yFunc(u, v + epsilon) - yFunc(u, v - epsilon)) / (2 * epsilon);
        float dv_z = (zFunc(u, v + epsilon) - zFunc(u, v - epsilon)) / (2 * epsilon);

        return Dmath::Vec3D(dv_x, dv_y, dv_z);
    }

    void createVectorSurface() {
        size_t iterations = 0;
        for (float i = systemStart; i <= systemStopp; i += resolution) {
            for (float j = systemStart; j <= systemStopp; j += resolution) {
                if (iterations == 0) {
                    mainSurface.push_back(Dmath::Vec3D(xFunc(i, j), yFunc(i, j), zFunc(i, j)));
                } else {
                    mainSurface.push_back(
                        Dmath::Vec3D(xFunc(i, j), yFunc(i, j), zFunc(i, j),
                        mainSurface[iterations].getOriginX(),
                        mainSurface[iterations].getOriginY(),
                        mainSurface[iterations].getOriginZ())
                    );
                }
                iterations++;
            }
        }
    }

    VectorSurface(std::function<float(float, float)> xFunc, std::function<float(float, float)> yFunc,
        std::function<float(float, float)> zFunc, float systemStart, float systemStopp, float resolution) :
        VectorAnalysis3D(systemStart,systemStopp,resolution){
        this->xFunc = xFunc;
        this->yFunc = yFunc;
        this->zFunc = zFunc;
        this->createVectorSurface();
        this->calculateSurfaceNormals();
    }

  public:
    static VectorSurface createStandardSurface(std::function<float(float, float)> xFunc, std::function<float(float, float)> yFunc,
        std::function<float(float, float)> zFunc){
        return VectorSurface(xFunc,yFunc,zFunc,ZERO,TWOPI,STDRES);
    }

    static VectorSurface createCustomSurface(std::function<float(float, float)> xFunc, std::function<float(float, float)> yFunc,
        std::function<float(float, float)> zFunc, float systemStart, float systemStopp, float resolution){
        return VectorSurface(xFunc,yFunc,zFunc,systemStart,systemStopp,resolution);
    }

        void calculateSurfaceNormals() {
        size_t iterations = 0;
        for (float i = systemStart; i <= systemStopp; i += resolution) {
            for (float j = systemStart; j <= systemStopp; j += resolution) {
                // Berechne partielle Ableitungen nach u und v
                Dmath::Vec3D du = calculatePartialDerivativeU(i, j);
                Dmath::Vec3D dv = calculatePartialDerivativeV(i, j);

                // Berechne die Flächennormale als Kreuzprodukt
                Dmath::Vec3D normal = du.vecProduct(dv);// Normalisierung für Einheitsnormalenvektor
                normal.normalize();
                surfaceNormals.push_back(normal);
                iterations++;
            }
        }
    }


};

NAMESPACEEND

#endif //VECTOR_SURFACE_HPP