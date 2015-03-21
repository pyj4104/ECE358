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
    _Next_Expecetd_Frame = 0;
    
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
	bool fire;
	
	done = 1;
	fire = false;
	
	//Prepare
	Time += (double) (_Header_Len + _Data_Len) / _Chan_Cap;
	if (_ES.empty())
	{
		to.type = TIME_OUT;
		to.time = _Buffer[0].Time + _Delta;
		
		_ES.push(to);
	}
	_Buffer[0].Time = Time;
	for (int i = 1; i < _N; i++)
	{
		_Buffer[i].Time = _Buffer[i-1].Time+(double)(_Data_Len + _Header_Len) / (_Chan_Cap);
		Send();
	}
	
	while (done < 10000)
	{
		while (done < 10000)
		{
			std::cout << done << std::endl;
			//Process
			top = _ES.top();
			std::cout << top.RN << " " << top.time << std::endl;
			std::cout << _Buffer[0].SN << " " << _Buffer[0].Time << std::endl << std::endl;
			//_ES.pop();
			if (top.type == TIME_OUT)
			{
				Time = top.time;
				while (!_ES.empty())
				{
					_ES.pop();
				}
				_Buffer[0].Time = Time;
				for (int i = 1; i < _N; i++)
				{
					_Buffer[i].Time = _Buffer[i-1].Time+(double)(_Data_Len + _Header_Len) / (_Chan_Cap);
					Send();
				}
				break;
			}
			else if (top.type == ACK && top.flag == ERROR_FREE)
			{
				for (int i = 0; i < _N; i++)
				{
					if (top.RN == _Buffer[i].SN)
					{
						fire = true;
					}
				}
				if (done >= 10000)
				{
					break;
				}
				if (fire)
				{
					if (_Buffer[_N-1].Time > top.time)
					{
						Time = _Buffer[_N-1].Time;
					}
					else
					{
						Time = top.time;
					}
					for (int i = 0; i < _N; i++)
					{
						if (top.RN == _Buffer[i].SN)
						{
							p = _Buffer[0].SN;
							ShiftLeft(i);
							while (!_ES.empty())
							{
								_ES.pop();
							}
							done += i;
							for(int j = 0; j < i; j++)
							{
								Send();
							}
							break;
						}
					}
				}
				fire = false;
			}else{
				Time = top.time;
			}
			buf_counter++;
		}
	
}

void GBN::Receiver(Status flag)
{
    if (flag != LOST)
    {
        if (flag == ERROR_FREE && _Buffer[0].SN == _Next_Expecetd_Frame)
        {
			_Next_Expecetd_Frame = (_Next_Expecetd_Frame + 1) % (_N + 1);
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
	bool last = false;
	if(_Buffer[_N-1].Time < Time){
		last = true;
	}
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
		if(last){
			last = false;
			_Buffer[i].Time = Time + (double)(_Header_Len + _Data_Len)/_Chan_Cap;
		}else{
			_Buffer[i].Time = _Buffer[i-1].Time + (double)(_Header_Len + _Data_Len)/_Chan_Cap;
		}
		
	}
}

GBN::~GBN()
{
    //delete[] _Buffer;
    //delete[] _Next_Expected_ACK;
}
