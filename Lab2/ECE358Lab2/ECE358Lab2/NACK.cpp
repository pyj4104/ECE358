//
//  NACK.cpp
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
#include "NACK.h"

NACK::NACK(double delta, int chan_cap, int data_len, int header_len, double ber, double tao) : ABP(delta, chan_cap, data_len, header_len, ber, tao)
{
    Event init;
    
    _Delta = delta;
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
};

void NACK::ES_Processor()
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
            else
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
        }
    }
}
