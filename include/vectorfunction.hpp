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

#pragma region Single

class SingleVectorFunction{

private:

    Dmath::SingleVarFunction xOfT;
    Dmath::SingleVarFunction yOfT;
    Dmath::SingleVarFunction zOfT; 

public:

    //constructor for 2D vectorFunction
    SingleVectorFunction(Dmath::SingleVarFunction xOfT, Dmath::SingleVarFunction yOfT);

    SingleVectorFunction(Dmath::SingleVarFunction xOfT, Dmath::SingleVarFunction yOfT, Dmath::SingleVarFunction zOfT);
   
    Dmath::Vec2D call2D(Dmath::Scalar t);
    
    Dmath::Vec3D operator ()(Dmath::Scalar t);

    //Getters:

    Dmath::SingleVarFunction getXFunc(){ return this->xOfT;    }
    Dmath::SingleVarFunction getYFunc(){ return this->yOfT;    }
    Dmath::SingleVarFunction getZFunc(){ return this->zOfT;    }


    //Call the functions
    inline Dmath::Scalar callX(Dmath::Scalar t){ return xOfT(t); }
    inline Dmath::Scalar callY(Dmath::Scalar t){ return yOfT(t); }
    inline Dmath::Scalar callZ(Dmath::Scalar t){ return zOfT(t); }

    
    Dmath::Vec3D getTangentialVectorAt(Dmath::Scalar t);
};

#pragma endregion //single 

#pragma region Double
class DoubleVectorFunction{
private:
    Dmath::DoubleVarFunction xOfUV;
    Dmath::DoubleVarFunction yOfUV;
    Dmath::DoubleVarFunction zOfUV;

public:

    DoubleVectorFunction() = default;

    DoubleVectorFunction(Dmath::DoubleVarFunction xOfUV, Dmath::DoubleVarFunction yOfUV, Dmath::DoubleVarFunction zOfUV);

    Dmath::Vec3D operator ()(Dmath::Scalar U, Dmath::Scalar V);

    inline Dmath::Scalar callX(Dmath::Scalar u, Dmath::Scalar v){ return xOfUV(u,v); }
    inline Dmath::Scalar callY(Dmath::Scalar u, Dmath::Scalar v){ return yOfUV(u,v); }
    inline Dmath::Scalar callZ(Dmath::Scalar u, Dmath::Scalar v){ return zOfUV(u,v); }


    Dmath::DoubleVarFunction getXFunc(){ return this->xOfUV;  }
    Dmath::DoubleVarFunction getYFunc(){ return this->yOfUV;  }
    Dmath::DoubleVarFunction getZFunc(){ return this->zOfUV;  }


    Dmath::Vec3D getPartialUAt(Dmath::Scalar u, Dmath::Scalar v);
    Dmath::Vec3D getPartialVAt(Dmath::Scalar u, Dmath::Scalar v);

    Dmath::Vec3D normVectorAt (Dmath::Scalar u, Dmath::Scalar v);

};

#pragma endregion


NAMESPACEEND



#endif