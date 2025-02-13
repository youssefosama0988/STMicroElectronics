#include "packets.h"

void
packet_handler(u_char * user_data, const struct pcap_pkthdr *pkthdr,
	       const u_char * packet)
{
	struct ip *ip_header, *ip_parent;
	// Process IP layer
	IP_Packet_t *ip_layer = Construct_IP_packet(packet);
	ip_header = ip_layer->ip_hdr;
	ip_layer->digest_ip(ip_layer);	//print ip header

	// Process Transport layer
	if (ip_header->ip_p == IPPROTO_TCP) {
		TCP_t *tcp_layer = Construct_TCP_packet(packet);
		tcp_layer->ip_packet->Digest_Protocol((IP_Packet_t *) tcp_layer);	// Polymorphism

		if (ntohs(tcp_layer->tcp_hdr->th_sport) == 80	//check if the packet is HTTP
		    || ntohs(tcp_layer->tcp_hdr->th_dport) == 80) {
			HTTP_t *http = Construct_HTTP_packet(packet);
			http->digest_http(packet);
			deconstruct_HTTP_packet(http);
		} else if (ntohs(tcp_layer->tcp_hdr->th_sport) == FTP_PORT	//check if the packet is FTP
			   || ntohs(tcp_layer->tcp_hdr->th_dport) == FTP_PORT) {
			FTP_t *ftp = Construct_FTP_packet(packet);
			ftp->print_FTP_data(packet);
			deconstruct_FTP_packet(ftp);
		} else {

		}

		deconstruct_TCP_packet(tcp_layer);	// Destructor
	} else if (ip_header->ip_p == IPPROTO_UDP) {
		UDP_t *udp_layer = Construct_UDP_packet(packet);
		udp_layer->ip_packet->Digest_Protocol((IP_Packet_t *) udp_layer);	// Polymorphism

		if (ntohs(udp_layer->udp_hdr->uh_sport) == DNS_PORT	//check if the packet is DNS
		    || ntohs(udp_layer->udp_hdr->uh_dport) == DNS_PORT) {

			DNS_t *dns = Construct_DNS_packet(packet);
			dns->digest_dns(packet);
			deconstruct_DNS_packet(dns);
		}

		deconstruct_UDP_packet(udp_layer);	// Destructor

	} else if (ip_header->ip_p == IPPROTO_ICMP) {
		ICMP_t *icmp_layer = Construct_ICMP_packet(packet);
		icmp_layer->ip_packet->Digest_Protocol((IP_Packet_t *) icmp_layer);	// Polymorphism
		deconstruct_ICMP_packet(icmp_layer);	// Destructor
	}

	deconstruct_IP_packet(ip_layer);
	printf
	    ("==============================================================\n");

	pcap_dumper_t *pcap_dumper = (pcap_dumper_t *) user_data;
	if (pcap_dumper != NULL) {
		pcap_dump((unsigned char *)pcap_dumper, pkthdr, packet);

	}

}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("Usage: %s <interface> <filter> -f <file.pcap>\n",
		       argv[0]);
		return 1;
	}

	struct bpf_program fp;

	pcap_t *handle;
	char errbuf[PCAP_ERRBUF_SIZE];

	handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "Error opening device %s: %s\n", argv[1],
			errbuf);
		return 1;
	}

	if (pcap_compile(handle, &fp, argv[2], 0, PCAP_NETMASK_UNKNOWN) == -1) {
		fprintf(stderr, "Error compiling filter: %s\n",
			pcap_geterr(handle));
		return 1;
	}
	// Set the filter on the capture handle
	if (pcap_setfilter(handle, &fp) == -1) {
		fprintf(stderr, "Error setting filter: %s\n",
			pcap_geterr(handle));
		return 1;
	}

	if (argv[3] != NULL) {

		if (strcmp("-f", argv[3]) == 0) {
			char *pcap_file = argv[4];
			pcap_dumper_t *pcap_dumper =
			    pcap_dump_open(handle, pcap_file);
			if (pcap_dumper == NULL) {
				printf("PCAPDUMPER!!\n");
				return -1;
			}
			pcap_loop(handle, 0, packet_handler,
				  (unsigned char *)pcap_dumper);
			pcap_dump_close(pcap_dumper);
			pcap_close(handle);
			return 0;
		}
	}

	pcap_loop(handle, 0, packet_handler, NULL);

	pcap_close(handle);
	return 0;
}
