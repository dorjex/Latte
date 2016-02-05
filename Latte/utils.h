//
//  utils.h
//  Latte
//
//  Created by Haoxi Zhang on 19/12/2015.
//  Copyright © 2015 Haoxi Zhang. All rights reserved.
//

#ifndef utils_h
#define utils_h
#include <stdlib.h>
#include <time.h>
#include <math.h>


double randn(const double Mean, const double SquareMargin)
{
    const double PI = 3.1415926;
    double model = 4294967296.0;
    double multiplicator = 663608941.0;
    double temp_a, temp_b;
    static double seed = (double)time(NULL);
    
    seed *= multiplicator;
    seed -= (int)(seed/model) * model;
    temp_a = seed/model;
    
    seed *= multiplicator;
    seed -= (int)(seed/model) * model;
    temp_b = seed/model;
    
    double norm_randn = sqrt(-2*log(temp_a))*cos(2*PI*temp_b);
    double gauss_rand = Mean + norm_randn*SquareMargin;
    return(gauss_rand);
}

double uniform(double min, double max) {
    return rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double gaussian(double x, double y) {
    return randn(y, x)/sqrt(x);
}


#endif /* utils_h */
