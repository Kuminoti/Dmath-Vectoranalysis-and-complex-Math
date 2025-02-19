#pragma once

#ifndef DMATH_VECTORFUNCTION_HPP
#define DMATH_VECTORFUNCTION_HPP

#include"mathFunction.hpp"

NAMESPACESTART

/* Diese Datei beinhaltet klassen zur beschreibung von vektoriell dargestellten funktionen z.B:
 * zur darstellung von parametrisierten oder oberflächen
 * => k(t) = [ x(t); y(t); z(t) ]
 * 
 * Die klasse SingleVectorFunction unterstützt sowohl zweidimensionale wie auch 3d funktionen
 * Die Darstellung der einzelnen funktionen funktioniert mit hilfe der Datentypen: 
 *      - Dmath::SingleVarFunction  
 *      - Dmath::DoubleVarFunction
 *        File: mathFunction.hpp 
 * 
 * Diese sind selbst geschriebene funktionsobjekte ähnlich dem std::function-objekt aus der
 * c++ STL mit dem unterschied, dass sie optimiert sind auf die beschreibung mathematischer
 * funktionen und dementsprechent über zusätzliche funktionalitäten verfügen. 
*/

class SingleVectorFunction{

private:

    Dmath::SingleVarFunction xOfT;
    Dmath::SingleVarFunction yOfT;
    Dmath::SingleVarFunction zOfT; 

public:

    //constructor for 2D vectorFunction
    SingleVectorFunction(Dmath::SingleVarFunction xOfT, Dmath::SingleVarFunction yOfT);

    SingleVectorFunction(Dmath::SingleVarFunction xOfT, Dmath::SingleVarFunction yOfT, Dmath::SingleVarFunction zOfT);
   
    Dmath::Vec2D call2D(double t);
    
    Dmath::Vec3D operator ()(double t);

    Dmath::SingleVarFunction getXFunc(){
        return this->xOfT;
    }
    Dmath::SingleVarFunction getYFunc(){
        return this->yOfT;
    }
    Dmath::SingleVarFunction getZFunc(){
        return this->zOfT;
    }

    inline Dmath::Scalar callX(double t){ return xOfT(t); }
    inline Dmath::Scalar callY(double t){ return yOfT(t); }
    inline Dmath::Scalar callZ(double t){ return zOfT(t); }


};



NAMESPACEEND



#endif