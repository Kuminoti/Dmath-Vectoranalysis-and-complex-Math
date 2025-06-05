#include"units.hpp"



Dmath::PhysicalUnit Dmath::PhysicalUnit::operator+(const Dmath::PhysicalUnit& other) const {
    if (this->siUnits == other.siUnits) {
        return Dmath::PhysicalUnit(this->siUnits, this->factor + other.factor);
    }
    throw std::invalid_argument("Cannot add units with different SI units.");
}



Dmath::PhysicalUnit Dmath::PhysicalUnit::operator-(const Dmath::PhysicalUnit& other) const {
    if (this->siUnits == other.siUnits) {
        return Dmath::PhysicalUnit(this->siUnits, this->factor - other.factor);
    }
    throw std::invalid_argument("Cannot subtract units with different SI units.");
}


Dmath::PhysicalUnit Dmath::PhysicalUnit::operator*(const Dmath::PhysicalUnit& other) const {
    Dmath::SI_Units newUnits = this->siUnits;
    newUnits.length += other.siUnits.length;
    newUnits.mass += other.siUnits.mass;
    newUnits.time += other.siUnits.time;
    newUnits.electricCurrent += other.siUnits.electricCurrent;
    newUnits.thermodynamicTemperature += other.siUnits.thermodynamicTemperature;
    newUnits.luminousIntensity += other.siUnits.luminousIntensity;
    newUnits.amountOfSubstance += other.siUnits.amountOfSubstance;

    return Dmath::PhysicalUnit(newUnits, this->factor * other.factor);
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