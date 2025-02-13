#include "Network_Layer.h"

IP_Packet::IP_Packet()
{
    printf("default constructor shouldn't be invoked\n");
}


IP_Packet::IP_Packet(const char *pckt)
{
    set_packet(pckt);
    set_iphdr((struct ip*)(pckt + SIZE_ETHERNET));
}


IP_Packet::~IP_Packet()
{
   
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


int IP_Packet::get_iPhdr_len(){
	return (ip_hdr->ip_hl) * 4;
}


void IP_Packet::digest_ip(){
	
	struct ip *ip_header = get_iphdr();

	printf("IP Header:\n");
	printf("   |-Version        : %d\n", ip_header->ip_v);
	printf("   |-Header Length  : %d\n", ip_header->ip_hl * 4);
	printf("   |-Total Length   : %d\n", ntohs(ip_header->ip_len));
	printf("   |-Protocol       : %d\n", ip_header->ip_p);
	printf("   |-Source Address : %s\n", inet_ntoa(ip_header->ip_src));
	printf("   |-Destination Address : %s\n", inet_ntoa(ip_header->ip_dst));

}



