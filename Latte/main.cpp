//
//  This is a Deep Learning based library for mobile devices
//
//  main.cpp
//  Latte 1
//
//
//  Created by Haoxi Zhang on 19/12/2015.
//  Copyright © 2015 Haoxi Zhang. All rights reserved.
//

#include <iostream>
#include "DDNA_Network.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, neural networks!\n";
 
    int sizes[] = {2, 3, 4, 5, 4};
    DDNA_Network net(5, sizes);
    
    int x = net.getNumberOfLayers();
    //net.printAtt();
    
    int input[]= {5,7};
    net.feedforward(input);
 
    return x;
}
