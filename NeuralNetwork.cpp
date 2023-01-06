#include "NeuralNetwork.h" 


Layer::Layer( int inputCount, int nodeCount ) {
    this->weightMatrix.Resize( nodeCount, inputCount );
    this->biasMatrix.Resize( nodeCount, 1 );

    std::cout << "\nWeight Matrix:\n";
    this->weightMatrix.Print();

    std::cout << "\nBias Matrix:\n";
    this->biasMatrix.Print();
}

Matrix Layer::GetOutput( 
    const Matrix& inputMatrix, bool shouldUseActivation 
) {
    Matrix res = this->weightMatrix.Multiply( inputMatrix );
    res.Accumulate( this->biasMatrix );
    if( shouldUseActivation ) {
        for( int i = 0; i < res.data.size(); ++i ) {
            for( int j = 0; j < res.data[i].size(); ++j ) {
                res.data[i][j] = NeuralNetwork::SigmoidActivation( res.data[i][j] );
            }
        }
    }
    return res;
}

NeuralNetwork::NeuralNetwork() {
    Layer l( 3, 2 );
    Matrix iM( 3, 1 );
    iM.FillFloat( 2.0f );
    std::cout << "\nInput Matrix:\n";
    iM.Print();
    Matrix m = l.GetOutput( iM );
    std::cout << "\nResult Matrix:\n";
    m.Print();
}

NeuralNetwork::NeuralNetwork( const Genome& genome ) {
    // Based on node connections in the genome create a Layer and add values to the Weight and Bias Matrices
}

void NeuralNetwork::CreateLayers( const Genome& genome ) {
    // Based on node connections in the genome create a Layer and add values to the Weight and Bias Matrices

}

float NeuralNetwork::SigmoidActivation( float value ) {
    return 1 / ( 1 + std::pow( E, -value ) );
}

Matrix NeuralNetwork::Predict( const Matrix& inputMatrix ) {
    return inputMatrix;
}