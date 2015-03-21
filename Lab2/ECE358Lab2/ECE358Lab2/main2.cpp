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
	NACK *lab;
    int h_len, p_len, chan_cap, n;
	double BER, delta, tao, BER1, BER2, tao2;
	
	tao = 0.005;
	tao2 = 0.25;
	delta = tao * 2.5;
	chan_cap = 5000000;
    h_len = 54;
    p_len = 1500;
	BER = 0.00000;
	BER1 = 0.00001;
	BER2 = 0.0001;
	n = 4;
	
	std::cout << "delta/tao," << "2*tao = 10 ms,,," << "2*tao = 500 ms,,," << std::endl;
	std::cout << "BER, 0, 0.00001, 0.0001, 0, 0.00001, 0.0001" << std::endl;
	std::cout << "2.5,";
	lab = new NACK(2.5, chan_cap, p_len, h_len, BER, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(2.5, chan_cap, p_len, h_len, BER1, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(2.5, chan_cap, p_len, h_len, BER2, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(2.5, chan_cap, p_len, h_len, BER, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(2.5, chan_cap, p_len, h_len, BER1, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(2.5, chan_cap, p_len, h_len, BER2, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	std::cout << std::endl;
	
	std::cout << "5.0,";
	lab = new NACK(5.0, chan_cap, p_len, h_len, BER, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(5.0, chan_cap, p_len, h_len, BER1, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(5.0, chan_cap, p_len, h_len, BER2, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(5.0, chan_cap, p_len, h_len, BER, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(5.0, chan_cap, p_len, h_len, BER1, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(5.0, chan_cap, p_len, h_len, BER2, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	std::cout << std::endl;
	
	std::cout << "7.5,";
	lab = new NACK(7.5, chan_cap, p_len, h_len, BER, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(7.5, chan_cap, p_len, h_len, BER1, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(7.5, chan_cap, p_len, h_len, BER2, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(7.5, chan_cap, p_len, h_len, BER, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(7.5, chan_cap, p_len, h_len, BER1, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(7.5, chan_cap, p_len, h_len, BER2, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	std::cout << std::endl;
	
	std::cout << "10,";
	lab = new NACK(10, chan_cap, p_len, h_len, BER, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(10, chan_cap, p_len, h_len, BER1, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(10, chan_cap, p_len, h_len, BER2, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(10, chan_cap, p_len, h_len, BER, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(10, chan_cap, p_len, h_len, BER1, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(10, chan_cap, p_len, h_len, BER2, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	std::cout << std::endl;
	
	std::cout << "12.5,";
	lab = new NACK(12.5, chan_cap, p_len, h_len, BER, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(12.5, chan_cap, p_len, h_len, BER1, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(12.5, chan_cap, p_len, h_len, BER2, tao);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(12.5, chan_cap, p_len, h_len, BER, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(12.5, chan_cap, p_len, h_len, BER1, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	lab = new NACK(12.5, chan_cap, p_len, h_len, BER2, tao2);
	lab->Send();
	lab->ES_Processor();
	std::cout << (double)p_len*8*10000/lab->Time << ",";
	delete lab;
	std::cout << std::endl;
	
    return 0;
}
