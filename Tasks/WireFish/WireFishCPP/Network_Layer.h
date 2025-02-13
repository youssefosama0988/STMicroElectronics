#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H


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

class IP_Packet {				//abstract class
   
    private:
        struct ip *ip_hdr;
        const char *packet;
            
    public:
        IP_Packet();
        IP_Packet(const char *pckt);
        
        virtual ~IP_Packet();
        
        void digest_ip();			//print ip header for any packet
        virtual void digest_protocol() = 0; 	//pure virtual 'abstract function'
        virtual void digest_applayer() = 0;	
        

    protected:
        struct ip* get_iphdr();
        void set_iphdr(struct ip* iphdr);
        const char *get_packet();
        void set_packet(const char *pckt);
        int get_iPhdr_len();



};

#endif // IP_PACKET_H
