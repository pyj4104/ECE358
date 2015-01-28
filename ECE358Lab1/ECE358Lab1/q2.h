//
//  q2.h
//  ECE358Lab1
//
//  Created by YeounJun Park on 2015. 1. 28..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <math.h>

#ifndef ECE358Lab1_q2_h
#define ECE358Lab1_q2_h

enum PacketType : char{a = 'a', d = 'd', o = 'o'};

struct packet
{
    PacketType TypeOfPacket;
    double GenerationTime;
};

class q2
{
public:
    q2 (int numberOfPackets);
    void GenerateArrivalPackects(), GenerateObserverPackets(), SortDES();
    int Np(), No(), Ni();
    ~q2();
private:
    void InsertPacket(std::list<packet>::iterator it, packet packetToInsert);
    double ExponentialRandomGenerator(double x);
    int _Na, _No, _Nd, _Ni, _Np, _L, _C, _Lambda, _Time;
	std::list<packet> _DES;
};

q2::q2(int timeElapsed)
{
    _Na = 0;
    _Nd = 0;
    _No = 0;
    _Ni = 0;
    _Np = 0;
    _Lambda = 75;
    _L = 12000;
    _C = 1000000;
	_Time = timeElapsed;
}

void q2::GenerateArrivalPackects()
{
	printf("Beginning of Generation of Arrival Packets\n");
	
	packet arrival;
	double ta;
	
	ta = 0;
	
	while (ta < _Time)
	{
		ta = ta + ExponentialRandomGenerator(_Lambda);
		
		arrival.TypeOfPacket = a;
		arrival.GenerationTime = ta;
		
		_DES.push_back(arrival);
	}
}

void q2::GenerateObserverPackets()
{
	printf("Beginning of Observer Packets\n");
	
	std::list<packet>::iterator it;
	packet observer;
	double alpha, to;
	
	alpha = 3*_Lambda;
	it = _DES.begin();
	to = 0;
	
	while (to < _Time)
	{
		to = to + ExponentialRandomGenerator(alpha);
		
		observer.TypeOfPacket = o;
		observer.GenerationTime = to;
		
		InsertPacket(it, observer);
	}
}

void q2::SortDES()
{
	printf("Beginnig of SortDES\n");
	
	std::list<packet>::iterator it;
	packet departure;
	double packetLength, serviceTime, td;
	
	it = _DES.begin();
	td = 0;
	
	while (!_DES.empty())
	{
		if (_DES.begin()->TypeOfPacket == a)
		{
			packetLength = ExponentialRandomGenerator((double)1/_L);
			serviceTime = packetLength/(double)_C;
			
			if (_Na - _Nd == 0)
			{
				td = _DES.begin()->GenerationTime + serviceTime;
			}
			else
			{
				td = td + serviceTime;
			}
			
			departure.TypeOfPacket = d;
			departure.GenerationTime = td;
			
			InsertPacket(it, departure);
			
			_Na = _Na + 1;
		}
		else if (_DES.begin()->TypeOfPacket == d)
		{
			_Nd = _Nd + 1;
		}
		else if (_DES.begin()->TypeOfPacket == o)
		{
			_No = _No + 1;
			_Np = _Np * (_No - _Nd);
			
			if (_Na - _Nd == 0)
			{
				_Ni = _Ni + 1;
			}
		}
		
		it++;
		_DES.pop_front();
		printf("Np: %d\tNo: %d\tNi: %d\nNa: %d\tNd: %d\n", _Np, _No, _Ni, _Na, _Nd);
	}
}

void q2::InsertPacket(std::list<packet>::iterator it, packet packetToInsert)
{
	if (it->GenerationTime > _DES.end()->GenerationTime)
	{
		if (it->GenerationTime > packetToInsert.GenerationTime)
		{
			_DES.insert(it, packetToInsert);
		}
		else
		{
			it = std::next(it);
			InsertPacket(it, packetToInsert);
		}
	}
	else
	{
		_DES.push_back(packetToInsert);
	}
}

double q2::ExponentialRandomGenerator(double x)
{
	double value, number;
	
	srand(time(0));
	number = rand()/double(RAND_MAX);
	value = -1 * log(1-number) / x;
	
	return value;
}

int q2::Np()
{
	return _Np;
}

int q2::No()
{
	return _No;
}

int q2::Ni()
{
	return _Ni;
}

q2::~q2()
{
    
}

#endif
