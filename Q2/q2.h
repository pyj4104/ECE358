//
//  q2.h
//  
//
//  Created by YeounJun Park on 2015-01-26.
//
//
#include <iostream>
#include <list>
#include "sim.h"
#include "packetStructure.h"

#ifndef _q2_h
#define _q2_h

class Q2
{
public:
    Q2(int numberOfPackets);
    void GenerateArrivalPackects();
    void GenerateObserverPackets();
    ~Q2();
private:
    void InsertArrivalPacket(std::list<int>::iterator it);
    
    int _Na, _Nd, _No, _Ni, _Np, _Ta, _Td, _To, _Time, _lambda;
    std::list<packet> * _DES;
};

Q2::Q2(int numberOfPackets)
{
    _DES = new std::list<packet>;
    _lambda = 75;
    _Na = 0;
    _Nd = 0;
    _No = 0;
    _Ni = 0;
    _Np = 0;
    _Ta = 0;
    _Td = 0;
    _To = 0;
    _Time = numberOfPackets;
}

void Q2::GenerateArrivalPackects()
{
    packet arrival;
    
    while (_Ta < _Time)
    {
        _Ta += ExponentialGenerator(_lambda);
        arrival.time = _Ta;
        arrival.type = a;
        _DES->push_back(arrival);
    }
}

void Q2::GenerateObserverPackets()
{
    int alpha;
    
    packet observer;
    std::list<int>::iterator iterator;
    
    alpha = 3*lambda;
    iterator = _DES->begin();
    
    while (_To < _Time)
    {
        _To += ExponentialGenerator(_alpha);
        observer.type = o;
        observer.time = _To;
        InsertArrivalPacket(iterator);
    }
}

void Q2::InsertArrivalPacket(std::list<int>::iterator it)
{
    if (it.)
    {
        <#statements#>
    }
}

Q2::~Q2()
{
    delete[] _DES;
}

#endif
