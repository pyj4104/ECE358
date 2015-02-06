//
//  main.cpp
//  ECE358Lab1
//
//  Created by YeounJun Park on 2015. 1. 28..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#include <iostream>
#include "q2.h"

using namespace std;

int main()
{
    int timeElapsed;
    
    timeElapsed = 10000;
    
    q2 * question2;
    
    question2 = new q2(timeElapsed, 1.2);
    question2->GenerateArrivalPackects();
    question2->GenerateObserverPackets();
    question2->SortDES();
	
    cout << "Average # of packets: " << (double)(question2 -> Np())/(double)(question2 -> No()) << endl;
    cout << "Idle Probability: " << (double)(question2 -> Ni())/(double)(question2 -> No()) << endl;
    
    question2 = NULL;
    delete question2;
    
    return 0;
}
