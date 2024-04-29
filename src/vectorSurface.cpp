#include"../include/vectorSurface.hpp"



Dmath::VectorSurface::VectorSurface(std::function<double(double, double)> xFunc, std::function<double(double, double)> yFunc,
    std::function<double(double, double)> zFunc, double systemStart, double systemStopp, double resolution) :
    VectorAnalysis3D(systemStart,systemStopp,resolution){
    this->xFunc = xFunc;
    this->yFunc = yFunc;
    this->zFunc = zFunc;
    this->createVectorSurface();
    this->calculateSurfaceNormals();
}

double Dmath::VectorSurface::integrateSurfaceArea() {
    double area = 0.0;
    for (size_t i = 0; i < this->mainSurface.size(); ++i) {
        Dmath::Vec3D du = this->calculatePartialDerivativeU(this->mainSurface[i].getX(), this->mainSurface[i].getY());
        Dmath::Vec3D dv = this->calculatePartialDerivativeV(this->mainSurface[i].getX(), this->mainSurface[i].getY());
        Dmath::Vec3D normal = du.vecProduct(dv);
        double local_area = normal.getAbs();
        area += local_area;
    }
    return area;
}


Dmath::VectorSurface Dmath::VectorSurface::createCustomSurface(std::function<double(double, double)> xFunc, std::function<double(double, double)> yFunc,
    std::function<double(double, double)> zFunc, double systemStart, double systemStopp, double resolution){
    return VectorSurface(xFunc,yFunc,zFunc,systemStart,systemStopp,resolution);
}

Dmath::VectorSurface Dmath::VectorSurface::createStandardSurface(std::function<double(double, double)> xFunc, std::function<double(double, double)> yFunc,
    std::function<double(double, double)> zFunc){
    return VectorSurface(xFunc,yFunc,zFunc,ZERO,TWOPI,STDRES);
}

Dmath::Vec3D Dmath::VectorSurface::calculatePartialDerivativeU(double u, double v) {
    double du_x = (this->xFunc(u + this->epsilon, v) - this->xFunc(u - this->epsilon, v)) / (2 * this->epsilon);
    double du_y = (this->yFunc(u + this->epsilon, v) - this->yFunc(u - this->epsilon, v)) / (2 * this->epsilon);
    double du_z = (this->zFunc(u + this->epsilon, v) - this->zFunc(u - this->epsilon, v)) / (2 * this->epsilon);

    return Dmath::Vec3D(du_x, du_y, du_z);
}


Dmath::Vec3D Dmath::VectorSurface::calculatePartialDerivativeV(double u, double v) {       
    double dv_x = (this->xFunc(u, v + this->epsilon) - this->xFunc(u, v - this->epsilon)) / (2 * this->epsilon);
    double dv_y = (this->yFunc(u, v + this->epsilon) - this->yFunc(u, v - this->epsilon)) / (2 * this->epsilon);
    double dv_z = (this->zFunc(u, v + this->epsilon) - this->zFunc(u, v - this->epsilon)) / (2 * this->epsilon);

    return Dmath::Vec3D(dv_x, dv_y, dv_z);
}

void Dmath::VectorSurface::createVectorSurface() {
    size_t iterations = 0;
    for (double i = this->systemStart; i <= this->systemStopp; i += this->resolution) {
        for (double j = this->systemStart; j <= this->systemStopp; j += this->resolution) {
            if (iterations == 0) {
                this->mainSurface.push_back(Dmath::Vec3D(xFunc(i, j), yFunc(i, j), zFunc(i, j)));
            } else {
                this->mainSurface.push_back(
                    Dmath::Vec3D(xFunc(i, j), yFunc(i, j), zFunc(i, j),
                    this->mainSurface[iterations].getOriginX(),
                    this->mainSurface[iterations].getOriginY(),
                    this->mainSurface[iterations].getOriginZ())
                );
            }
            iterations++;
        }
    }
}




void Dmath::VectorSurface::calculateSurfaceNormals() {
    size_t iterations = 0;
    for (double i = this->systemStart; i <= this->systemStopp; i += this->resolution) {
        for (double j = this->systemStart; j <= this->systemStopp; j += this->resolution) {
            // Berechne partielle Ableitungen nach u und v
            Dmath::Vec3D du = this->calculatePartialDerivativeU(i, j);
            Dmath::Vec3D dv = this->calculatePartialDerivativeV(i, j);

            Dmath::Vec3D normal = du.vecProduct(dv);
            normal.normalize();
            this->surfaceNormals.push_back(normal);
            iterations++;
        }
    }
}

Dmath::Vec3D Dmath::VectorSurface::getVectorAtPointT(double t){
        if(t <= this->systemStopp && t >= this->systemStart){
            double t_index = t / this->resolution;
            return this->mainSurface[t_index];
        } else {
            return Dmath::Vec3D::zeroVector();
        }
    }

double Dmath::VectorSurface::maxX(){
    double max = 0;
    for(size_t i = 0; i< this->mainSurface.size(); i++){
        if(this->mainSurface[i].getX() > max){
            max = this->mainSurface[i].getX();
        } else {
            continue;
        }
    }
    return max;

}

double Dmath::VectorSurface::maxY(){
    double max = 0;
    for(size_t i = 0; i< this->mainSurface.size(); i++){
        if(this->mainSurface[i].getY() > max){
            max = this->mainSurface[i].getY();
        } else {
            continue;
        }
    }
    return max;

}

double Dmath::VectorSurface::maxZ(){
    double max = 0;
    for(size_t i = 0; i< this->mainSurface.size(); i++){
        if(this->mainSurface[i].getZ() > max){
            max = this->mainSurface[i].getZ();
        } else {
            continue;
        }
    }
    return max;
}



double Dmath::VectorSurface::minX(){
    double min = this->mainSurface[0].getX();
    for(size_t i = 0; i< this->mainSurface.size(); i++){
        if(this->mainSurface[i].getX() < min){
            min = this->mainSurface[i].getX();
        } else {
            continue;
        }
    }
    return min;
}

double Dmath::VectorSurface::minY(){
    double min = this->mainSurface[0].getY();
    for(size_t i = 0; i< this->mainSurface.size(); i++){
        if(this->mainSurface[i].getY() < min){
            min = this->mainSurface[i].getY();
        } else {
            continue;
        }
    }
    return min;
}

double Dmath::VectorSurface::minZ(){
    double min = this->mainSurface[0].getZ();
    for(size_t i = 0; i< this->mainSurface.size(); i++){
        if(this->mainSurface[i].getZ() < min){
            min = this->mainSurface[i].getZ();
        } else {
            continue;
        }
    }
    return min;
}


double Dmath::VectorSurface::calculatePerimeter() {
    double perimeter = 0.0;
    size_t numPoints = this->mainSurface.size();

    perimeter += (mainSurface[numPoints - 1] - mainSurface[0]).getAbs();

    for (size_t i = 1; i < numPoints; ++i) {
        perimeter += (mainSurface[i] - mainSurface[i - 1]).getAbs();
    }

    return perimeter;
}