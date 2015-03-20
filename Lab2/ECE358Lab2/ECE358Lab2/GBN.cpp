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
    std::cout << "start" << std::endl;
    
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
    //_Next_Expected_ACK = new int[_N];
    
    for (int i = 0; i < _N; i++)
    {
		_Buffer[i].SN = i;
        _Next_Expected_ACK[i] = NULL;
    }
    
    std::srand(time(NULL));
}

void GBN::Sender()
{
    std::cout << "sender" << std::endl;
    Event to, top;
    int p, packets_Transfered, buf_counter;
	
	buf_counter = 0;
    
	while (true)
	{
		while (buf_counter < _N)
		{
			//Prepare
			Time += (double)(_Data_Len + _Header_Len) / (_Chan_Cap);
			_Buffer[buf_counter].Time = Time;
			_Next_Expected_ACK[buf_counter] = (_Buffer[buf_counter].SN+1)%(_N);
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
			
			int x = 1;
		}
	}
}

void GBN::Receiver(Status flag)
{
    if (flag != LOST)
    {
        if (flag == ERROR_FREE)
        {
            _Next_Expecetd_Frame = (_Next_Expecetd_Frame) % (_N);
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
        Chan(_Header_Len);
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
    for (int i = 0; i < (_N - 1); i++)
    {
        _Buffer[i] = _Buffer[i+by] ;
    }
}

GBN::~GBN()
{
    //delete[] _Buffer;
    //delete[] _Next_Expected_ACK;
}
