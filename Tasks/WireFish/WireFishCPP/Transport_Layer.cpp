#include "Transport_Layer.h"
/*******************************TCP Class Functions***********************************************/
struct tcphdr* TCP::get_tcphdr(){

    return tcp_hdr;
}
void TCP::set_tcphdr(struct tcphdr *tcp_header){
    tcp_hdr = tcp_header;
 
}

TCP::TCP(const char *pckt) : IP_Packet(pckt){
	
	int iphdr_len = get_iPhdr_len();
	tcp_hdr = (struct tcphdr *)(pckt + SIZE_ETHERNET + iphdr_len);
	int tcphdr_len = get_tcphdr_len();
	offset = SIZE_ETHERNET + iphdr_len + tcphdr_len;
}


int TCP::get_tcphdr_len(){
	return tcp_hdr->doff * 4;
}

int TCP::get_offset(){
	return offset;
}
void TCP::digest_protocol(){

	printf("TCP Header:\n");
	printf("   |-Source Port     : %d\n", ntohs(tcp_hdr->th_sport));
	printf("   |-Destination Port: %d\n", ntohs(tcp_hdr->th_dport));
	printf("   |-Sequence Number : %u\n", ntohl(tcp_hdr->th_seq));
	printf("   |-Acknowledgment  : %u\n", ntohl(tcp_hdr->th_ack));



}
/*******************************UDP Class Functions***********************************************/
struct udphdr* UDP::get_udphdr(){
    return udp_hdr;
}

void UDP::set_udphdr(struct udphdr *udp_header){

    udp_hdr = udp_header;
}

UDP::UDP(const char *pckt) : IP_Packet(pckt){
	
	int iphdr_len = get_iPhdr_len();
	int udphdr_len = get_udphdr_len();
	
	udp_hdr = (struct udphdr *)(pckt + SIZE_ETHERNET + iphdr_len);
	offset = SIZE_ETHERNET + iphdr_len + udphdr_len;
	
}


int UDP::get_udphdr_len(){
	return UDP_HEADER;
}

int UDP::get_offset(){
	return offset;
}
void UDP::digest_protocol(){

	printf("UDP Header:\n");
	printf("   |-Source Port     : %d\n", ntohs(udp_hdr->uh_sport));
	printf("   |-Destination Port: %d\n", ntohs(udp_hdr->uh_dport));
	printf("   |-Length          : %d\n", ntohs(udp_hdr->uh_ulen));
}


/*******************************ICMP Class Functions***********************************************/
struct icmphdr *ICMP::get_icmphdr(){
    return icmp_hdr;
}
void ICMP::set_icmphdr(struct icmphdr *icmp_header){
    icmp_hdr = icmp_header;
}

ICMP::ICMP(const char *pckt) : IP_Packet(pckt){
	int iphdr_len = get_iPhdr_len();
	icmp_hdr = (struct icmphdr *)(pckt + SIZE_ETHERNET + iphdr_len);

}

void ICMP::digest_protocol(){

	// Print basic ICMP information
	printf("ICMP Packet :\n");
	printf("	|-ICMP Type: %d\n", icmp_hdr->type);
	printf("	|-ICMP Code: %d\n", icmp_hdr->code);
	printf("	|-ICMP Checksum: 0x%04x\n",
	       ntohs(icmp_hdr->checksum));

	// Handle specific types of ICMP messages
	switch (icmp_hdr->type) {
	case ICMP_ECHO:
		printf("	Type: Echo Request\n");
		break;
	case ICMP_ECHOREPLY:
		printf("	Type: Echo Reply \n");
		break;
	case ICMP_DEST_UNREACH:
		printf("	(Destination Unreachable)\n");
		break;
		break;
	case ICMP_TIME_EXCEEDED:
		printf("	Type: Time Exceeded\n");
		break;
	case ICMP_PARAMPROB:
		printf("	Type: Parameter Problem\n");
		break;
	default:
		printf("	Type: Unknown ICMP Type\n");
		break;
	}

}


