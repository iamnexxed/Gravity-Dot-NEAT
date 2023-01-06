#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

#include <vector>
#include <iostream>

class Matrix {
    public:
        std::vector<std::vector<float>> data;
        Matrix();
        Matrix( int rows, int cols );
        void Accumulate( const Matrix& other);
        Matrix Multiply( const Matrix& other );
        void Print();
        void FillFloat( float num );
        void Resize( int rows, int cols );
};


#endif