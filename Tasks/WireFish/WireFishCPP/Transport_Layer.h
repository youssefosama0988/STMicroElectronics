#ifndef TRANSPORT_LAYER_H_INCLUDED
#define TRANSPORT_LAYER_H_INCLUDED
#include "IP_Packet.h"

class TCP : public IP_Packet{
    private:
        struct tcphdr *tcp_hdr;
    protected:


    public:
        TCP(const char *pckt) : IP_Packet(pckt);
        virtual ~TCP(){}
        struct tcphdr *get_tcphdr();
        void set_tcphdr(struct tcphdr *tcp_header);
        virtual digest_applayer(){}
};


class UDP : public IP_Packet{
    private:
        struct udphdr *udp_hdr;
    protected:


    public:
        UDP(const char *pckt) : IP_Packet(pckt);
        virtual ~UDP(){}
        struct udphdr *get_udphdr();
        void set_udphdr(struct udphdr *udp_header);
        virtual digest_applayer(){}
};



class ICMP : public IP_Packet{
    private:
        struct icmphdr *icmp_hdr;
    protected:


    public:
        ICMP(const char *pckt) : IP_Packet(pckt){

        }
        virtual ~ICMP(){}
        struct icmphdr *get_icmphdr();
        void set_icmphdr(struct icmphdr *icmp_header);
};



#endif // TRANSPORT_LAYER_H_INCLUDED
