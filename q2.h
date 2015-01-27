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
    int _Na, _Nd, _No, _Ni, _Np, _Ta, _Td, _To, _Time;
    std::list<packet> * _DES;
    
};

Q2::Q2(int numberOfPackets)
{
    _DES = new std::list<packet>;
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
    int lambda;
    packet arrival;
    
    lambda = 75;
    
    while (_Ta < _Time)
    {
        arrival.time = _Ta + ExponentialGenerator(lambda);
        arrival.type = a;
        _DES->push_back(arrival);
    }
}

Q2::~Q2()
{
    delete[] _DES;
}

#endif
