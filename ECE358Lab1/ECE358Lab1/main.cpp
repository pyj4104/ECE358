//
//  main.cpp
//  ECE358Lab1
//
//  Created by YeounJun Park on 2015. 1. 28..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#include <iostream>
#include "q2.h"

int main()
{
    int timeElapsed;
    
    printf("hi");
    timeElapsed = 10;
    
    q2 * question2;
    
    question2 = new q2(timeElapsed);
    question2->GenerateArrivalPackects();
    question2->GenerateObserverPackets();
    question2->SortDES();
    
    printf("Average # of packets: %f\n", (double)(question2 -> Np())/(double)(question2 -> No()));
    printf("Idle Probability: %f\n", (double)(question2 -> Ni())/(double)(question2 -> No()));
    
    question2 = NULL;
    delete question2;
    
    return 0;
}
