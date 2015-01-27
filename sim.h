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

double ExponentGenerator(double number)
{
    double value, lambda;
    
    lambda = 75;
    
    value = -1 * log(1-number) / lambda;
    return value;
}

#endif
