//ece 358
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <math.h>
using namespace std;

double ExponentGenerator(double number)
{
    double value, lambda;
    
    lambda = 75;
    
    value = -1 * log(1-number) / lambda;
    return value;
}

double VarCalc(double generatedNums[1000], double mean)
{
    double totalToCalcVar, var;
    
    totalToCalcVar = 0;
    
    for (int i = 0; i < 1000; i++)
    {
        totalToCalcVar += (generatedNums[i] - mean) * (generatedNums[i] - mean);
    }
    
    var = totalToCalcVar / 1000;
    
    return var;
}

void Question1()
{
    double number, total, mean, totalToCalcVar, var, max, generatedNums[1000];
    
    total = 0;
    totalToCalcVar = 0;
    
    srand(time(0));
    for(int i = 0; i < 1000; i++)
    {
        number = ExponentGenerator(rand()/(double)(RAND_MAX));
        generatedNums[i] = number;
        total = total + number;
    }
    
    mean = total/1000;
    var = VarCalc(generatedNums, mean);
    
    printf("Mean: %f\n", mean);
    printf("Varience: %f\n", var);
}

int main()
{
    double test, product;
    
    test = 0.5;
    product = 0;
    
    product = ExponentGenerator(test);
    printf("%f\n", product);
    
    Question1();
    
	return 0;
}