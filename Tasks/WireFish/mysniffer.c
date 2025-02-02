#include "packets.h"


void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr,const u_char *packet) {
    
   // struct ip *ip_header = (struct ip *)(packet + 14);  // Skip Ethernet header

    // Process IP layer
    IP_Packet_t *ip_layer = Construct_IP_packet(packet);
    ip_layer->digest_ip(ip_layer); 				 // Polymorphism
    struct ip *ip_header = ip_layer->ip_hdr;

    // Process Transport layer
    if (ip_header->ip_p == IPPROTO_TCP) {
        TCP_t *tcp_layer = Construct_TCP_packet(packet);
        tcp_layer->ip_packet->Digest_Protocol((IP_Packet_t *)tcp_layer);  // Polymorphism
        deconstruct_TCP_packet(tcp_layer);  // Destructor
    }
    else if (ip_header->ip_p == IPPROTO_UDP) {
        UDP_t *udp_layer = Construct_UDP_packet(packet);
        udp_layer->ip_packet->Digest_Protocol((IP_Packet_t *)udp_layer);  // Polymorphism
        deconstruct_UDP_packet(udp_layer);  // Destructor
    }
    else if (ip_header->ip_p == IPPROTO_ICMP) {
        ICMP_t *icmp_layer = Construct_ICMP_packet(packet);
        icmp_layer->ip_packet->Digest_Protocol((IP_Packet_t *)icmp_layer);  // Polymorphism
        deconstruct_ICMP_packet(icmp_layer);  // Destructor
    }

	deconstruct_IP_packet(ip_layer);
	printf("==============================================================\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <interface>\n", argv[0]);
        return 1;
    }


    struct bpf_program fp;

    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Error opening device %s: %s\n", argv[1], errbuf);
        return 1;
    }
    
    if (pcap_compile(handle, &fp, argv[2], 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Error compiling filter: %s\n", pcap_geterr(handle));
        return 1;
    }

    // Set the filter on the capture handle
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Error setting filter: %s\n", pcap_geterr(handle));
        return 1;
    }

    pcap_loop(handle, 0, packet_handler, NULL);

    pcap_close(handle);
    return 0;
}

