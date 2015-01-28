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
    
    int _Na, _Nd, _No, _Ni, _Np, _Time, _lambda, _L, _C;
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
    _Time = timeElapsed;
    _L = 12000;
    _C = 1000000;
}

void Q2::GenerateArrivalPackects()
{
    printf("Beginnig of Observer Packets");
    double ta;
    packet arrival;
    
    ta = 0;
    
    while (ta < _Time)
    {
        ta += ExponentialGenerator(_lambda);
        arrival.time = ta;
        arrival.type = a;
        _DES.push_back(arrival);
    }
}

void Q2::GenerateObserverPackets()
{
    printf("Beginnig of Observer Packets");
    int alpha;
    double to;
    
    packet observer;
    std::list<packet>::iterator it;
    
    alpha = 3*_lambda;
    it = _DES.begin();
    to = 0;
    
    while (to < _Time)
    {
        to += ExponentialGenerator(alpha);
        observer.type = o;
        observer.time = to;
        InsertPacket(it, observer);
    }
}

void Q2::SortDES()
{
    printf("Beginning of SortDES");
    double packetLength, serviceTime, td;
    
    packet event, departure;
    std::list<packet>::iterator it;
    
    it = _DES.begin();
    td = 0;
    
    while (!_DES.empty())
    {
        event = _DES.front();
        
        if (event.type == a)
        {
            packetLength = ExponentialGenerator((double)1/_L);
            serviceTime = packetLength/_C;
            
            if (_Na-_Nd == 0)
            {
                td = event.time + serviceTime;
            }
            else
            {
                td += serviceTime;
            }
            
            departure.time = td;
            departure.type = d;
            
            InsertPacket(it, departure);
            _Na += 1;
        }
        else if(event.type == d)
        {
            _Nd += 1;
        }
        else if(event.type == o)
        {
            _No += 1;
            _Np = _Np * (_No - _Nd);
            
            if (_Na-_Nd == 0)
            {
                _Ni += 1;
            }
        }
        
        _DES.pop_front();
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
            it++;
            InsertPacket(it, packetToInsert);
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

