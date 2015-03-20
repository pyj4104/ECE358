//
//  Event.cpp
//  ECE358Lab2
//
//  Created by YeounJun Park on 2015. 3. 2..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#include "Event.h"
#include <queue>

using namespace std;

L2::L2(int delta_time_out, int header_len, int packet_Len, int chan_cap, int tao, double ber)
{
	Event current;
	srand(time(NULL));
	
	_Tc = 0;
	_SN = 0;
	_NumError= 0;
	_NumFramesReceived = 0;
	_NEXT_EXPECTED_FRAME = 0;
	_BER = ber;
	_Tao = tao;
	_LenHeader = header_len;
	_Channel_Capacity = chan_cap;
	_Delta = delta_time_out;
	_LengthOfPacket = header_len + packet_Len;
	_Tc = _Tc + _LengthOfPacket / chan_cap;
	_NEXT_EXPECTED_ACK = (_SN+1)%2;
	current.TypeOfEvent = TIME_OUT;
	current.Time = _Tc;
	
	_ES.push(current);
}

void L2::Send()
{
	Event event;
	
	Chan(_LengthOfPacket);
	event = Receiver();
	if (_Status != LOST)
	{
		Chan(_LenHeader);
		_ES.push(event);
	}
}

void L2::Chan(int len)
{
	double corruptionProb;
	
	for (int i = 0; i < len; i++)
	{
		corruptionProb = rand()/(RAND_MAX+1);
		
		if (corruptionProb < _BER)
		{
			_NumError++;
		}
	}
	
	if (_NumError < 5)
	{
		_Status = LOST;
	}
	else if (_NumError < 5 && _NumError > 0)
	{
		_Status = ERROR;
	}
	else
	{
		_Status = ERROR_FRAME;
	}

	_Tc += _Tao;
}

Event L2::Receiver()
{
	Event event;
	
	if (_Status == ERROR)
	{
		event.TypeOfEvent = ACK;
		event.Time = _Tc;
		event.SeqNum = _NEXT_EXPECTED_FRAME;
		event.Error = _Status;
	}
	else if (_Status == ERROR_FRAME)
	{
		_NEXT_EXPECTED_FRAME = (_NEXT_EXPECTED_FRAME + 1) % 2;
		event.TypeOfEvent = ACK;
		event.Time = _Tc;
		event.SeqNum = _NEXT_EXPECTED_FRAME;
		event.Error = _Status;
		_NumFramesReceived++;
	}
	return event;
}

void L2::ES_Processor()
{
	Event current;
	Event Time_Out;
	
	current = _ES.top();
	
	while (!_ES.empty())
	{
		if (current.TypeOfEvent == ACK && current.Error == ERROR_FRAME && current.SeqNum == _NEXT_EXPECTED_FRAME)
		{
			_SN++;
			_NEXT_EXPECTED_ACK = (_SN + 1) % 2;
			_Tc = _Tc + _LengthOfPacket / _Channel_Capacity;
			Send();
			_Time_out = 0;
			_Time_out = _Tc + _Delta;
		}
		else if (current.TypeOfEvent == ACK && (current.Error == ERROR || _SN != _NEXT_EXPECTED_ACK))
		{
			;
		}
		else if (current.TypeOfEvent == TIME_OUT)
		{
			Send();
			_Time_out = 0;
			_Time_out = _Tc + _Delta;
		}
	}
}
