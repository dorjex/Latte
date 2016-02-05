//
//  DDNA_Network.h
//  Latte
//
//  Created by Haoxi Zhang on 19/12/2015.
//  Copyright © 2015 Haoxi Zhang. All rights reserved.
//

#ifndef DDNA_Network_h
#define DDNA_Network_h

class DDNA_Network{

  private:
    int *iSizes;
    int iNum_of_layers;
    int iIndex_of_OutputLayer;
    int iInputSize;
    double ***dW; //Weights
    double **db;  //biase
    void default_weight_initializer();
    bool bInitialized = false;
  
  public:
    DDNA_Network(int, int *);
    ~DDNA_Network();
    
    int getNumberOfLayers();
    void printAtt();
    double *feedforward(int *);
    
//    void test( int (&inn)[] );
    
    void testInit();
    double b[3][4];
    double W[2][3][4];
};

#endif /* DDNA_Network_h */
