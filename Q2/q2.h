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
    void SortDES();
    ~Q2();
private:
    void InsertPacket(std::list<packet>::iterator it, packet packetToInsert);
    
    int _Na, _Nd, _No, _Ni, _Np, _Ta, _Td, _To, _Time, _lambda;
    std::list<packet> _DES;
};

Q2::Q2(int numberOfPackets)
{
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
        _DES.push_back(arrival);
    }
}

void Q2::GenerateObserverPackets()
{
    int alpha;
    
    packet observer;
    std::list<packet>::iterator it;
    
    alpha = 3*_lambda;
    it = _DES.begin();
    
    while (_To < _Time)
    {
        _To += ExponentialGenerator(alpha);
        observer.type = o;
        observer.time = _To;
        InsertPacket(it, observer);
    }
}

void Q2::SortDES()
{
    packet event;
    
    while (_DES.empty())
    {
        event = _DES.front();
        if (event.type == a)
        {
            
        }
    }
}

void Q2::InsertPacket(std::list<packet>::iterator it, packet packetToInsert)
{
    if (it != _DES.end())
    {
        if (it->time > packetToInsert.time)
        {
            _DES.insert(it, packetToInsert);
        }
        else
        {
            if (std::next(it)->time > packetToInsert.time)
            {
                _DES.insert(std::next(it), packetToInsert);
            }
            else
            {
                it++;
                InsertPacket(it, packetToInsert);
            }
        }
    }
    else
    {
        _DES.push_back(packetToInsert);
    }
}

Q2::~Q2()
{
}

#endif
