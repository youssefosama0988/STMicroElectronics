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

#define SIZE_ETHERNET 	14
#define ETHER_ADDR_LEN	6
#define DNS_PORT 	53
#define FTP_PORT        21
#define UDP_HEADER  	8
#define DNS_HEADER   	12

//DNS Header Structure (first 12 bytes)
struct dnshdr
{
  unsigned short id;		// Transaction ID
  unsigned short flags;		// Flags and response codes
  unsigned short qdcount;	// Number of questions
  unsigned short ancount;	// Number of answers
  unsigned short nscount;	// Number of authority records
  unsigned short arcount;	// Number of additional records
};

/* Ethernet header */
struct sniff_ethernet
{
  u_char ether_dhost[ETHER_ADDR_LEN];	/* destination host address */
  u_char ether_shost[ETHER_ADDR_LEN];	/* source host address */
  u_short ether_type;		/* IP? ARP? RARP? etc */
};


typedef struct IP_Packet
{

  struct sniff_ethernet *eth_hdr;
  struct ip *ip_hdr;
  void (*digest_ip) (struct IP_Packet * ip_packet);		//fixed implementation to all packets to print ip-header
  void (*Digest_Protocol) (struct IP_Packet * ip_packet);	//implemented by each packet to show each protocol-header
  void (*digest_applayer)(const u_char * packet);
} IP_Packet_t;

/*********************Trasnport Layer***********************/
typedef struct
{
  IP_Packet_t *ip_packet;	//inheritance
  struct tcphdr *tcp_hdr;

} TCP_t;

typedef struct
{
  IP_Packet_t *ip_packet;	//inheritance
  struct udphdr *udp_hdr;

} UDP_t;

/******************** ICMP *********************************/
typedef struct
{
  IP_Packet_t *ip_packet;	//inheritance
  struct icmphdr *icmp_hdr;

} ICMP_t;

/*********************Application Layer*********************/
typedef struct
{
  TCP_t *tcp_packet;		//inheritance
  
} HTTP_t;

typedef struct
{
  TCP_t *tcp_packet;		//inheritance
  
} FTP_t;

typedef struct
{
  UDP_t *udp_packet;		//inheritance
  
} DNS_t;



/*******************Functions Declaration*****************************/
void Digest_IP (IP_Packet_t * layer);
void digest_tcp (IP_Packet_t * layer);
void digest_udp (IP_Packet_t * layer);
void digest_icmp (IP_Packet_t * layer);

void print_FTP_data (const u_char * packet);

IP_Packet_t *Construct_IP_packet (const u_char * packet);
void deconstruct_IP_packet (IP_Packet_t * ip_packet);


TCP_t *Construct_TCP_packet (const u_char * packet);
void deconstruct_TCP_packet (TCP_t * tcp);

UDP_t *Construct_UDP_packet (const u_char * packet);
void deconstruct_UDP_packet (UDP_t * udp);

ICMP_t *Construct_ICMP_packet (const u_char * packet);
void deconstruct_ICMP_packet (ICMP_t * tcp);


HTTP_t *Construct_HTTP_packet (const u_char * packet);
void deconstruct_HTTP_packet (HTTP_t * tcp);

FTP_t *Construct_FTP_packet (const u_char * packet);
void deconstruct_FTP_packet (FTP_t * tcp);

DNS_t *Construct_DNS_packet (const u_char * packet);
void deconstruct_DNS_packet (DNS_t * tcp);
