//ece 358
#include <iostream>
#include "q2.h"

using namespace std;

int timeElapsed;

int main()
{
    printf("hi");
    timeElapsed = 10;
    
    Q2 * question2;
    
    question2 = new Q2(timeElapsed);
    question2->GenerateArrivalPackects();
    question2->GenerateObserverPackets();
    question2->SortDES();
    
    printf("Average # of packets: %f\n", (double)(question2 -> Np())/(double)(question2 -> No()));
    printf("Idle Probability: %f\n", (double)(question2 -> Ni())/(double)(question2 -> No()));
    
	return 0;
}