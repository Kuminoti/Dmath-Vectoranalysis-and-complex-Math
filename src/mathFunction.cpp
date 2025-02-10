#include"../include/mathFunction.hpp"

#pragma region SingleVar

bool Dmath::SingleVarFunction::checkParams(Dmath::Parameters params){
        if(params.one >= params.two || params.three == 0){
            return 0;
        }
    return true;
    }





std::vector<double>  Dmath::SingleVarFunction::getFunctionVector(double start, double stopp, double stepps){
    //Error checking: 

    if(start >= stopp || stepps == 0){
        return std::vector<double>(0);
    }

    Dmath::Parameters params(start,stopp,stepps);
    const size_t num = this->numOfElements(params);
 
    std::vector<double> mainVec;

    for(size_t i = 0; i < num; i++){
        double currentResult = funcBase->Callx((start + i*stepps));
        mainVec.push_back(currentResult);
    }
    return mainVec;
}


std::vector<double> Dmath::SingleVarFunction::getDerivativeVector(double start, double stopp, double stepps){

    //It,s simpler to use a struct in stet of all args inside the class 
    Dmath::Parameters params(start,stopp,stepps);
    
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }

    //Number of elements
    const size_t num = this->numOfElements(params);
    
    std::vector<double> mainVector;

    for(size_t i = 0; i < num; i++){

        double x = start + i * stepps; // Current x value
        double plusDX  = this->funcBase->Callx(x + dx); // f(x + dx)
        double minusDX = this->funcBase->Callx(x - dx); // f(x - dx)
        double result  = (plusDX - minusDX) / (2 * dx); // Central difference method

        mainVector.push_back(result); // Store the result

    }
    return mainVector;
}

std::vector<double> Dmath::SingleVarFunction::getSecondDerivative(double start, double stopp, double stepps){
    const Dmath::Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
    const size_t num = this->numOfElements(params);
    std::vector<double> mainVector;
    for(size_t i = 0; i < num; i++){
        const double x = start + i * stepps;
        const double TwofOfX = 2 * this->funcBase->Callx(x);
        const double plusDX  = this->funcBase->Callx(x+this->dx);
        const double minusDX = this->funcBase->Callx(x-this->dx);

        const double currentResult = (plusDX - TwofOfX + minusDX)/(dx*dx);
        mainVector.push_back(currentResult);

    }
    return mainVector;
}


std::vector<double> Dmath::SingleVarFunction::getAntiDerivativeVector(double start, double stopp, double stepps) {
    Dmath::Parameters param(start, stopp, stepps);
    if (!this->checkParams(param)) {
        return std::vector<double>(0);
    }

    // Number of intervals
    size_t num = this->numOfElements(param);
    std::vector<double> mainVec;
    double integral = this->funcBase->Callx(start);
    mainVec.push_back(integral);
    // Numerical integration over the interval
    for (size_t i = 0; i < num; i++) {
        double currentX = start + i * stepps;
        double nextX = currentX + stepps;

        // Trapezoidal rule: Average of function values at currentX and nextX
        double avgValue = 0.5 * (this->funcBase->Callx(currentX) + this->funcBase->Callx(nextX));
        
        integral += avgValue * stepps;   // Step size * average value
        mainVec.push_back(integral);     // Store the integrated value
    }

    return mainVec;
}


#pragma endregion 

#pragma region DoubleVar


bool Dmath::DoubleVarFunction::checkParams(Dmath::Parameters params){

    if(params.one >= params.two || params.three == 0){
        return false;
    }
    return true;
}

std::vector<double> Dmath::DoubleVarFunction::getFunctionVector(double start, double stopp, double stepps){
    Dmath::Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
        const size_t num = static_cast<size_t>((stopp-start)/stepps);

        std::vector<double> mainVec;
        for(size_t x = 0; x < num; x++){
            double currentX = (start + x * stepps);
            for(size_t y = 0; y < num; y++){
                double currentY = (start + y * stepps);

                double currentData = this->funcBase->CallXY(currentX,currentY);

                mainVec.push_back(currentData);
            }
        }

        return mainVec;
    }


std::vector<double> Dmath::DoubleVarFunction::getPartialDerivteX(double start, double stopp, double stepps){
    Dmath::Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
    const size_t num = static_cast<size_t>((stopp-start)/stepps);

    std::vector<double> mainVec;

    for(size_t i = 0; i < num; i++){
        double currentX = (start + i * stepps);
        for(size_t j = 0; j < num ; j++){
            double currentY = start+j*stepps;
            double dxPlus   = this->funcBase->CallXY(currentX + dx, currentY);
            double dxMinus  = this->funcBase->CallXY(currentX - dx, currentY);
            double result   = ((dxPlus - dxMinus)/(2*dx));
            mainVec.push_back(result); 
        }
        
    } 
    return mainVec;
}


std::vector<double> Dmath::DoubleVarFunction::getPartialDerivteY(double start, double stopp, double stepps){
    Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
    const size_t num = static_cast<size_t>((stopp-start)/stepps);

    std::vector<double> mainVec;

    for(size_t i = 0; i < num; i++){
        double currentX = (start + i * stepps);
        for(size_t j = 0; j < num ; j++){
            double currentY = start+j*stepps;
            double dxPlus   = this->funcBase->CallXY(currentX, currentY + dx);
            double dxMinus  = this->funcBase->CallXY(currentX, currentY - dx);

            double result   = ((dxPlus - dxMinus)/(2*dx));
            mainVec.push_back(result); 
        }
        
    } 
    return mainVec;
}



std::vector<double> Dmath::DoubleVarFunction::getAntiDerivativeX(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }

    size_t num = this->numOfElements(params);
    std::vector<double> mainVec;
    double integral = this->funcBase->CallXY(start, start);
    mainVec.push_back(integral);

    // Numerical integration over the interval in X direction
    for (size_t i = 0; i < num; i++) {
        double currentX = start + i * stepps;
        double nextX = currentX + stepps;
        
        for (size_t j = 0; j < num; j++) {
            double currentY = start + j * stepps;

            // Trapezoidal rule: Average of function values at currentX and nextX
            double avgValue = 0.5 * (this->funcBase->CallXY(currentX, currentY) + this->funcBase->CallXY(nextX, currentY));
            
            integral += avgValue * stepps;
            mainVec.push_back(integral); // Store the integrated value after each X interval
        }
        
    }
    return mainVec;
}

std::vector<double> Dmath::DoubleVarFunction::getAntiDerivativeY(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }

    size_t num = this->numOfElements(params);
    std::vector<double> mainVec;
    double integral = this->funcBase->CallXY(start, start);
    mainVec.push_back(integral);

    // Numerical integration over the interval in Y direction
    for (size_t i = 0; i < num; i++) {
        double currentX = start + i * stepps;
        
        for (size_t j = 0; j < num; j++) {
            double currentY = start + j * stepps;
            double nextY = currentY + stepps;

            // Trapezoidal rule: Average of function values at currentY and nextY
            double avgValue = 0.5 * (this->funcBase->CallXY(currentX, currentY) + this->funcBase->CallXY(currentX, nextY));
            
            integral += avgValue * stepps;
            mainVec.push_back(integral); // Store the integrated value after each Y interval

        }
    }
    return mainVec;
}



size_t Dmath::DoubleVarFunction::numOfElements(Dmath::Parameters params){
    if( !this->checkParams(params)){
        return 0;
    }
    size_t num = static_cast<size_t>((params.two - params.one)/params.three);
    return num;
}

#pragma endregion



#pragma region TrippleVar


bool Dmath::TripleVarFunction::checkParams(Dmath::Parameters params){
    if(params.one >= params.two || params.three == 0 ){
        return false;
    }
    return true;
}

size_t Dmath::TripleVarFunction::numberOfElements(Dmath::Parameters params){
    if(!this->checkParams(params)){ return 0; }

    size_t num = static_cast<size_t>((params.two - params.one)/params.three);
    return num;
}

std::vector<double> Dmath::TripleVarFunction::getFunctionVector(double start, double stopp, double stepps){
    Dmath::Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
    const size_t num = this->numberOfElements(params);

    std::vector<double> funcVector;

    for(size_t x = 0; x < num; x++){
        double currentX = start + x * stepps;

        for(size_t y = 0; y < num; y++){
            double currentY = start + y * stepps;

            for(size_t z = 0; z < num; z++){
                double currentZ = start + z * stepps;

                double currentResult = this->funcBase->CallXYZ(currentX,currentY,currentZ);

                funcVector.push_back(currentResult);
            }
        }
    }
    return funcVector;
}



std::vector<double> Dmath::TripleVarFunction::getPartialDerivteX(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }
    const size_t num = this->numberOfElements(params);

    std::vector<double> funcVector;
    funcVector.reserve(num * num * num);

    for (size_t x = 0; x < num; x++) {
        double currentX = (start + x * stepps);

        for (size_t y = 0; y < num; y++) {
            double currentY = (start + y * stepps);

            for (size_t z = 0; z < num; z++) {
                double currentZ = (start + z * stepps);  // Korrigiert auf z

                double xDX = this->funcBase->CallXYZ(currentX + this->dx, currentY, currentZ);
                double Xdx = this->funcBase->CallXYZ(currentX - this->dx, currentY, currentZ);

                double result = (xDX - Xdx) / (2 * this->dx);  // Klammern hinzugefügt
                funcVector.push_back(result);
            }
        }
    }

    return funcVector;
}







std::vector<double> Dmath::TripleVarFunction::getPartialDerivteY(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }
    const size_t num = this->numberOfElements(params);

    std::vector<double> funcVector;
    funcVector.reserve(num * num * num);

    for (size_t x = 0; x < num; x++) {
        double currentX = (start + x * stepps);

        for (size_t y = 0; y < num; y++) {
            double currentY = (start + y * stepps);

            for (size_t z = 0; z < num; z++) {
                double currentZ = (start + z * stepps);  // Korrigiert auf z

                double yDY = this->funcBase->CallXYZ(currentX, currentY + this->dx, currentZ);
                double Ydy = this->funcBase->CallXYZ(currentX, currentY - this->dx, currentZ);

                double result = (yDY - Ydy) / (2 * this->dx);  // Klammern hinzugefügt
                funcVector.push_back(result);
            }
        }
    }

    return funcVector;
}



std::vector<double> Dmath::TripleVarFunction::getPartialDerivteZ(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }
    const size_t num = this->numberOfElements(params);

    std::vector<double> funcVector;
    funcVector.reserve(num * num * num);

    for (size_t x = 0; x < num; x++) {
        double currentX = (start + x * stepps);

        for (size_t y = 0; y < num; y++) {
            double currentY = (start + y * stepps);

            for (size_t z = 0; z < num; z++) {
                double currentZ = (start + z * stepps);  // Korrigiert auf z

                double zDZ = this->funcBase->CallXYZ(currentX, currentY, currentZ + this->dx);
                double Zdz = this->funcBase->CallXYZ(currentX, currentY, currentZ - this->dx);

                double result = (zDZ - Zdz) / (2 * this->dx);  // Klammern hinzugefügt
                funcVector.push_back(result);
            }
        }
    }

    return funcVector;
}


#pragma endregion