#include"../include/units.hpp"

void Dmath::PhysicalUnit::changeFaktorType(){
    // If the current unit is a vector it will be changed into a scalar
    if(this->isVector){
        this->vectorFactor.setAllCatesian(0);
        this->isVector = false;
        return;
    } else{

        // If the current unit is a scalar it will be changed into a vector
        this->isVector = true;
        this->factor = 0;
        return;
    }
}

Dmath::PhysicalUnit Dmath::PhysicalUnit::operator+(const Dmath::PhysicalUnit& other) const {
    Dmath::PhysicalUnit newUnit;

    if (this->siUnits != other.siUnits) {
        throw std::invalid_argument("Cannot add units with different SI units.");
    }

        if(this->isVector == true){
            Dmath::Vec3D newVec = this->vectorFactor + other.vectorFactor;
            newUnit.setSIUnits(this->siUnits);
            newUnit.setVector(newVec);
        }

        else{
            newUnit.setSIUnits(this->siUnits);
            Dmath::Scalar newFactor = this->factor + other.factor;
            newUnit.setFactor(newFactor);
        }

    return newUnit;
   
}



Dmath::PhysicalUnit Dmath::PhysicalUnit::operator-(const Dmath::PhysicalUnit& other) const {
    Dmath::PhysicalUnit newUnit;

    if (this->siUnits != other.siUnits) {
        throw std::invalid_argument("Cannot add units with different SI units.");
    }

        if(this->isVector == true){
            Dmath::Vec3D newVec = this->vectorFactor - other.vectorFactor;
            newUnit.setSIUnits(this->siUnits);
            newUnit.setVector(newVec);
        }

        else{
            newUnit.setSIUnits(this->siUnits);
            Dmath::Scalar newFactor = this->factor - other.factor;
            newUnit.setFactor(newFactor);
        }

    return newUnit;
   
}


Dmath::PhysicalUnit Dmath::PhysicalUnit::operator*(const Dmath::PhysicalUnit& other) const {

    Dmath::PhysicalUnit newUnit;

    Dmath::SI_Units newUnits = this->siUnits;
    newUnits.length += other.siUnits.length;
    newUnits.mass += other.siUnits.mass;
    newUnits.time += other.siUnits.time;
    newUnits.electricCurrent += other.siUnits.electricCurrent;
    newUnits.thermodynamicTemperature += other.siUnits.thermodynamicTemperature;
    newUnits.luminousIntensity += other.siUnits.luminousIntensity;
    newUnits.amountOfSubstance += other.siUnits.amountOfSubstance;

    if(this->isVector){
        Dmath::Scalar newFactor = this->vectorFactor * this->vectorFactor;
        this->changeFaktorType();
        newUnit.setFactor(newFactor);
        newUnit.setSIUnits(newUnits);

    } else {
        Dmath::Scalar newFactor = this->factor * other.factor;
        newUnit.setFactor(newFactor);
        newUnit.setSIUnits(newUnits);
    }

    return newUnit;
}

Dmath::PhysicalUnit Dmath::PhysicalUnit::operator/(const Dmath::PhysicalUnit& other) const {
    if (other.factor == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    Dmath::SI_Units newUnits = this->siUnits;
    newUnits.length -= other.siUnits.length;
    newUnits.mass -= other.siUnits.mass;
    newUnits.time -= other.siUnits.time;
    newUnits.electricCurrent -= other.siUnits.electricCurrent;
    newUnits.thermodynamicTemperature -= other.siUnits.thermodynamicTemperature;
    newUnits.luminousIntensity -= other.siUnits.luminousIntensity;
    newUnits.amountOfSubstance -= other.siUnits.amountOfSubstance;

    return Dmath::PhysicalUnit(newUnits, this->factor / other.factor);
}

bool Dmath::PhysicalUnit::operator<(const Dmath::PhysicalUnit& other) const {
    if (this->siUnits == other.siUnits) {
        return this->factor < other.factor;
    }
    throw std::invalid_argument("Cannot compare units with different SI units.");
}