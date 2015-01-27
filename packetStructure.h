//
//  packetStructure.h
//  
//
//  Created by YeounJun Park on 2015-01-26.
//
//

#ifndef _packetStructure_h
#define _packetStructure_h
enum PacketType {a, d, o};

struct packet
{
    PacketType type;
    double time;
};
#endif
