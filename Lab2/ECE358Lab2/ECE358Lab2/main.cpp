//
//  main.cpp
//  ECE358Lab2
//
//  Created by YeounJun Park on 2015. 3. 2..
//  Copyright (c) 2015년 YeounJun Park. All rights reserved.
//

#include <iostream>
#include "ABP.h"
#include "NACK.h"
#include "GBN.h"

int main(int argc, const char * argv[])
{
	ABP *lab;
	NACK *nack;
	GBN *gbn;
    int h_len, p_len, chan_cap, n;
	double BER, delta, tao;
	
	tao = 0.005;
	delta = tao * 2.5;
	chan_cap = 5000000;
    h_len = 54;
    p_len = 1500;
	BER = 0.00000;
	n = 4;
    
    //lab = new ABP(delta, chan_cap, p_len, h_len, BER, tao);
	//nack = new NACK(delta, chan_cap, p_len, h_len, BER, tao);
	//lab->Send();
	//lab->ES_Processor();
	
	//std::cout << lab->Time << std::endl;
	//std::cout << p_len*8*10000 << std::endl;
	//std::cout << (double)p_len*8*10000/lab->Time << std::endl;
	
	gbn = new GBN(delta, chan_cap, p_len, h_len, BER, tao, n);
	gbn->Sender();
	
	std::cout << gbn->Time << std::endl;
	std::cout << p_len*8*10000 << std::endl;
	std::cout << (double)p_len*8*10000/gbn->Time << std::endl;
	
	delete gbn;
	
    return 0;
}
