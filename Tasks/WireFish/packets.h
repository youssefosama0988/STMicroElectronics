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

/* IP header */
struct sniff_ip {
        u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
        u_char  ip_tos;                 /* type of service */
        u_short ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        u_short ip_off;                 /* fragment offset field */
        #define IP_RF 0x8000            /* reserved fragment flag */
        #define IP_DF 0x4000            /* don't fragment flag */
        #define IP_MF 0x2000            /* more fragments flag */
        #define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
        u_char  ip_ttl;                 /* time to live */
        u_char  ip_p;                   /* protocol */
        u_short ip_sum;                 /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
};

#define IP_HL(ip)               (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)                (((ip)->ip_vhl) >> 4)


/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp {
        u_short th_sport;               /* source port */
        u_short th_dport;               /* destination port */
        tcp_seq th_seq;                 /* sequence number */
        tcp_seq th_ack;                 /* acknowledgement number */
        u_char  th_offx2;               /* data offset, rsvd */
	#define TH_OFF(th)      (((th)->th_offx2 & 0xf0) >> 4)
        u_char  th_flags;
        #define TH_FIN  0x01
        #define TH_SYN  0x02
        #define TH_RST  0x04
        #define TH_PUSH 0x08
        #define TH_ACK  0x10
        #define TH_URG  0x20
        #define TH_ECE  0x40
        #define TH_CWR  0x80
        #define TH_FLAGS        (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
        u_short th_win;                 /* window */
        u_short th_sum;                 /* checksum */
        u_short th_urp;                 /* urgent pointer */
};


typedef struct IP_Packet{

	struct sniff_ethernet *eth_hdr;
	struct ip *ip_hdr;
	void (*digest_ip) (struct IP_Packet *ip_packet);		//fixed implementation to all packets to print ip-header
	void (*Digest_Protocol) (struct IP_Packet *layer);       	//implemented by each packet to show each protocol-header
	void (*print_applicationPort)(int port);
}IP_Packet_t;


typedef struct{
	IP_Packet_t *ip_packet;			//inheritance
	struct sniff_tcp *tcp_hdr;	

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

IP_Packet_t *Construct_IP_packet(const u_char *packet);
void deconstruct_IP_packet(IP_Packet_t *ip_packet);

TCP_t *Construct_TCP_packet(const u_char *packet);
void deconstruct_TCP_packet(TCP_t *tcp);

UDP_t *Construct_UDP_packet(const u_char *packet);
void deconstruct_UDP_packet(TCP_t *udp);










