//
//  ABP.cpp
//  ECE358Lab2
//
//  Created by YeounJun Park on 2015. 3. 18..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <time.h>
#include <iostream>
#include "ABP.h"

ABP::ABP(double delta, int chan_cap, int data_len, int header_len, double ber, double tao)
{
    Event init;
    
    _Delta = delta * tao;
    _Chan_Cap = chan_cap;
    _Data_Len = data_len * 8;
    _Header_Len = header_len * 8;
    _BER = ber;
	_Counter = 1;
	_Tao = tao;
	
    Time = 0;
    Time = Time + (_Data_Len + _Header_Len) / (double)_Chan_Cap;
    _SN = 0;
    _Next_Expected_ACK = (_SN + 1) % 2;
    _Next_Expecetd_Frame = 0;
    
    init.type = TIME_OUT;
    init.time = Time + _Delta;
    
    _ES.push(init);
    
    srand(time(NULL));
}

void ABP::Send()
{
    Chan(_Data_Len + _Header_Len);
    Receiver();
	if (_Flag != LOST)
	{
		Chan(_Header_Len);
	}
	if (_Flag != LOST)
	{
		_Return_Packet.type = ACK;
		_Return_Packet.flag = _Flag;
		_Return_Packet.time = Time;
		
		_ES.push(_Return_Packet);
	}
}

void ABP::Chan(int packetLen)
{
	int _Num_Error;
    double prob;
	
	_Num_Error = 0;
	
    for (unsigned i = 0; i < packetLen; i++)
    {
        prob = (double)rand()/(RAND_MAX);
		
        if (prob < _BER)
        {
            _Num_Error++;
        }
    }
	
    if (_Num_Error > 5)
    {
        _Flag = LOST;
    }
    else if (_Num_Error <= 5 && _Num_Error > 0)
    {
        _Flag = ERROR;
    }
    else
    {
        _Flag = ERROR_FREE;
    }
    
    Time = Time + _Tao;
}

void ABP::Receiver()
{
    if (_Flag != LOST)
    {
		_Return_Packet.type = ACK;
		
        if (_Flag == ERROR)
        {
            _Return_Packet.RN = _Next_Expecetd_Frame;
        }
        else
        {
			_Next_Expecetd_Frame = (_Next_Expecetd_Frame + 1) % 2;
			_Return_Packet.RN = _Next_Expecetd_Frame;
		}
		Time = Time + (_Header_Len / (double) _Chan_Cap);
    }
}

void ABP::ES_Processor()
{
	Event event;
	Event init;
	
	while (!_ES.empty())
	{
		event = _ES.top();
		_ES.pop();
		
		if (event.type == TIME_OUT)
		{
			while (!_ES.empty())
			{
				_ES.pop();
			}
			Time = event.time;
			Time = Time + (_Header_Len + _Data_Len) / (double)_Chan_Cap;
			init.type = TIME_OUT;
			init.time = Time + _Delta;
			_ES.push(init);
			Send();
		}
		else
		{
			if (event.flag == ERROR_FREE && event.RN == _Next_Expected_ACK)
			{
				if (_Counter == 10000)
				{
					break;
				}
				else
				{
					_Counter++;
				}
				_SN = (_SN + 1) % 2;
				_Next_Expected_ACK = (_SN + 1) % 2;
				while (!_ES.empty())
				{
					_ES.pop();
				}
				Time = Time + (_Header_Len + _Data_Len) / (double)_Chan_Cap;
				init.type = TIME_OUT;
				init.time = Time + _Delta;
				_ES.push(init);
				Send();
			}
		}
	}
}
