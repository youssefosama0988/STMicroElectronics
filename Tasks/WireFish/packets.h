#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

#define SIZE_ETHERNET 14
#define ETHER_ADDR_LEN	6


/* Ethernet header */
struct sniff_ethernet {
        u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */
        u_char  ether_shost[ETHER_ADDR_LEN];    /* source host address */
        u_short ether_type;                     /* IP? ARP? RARP? etc */
};


typedef struct IP_Packet{

	struct sniff_ethernet *eth_hdr;
	struct ip *ip_hdr;
	void (*digest_ip) (struct IP_Packet *ip_packet);		//fixed implementation to all packets to print ip-header
	void (*Digest_Protocol) (struct IP_Packet *ip_packet);       	//implemented by each packet to show each protocol-header
	void (*print_applicationPort)(int port);
}IP_Packet_t;


typedef struct{
	IP_Packet_t *ip_packet;			//inheritance
	struct tcphdr *tcp_hdr;	

}TCP_t;

typedef struct{
	IP_Packet_t *ip_packet;			//inheritance
	struct udphdr *udp_hdr;	

}UDP_t;

typedef struct{
	IP_Packet_t *ip_packet;			//inheritance
	struct icmphdr *icmp_hdr;	

}ICMP_t;

void Digest_IP(IP_Packet_t *layer);
void digest_tcp(IP_Packet_t *layer);
void digest_udp(IP_Packet_t *layer);
void digest_ICMP(IP_Packet_t *layer);

IP_Packet_t *Construct_IP_packet(const u_char *packet);
void deconstruct_IP_packet(IP_Packet_t *ip_packet);

TCP_t *Construct_TCP_packet(const u_char *packet);
void deconstruct_TCP_packet(TCP_t *tcp);

UDP_t *Construct_UDP_packet(const u_char *packet);
void deconstruct_UDP_packet(UDP_t *udp);










