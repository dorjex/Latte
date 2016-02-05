//
//  DDNA_Network.cpp
//  Latte
//
//  Created by Haoxi Zhang on 19/12/2015.
//  Copyright © 2015 Haoxi Zhang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "DDNA_Network.h"
#include "utils.h"
using namespace std;

/*
template <typename T, size_t N>
constexpr size_t countof(T(&)[N])
{
    return N;
}
*/

DDNA_Network::DDNA_Network(int num_of_layers, int *network_sizes){
    iNum_of_layers = num_of_layers;
    iSizes = network_sizes;
    /*
    int iLen = sizeof(iSizes)/sizeof(iSizes[0]);
    
    if (iNum_of_layers <= 0 || iNum_of_layers != iLen) {
        std::cout << "Check the number of layers with network sizes.\n" << std::endl;
        return;
    }    
    */
    iIndex_of_OutputLayer = iNum_of_layers -1;
    iInputSize = iSizes[0];
    //default_weight_initializer();
    testInit();
}

//DDNA_Network::test(int &inn[]){
//    int i = countof(inn);
//}

DDNA_Network::~DDNA_Network(){
    
    for(int i = 0; i < iIndex_of_OutputLayer ; i++ ){
        delete db[i];
        delete dW[i];
    }
    delete [] dW;
    delete [] db;
}

int DDNA_Network::getNumberOfLayers(){
    return iNum_of_layers;
}

void DDNA_Network::testInit(){

    db = new double *[iIndex_of_OutputLayer];
    dW = new double **[iIndex_of_OutputLayer];
    
    for(int i = 0; i < iIndex_of_OutputLayer ; i++ ){
        int x = iSizes[i];
        int y = iSizes[i+1];
        // initializing biases first
        db[i] = new double[y];
        for( int j = 0; j < y; j++){
            db[i][j] = j;
        }
        // initializing weights
        dW[i] = new double*[x];
        for( int k = 0; k < x; k++){
            dW[i][k] = new double[y];
            for( int l = 0; l < y; l++ ){
                dW[i][k][l] = l;
            }
        }
        
    }
    bInitialized = true;
}

void DDNA_Network::default_weight_initializer(){
   
    db = new double *[iIndex_of_OutputLayer];
    dW = new double **[iIndex_of_OutputLayer];
    
    for(int i = 0; i < iIndex_of_OutputLayer ; i++ ){
        int x = iSizes[i];
        int y = iSizes[i+1];
        // initializing biases first
        db[i] = new double[y];
        for( int j = 0; j < y; j++){
            db[i][j] = gaussian(y, 1);
        }
        // initializing weights
        dW[i] = new double*[x];
        for( int k = 0; k < x; k++){
            dW[i][k] = new double[y];
            for( int l = 0; l < y; l++ ){
                dW[i][k][l] = gaussian(x, y);
            }
        }
        
    }
    bInitialized = true;
}


/*
Return the output of the network
*/
double * DDNA_Network::feedforward(int *input){
    
    if (!bInitialized) {
        std::cout << "Please initialize the network first! \n" << std::endl;
        return 0;
    }
    /*
    int is = sizeof(input)/sizeof(input[0]);
    if (is != iInputSize) {
        std::cout << "Please check the input_size parameter with the real input size! \n"
        << std::endl;
        return 0;
    }
    */
    double **result = new double *[iNum_of_layers];
    double * dPreInput = new double [iInputSize];
    
    int iOutSize = iSizes[iIndex_of_OutputLayer];
    
    for( int n = 0; n < iInputSize; n++)
        dPreInput[n] = input[n];
    
    for( int i = 0; i < iIndex_of_OutputLayer ; i++ ){
        int x = iSizes[i];
        int y = iSizes[i+1];
        
        result[i] = new double[y];
        
        for( int j = 0; j < x; j++){
            for( int k = 0; k < y; k++ ){
                //result[i][k] = sigmoid( dW[i][j][k] * dPreInput[j] + db[i][k] );
                result[i][k] += dW[i][j][k] * dPreInput[j];
                //printf("%f ", result[i][k]);
            }
        }
        delete [] dPreInput;
        dPreInput = new double[y];
        for( int c = 0; c < y; c++ ){
            dPreInput[c] = sigmoid( result[i][c] + db[i][c] );
            printf("dpre %f ", dPreInput[c]);
        }
        printf("---layer---- \n");
    }
    
    printf("\n the LATTE network output: \n");
    for( int j = 0; j < iOutSize; j++)
        printf("%f ", dPreInput[j]);
    printf("\n\n");
    return result[iIndex_of_OutputLayer];
}

void DDNA_Network::printAtt(){
    
    std::cout << "--- biases --- \n" << std::endl;
    for(int i = 0; i < iIndex_of_OutputLayer ; i++ ){
        int y = iSizes[i+1];
        
        for( int j = 0; j < y; j++){
            std::cout << db[i][j] << " ";
        }
        std::cout << "----" << std::endl;
    }
    std::cout << "--- end biases --- \n" << std::endl;
    
    /////////////////////////
    std::cout << "--- weights --- \n" << std::endl;
    for(int i = 0; i < iIndex_of_OutputLayer ; i++ ){
        int x = iSizes[i];
        int y = iSizes[i+1];
        for( int j = 0; j < x; j++){
            for( int k = 0; k < y; k++ ){
                std::cout << dW[i][j][k] << " ";
            }
            std::cout << "----" << std::endl;
        }
        std::cout << "----" << std::endl;
    }
    std::cout << "--- end weights --- \n" << std::endl;
}