#include "Transport_Layer.h"

struct tcphdr* TCP::get_tcphdr(){

    return tcp_hdr;
}
void TCP::set_tcphdr(struct tcphdr *tcp_header){
    tcp_hdr = tcp_header;
}
TCP::TCP(const char *pckt) : IP_Packet(pckt){

}

struct udphdr* UDP::get_udphdr(){
    return udp_hdr;
}
void UDP::set_udphdr(struct udphdr *udp_header){

    udp_hdr = udp_header;
}


struct icmphdr *get_icmphdr(){
    return icmp_hdr;
}
void set_icmphdr(struct icmphdr *icmp_header){
    icmp_hdr = icmp_header;
}

