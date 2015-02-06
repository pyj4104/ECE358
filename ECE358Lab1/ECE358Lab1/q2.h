//
//  q2.h
//  ECE358Lab1
//
//  Created by YeounJun Park on 2015. 1. 28..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <math.h>

#ifndef ECE358Lab1_q2_h
#define ECE358Lab1_q2_h

using namespace std;

enum EventType {a, d, o};

struct event
{
    EventType TypeOfPacket;
    double GenerationTime;
	bool operator<(const event& rhs) const
	{
		return GenerationTime > rhs.GenerationTime;
	}
	bool operator>(const event& rhs) const
	{
		return GenerationTime < rhs.GenerationTime;
	}
};

class q2
{
public:
	q2 (int numberOfPackets);
	q2 (int numberOfPackets, double row);
	void GenerateArrivalPackects(), GenerateObserverPackets(), GenerateDeparturePackets(), SortDES();
    long Np(), No(), Ni();
    ~q2();
private:
    double ExponentialRandomGenerator(double x);
    long _Na, _No, _Nd, _Ni, _Np, _L, _C, _Time;
	double _Row, _Lambda;
	priority_queue<event> _DES;
};

q2::q2(int timeElapsed)
{
    _Na = 0;
    _Nd = 0;
    _No = 0;
    _Ni = 0;
    _Np = 0;
    _L = 12000;
    _C = 1000000;
    _Row = 0.25;
    _Lambda = _Row * (double)_C / (double)_L;
    _Time = timeElapsed;
	srand(time(NULL));
}

q2::q2(int timeElapsed, double row)
{
	_Na = 0;
	_Nd = 0;
	_No = 0;
	_Ni = 0;
	_Np = 0;
	_L = 12000;
	_C = 1000000;
	_Row = row;
	_Lambda = _Row * (double)_C / (double)_L;
	_Time = timeElapsed;
	srand(time(NULL));
}

void q2::GenerateArrivalPackects()
{
	cout << "Beginning of Generation of Arrival Packets" << endl;
	
	event arrival;
	double ta = 0.0;
	
	
	while (ta < _Time)
	{
		ta += ExponentialRandomGenerator(_Lambda);
		
		arrival.TypeOfPacket = a;
		arrival.GenerationTime = ta;
		
		_DES.push(arrival);
	}
}

void q2::GenerateObserverPackets()
{
	cout << "Beginning of Observer Packets" << endl;
	
	event observer;
	double alpha, to;
	
	alpha = 3*_Lambda;
	to = 0.0;
	
	while (to < _Time)
	{
		to += ExponentialRandomGenerator(alpha);
		
		observer.TypeOfPacket = o;
		observer.GenerationTime = to;
		
		_DES.push(observer);
	}
}

void q2::SortDES()
{
	cout << "Beginnig of SortDES" << endl;
	
	event departure;
	double packetLength, serviceTime, td;
	
	td = 0.0;
	
	while (!_DES.empty())
	{
		if (_DES.top().TypeOfPacket == a)
		{
			packetLength = ExponentialRandomGenerator(1.0/_L);
			serviceTime = packetLength/(double)_C;
			
			if (_Na - _Nd == 0)
			{
				td = _DES.top().GenerationTime + serviceTime;
			}
			else
			{
				td += serviceTime;
			}
			
			departure.TypeOfPacket = d;
			departure.GenerationTime = td;
			
			_DES.push(departure);
			
			_Na++;
		}
		else if (_DES.top().TypeOfPacket == d)
		{
			_Nd++;
		}
		else if (_DES.top().TypeOfPacket == o)
		{
			_No++;
			_Np += _Na - _Nd;
			
			if (_Na - _Nd == 0)
			{
				_Ni++;
			}
		}
		
		_DES.pop();
	}
}

double q2::ExponentialRandomGenerator(double x)
{
	double value, number;
	
	number = rand()/double(RAND_MAX);
	value = -1 * log(1-number) / x;
	
	return value;
}

long q2::Np()
{
	return _Np;
}

long q2::No()
{
	return _No;
}

long q2::Ni()
{
	return _Ni;
}

q2::~q2()
{
    
}

#endif
