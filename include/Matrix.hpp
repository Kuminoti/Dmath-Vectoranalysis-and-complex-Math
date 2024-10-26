#pragma once
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include"macros.hpp"
#include"mathVector.hpp"

#ifdef SYSTEM_READY
    #ifdef VECTORMATH_H
        #define _VEC
    #endif//VECTORMATH_H
#endif // SYSTEM_READY

NAMESPACESTART


template<class mat>
class Matrix {
private: //Private members

    mat** mainMatrix;
    bool squaredMatrix = false;

    uint8_t elementsRow    = 0;
    uint8_t elementsColumn = 0;
    uint16_t totalElements = 0;

    
    

private: //Private methods and helper functions


    Matrix<mat> getSubMatrix(uint8_t excludingRow, uint8_t excludingCol) const {
        Matrix<mat> subMatrix(this->elementsRow - 1, this->elementsColumn - 1);
        uint8_t subMatrixRow = 0;
        uint8_t subMatrixCol = 0;

        for (uint8_t row = 0; row < this->elementsRow; row++) {
            if (row == excludingRow) continue;
            subMatrixCol = 0;
            for (uint8_t col = 0; col < this->elementsColumn; col++) {
                if (col == excludingCol) continue;
                subMatrix.setElement(subMatrixRow + 1, subMatrixCol + 1, this->getElement(row + 1, col + 1));
                subMatrixCol++;
            }
            subMatrixRow++;
        }

        return subMatrix;
    }


    bool checkMatrixSizes(Matrix matrixOne, Matrix matrixTwo){
        bool valid = false;

        if(matrixOne.elementsColumn == matrixTwo.elementsColumn &&
           matrixOne.elementsRow    == matrixTwo.elementsRow    ){
            valid = true;
        }
        return valid;
    }


public: // condtructor and destructor

    // Squared matrix constructor
    Matrix(uint8_t elements){
        this->squaredMatrix = true;
        this->elementsColumn = elements;
        this->elementsRow = elements;
        this->totalElements = elements * elements;
    }

    Matrix(uint8_t elementsRow, uint8_t elementsColumn){
        this->elementsColumn =  elementsColumn;
        this->elementsRow    =  elementsRow;
        this->totalElements  =  elementsRow * elementsColumn;

        if(elementsColumn == elementsRow){
            this->squaredMatrix = true;
        }


        this->mainMatrix = new uint8_t*[this->elementsRow];
        for(uint8_t i = 0; i<this->elementsRow; i++){
            this->mainMatrix[i] = new mat[this->elementsColumn];
        }
    }

    ~Matrix(){
        for(uint8_t i = 0; i < this->elementsRow; i++){
            delete[] this->mainMatrix[i];
        }
        delete[] this->mainMatrix;
        this->mainMatrix = nullptr;
    }


public: //Getters and setters

    inline bool isSquared(){
        return this->squaredMatrix;
    }



    void setAll(mat data){
        for(size_t i = 0; i < this->elementsRow; i++){
            for(uint8_t j = 0; j < this->elementsColumn; j++){
                this->mainMatrix[i][j] = data;
            }

        }
    }


    Matrix transpose() {
        Matrix transposedMatrix(this->elementsColumn, this->elementsRow);

        for (uint8_t row = 0; row < this->elementsRow; row++) {
            for (uint8_t col = 0; col < this->elementsColumn; col++) {
                transposedMatrix.setElement(col + 1, row + 1, this->getElement(row + 1, col + 1));
            }
        }

        return transposedMatrix;
    }

public: 
    mat getElement(uint8_t row, uint8_t Column){
        if(row < 0 || row > this->elementsRow || Column < 0 || Column > this->elementsColumn){
#ifdef WORKING
            std::cerr << "Error out of range" <<std::endl;
#endif //Working
            return CNULL; // NULL ((void *)0)
        }
        mat Result;
        Result = this->mainMatrix[row-1][Column-1]; //Since an array is 0 indexed
        return Result;
    }

    void setElement(uint8_t row, uint8_t Column, mat data){
        if(row < 0 || row > this->elementsRow || Column < 0 || Column > this->elementsColumn){
#ifdef WORKING
            std::cerr << "Error out of range" <<std::endl;
#endif //WORKING
            return; 
        }
        this->mainMatrix[row-1][Column-1] = data;
    }


    Matrix getSquaredMatrix(uint8_t elements){
        return Matrix(elements);
    }


public: //Macro dependend code


    /*
     * Mathmatical operations with Vectos and Matrix
     */

    template<typename t = mat, typename T, typename d_type_two = double ,typename std::enable_if<std::is_same<T, d_type_two>::value, int>::type = 0>
    Matrix vectorMultiplication(Dmath::Vec2D &vec){
        if(this->elementsColumn < 2){
            //Daten stimmen nicht überein 
            //Vektormultiplikation nicht möglich
            return Matrix(1,1);
        }
        Matrix<double> endMatrix(1,this->elementsColumn);

        double resultOne = 0;
        double resultTwo = 0;

        for(size_t i = 0; i < this->elementsRow; i++){
            resultOne += vec.getX() * this->mainMatrix[i][0] ;
            resultTwo += vec.getY() * this->mainMatrix[i][1] ;
        }

      

        

        /* The endmatrix will be 1x2 vector-like matrix
         * A = ([resultOne]
        *      [resultTwo] )
        */
        endMatrix.setElement(1,1,resultOne);
        endMatrix.setElement(2,1,resultTwo);

        return endMatrix;

    }

   
    template<typename t = mat, typename T, typename d_type_two = double, typename std::enable_if<std::is_same<T, d_type_two>::value, int>::type = 0>
    Matrix vectorMultiplication(Dmath::Vec3D &vec){
        if(this->elementsColumn < 3){
            //Daten stimmen nicht überein 
            //Vektormultiplikation nicht möglich
            return Matrix(1,1);
        }

        double resultOne = 0;
        double resultTwo = 0;
        double resultTri = 0;

        for(size_t i = 0; i < this->elementsColumn; i++){
            resultOne += this->mainMatrix[i][0] ;
            resultTwo += this->mainMatrix[i][1] ;
            resultTri += this->mainMatrix[i][2]
        }

    }
    

public:

    mat determinant() const {
        if (!this->squaredMatrix) {
            std::cerr << "Determinant is undefined for non-square matrices. Returning 0." << std::endl;
            return 0; 
        }

        if (this->elementsRow == 1) {
            return this->mainMatrix[0][0]; // 1x1-Matrix
        }

        if (this->elementsRow == 2) {
            return this->mainMatrix[0][0] * this->mainMatrix[1][1] - this->mainMatrix[0][1] * this->mainMatrix[1][0];
        }

        mat det = 0;
        for (uint8_t col = 0; col < this->elementsColumn; col++) {
            Matrix<mat> subMatrix = this->getSubMatrix(0, col); // Untermatrix erstellen
            det += (col % 2 == 0 ? 1 : -1) * this->mainMatrix[0][col] * subMatrix.determinant();
        }

        return det;
    }



    

};

NAMESPACEEND

#endif //MATRIX_HPP