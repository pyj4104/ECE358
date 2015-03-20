//
//  Event.h
//  ECE358Lab2
//
//  Created by YeounJun Park on 2015. 3. 2..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#ifndef __ECE358Lab2__Event__
#define __ECE358Lab2__Event__

#include <stdio.h>
#include <queue>
#include <iostream>

enum EventType {ACK, TIME_OUT};
enum PacketStatus {ERROR, ERROR_FRAME, LOST};

struct Event
{
    EventType TypeOfEvent;
	double Time;
	PacketStatus Error;
	int SeqNum;
	
    bool operator<(const Event& rhs) const
    {
        return Time > rhs.Time;
    }
    bool operator>(const Event& rhs) const
    {
        return Time < rhs.Time;
    }
};

class L2
{
    public:
        L2 (int delta_time_out, int header_len, int packet_Len, int chan_cap, int tao, double ber);
		void Send();
		void ES_Processor();
        ~L2();
    private:
		int _SN, _NEXT_EXPECTED_ACK, _NEXT_EXPECTED_FRAME, _Time_out, _Tc, _LengthOfPacket, _Channel_Capacity, _NumError, _NumFramesReceived, _Tao, _LenHeader, _Delta;
		double _BER;
		PacketStatus _Status;
		std::priority_queue<Event> _ES;
		void Chan(int len);
		Event Receiver();
};

#endif /* defined(__ECE358Lab2__Event__) */
