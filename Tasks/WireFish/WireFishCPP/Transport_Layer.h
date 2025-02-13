#ifndef TRANSPORT_LAYER_H_INCLUDED
#define TRANSPORT_LAYER_H_INCLUDED

#include "Network_Layer.h"

class TCP : public IP_Packet{
    private:
        struct tcphdr *tcp_hdr;
        int offset;			//length of (ethernet hdr + iphdr + tcphdr)
    protected:


    public:
        TCP(const char *pckt);
        virtual ~TCP(){}
        
        struct tcphdr *get_tcphdr();
        void set_tcphdr(struct tcphdr *tcp_header);
        int get_tcphdr_len();
        int get_offset();
        
        void digest_protocol();
};


class UDP : public IP_Packet{
    private:
        struct udphdr *udp_hdr;
        int offset;
    protected:


    public:
        UDP(const char *pckt);
        virtual ~UDP(){}
        
        struct udphdr *get_udphdr();
        void set_udphdr(struct udphdr *udp_header);
        int get_udphdr_len();
        int get_offset();
        
        void digest_protocol();
};



class ICMP : public IP_Packet{
    private:
        struct icmphdr *icmp_hdr;
    protected:


    public:
        ICMP(const char *pckt);
        virtual ~ICMP(){}
        
        struct icmphdr *get_icmphdr();
        void set_icmphdr(struct icmphdr *icmp_header);
        
        void digest_protocol();
        void digest_applayer(){}
};



#endif // TRANSPORT_LAYER_H_INCLUDED
