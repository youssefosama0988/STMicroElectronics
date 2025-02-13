#ifndef IP_PACKET_H
#define IP_PACKET_H
#include "Application_Layer.h"
#include "Transport_Layer.h"

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

class IP_Packet
{
    public:
        IP_Packet();
        IP_Packet(const char *pckt);
        virtual ~IP_Packet();
        void digest_ip();
        virtual digest_protocol() = 0; //abstract function

    protected:
        struct ip* get_iphdr() const;
        void set_iphdr(struct ip* iphdr);
        const char *get_packet() const;
        void set_packet(const char *pckt);

    private:
        struct ip *ip_hdr;
        const char *packet;

};

#endif // IP_PACKET_H
