//
//  Sim.h
//  
//
//  Created by YeounJun Park on 2015-01-26.
//
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <math.h>

#ifndef _Sim_h
#define _Sim_h

double ExponentialGenerator(int x)
{
    double value, number;
    int lambda;
    
    lambda = x;
    
    srand(time(0));
    number = rand()/(double)(RAND_MAX);
    
    value = -1 * log(1-number) / lambda;
    return value;
}

#endif
