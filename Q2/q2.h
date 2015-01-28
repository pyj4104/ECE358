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
    int Np();
    int No();
    int Ni();
    ~Q2();
private:
    void InsertPacket(std::list<packet>::iterator it, packet packetToInsert);
    
    int _Na, _Nd, _No, _Ni, _Np, _Ta, _Td, _To, _Time, _lambda, _L, _C;
    std::list<packet> _DES;
};

Q2::Q2(int timeElapsed)
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
    _Time = timeElapsed;
    _L = 12000;
    _C = 1000000;
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
    double packetLength, serviceTime;
    
    packet event, departure;
    std::list<packet>::iterator it;
    
    it = _DES.begin();
    
    while (!_DES.empty())
    {
        event = _DES.front();
        
        if (event.type == a)
        {
            packetLength = ExponentialGenerator(1/_L);
            serviceTime = packetLength/_C;
            
            if (_Na-_Nd == 0)
            {
                _Td = event.time + serviceTime;
            }
            else
            {
                _Td += serviceTime;
            }
            
            departure.time = _Td;
            departure.type = d;
            
            InsertPacket(it, departure);
            _Na += 1;
        }
        else if(event.type == d)
        {
            _Nd += 1;
            it = std::next(it);
            _DES.pop_front();
        }
        else if(event.type == o)
        {
            _No += 1;
            _Np = _Np * (_No - _Nd);
            
            if (_Na-_Nd == 0)
            {
                _Ni += 1;
            }
            
            it = std::next(it);
            _DES.pop_front();
        }
        
        if (it != _DES.end())
        {
            it++;
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

int Q2::Np()
{
    return _Np;
}

int Q2::No()
{
    return _No;
}

int Q2::Ni()
{
    return _Ni;
}

Q2::~Q2()
{
}

#endif
