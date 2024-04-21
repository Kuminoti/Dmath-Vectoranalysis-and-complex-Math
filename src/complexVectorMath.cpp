#include"../include/complexVectorMath.hpp"



//2D curves



std::vector<Dmath::Vec2D> Dmath::VectorCurve2D::createVectorialCurve(){
    std::vector<Dmath::Vec2D> output;
    int iterations = 0;
    for(double i = this->curveStart; i<curveStopp; i+=resolution){
        if(i == this->curveStart){
            output.push_back(Dmath::Vec2D(this->mainXFunc(i),this->mainXFunc(i),0,0));
            iterations++;
        } else {

            output.push_back(Dmath::Vec2D(this->mainXFunc(i),this->mainYFunc(i),output[iterations-1].getX(),output[iterations-1].getY()));
            iterations++;
        }
    }
    return output;
}



Dmath::VectorCurve2D::VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc){
    this->mainXFunc = xFunc;
    this->mainYFunc = yFunc;
    this->numberOfElements = static_cast<int>((this->curveStopp - this->curveStart) / this->resolution);
    this->mainCurve = this->createVectorialCurve();
}

Dmath::VectorCurve2D::VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res){
    this->mainXFunc = xFunc;
    this->mainYFunc = yFunc;
    this->curveStart = start;
    this->curveStopp = stopp;
    this->resolution = res;
    this->numberOfElements = static_cast<int>((this->curveStopp - this->curveStart) / this->resolution);
    this->mainCurve = this->createVectorialCurve();
    
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY ){
    return Dmath::VectorCurve2D(funcX,funcY);
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::createCustomCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,float start,float stopp,float res ){
    return Dmath::VectorCurve2D(funcX,funcY,start,stopp,res);
}


Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromPoint(float point){
    if(point > this->curveStopp || point < this->curveStart){
        std::cerr << "Error index out of limit! \n Returning a null vector \n" ;
            return Dmath::Vec2D::zeroVector();
        }
    int foundPoint = static_cast<int> (point/this->resolution);
    Dmath::Vec2D outputVector = this->mainCurve[foundPoint];
    return outputVector;
}

Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromFunction(float vecX, float vecY){
    float xValue = this->mainXFunc(vecX);
    float yValue = this->mainYFunc(vecY);
    Dmath::Vec2D outputVector(xValue, yValue);
    return outputVector;
}


Dmath::Vec2D Dmath::VectorCurve2D::tangentVector(float t){
    float h = 0.000001; 
    float x_t_plus_h = this->mainXFunc(t + h);
    float x_t_minus_h = this->mainXFunc(t - h);
    float y_t_plus_h = this->mainYFunc(t + h);
    float y_t_minus_h = this->mainYFunc(t - h);

    float dx = (x_t_plus_h - x_t_minus_h) / (2 * h); 
    float dy = (y_t_plus_h - y_t_minus_h) / (2 * h); 

    return Dmath::Vec2D(dx, dy); 
}

float Dmath::VectorCurve2D::curveLenght(){
        float lenght = 0;
        for(int i = 0; i<this->mainCurve.size(); i++){
            std::cout << this->mainCurve[i].getAbs() <<std::endl;
            lenght += this->mainCurve[i].getAbs();
        }
        lenght = lenght*resolution;
        return lenght;
    }



//3D curves
std::vector<Dmath::Vec3D> Dmath::VectorCurve3D::createVectorCurve(){
    std::vector<Dmath::Vec3D> output;
    for(double i = 0; i<this->numberOfElements; i+= this->resolution){
        output.push_back(Dmath::Vec3D(this->mainXFunc(i),this->mainYFunc(i),this->mainZFunc(i)));
    }
    return output;
}

std::vector<Dmath::Vec3D> Dmath::VectorCurve3D::createVectorialCurve(){
    std::vector<Dmath::Vec3D> output;
    int iterations = 0;
    for(double i = this->curveStart; i<curveStopp; i+=resolution){
        if(i == this->curveStart){
            output.push_back(Dmath::Vec3D(this->mainXFunc(i),this->mainYFunc(i), this->mainZFunc(i),0,0,0));
            iterations++;
        } else {
            output.push_back(Dmath::Vec3D(this->mainXFunc(i),this->mainYFunc(i),this->mainZFunc(i),output[iterations-1].getX(),output[iterations-1].getY(),output[iterations-1].getZ()));
            iterations++;
        }
    }
    return output;
}



Dmath::VectorCurve3D::VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc,std::function<float(float)> zFunc){
    this->mainXFunc = xFunc;
    this->mainYFunc = yFunc;
    this->mainZFunc = zFunc;
    this->numberOfElements = static_cast<int>((this->curveStopp - this->curveStart) / this->resolution);
    this->mainCurve = this->createVectorCurve();
}

Dmath::VectorCurve3D::VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc,std::function<float(float)> zFunc, float start, float stopp, float res){
    this->mainXFunc = xFunc;
    this->mainYFunc = yFunc;
    this->mainZFunc = zFunc;
    this->curveStart = start;
    this->curveStopp = stopp;
    this->resolution = res;
    this->numberOfElements = static_cast<int>((this->curveStopp - this->curveStart) / this->resolution);
    this->mainCurve = this->createVectorCurve();
}

Dmath::VectorCurve3D Dmath::VectorCurve3D::createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,std::function<float(float)> zFunc ){
    return Dmath::VectorCurve3D(funcX,funcY,zFunc);
}

Dmath::VectorCurve3D Dmath::VectorCurve3D::createCustomCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,std::function<float(float)> zFunc, float start,float stopp,float res ){
    return Dmath::VectorCurve3D(funcX,funcY,zFunc,start,stopp,res);
}

Dmath::Vec3D  Dmath::VectorCurve3D::getVectorFromFunction(float xValue, float yValue, float zValue){
    float vecX = this->mainXFunc(xValue);
    float vecY = this->mainYFunc(yValue);
    float vecZ = this->mainZFunc(zValue);
    Dmath::Vec3D outputVector(vecX,vecY,vecZ);
    return outputVector;
}

Dmath::Vec3D Dmath::VectorCurve3D::getVectorFromPoint(float point){
    if(point > this->curveStopp || point < this->curveStart){
        std::cerr << "Error index out of limit! \n Returning a null vector \n" ;
        return Dmath::Vec3D::zeroVector();
    }
    int foundPoint = static_cast<int> (point/this->resolution);
    Dmath::Vec3D outputVector = this->mainCurve[foundPoint];
    return outputVector;
}


Dmath::Vec3D  Dmath::VectorCurve3D::tangentVector(float t){
    float h = 0.00000001; // Kleine Schrittweite
    float x_t_plus_h = this->mainXFunc(t + h);
    float x_t_minus_h = this->mainXFunc(t - h);
    float y_t_plus_h = this->mainYFunc(t + h);
    float y_t_minus_h = this->mainYFunc(t - h);
    float z_t_plus_h = this->mainZFunc(t + h);
    float z_t_minus_h = this->mainZFunc(t - h);

    // Überprüfung, ob die Funktionswerte positiv oder negativ sind
    bool x_positive = (x_t_plus_h >= 0) && (x_t_minus_h >= 0);
    bool y_positive = (y_t_plus_h >= 0) && (y_t_minus_h >= 0);
    bool z_positive = (y_t_plus_h >= 0) && (y_t_minus_h >= 0);

    // Berechnung des Tangentialvektors
    float dx = (x_t_plus_h - x_t_minus_h) / (2 * h); // Zentrale Differenz für die Ableitung von x nach t
    float dy = (y_t_plus_h - y_t_minus_h) / (2 * h); // Zentrale Differenz für die Ableitung von y nach t
    float dz = (z_t_plus_h - z_t_minus_h) / (2 * h); // Zentrale Differenz für die Ableitung von y nach t
    // Wenn die Funktionswerte negativ sind, invertiere den Tangentialvektor
    if (!x_positive) dx = -dx;
    if (!y_positive) dy = -dy;

    return Dmath::Vec3D(dx, dy,dz); // Tangentialvektor
}


float Dmath::VectorCurve3D::curveLenght(){
    float lenght = 0;
    for(int i = 0; i<this->mainCurve.size(); i++){
        lenght += this->mainCurve[i].getAbs();
    }
    return lenght;
}