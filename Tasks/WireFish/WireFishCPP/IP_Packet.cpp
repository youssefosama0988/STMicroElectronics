#include "IP_Packet.h"

IP_Packet::IP_Packet()
{
    printf("default constructor shouldn't be invoked\n");
}
IP_Packet::IP_Packet(const char *pckt)
{
    set_packet(pckt);
    set_iphdr((struct ip*)(pckt + 14));
}

IP_Packet::~IP_Packet()
{
    //dtor
}

struct ip* IP_Packet::get_iphdr(){
    return ip_hdr;
}
void IP_Packet::set_iphdr(struct ip* iphdr){
    ip_hdr = iphdr;
}
const char *IP_Packet::get_packet(){

    return packet;

}
void IP_Packet::set_packet(const char *pckt){

    packet = pckt;
}

void digest_ip(){





}

