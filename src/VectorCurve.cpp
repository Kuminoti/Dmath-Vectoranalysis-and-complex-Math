#include "../include/VectorCurve.hpp"
// 2D curves

std::vector<Dmath::Vec2D> Dmath::VectorCurve2D::createVectorialCurve() {
    std::vector<Dmath::Vec2D> output;
    int iterations = 0;
    for (double i = this->systemStart; i < systemStopp; i += resolution) {
        
        if (i == this->systemStart) {
            Dmath::Vec2D currentVec(this->xFunc(i), this->yFunc(i), 0, 0);
            currentVec.setT(i);
            output.push_back(currentVec);
            iterations++;
        } else {
            Dmath::Vec2D currentVec(this->xFunc(i), this->yFunc(i), output[iterations - 1].getX(), output[iterations - 1].getY());
            currentVec.setT(i);
            output.push_back(currentVec);
            iterations++;
        }
    }
    return output;
}

// Constructors

Dmath::VectorCurve2D::VectorCurve2D(singleVarFunction xFunc, singleVarFunction yFunc) : VectorAnalysis2D(xFunc, yFunc) {
    std::cout << "Constructor" << std::endl;
    this->mainCurve = this->createVectorialCurve();
}

Dmath::VectorCurve2D::VectorCurve2D(singleVarFunction xFunc, singleVarFunction yFunc, double start, double stopp, double res)
    : VectorAnalysis2D(xFunc, yFunc, start, stopp, res) {
    this->mainCurve = this->createVectorialCurve();
}

Dmath::VectorCurve2D::VectorCurve2D(singleVarFunction xFunc, singleVarFunction yFunc, double start, double stopp, double res,
                                    std::vector<Dmath::Vec2D> mainCurve)
    : VectorAnalysis2D(xFunc, yFunc, start, stopp, res) {
    this->mainCurve = mainCurve;
}

Dmath::VectorCurve2D::VectorCurve2D(singleVarFunction xFunc, singleVarFunction yFunc, double start, double stopp, double res,
                                    std::vector<Dmath::Vec2D> mainCurve, double rotation)
    : VectorAnalysis2D(xFunc, yFunc, start, stopp, res, rotation) {
    this->mainCurve = mainCurve;
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::createStandardCurve(singleVarFunction funcX, singleVarFunction funcY) {
    std::cout << "One" << std::endl;
    return Dmath::VectorCurve2D(funcX, funcY);
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::createCustomCurve(singleVarFunction funcX, singleVarFunction funcY, double start, double stopp,
                                                             double res) {
    return Dmath::VectorCurve2D(funcX, funcY, start, stopp, res);
}

// Pick a specific vector from one point of the curve
Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromPoint(double point) {
    if (point < this->systemStart || point > this->systemStopp) {

#ifdef WORKING
        std::cerr << "Error index out of limit! \n Returning a null vector \n";
#endif

        return Dmath::Vec2D::zeroVector();
    }
    // Calculate the origin of the new vector, based of the last Vectors position
    double newOriginX = this->xFunc(point - this->resolution);
    double newOriginY = this->yFunc(point - this->resolution);

    double xValue = this->xFunc(point); // VecX = X(t)
    double yValue = this->yFunc(point); // VecY = Y(t)

    Dmath::Vec2D outputVector(xValue, yValue, newOriginX, newOriginY);

    return outputVector;
}

// Operator overloading:

void Dmath::VectorCurve2D::operator+(Dmath::Vec2D vec) {
    double lastVecX = this->mainCurve[this->numberOfElements - 1].getX();
    double lastVecY = this->mainCurve[this->numberOfElements - 1].getY();
    vec.setOriginX(lastVecX);
    vec.setOriginY(lastVecY);
    this->mainCurve.push_back(vec);
}

void Dmath::VectorCurve2D::operator++() {
    this->addToAllX(1);
    this->addToAllY(1);
}

Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromStdVec(size_t index) {
    // Check if the input is in range
    if (index > this->mainCurve.size() || index < 0) {

#ifdef WORKING

        std::cerr << "Error index out of range, returning zeroVector" << std::endl;

#endif

        return Dmath::Vec2D::zeroVector();
    }
    return this->mainCurve[index];
}

// Pic a vector from a specific point in the functions
Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromFunction(double vecX, double vecY) {

    double xValue = this->xFunc(vecX); // VecX = X(t)
    double yValue = this->yFunc(vecY); // VecY = Y(t)

    Dmath::Vec2D outputVector(xValue, yValue);
    return outputVector;
}

// Integration

// Calculates the Area between the curve and the x-achsis
double Dmath::VectorCurve2D::calculateAreaXAchsis(double tStart, double tEnd) {
    if (tStart < this->systemStart || tEnd > this->systemStopp) {

#ifdef WORKING

        std::cerr << "Error out of range" << std::endl;

#endif

        return 0;
    }
    auto yAbsolute = [&](double t) -> double { return std::abs(this->xFunc(t)); };
    auto dx_dt = [&](double t) -> double { return std::abs(this->calculateSlopeOnPoint(t)); };

    double area = 0.0;
    double dt = 0.001;
    for (double t = tStart; t < tEnd; t += dt) {
        area += yAbsolute(t) * dx_dt(t) * dt;
    }
    return area;
}

double Dmath::VectorCurve2D::calculateAreaYAchsis(double tStart, double tEnd) {
    if (tStart < this->systemStart || tEnd > this->systemStopp) {

#ifdef WORKING

        std::cerr << "Error out of range" << std::endl;

#endif
        return 0;
    }
    auto xAbsolute = [&](double t) -> double { return std::abs(this->yFunc(t)); };
    auto dx_dt = [&](double t) -> double { return std::abs(this->calculateSlopeOnPoint(t)); };

    double area = 0.0;
    double dt = 0.001;
    for (double t = tStart; t < tEnd; t += dt) {
        area += xAbsolute(t) * dx_dt(t) * dt;
    }
    return area;
}

double Dmath::VectorCurve3D::calculateAreaZAchsis(double tStart, double tEnd) {
    if (tStart < this->systemStart || tEnd > this->systemStopp) {

#ifdef WORKING

        std::cerr << "Error out of range" << std::endl;

#endif

        return 0;
    }
    auto zAbsolute = [&](double t) -> double { return std::abs(this->zFunc(t)); };
    auto dz_dt = [&](double t) -> double { return std::abs(this->calculateSlopeOnPoint(t)); };

    double area = 0.0;
    double dt = 0.001;
    for (double t = tStart; t < tEnd; t += dt) {
        area += zAbsolute(t) * dz_dt(t) * dt;
    }
    return area;
}

double Dmath::VectorCurve3D::calculateAreaYAchsis(double tStart, double tEnd) {
    if (tStart < this->systemStart || tEnd > this->systemStopp) {

#ifdef WORKING

        std::cerr << "Error out of range" << std::endl;

#endif

        return 0;
    }
    auto yAbsolute = [&](double t) -> double { return std::abs(this->yFunc(t)); };
    auto dy_dt = [&](double t) -> double { return std::abs(this->calculateSlopeOnPoint(t)); };

    double area = 0.0;
    double dt = 0.001;
    for (double t = tStart; t < tEnd; t += dt) {
        area += yAbsolute(t) * dy_dt(t) * dt;
    }
    return area;
}

double Dmath::VectorCurve3D::calculateAreaXAchsis(double tStart, double tEnd) {
    if (tStart < this->systemStart || tEnd > this->systemStopp) {

#ifdef WORKING

        std::cerr << "Error out of range" << std::endl;

#endif
        return 0;
    }
    auto xAbsolute = [&](double t) -> double { return std::abs(this->xFunc(t)); };
    auto dx_dt = [&](double t) -> double { return std::abs(this->calculateSlopeOnPoint(t)); };

    double area = 0.0;
    double dt = 0.001;
    for (double t = tStart; t < tEnd; t += dt) {
        area += xAbsolute(t) * dx_dt(t) * dt;
    }
    return area;
}

double Dmath::VectorCurve3D::calculateSlopeOnPoint(double t) {
    Dmath::Vec3D vec = this->tangentVector(t);

    if (vec.getY() != 0) {
        return vec.getX() / vec.getY();
    } else if (vec.getZ() != 0) {
        return vec.getX() / vec.getZ();
    } else {

        return 0;
    }
}

Dmath::Vec2D Dmath::VectorCurve2D::tangentVector(double t) {

    if (t > this->systemStopp || t < this->systemStart) {

#ifdef WORKING

        std::cerr << "Error out of range, returning zero vector" << std::endl;

#endif // WORKING

        return Dmath::Vec2D::zeroVector();
    }

    const double originX = this->xFunc(t - this->resolution);
    const double originY = this->yFunc(t - this->resolution);

    double h = 0.000001;
    double x_t_plus_h = this->xFunc(t + h);
    double x_t_minus_h = this->xFunc(t - h);
    double y_t_plus_h = this->yFunc(t + h);
    double y_t_minus_h = this->yFunc(t - h);

    double dx = (x_t_plus_h - x_t_minus_h) / (2 * h);
    double dy = (y_t_plus_h - y_t_minus_h) / (2 * h);

    return Dmath::Vec2D(dx, dy, originX, originY);
}

Dmath::Vec2D Dmath::VectorCurve2D::tangetUnitVector(double t) {
    if (t > this->systemStopp || t < this->systemStart) {

#ifdef WORKING

        std::cerr << "Error out of range, returning zero vector" << std::endl;

#endif // WORKING

        return Dmath::Vec2D::zeroVector();
    }
    Dmath::Vec2D newVector = this->tangentVector(t);
    newVector.normalize();
    return newVector;
}

Dmath::Vec2D Dmath::VectorCurve2D::principalNormalUnitVector(double t) {
    if (t > this->systemStopp || t < this->systemStart) {

#ifdef WORKING

        std::cerr << "Error out of range, returning zero vector" << std::endl;

#endif

        return Dmath::Vec2D::zeroVector();
    }
    Dmath::Vec2D newVec = this->tangetUnitVector(t);
    newVec.normalize();
    return newVec;
}

double Dmath::VectorCurve2D::getCurvature(double t) {
    if (t > this->systemStopp || t < this->systemStart) {
        // T out of range!
        return 0.0;
    }
    double curvature = 0;
    Dmath::Vec2D vec = this->principalNormalUnitVector(t);
    curvature = vec.getAbs();
    return curvature;
}

double Dmath::VectorCurve2D::curveLenght() {
    double lenght = 0;
    for (int i = 0; i < this->mainCurve.size(); i++) {
        lenght += this->mainCurve[i].getAbs();
    }
    lenght = lenght * resolution;
    return lenght;
}

double Dmath::VectorCurve2D::maximumY() {
    double maxY = 0;
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        if (this->mainCurve[i].getY() > maxY) {
            maxY = this->mainCurve[i].getY();
        } else {
            continue;
        }
    }
    return maxY;
}

double Dmath::VectorCurve2D::minimumY() {
    double minY = this->mainCurve[0].getY();
    for (int i = 0; i < this->mainCurve.size(); i++) {
        if (this->mainCurve[i].getY() < minY) {
            minY = this->mainCurve[i].getY();
        } else {
            continue;
        }
    }
    return minY;
}

double Dmath::VectorCurve2D::MaximumX() {
    double maxX = 0;
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        if (this->mainCurve[i].getX() > maxX) {
            maxX = this->mainCurve[i].getX();
        } else {
            continue;
        }
    }
    return maxX;
}

bool Dmath::VectorCurve2D::existsIn(Dmath::Vec2D vec) {
    bool exsitance = false;
    size_t lenght = this->numberOfElements;
    for (size_t i = 0; i < lenght; i++) {
        if (this->mainCurve[i].getX() == vec.getX() && this->mainCurve[i].getY() == vec.getY() &&
            this->mainCurve[i].getOriginX() == vec.getOriginX() && this->mainCurve[i].getOriginY() == vec.getOriginY()) {
            exsitance = true;
        }
    }
    return exsitance;
}

double Dmath::VectorCurve2D::calculateSlopeOnPoint(double t) {
    Dmath::Vec2D vec = this->tangentVector(t);
    double result = 0;
    if (vec.getY() != 0) {
        result = vec.getX() / vec.getY();
    } else {
        return 0;
    }
    return result;
}

// Needs to be optimised

size_t Dmath::VectorCurve2D::numberOfYZeroPoints() {
    size_t zeroPoints = 0;
    size_t iterations = 1;
    for (size_t i = 1; i < this->mainCurve.size(); ++i) {
        if ((this->mainCurve[i].getY() > 0 && this->mainCurve[iterations - 1].getY() < 0) ||
            (this->mainCurve[i].getY() < 0 && this->mainCurve[iterations - 1].getY() > 0)) {
            zeroPoints++;
        }
        iterations++;
    }
    return zeroPoints;
}

size_t Dmath::VectorCurve2D::numberOfXZeroPoints() {
    size_t zeroPoints = 0;
    size_t iterations = 1;
    for (size_t i = 1; i < this->mainCurve.size(); ++i) {
        if ((this->mainCurve[i].getX() > -0.01 && this->mainCurve[iterations - 1].getX() < 0.010) ||
            (this->mainCurve[i].getX() < 0.01 && this->mainCurve[iterations - 1].getX() > 0.10)) {
            zeroPoints++;
        }
        iterations++;
    }
    return zeroPoints;
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::subtractCurve(VectorCurve2D curve) {
    double mainCurveEnd = this->getEnd();
    double otherCurveEnd = this->getEnd();
    double newCurveEnd = TWOPI;

    double mainCurveStart = this->getStart();
    double otherCurveStart = this->getStart();
    double newCurveStart = 0;

    if (mainCurveEnd >= otherCurveEnd) {
        newCurveEnd = otherCurveEnd;
    }
    if (mainCurveStart >= otherCurveStart) {
        newCurveStart = mainCurveStart;
    }
    auto newXFunc = [this, &curve](double t) -> double { return this->xFunc(t) + curve.xFunc(t); };
    auto newYFunc = [this, &curve](double t) -> double { return this->yFunc(t) + curve.yFunc(t); };
    return Dmath::VectorCurve2D(newXFunc, newYFunc, mainCurveStart, mainCurveEnd, 0.1);
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::rotateCurve(double radiants) {
    std::vector<Dmath::Vec2D> newCurve;
    for (size_t i = 0; i < this->mainCurve.size(); i++) {

        // This function rotates all vectors in the main curve und pushes it in a new std::vector
        newCurve.push_back(this->mainCurve[i].rotateVector(radiants));
    }
    return VectorCurve2D(this->xFunc, this->yFunc, this->systemStart, this->systemStopp, this->resolution, newCurve);
}

double Dmath::VectorCurve2D::dotProductVectorCurve(Dmath::VectorCurve2D vec) {
    double curveOneStart = this->getStart();
    double curveTwoStart = vec.getStart();
    double curveOneEnd = this->getEnd();
    double curveTwoEnd = vec.getEnd();
    double dotProduct = 0;

    size_t startIdx = 0;
    size_t endIdx = static_cast<size_t>(min(this->mainCurve.size(), vec.mainCurve.size()));

    if (curveOneStart >= curveTwoStart) {
        startIdx = curveOneStart;
    } else {
        startIdx = curveTwoStart;
    }
    if (curveOneEnd <= curveTwoEnd) {
        endIdx = curveOneEnd;
    } else {
        endIdx = curveTwoEnd;
    }
    for (size_t i = startIdx; i < endIdx; i++) {
        dotProduct += this->mainCurve[i].dotProduct(vec.mainCurve[i]);
    }
    return dotProduct;
}

double Dmath::VectorCurve2D::minimumX() {
    double minX = this->mainCurve[0].getX();
    for (int i = 0; i < this->mainCurve.size(); i++) {
        if (this->mainCurve[i].getX() < minX) {
            minX = this->mainCurve[i].getX();
        } else {
            continue;
        }
    }
    return minX;
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::addCurve(Dmath::VectorCurve2D curve) {
    double mainCurveEnd = this->getEnd();
    double otherCurveEnd = curve.getEnd();
    double newCurveEnd = TWOPI;

    double mainCurveStart = this->getStart();
    double otherCurveStart = curve.getStart();
    double newCurveStart = 0;

    if (mainCurveEnd >= otherCurveEnd) {
        newCurveEnd = otherCurveEnd;
    }
    if (mainCurveStart >= otherCurveStart) {
        newCurveStart = mainCurveStart;
    }

    auto newX = [this, &curve](double t) -> double { return this->xFunc(t) + curve.xFunc(t); };
    auto newY = [this, &curve](double t) -> double { return this->yFunc(t) + curve.yFunc(t); };

    return VectorCurve2D(newX, newY, mainCurveStart, mainCurveEnd, 0.1);
}

void Dmath::VectorCurve2D::moveCurve(double moveX, double moveY) {
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].moveVector(moveX, moveY);
    }
}

void Dmath::VectorCurve2D::moveX(double moveX) {
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].moveVectorX(moveX);
    }
}

void Dmath::VectorCurve2D::moveY(double moveY) {
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].moveVectorY(moveY);
    }
}

void Dmath::VectorCurve2D::rotateThisCurve(double radiants) {
    for (int i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].rotateThisVector(radiants);
    }
}

void Dmath::VectorCurve2D::addToAll(double plus) {
    const double num = this->numberOfElements; // to keep the for-loop-args smaller

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].addToThis(plus);
    }
}

void Dmath::VectorCurve2D::addToAllX(double xPlusN) {
    const double num = this->numberOfElements; // to keep the for-loop-args smaller

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].addToX(xPlusN);
    }
}

void Dmath::VectorCurve2D::addToAllY(double yPlusN) {
    const double num = this->numberOfElements; // to keep the for-loop-args smaller

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].addToY(yPlusN);
    }
}

void Dmath::VectorCurve2D::allXDividedBy(double dividedBy) {
    const double num = this->numberOfElements; // to keep the for-loop-args smaller

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].divideXBy(dividedBy);
    }
}

void Dmath::VectorCurve2D::allYDividedBy(double dividedBy) {
    const double num = this->numberOfElements; // to keep the for-loop-args smaller

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].divideYBy(dividedBy);
    }
}

void Dmath::VectorCurve2D::divideAllBy(double quotient) {
    if (quotient == 0) {
        std::cerr << "Division by Zero! Idiot" << std::endl;
    }
    const double num = this->numberOfElements; // to keep the for-loop-args smaller

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].divideThisBy(quotient);
    }
}

void Dmath::VectorCurve2D::multiplyAllX(double mult) {
    const double num = this->numberOfElements; // to keep the for-loop-args smaller

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].multiplyXBy(mult);
    }
}

void Dmath::VectorCurve2D::multiplyAllY(double mult) {
    const double num = this->numberOfElements;

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].multiplyYBy(mult);
    }
}

void Dmath::VectorCurve2D::multiplyAll(double faktor) {
    const double num = this->numberOfElements;

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].multipyThisBy(faktor);
    }
}

void Dmath::VectorCurve2D::subtractFromX(double minus) {
    const double num = this->numberOfElements;

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].subtractFromX(minus);
    }
}

void Dmath::VectorCurve2D::subtractFromY(double minus) {
    const double num = this->numberOfElements;

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].subtractFromY(minus);
    }
}

void Dmath::VectorCurve2D::subtractFromXY(double minus) {
    const double num = this->numberOfElements;

    for (size_t i = 0; i < num; i++) {
        this->mainCurve[i].substractThis(minus);
    }
}

// 3D curves

double Dmath::VectorCurve3D::dotProductVectorCurve(Dmath::VectorCurve3D vec) {

    double curveOneStart = this->getStart();
    double curveTwoStart = vec.getStart();
    double curveOneEnd = this->getEnd();
    double curveTwoEnd = vec.getEnd();
    double dotProduct = 0;

    size_t startIdx = 0;
    size_t endIdx = min(this->mainCurve.size(), vec.mainCurve.size());

    if (curveOneStart >= curveTwoStart) {
        startIdx = curveOneStart;
    } else {
        startIdx = curveTwoStart;
    }
    if (curveOneEnd <= curveTwoEnd) {
        endIdx = curveOneEnd;
    } else {
        endIdx = curveTwoEnd;
    }
    for (size_t i = startIdx; i < endIdx; i++) {
        dotProduct += this->mainCurve[i].dotProduct(vec.mainCurve[i]);
    }
    return dotProduct;
}

std::vector<Dmath::Vec3D> Dmath::VectorCurve3D::createVectorialCurve() {
    std::vector<Dmath::Vec3D> output;
    int iterations = 0;
    for (double i = this->systemStart; i < this->numberOfElements; i += resolution) {
        if (i == this->systemStart) {
            Dmath::Vec3D currentVec(this->xFunc(i), this->yFunc(i), this->zFunc(i), 0, 0, 0);
            currentVec.setT(i);
            output.push_back(currentVec);
            iterations++;
        } else {
            Dmath::Vec3D currentVec(this->xFunc(i), this->yFunc(i), this->zFunc(i), output[iterations - 1].getX(),
                                          output[iterations - 1].getY(), output[iterations - 1].getZ());
            currentVec.setT(i);
            output.push_back(currentVec);
            iterations++;
        }
    }
    return output;
}

Dmath::VectorCurve3D::VectorCurve3D(Dmath::singleVarFunction xFunc, std::function<double(double)> yFunc, Dmath::singleVarFunction zFunc, double start,
                                    double stopp, double res, std::vector<Dmath::Vec3D> mainCurve)
    : VectorAnalysis3D(xFunc, yFunc, zFunc, start, stopp, res) {
    this->mainCurve = mainCurve;
}

Dmath::VectorCurve3D::VectorCurve3D(Dmath::singleVarFunction xFunc, Dmath::singleVarFunction yFunc, std::function<double(double)> zFunc)
    : VectorAnalysis3D(xFunc, yFunc, zFunc) {
    this->mainCurve = this->createVectorialCurve();
}

Dmath::VectorCurve3D::VectorCurve3D(Dmath::singleVarFunction xFunc, std::function<double(double)> yFunc, std::function<double(double)> zFunc,
                                    double start, double stopp, double res)
    : VectorAnalysis3D(xFunc, yFunc, zFunc, start, stopp, res) {
    this->mainCurve = this->createVectorialCurve();
}

Dmath::VectorCurve3D Dmath::VectorCurve3D::createStandardCurve(Dmath::singleVarFunction funcX, Dmath::singleVarFunction funcY,
                                                               Dmath::singleVarFunction zFunc) {
    return Dmath::VectorCurve3D(funcX, funcY, zFunc);
}

Dmath::VectorCurve3D Dmath::VectorCurve3D::createCustomCurve(Dmath::singleVarFunction funcX, Dmath::singleVarFunction funcY,
                                                             Dmath::singleVarFunction zFunc, double start, double stopp, double res) {
    return Dmath::VectorCurve3D(funcX, funcY, zFunc, start, stopp, res);
}

// Dmath::VectorCurve3D Dmath::VectorCurve3D::createCustomCurve(std::function<double(double)> funcX,std::function<double(double)>
// funcY,std::function<double(double)> zFunc, double start,double stopp,double res ){
//     return Dmath::VectorCurve3D(funcX,funcY,zFunc,start,stopp,res);
// }

Dmath::Vec3D Dmath::VectorCurve3D::getVectorFromFunction(double xValue, double yValue, double zValue) {
    double vecX = this->xFunc(xValue); // vecX = X(t)
    double vecY = this->yFunc(yValue); // vecY = Y(t)
    double vecZ = this->zFunc(zValue); // vecZ = Z(t)
    Dmath::Vec3D outputVector(vecX, vecY, vecZ);
    return outputVector;
}

Dmath::Vec3D Dmath::VectorCurve3D::getVectorFromPoint(double point) {
    if (point > this->systemStart || point < this->systemStopp) {
#ifdef WORKING
        std::cerr << "Error index out of limit! \n Returning a null vector \n";
#endif
        return Dmath::Vec3D::zeroVector();
    }

    // Get the origin based of the position of the last vector in the curve

    double originXL = this->xFunc(point - this->resolution);
    // The Variable is called origin...L -> origin...Last and it is one step behind the wanted vector
    double originYL = this->yFunc(point - this->resolution);
    double originZL = this->zFunc(point - this->resolution);

    double vecX = this->xFunc(point); // vecX = X(t)
    double vecY = this->yFunc(point); // vecY = Y(t)
    double vecZ = this->zFunc(point); // vecZ = Z(t)

    Dmath::Vec3D outputVector(vecX, vecY, vecZ, originXL, originYL, originZL);
    return outputVector;
}

Dmath::Vec3D Dmath::VectorCurve3D::getVectorFromStdVec(size_t index) {
    if (index > this->mainCurve.size() || index < 0) {

#ifdef WORKING

        std::cerr << "Error out of range, returning zero vector" << std::endl;

#endif

        return Dmath::Vec3D::zeroVector();
    }
    return this->mainCurve[index];
}

Dmath::Vec3D Dmath::VectorCurve3D::tangentVector(double t) {
    if (t > this->systemStopp || t < this->systemStart) {

#ifdef WORKING

        std::cerr << "Error out of range, returning zero vector" << std::endl;

#endif

        return Dmath::Vec3D::zeroVector();
    }
    double h = 0.00000001;
    double x_t_plus_h = this->xFunc(t + h);
    double x_t_minus_h = this->xFunc(t - h);
    double y_t_plus_h = this->yFunc(t + h);
    double y_t_minus_h = this->yFunc(t - h);
    double z_t_plus_h = this->zFunc(t + h);
    double z_t_minus_h = this->zFunc(t - h);

    bool x_positive = (x_t_plus_h >= 0) && (x_t_minus_h >= 0);
    bool y_positive = (y_t_plus_h >= 0) && (y_t_minus_h >= 0);
    bool z_positive = (y_t_plus_h >= 0) && (y_t_minus_h >= 0);

    double dx = (x_t_plus_h - x_t_minus_h) / (2 * h);
    double dy = (y_t_plus_h - y_t_minus_h) / (2 * h);
    double dz = (z_t_plus_h - z_t_minus_h) / (2 * h);
    if (!x_positive)
        dx = -dx;
    if (!y_positive)
        dy = -dy;

    return Dmath::Vec3D(dx, dy, dz);
}

Dmath::Vec3D Dmath::VectorCurve3D::tangetUnitVector(double t) {
    Dmath::Vec3D newVector = this->tangentVector(t);
    newVector.normalize();
    return newVector;
}

Dmath::Vec3D Dmath::VectorCurve3D::principalNormalUnitVector(double t) {
    Dmath::Vec3D newVec = this->tangetUnitVector(t);
    newVec.normalize();
    return newVec;
}

double Dmath::VectorCurve3D::getCurvature(double t) {
    if (t > this->systemStopp || t < this->systemStart) {
        // Error t out of range!
        return 0;
    }
    double curvature = 0;
    Dmath::Vec3D vec = this->principalNormalUnitVector(t);
    curvature = vec.getAbs();
    return curvature;
}

double Dmath::VectorCurve3D::curveLenght() {
    double lenght = 0;
    for (int i = 0; i < this->mainCurve.size(); i++) {
        lenght += this->mainCurve[i].getAbs();
    }
    return lenght;
}

double Dmath::VectorCurve3D::calculateSlopeXOnPoint(double t) {
    Dmath::Vec3D vec = this->tangentVector(t);
    double result = 0;
    if (vec.getX() == 0) {
        return 0;
    }
    result = vec.getZ() / vec.getX();
    return result;
}

// Maximum and minimum

double Dmath::VectorCurve3D::calculateSlopeYOnPoint(double t) {
    Dmath::Vec3D vec = this->tangentVector(t);
    double result = 0;
    if (vec.getY() == 0) {
        return 0;
    }
    result = vec.getZ() / vec.getY();
    return result;
}

double Dmath::VectorCurve3D::minimumX() {
    double minX = this->mainCurve[0].getX();
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        if (this->mainCurve[i].getX() < minX) {
            minX = this->mainCurve[i].getX();
            continue;
        } else {
            continue;
        }
    }
    return minX;
}

double Dmath::VectorCurve3D::minimumY() {
    double minY = this->mainCurve[0].getY();
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        if (this->mainCurve[i].getY() < minY) {
            minY = this->mainCurve[i].getY();
            continue;
        } else {
            continue;
        }
    }
    return minY;
}

double Dmath::VectorCurve3D::maximumX() {
    double maxX = 0;
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        if (this->mainCurve[i].getX() > maxX) {
            maxX = this->mainCurve[i].getX();
        } else {
            continue;
        }
    }
    return maxX;
}

double Dmath::VectorCurve3D::maximumY() {
    double maxY = 0;
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        if (this->mainCurve[i].getY() > maxY) {
            maxY = this->mainCurve[i].getY();
        } else {
            continue;
        }
    }
    return maxY;
}

// Calculates the x-zeropoints of the curve by checking for X = 0 with a tollerance
size_t Dmath::VectorCurve3D::numberOfXZeroPoints() {
    size_t zeroPoints = 0;
    size_t iterations = 1;
    for (size_t i = 1; i < this->mainCurve.size(); ++i) {
        if ((this->mainCurve[i].getX() > 0 && this->mainCurve[iterations - 1].getX() < 0) ||
            (this->mainCurve[i].getX() < 0 && this->mainCurve[iterations - 1].getX() > 0)) {
            zeroPoints++;
        }
        iterations++;
    }
    return zeroPoints;
}

// Calculates the y-zeropoints of the curve by checking for Y = 0 with a tollerance
size_t Dmath::VectorCurve3D::numberOfYZeroPoints() {
    size_t zeroPoints = 0;
    size_t iterations = 1;
    for (size_t i = 1; i < this->mainCurve.size(); ++i) {
        if ((this->mainCurve[i].getY() > 0 && this->mainCurve[iterations - 1].getY() < 0) ||
            (this->mainCurve[i].getY() < 0 && this->mainCurve[iterations - 1].getY() > 0)) {
            zeroPoints++;
        }
        iterations++;
    }
    return zeroPoints;
}

// Calculates the Z-zeropoints of the curve by checking for Z = 0 with a tollerance
size_t Dmath::VectorCurve3D::numberOfZZeroPoints() {
    size_t zeroPoints = 0;
    size_t iterations = 1;
    for (size_t i = 1; i < this->mainCurve.size(); ++i) {
        if ((this->mainCurve[i].getZ() > 0 && this->mainCurve[iterations - 1].getZ() < 0) ||
            (this->mainCurve[i].getZ() < 0 && this->mainCurve[iterations - 1].getZ() > 0)) {
            zeroPoints++;
        }
        iterations++;
    }
    return zeroPoints;
}

// Curve movement
void Dmath::VectorCurve3D::moveZ(double moveZ) {
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].moveVectorZ(moveZ);
    }
}

void Dmath::VectorCurve3D::moveY(const double moveY) {
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].moveVectorY(moveY);
    }
}

void Dmath::VectorCurve3D::moveX(const double moveX) {
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].moveVectorX(moveX);
    }
}

void Dmath::VectorCurve3D::moveCurve(const double moveX, const double moveY, const double moveZ) {
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].moveVector(moveX, moveY, moveZ);
    }
}

// Curve Rotation
void Dmath::VectorCurve3D::rotateThisCurve(const double phi, const double theta) {
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        this->mainCurve[i].rotateThisVector(phi, theta);
    }
}

bool Dmath::VectorCurve3D::exsitsIn(Dmath::Vec3D vec) {
    const double num = this->numberOfElements;
    bool result = false;
    for (size_t i = 0; i < num; i++) {
        if (this->mainCurve[i].isEqual(vec)) {
            result = true;
        }
        continue;
    }
    return result;
}

// Rotate the Curve based on two angles
Dmath::VectorCurve3D Dmath::VectorCurve3D::rotateCurve(double phi, double theta) {
    std::vector<Dmath::Vec3D> newVec;
    for (size_t i = 0; i < this->mainCurve.size(); i++) {
        newVec.push_back(this->mainCurve[i].rotateVector(phi, theta));
    }
    return VectorCurve3D(this->xFunc, this->yFunc, this->zFunc, this->systemStart, this->systemStopp, this->resolution, newVec);
}
