#pragma once

#ifndef DMATH_VECTORFUNCTION_HPP
#define DMATH_VECTORFUNCTION_HPP

#include"mathFunction.hpp"

NAMESPACESTART

/* Diese Datei beinhaltet klassen zur beschreibung von vektoriell dargestellten funktionen z.B:
 * zur darstellung von Parametrisierungen von kurven oder oberflächen
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
    SingleVectorFunction() = default;
    //constructor for 2D vectorFunction
    SingleVectorFunction(Dmath::SingleVarFunction xOfT, Dmath::SingleVarFunction yOfT);

    SingleVectorFunction(Dmath::SingleVarFunction xOfT, Dmath::SingleVarFunction yOfT, Dmath::SingleVarFunction zOfT);
   
    Dmath::Vec2D call2D(Dmath::Scalar t);
    
    Dmath::Vec3D operator ()(Dmath::Scalar t);

    SingleVectorFunction operator+(SingleVectorFunction funcTwo);
    SingleVectorFunction operator-(SingleVectorFunction funcTwo);

    //Operator for scalar multiplikation
    Dmath::SingleVarFunction operator*(SingleVectorFunction funcTwo);

    //operator for crossproducts
    SingleVectorFunction crossProduct(SingleVectorFunction funcTwo);
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
    Dmath::Vec3D operator ()(Dmath::Vec2D vec);

    inline Dmath::Scalar callX(Dmath::Scalar u, Dmath::Scalar v){ return xOfUV(u,v); }
    inline Dmath::Scalar callY(Dmath::Scalar u, Dmath::Scalar v){ return yOfUV(u,v); }
    inline Dmath::Scalar callZ(Dmath::Scalar u, Dmath::Scalar v){ return zOfUV(u,v); }

    Dmath::DoubleVarFunction operator*(DoubleVectorFunction func){
        //Scalarproduct operator
        
        //Copy the functions to avoid bugs caused by missing refrences

        Dmath::DoubleVarFunction thisX = this->getXFunc();
        Dmath::DoubleVarFunction thisY = this->getYFunc();
        Dmath::DoubleVarFunction thisZ = this->getZFunc();

        Dmath::DoubleVarFunction funcX = func.getXFunc();
        Dmath::DoubleVarFunction funcY = func.getYFunc();
        Dmath::DoubleVarFunction funcZ = func.getZFunc();

        //Calculation of the components of the scalarproduct
        Dmath::DoubleVarFunction scalarX = thisX * funcX;
        Dmath::DoubleVarFunction scalarY = thisY * funcY;   
        Dmath::DoubleVarFunction scalarZ = thisZ * funcZ;
        //Return a new function

        Dmath::DoubleVarFunction scalarProduct = scalarX + scalarY + scalarZ;
        return scalarProduct;
        
    }


    Dmath::DoubleVectorFunction operator+(DoubleVectorFunction funcTwo);

    Dmath::DoubleVectorFunction crossPruduct(DoubleVectorFunction funcTwo);

    Dmath::DoubleVarFunction getXFunc(){ return this->xOfUV;  }
    Dmath::DoubleVarFunction getYFunc(){ return this->yOfUV;  }
    Dmath::DoubleVarFunction getZFunc(){ return this->zOfUV;  }

   
    Dmath::Vec3D getPartialUAt(Dmath::Scalar u, Dmath::Scalar v);
    Dmath::Vec3D getPartialVAt(Dmath::Scalar u, Dmath::Scalar v);

    Dmath::Vec3D normVectorAt (Dmath::Scalar u, Dmath::Scalar v);

    
    Dmath::Matrix<Dmath::Scalar> getMetricAt(Dmath::Scalar u, Dmath::Scalar v){
        const Dmath::Scalar dxDu = this->xOfUV.derivativeXAT(u,v);
        const Dmath::Scalar dyDu = this->yOfUV.derivativeXAT(u,v);
        const Dmath::Scalar dzDU = this->zOfUV.derivativeXAT(u,v);

        Dmath::Vec3D basisVecU(dxDu,dyDu,dzDU);

        const Dmath::Scalar dxDV = this->xOfUV.derivativeYAT(u,v);
        const Dmath::Scalar dyDV = this->yOfUV.derivativeYAT(u,v);
        const Dmath::Scalar dzDV = this->zOfUV.derivativeYAT(u,v);
        Dmath::Vec3D basisVecV(dxDV,dyDV,dzDV);
        
        
        const Dmath::Scalar metricOne = basisVecU * basisVecU;
        const Dmath::Scalar metricTwo = basisVecU * basisVecV;
        // metric2 = metric 3
        const Dmath::Scalar metricfour = basisVecV * basisVecV;

        Dmath::Matrix<Dmath::Scalar> metric(2);
        metric.setElement(1,1,metricOne);
        metric.setElement(1,2,metricTwo);
        metric.setElement(2,1,metricTwo);
        metric.setElement(2,2,metricfour);

        return metric;
    }
};


#pragma endregion



#pragma region Triple

class TripleVectorFunction{
  private:
    Dmath::TripleVarFunction xOfUVW;
    Dmath::TripleVarFunction yOfUVW;
    Dmath::TripleVarFunction zOfUVW;

  public:

    TripleVectorFunction(Dmath::TripleVarFunction xOfUVW, Dmath::TripleVarFunction yOfUVW, Dmath::TripleVarFunction zOfUVW);
    Dmath::Vec3D operator()(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);

    //Tangential vektoren
    Dmath::Vec3D getPartialUAt(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Vec3D getPartialVAt(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Vec3D getPartialWAt(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);

    Dmath::Scalar callX(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Scalar callY(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Scalar callZ(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);

    //Patielle ableitungen aller funktionen
    Dmath::Scalar callXPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Scalar callYPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Scalar callZPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);

};

NAMESPACEEND
#endif