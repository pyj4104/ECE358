//
//  ABP.h
//  ECE358Lab2
//
//  Created by YeounJun Park on 2015. 3. 18..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#ifndef __ECE358Lab2__ABP__
#define __ECE358Lab2__ABP__

#include <stdio.h>
#include <queue>

enum EventType {ACK, TIME_OUT};
enum Status {ERROR, ERROR_FREE, LOST};
struct Event
{
    EventType type;
    Status flag;
    double time;
    int RN;
	
	bool operator>(const Event& rhs) const
	{
		return time < rhs.time;
	}
	bool operator<(const Event& rhs) const
	{
		return time > rhs.time;
	}
};

class ABP
{
public:
    ABP(double delta, int chan_cap, int data_len, int header_len, double ber, double tao);
    void Send(), ES_Processor();
	double Time;
protected:
    unsigned _Next_Expected_ACK, _Next_Expecetd_Frame, _Header_Len, _Data_Len, _SN, _Chan_Cap, _Counter;
    double _BER, _Tao, _Delta;
    std::priority_queue<Event> _ES;
    Event _Return_Packet;
	Status _Flag;
    void Chan(int packetLen), Receiver();
};

#endif /* defined(__ECE358Lab2__ABP__) */
