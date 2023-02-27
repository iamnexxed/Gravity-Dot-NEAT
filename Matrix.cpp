#include "Matrix.h"

Matrix::Matrix() {
    // No Rows and Columns
    // Empty Matrix
}

Matrix::Matrix( int rows, int cols ) {
    this->Resize( rows, cols );
}

void Matrix::Accumulate( const Matrix& other) {
    for( int i = 0; i < this->data.size(); ++i ) {
        if( this->data.size() != other.data.size() || 
            this->data[i].size() != other.data[i].size()
        ) {
            std::cout << "\nMatrices are not similar in dimensions\n Addition Not Possible!";
            return;
        }
        for( int j = 0; j < this->data[i].size(); ++j ) {
            this->data[i][j] += other.data[i][j];
        }
    }
    
}

Matrix Matrix::Multiply( const Matrix& other ) {
    Matrix m( this->data.size(), other.data[0].size() );
    
    for( int i = 0; i < m.data.size(); ++i ) {
        if( this->data[i].size() == other.data.size() ) {
            for( int j = 0; j < m.data[i].size(); ++j ) {   
                    for( int k = 0; k < this->data[i].size(); ++k )
                        m.data[i][j] += this->data[i][k] * other.data[k][j];
            } 
        }
        else {
            std::cout << "\nMATRIX ERROR: Cannot perform matrix multiplication!\n";
            break;
        }
            
    }
    return m;
}

void Matrix::Print() {
    for( int i = 0; i < this->data.size(); ++i ) {
        for( int j = 0; j < this->data[i].size(); ++j ) {
            std::cout << "\t" << this->data[i][j];
        }
        std::cout << "\n";
    }
}

void Matrix::FillFloat( float num ) {
    for( int i = 0; i < this->data.size(); ++i ) {
        for( int j = 0; j < this->data[i].size(); ++j ) {
            this->data[i][j] = num;
        }
    }
}

void Matrix::Resize( int rows, int cols ) {
    this->data.resize( rows );
    for( int i = 0; i < rows; ++i ) {
        this->data[i].resize( cols );
    }
}