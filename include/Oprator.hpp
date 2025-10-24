#pragma once


/* File experimental/Operator.hpp
 * 
 * Project Start:
 * 24. October 2025
 * 
 * Purpose: 
 * This file contains functions and classes for 
 * pre written Functional operators (mathFunctional.hpp)
 * Like Arclenth functionals
 * Sum operators 
 * diffrential and integral operators
 * 
 * Example the Arclenght integral
 * ∫ ds ->[a,b] = ∫ sqrt(1 + (f'(x)^2)
 * 
*/

#ifndef DMATH_OPERATOR_HPP
#define DMATH_OPERATOR_HPP

    #include"vectorfunction.hpp"
    #include"dFunctions.hpp"

    NAMESPACESTART //Namespace Dmath
      


    #pragma region IntegralOperators

    /* This function calculates the arclenght of a funtion using the Arclenght integral
     * ∫ ds ->[a,b] = ∫ sqrt(1 + (f'(x)^2)
     * Or in the case of a curve in parameter form:
     * k(t) = { x(t); y(t); z(t) }
     * ∫ ds ->[a,b] = ∫ sqrt((x'(t))² + (y'(t))² + (z'(t))² )
     */
    template<typename Func>
    Dmath::Scalar arcLenght(Dmath::Parameters param, Func func){
        if (!Dmath::checkParams(param)){
            std::cerr << "ERROR: Wrong parameters\nError code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
            return 0;
        }
  
        const Dmath::Natural a = static_cast<size_t>(param.one);
        const Dmath::Natural b = static_cast<size_t>(param.two);
        const Dmath::Scalar dx = param.three;

        Dmath::Scalar sum = 0;

        Dmath::Natural num = Dmath::numberOfElements(param);

        

        for(size_t i = 0; i < num; i++){
            Dmath::Scalar currentX = a + i * dx;
            if constexpr (std::is_same<Func, Dmath::SingleVectorFunction>::value){
                Dmath::Scalar currentResult = std::sqrt(
                    (func.getXFunc().getDerivativeAt(currentX) * func.getXFunc().getDerivativeAt(currentX)) + 
                    (func.getYFunc().getDerivativeAt(currentX) * func.getYFunc().getDerivativeAt(currentX)) 
                    (func.getZFunc().getDerivativeAT(currentX) * func.getZFunc().getDerivativeAT(currentX))
                    ) * dx;

                sum += currentResult;
                continue;
            }
            Dmath::Scalar currentResult = std::sqrt(1 + (func.getDerivativeAt(currentX) * func.getDerivativeAt(currentX))) * dx;
            sum += currentResult;
            
        }

        return sum;
    }

    /*
     * The integral between to points on a functiongraph calculates the area between
     * the funtion graph and the x Achsis.
     * numericly the integral is calculated by summing up infinitesimal surface elements
    */
    SHARED_LIB Dmath::Scalar IntegralOperator(Dmath::Parameters param, Dmath::SingleVarFunction func);


    #pragma endregion //IntegralOperators

 
    
    #pragma region SumOperators

    /*
     * This function calculates the sum form given boundaries i -> [a,b]
     * 
     * ∑( f(x) ) = f(a) + f(a + 1) + ... f(b)
     * 
     * scince Scalar functions and vector functions need to be handelt seperatly
     * there are different Sigma functions
     * 
     */
    SHARED_LIB Dmath::Scalar sumOverS(Dmath::Parameters param, Dmath::SingleVarFunction func);


    SHARED_LIB Dmath::Vec3D sumOverV(Dmath::Parameters param, Dmath::SingleVectorFunction func);

    #pragma endregion //SumOperators
    
        
    NAMESPACEEND





#endif //DMATH_EXPERIMATAL_OPERATOR_HPP