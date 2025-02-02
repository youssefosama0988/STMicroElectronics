
#include "packets.h"


void Digest_IP(IP_Packet_t *ip_packet){
    
    struct ip *ip_header = ip_packet->ip_hdr;

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

    struct tcphdr *tcp_header = ((TCP_t *)layer)->tcp_hdr;
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


void digest_icmp(IP_Packet_t *layer){
	
	struct icmphdr *icmp_header = ((ICMP_t *)layer)->icmp_hdr;

    // Print basic ICMP information
    printf("ICMP Packet :\n");
    printf("	|-ICMP Type: %d\n", icmp_header->type);
    printf("	|-ICMP Code: %d\n", icmp_header->code);
    printf("	|-ICMP Checksum: 0x%04x\n", ntohs(icmp_header->checksum));

    // Handle specific types of ICMP messages
    switch (icmp_header->type){
        case ICMP_ECHO:
            printf("	Type: Echo Request\n");
            break;
        case ICMP_ECHOREPLY:
            printf("	Type: Echo Reply \n");
            break;
        case ICMP_DEST_UNREACH:
             printf("	(Destination Unreachable)\n"); break;
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
void print_applicationPort(int port){
  
        if (port == 80) {
            // HTTP (Port 80)
            printf("		HTTP Application Layer Data:\n");
        }
        // Check for HTTPS (Port 443)
        else if (port == 443) {
            // HTTPS (Port 443) - Encrypted, cannot display actual data
            printf("		HTTPS Traffic (Encrypted, not printable)\n");
        }
        // Check for SSH (Port 22)
        else if (port == 22) {
            // SSH (Port 22) - Encrypted, cannot display actual data
            printf("		SSH Traffic (Encrypted, not printable)\n");
        }
        else {
            printf("	No supported application layer protocol found for port %d.\n", port);
        }

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
	ip_packet->print_applicationPort = print_applicationPort;
	
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
	tcp_packet->ip_packet = Construct_IP_packet(packet);  
	tcp_packet->tcp_hdr = (struct tcphdr *)(packet + 14 + (tcp_packet->ip_packet->ip_hdr->ip_hl * 4));
	tcp_packet->ip_packet->Digest_Protocol = digest_tcp;			//polymorphism
	
	return tcp_packet;
}


void deconstruct_TCP_packet(TCP_t *tcp){
	deconstruct_IP_packet(tcp->ip_packet);
	free(tcp);

}
/***************************************************************************************************************************/

UDP_t *Construct_UDP_packet(const u_char *packet){

	UDP_t *udp_packet = (UDP_t *)malloc(sizeof(UDP_t));
	if(!udp_packet){
		perror("malloc\n");
		exit(-1);
	}
	udp_packet->ip_packet = Construct_IP_packet(packet);  
	udp_packet->udp_hdr = (struct udphdr *)(packet + 14 + (udp_packet->ip_packet->ip_hdr->ip_hl * 4));
	udp_packet->ip_packet->Digest_Protocol = digest_udp;			//polymorphism
	
	return udp_packet;
}


void deconstruct_UDP_packet(UDP_t *udp){
	deconstruct_IP_packet(udp->ip_packet);
	free(udp);

}


/***************************************************************************************************************************/

ICMP_t *Construct_ICMP_packet(const u_char *packet){

	ICMP_t *icmp_packet = (ICMP_t *)malloc(sizeof(ICMP_t));
	if(!icmp_packet){
		perror("malloc\n");
		exit(-1);
	}
	icmp_packet->ip_packet = Construct_IP_packet(packet);  
	icmp_packet->icmp_hdr = (struct icmphdr *)(packet + 14 + (icmp_packet->ip_packet->ip_hdr->ip_hl * 4));
	icmp_packet->ip_packet->Digest_Protocol = digest_icmp;			//polymorphism
	
	return icmp_packet;
}


void deconstruct_ICMP_packet(ICMP_t *icmp){
	deconstruct_IP_packet(icmp->ip_packet);
	free(icmp);

}
