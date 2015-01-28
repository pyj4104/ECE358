//
//  TestInsertion.cpp
//  
//
//  Created by YeounJun Park on 2015. 1. 27..
//
//

#include <stdlib.h>
#include <iostream>
#include <list>
#include <math.h>

using namespace std;

list<int> _DES;

void InsertPacket(std::list<int>::iterator it, int number)
{
    if (it != _DES.end())
    {
        if (*it > number)
        {
            _DES.insert(it, number);
        }
        else
        {
            if (*(std::next(it)) > number)
            {
                _DES.insert(std::next(it), number);
            }
            else
            {
                it++;
                InsertPacket(it, number);
            }
        }
    }
    else
    {
        _DES.push_back(number);
    }
}

int main()
{
    int number = 0;
    int period = 50;
    
    list<int>::iterator it;
    
    srand(time(0));
    
    while (number < period)
    {
        number += rand() % 10 + 1;
        _DES.push_back(number);
        printf("%i ", number);
    }
    
    printf("\n");
    
    it = _DES.begin();
    
    while (it != _DES.end())
    {
        printf("%i ", *it);;
        it++;
    }
    
    printf("\nFirstTest\n");
    
    number = 0;
    it = _DES.begin();
    
    while (number < 75)
    {
        number += rand() % 10;
        InsertPacket(it, number);
    }
    
    it = _DES.begin();
    while (it != _DES.end())
    {
        printf("%i ", *it);;
        it++;
    }
    
    printf("\nSecondTest\n");
    
    return 0;
}
