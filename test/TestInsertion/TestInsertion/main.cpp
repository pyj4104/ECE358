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

std::list<int>::iterator InsertPacket(std::list<int>::iterator &it, int number)
{
    if (it != _DES.end())
    {
        while (number > *it)
        {
            if (*(std::next(it)) > number)
            {
                _DES.insert(std::next(it), number);
                break;
            }
            it++;
        }
        if (number < *it)
        {
            _DES.insert(it, number);
        }
    }
    else
    {
        _DES.push_back(number);
    }
    return it;
}

int main()
{
    int number = 10;
    int period = 50;
    
    list<int>::iterator it;
    
    srand(time(0));
    
    while (number < 50)
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
    
    while (number < 10)
    {
        number += rand() % 2 + 1;
        it = InsertPacket(it, number);
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
