//
//  NACK.h
//  ECE358Lab2
//
//  Created by YeounJun Park on 2015. 3. 19..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#ifndef __ECE358Lab2__NACK__
#define __ECE358Lab2__NACK__

#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <queue>
#include <time.h>
#include <iostream>
#include "ABP.h"

class NACK:public ABP
{
public:
    NACK(double delta, int chan_cap, int data_len, int header_len, double ber, double tao);
    void ES_Processor();
};

#endif /* defined(__ECE358Lab2__NACK__) */
