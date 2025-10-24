#include"../include/Oprator.hpp"

Dmath::Scalar Dmath::IntegralOperator(Dmath::Parameters param, Dmath::SingleVarFunction func){
    if(!Dmath::checkParams(param)){
        std::cerr << "ERROR: Wrong parameters\nError code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
        return 0;
    }
    Dmath::Natural a = param.one;
    Dmath::Natural b = param.two;
    Dmath::Scalar dx = param.three;


    Dmath::Natural num = Dmath::numberOfElements(param);
    Dmath::Scalar  sum = 0;
    for(size_t i = 0; i < num; i++){
        Dmath::Scalar currentIteration = a + i * dx;
        Dmath::Scalar currentResult    = func(currentIteration) * dx;
        sum += currentResult; 
    }

    return sum;
} 


Dmath::Scalar Dmath::sumOverS(Dmath::Parameters param, Dmath::SingleVarFunction func){
    if (!Dmath::checkParams(param)){
        std::cerr << "ERROR: Wrong parameters\nError code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
        return 0;
    }

    const Dmath::Natural a = static_cast<size_t>(param.one);
    const Dmath::Natural b = static_cast<size_t>(param.two);
    //const Dmath::Scalar dx = param.three;

    Dmath::Scalar sum = 0;

    for(size_t i = a; i <= b; i++){
        
        sum += func(i);
    }
    return sum;
}


Dmath::Vec3D Dmath::sumOverV(Dmath::Parameters param, Dmath::SingleVectorFunction func){
    if (!Dmath::checkParams(param)){
        std::cerr << "ERROR: Wrong parameters\nError code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
        return 0;
    }

    const Dmath::Natural a = static_cast<size_t>(param.one);
    const Dmath::Natural b = static_cast<size_t>(param.two);

    Dmath::Vec3D sum(0,0,0);

    for(size_t i = a; i <= b; i++){
        
        sum += func(i);
    }
    return sum;
}
