//ece 358
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include "sim.h"
#include "q2.h"
#include "packetStructure.h"

using namespace std;

int timeElapsed;

int main()
{
    timeElapsed = 1;
    
    Q2 * question2;
    
    question2 = new Q2(timeElapsed);
    question2 -> GenerateArrivalPackects();
    question2 -> GenerateObserverPackets();
    question2 -> SortDES();
    
    printf("Average # of packets: %f\n", (double)(question2 -> Np())/(double)(question2 -> No()));
    printf("Idle Probability: %f\n", (double)(question2 -> Ni())/(double)(question2 -> No()));
    
	return 0;
}