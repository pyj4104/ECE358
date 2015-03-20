//
//  GBN.h
//  ECE358Lab2
//
//  Created by YeounJun Park on 2015. 3. 19..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#ifndef __ECE358Lab2__GBN__
#define __ECE358Lab2__GBN__

#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <queue>
#include <time.h>
#include <iostream>
#include "ABP.h"

struct Buffer
{
    int SN;
    double Time;
};

class GBN
{
public:
    GBN(double delta, int chan_cap, int data_len, int header_len, double ber, double tao, int n);
    void Sender();
    ~GBN();
    double Time;
private:
    int _N, _Header_Len, _Data_Len, _Chan_Cap, _Next_Expecetd_Frame;
    int _Next_Expected_ACK[4];
    double _BER, _Tao, _Delta;
    std::priority_queue<Event> _ES;
    Buffer _Buffer[4];
    void ShiftLeft(int by), Send(), Receiver(Status flag);
    Status Chan(int packetLen);
};

#endif /* defined(__ECE358Lab2__GBN__) */
