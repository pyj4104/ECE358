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
	q2 Question2;
	int timeElapsed;
	
	timeElapsed = 10000;
	
	for (long sizeofBuffer; sizeofBuffer < 20; sizeofBuffer += 5)
	{
		if (sizeofBuffer == 0)
		{
			cout << "Buffer of inf" << endl;
		}
		else
		{
			cout << "Buffer of " << sizeofBuffer << endl;
		}
		
		cout << "Rho Value,Average # of Packets" << endl;
		
		for (double rho = 0.5; rho < 1.6; rho += 0.1)
		{
			Question2 = *new q2(timeElapsed, rho, sizeofBuffer);
			
			Question2.GenerateArrivalPackects();
			Question2.GenerateObserverPackets();
			Question2.SortDES();
			
			cout << rho << "," << (double)(Question2.Np())/(double)(Question2.No()) << endl;
		}
		
		cout << endl;
	}
}

//
//int main()
//{
//    int timeElapsed;
//    
//    timeElapsed = 10000;
//    
//    q2 * question2;
//    
//    question2 = new q2(timeElapsed, 0.5, 5);
//    question2->GenerateArrivalPackects();
//    question2->GenerateObserverPackets();
//    question2->SortDES();
//	
//    cout << "Average # of Packets: " << (double)(question2 -> Np())/(double)(question2 -> No()) << endl;
//    cout << "Idle Probability: " << (double)(question2 -> Ni())/(double)(question2 -> No()) << endl;
//    cout << "Number of Lost Packets: " << question2 -> Nloss() << endl;
//    cout << "Number of Generated Packets: " << question2 -> Ngen() << endl;
//    
//    question2 = NULL;
//    delete question2;
//    
//    return 0;
//}
