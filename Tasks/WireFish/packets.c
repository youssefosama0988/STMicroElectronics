
#include "packets.h"


void Digest_IP(IP_Packet_t *layer){
    
    struct ip *ip_header = layer->ip_hdr;

    printf("IP Header:\n");
    printf("   |-Version        : %d\n", ip_header->ip_v);
    printf("   |-Header Length  : %d\n", ip_header->ip_hl * 4);
    printf("   |-Total Length   : %d\n", ntohs(ip_header->ip_len));
    printf("   |-Protocol       : %d\n", ip_header->ip_p);
    printf("   |-Source Address : %s\n", inet_ntoa(ip_header->ip_src));
    printf("   |-Destination Address : %s\n", inet_ntoa(ip_header->ip_dst));
}


// Function to print TCP header fields
void digest_tcp(IP_Packet_t *layer){

    struct sniff_tcp *tcp_header = ((TCP_t *)layer)->tcp_hdr;
    printf("TCP Header:\n");
    printf("   |-Source Port     : %d\n", ntohs(tcp_header->th_sport));
    printf("   |-Destination Port: %d\n", ntohs(tcp_header->th_dport));
    printf("   |-Sequence Number : %u\n", ntohl(tcp_header->th_seq));
    printf("   |-Acknowledgment  : %u\n", ntohl(tcp_header->th_ack));
}


// Function to print UDP header fields
void digest_udp(IP_Packet_t *layer) {
    struct udphdr *udp_header = ((UDP_t *)layer)->udp_hdr;
    printf("UDP Header:\n");
    printf("   |-Source Port     : %d\n", ntohs(udp_header->uh_sport));
    printf("   |-Destination Port: %d\n", ntohs(udp_header->uh_dport));
    printf("   |-Length          : %d\n", ntohs(udp_header->uh_ulen));
}



/***************************************************************************************************************************/
IP_Packet_t *Construct_IP_packet(const u_char *packet){
	
	IP_Packet_t *ip_packet = (IP_Packet_t *)malloc(sizeof(IP_Packet_t));
	if(!ip_packet){
		perror("malloc\n");
		exit(-1);
	}
	
	ip_packet->eth_hdr = (struct sniff_ethernet *) packet;
	ip_packet->ip_hdr = (struct ip *)(packet + 14);
	ip_packet->digest_ip = Digest_IP;					//polymorphism
	
	return ip_packet;
}

void deconstruct_IP_packet(IP_Packet_t *ip_packet){

	free(ip_packet);
}

/***************************************************************************************************************************/

TCP_t *Construct_TCP_packet(const u_char *packet){

	TCP_t *tcp_packet = (TCP_t *)malloc(sizeof(TCP_t));
	if(!tcp_packet){
		perror("malloc\n");
		exit(-1);
	}
	tcp_packet->ip_packet = (IP_Packet_t *)packet;  
	tcp_packet->tcp_hdr = (struct sniff_tcp *)(packet + 14 + (tcp_packet->ip_packet->ip_hdr->ip_hl * 4));
	tcp_packet->ip_packet->Digest_Protocol = digest_tcp;			//polymorphism
	
	return tcp_packet;
}


void deconstruct_TCP_packet(TCP_t *tcp){

	free(tcp);

}
/***************************************************************************************************************************/
UDP_t *Construct_UDP_packet(const u_char *packet){

	UDP_t *udp_packet = (UDP_t *)malloc(sizeof(UDP_t));
	if(!udp_packet){
		perror("malloc\n");
		exit(-1);
	}
	udp_packet->ip_packet = (IP_Packet_t *)packet;
	udp_packet->udp_hdr = (struct udphdr *)(packet + 14 + (udp_packet->ip_packet->ip_hdr->ip_hl * 4));    
	udp_packet->ip_packet->Digest_Protocol = digest_udp;                       //polymorphism
	
	return udp_packet;

}

void deconstruct_UDP_packet(TCP_t *udp){

	free(udp);

}
