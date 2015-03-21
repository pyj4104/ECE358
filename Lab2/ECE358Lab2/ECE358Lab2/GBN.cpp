//
//  GBN.cpp
//  ECE358Lab2
//
//  Created by YeounJun Park on 2015. 3. 19..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <time.h>
#include <iostream>
#include "GBN.h"
#include "ABP.h"

GBN::GBN(double delta, int chan_cap, int data_len, int header_len, double ber, double tao, int n)
{
    _Delta = delta;
    _Chan_Cap = chan_cap;
    _Data_Len = data_len * 8;
    _Header_Len = header_len * 8;
    _BER = ber;
    _Tao = tao;
    _N = n;
    
    Time = 0;
    //_Buffer = new Buffer[_N];
    _Buffer[0].SN = 0;
    _Next_Expecetd_Frame = 1;
    
    for (int i = 0; i < _N; i++)
    {
		_Buffer[i].SN = i;
    }
    
    std::srand(time(NULL));
}

void GBN::Sender()
{
    Event to, top;
    int p, buf_counter, done;
	
	done = 1;
    
	while (true)
	{
		buf_counter = 0;
		while (buf_counter < _N)
		{
			//Prepare
			Time += (double)(_Data_Len + _Header_Len) / (_Chan_Cap);
			_Buffer[buf_counter].Time = Time;
			if (_ES.empty())
			{
				to.type = TIME_OUT;
				to.time = _Buffer[buf_counter].Time + _Delta;
				
				_ES.push(to);
			}
			//Send
			Send();
			//Process
			top = _ES.top();
			_ES.pop();
			if (top.type == TIME_OUT)
			{
				while (!_ES.empty())
				{
					_ES.pop();
				}
				buf_counter = 0;
				break;
			}
			else if (top.type == ACK && top.flag == ERROR_FREE)
			{
				if (done > 10000)
				{
					break;
				}
				for (int i = 0; i < _N; i++)
				{
					if (top.RN == _Buffer[i].SN)
					{
						p = _Buffer[0].SN;
						ShiftLeft(i+1);
						while (!_ES.empty())
						{
							_ES.pop();
						}
						done += i+1;
					}
				}
			}
			buf_counter++;
		}
		if (done > 10000)
		{
			break;
		}
	}
}

void GBN::Receiver(Status flag)
{
    if (flag != LOST)
    {
        if (flag == ERROR_FREE)
        {
			_Next_Expecetd_Frame = (_Next_Expecetd_Frame + 1) % (_N);
        }
        Time = Time + (_Header_Len / (double) _Chan_Cap);
    }
}

void GBN::Send()
{
	Event return_Event;
	Status flag;
	
    flag = Chan(_Data_Len + _Header_Len);
    Receiver(flag);
    if (flag != LOST)
    {
        flag = Chan(_Header_Len);
    }
    if (flag != LOST)
    {
        return_Event.type = ACK;
        return_Event.flag = flag;
        return_Event.time = Time;
		return_Event.RN = _Next_Expecetd_Frame;
        
        _ES.push(return_Event);
    }
}

Status GBN::Chan(int packetLen)
{
	int num_Error;
	double prob;
	Status flag;
	
	num_Error = 0;
	
	for (unsigned i = 0; i < packetLen; i++)
	{
		prob = (double)rand()/(RAND_MAX);
		
		if (prob < _BER)
		{
			num_Error++;
		}
	}
	
	if (num_Error > 5)
	{
		flag = LOST;
	}
	else if (num_Error <= 5 && num_Error > 0)
	{
		flag = ERROR;
	}
	else
	{
		flag = ERROR_FREE;
	}
	
	Time = Time + _Tao;
	
	return flag;
}

void GBN::ShiftLeft(int by)
{
	int lastnum, lasti;
	
    for (int i = 0; i < (_N - by); i++)
    {
		_Buffer[i] = _Buffer[i+by];
		lastnum = _Buffer[i].SN;
		lasti = i;
    }
	for (int i = (lasti + 1); i < _N; i++)
	{
		lastnum = (lastnum + 1) % (_N+1);
		_Buffer[i].SN = lastnum;
	}
}

GBN::~GBN()
{
    //delete[] _Buffer;
    //delete[] _Next_Expected_ACK;
}
