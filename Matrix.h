#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

#include <vector>

class Matrix {
    public:
        std::vector<std::vector<float>> data;
        Matrix( int rows, int cols );

};


#endif