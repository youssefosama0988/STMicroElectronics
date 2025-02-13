#include "packets.h"

void
packet_handler(u_char * user_data, const struct pcap_pkthdr *pkthdr,
	       const u_char * packet)
{
	struct ip *ip_header;
	const void* app_ptr;
	IP_Packet_t *pckt;
	ip_header = (struct ip *)(packet + 14);
	
/*****************************************Construct the packet**********************************************/	
	if (ip_header->ip_p == IPPROTO_TCP) {
		struct tcphdr *tcp_hdr = (struct tcphdr *) (packet + 14 + ip_header->ip_hl * 4);
		
		if (ntohs(tcp_hdr->th_sport) == 80	//check if the packet is HTTP
		    || ntohs(tcp_hdr->th_dport) == 80) {
			app_ptr = (const void *)Construct_HTTP_packet(packet);
			pckt = ((HTTP_t *)app_ptr)->tcp_packet->ip_packet;
			
		} else if (ntohs(tcp_hdr->th_sport) == FTP_PORT	//check if the packet is FTP
			   || ntohs(tcp_hdr->th_dport) == FTP_PORT) {
			app_ptr = (const void *)Construct_FTP_packet(packet);
			pckt = ((FTP_t *)app_ptr)->tcp_packet->ip_packet;
			
		} else {

		}

	} else if (ip_header->ip_p == IPPROTO_UDP) {
		
		struct udphdr *udp_hdr = (struct udphdr *) (packet + 14 + ip_header->ip_hl * 4);
		

		if (ntohs(udp_hdr->uh_sport) == DNS_PORT	//check if the packet is DNS
		    || ntohs(udp_hdr->uh_dport) == DNS_PORT) {

			app_ptr = (const void *)Construct_DNS_packet(packet);
			pckt = ((DNS_t *)app_ptr)->udp_packet->ip_packet;
			
		}


	} else if (ip_header->ip_p == IPPROTO_ICMP) {
		app_ptr = (const void *)Construct_ICMP_packet(packet);
		pckt = ((ICMP_t *)app_ptr)->ip_packet;
	}

/**************************************Process the packet***************************************/
	if(NULL != pckt){
		pckt->digest_ip(pckt);
		pckt->Digest_Protocol(pckt);
		pckt->digest_applayer(packet);
	}
	printf
	    ("==============================================================\n");
	
/****************************************Destruct the packet********************************************/
			//here	
			free((void *)app_ptr);            //simulate DESTRUCTOR

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
