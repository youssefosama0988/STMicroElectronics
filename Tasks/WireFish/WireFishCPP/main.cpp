#include <iostream>
#include "Network_Layer.h"
#include "Application_Layer.h"
#include "Transport_Layer.h"


using namespace std;
void
packet_handler(u_char * user_data, const struct pcap_pkthdr *pkthdr,
	       const u_char * packet);


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


/**************************************************************************** END OF MAIN *****************************************************************************************/
void
packet_handler(u_char * user_data, const struct pcap_pkthdr *pkthdr, const u_char * packet)
{
	struct ip *ip_header;
	IP_Packet* pckt = NULL;
	
	ip_header = (struct ip *)(packet + 14);
	
	/***************************construct packet*****************************/
	if (ip_header->ip_p == IPPROTO_TCP) {
		
		struct tcphdr *tcp_hdr = (struct tcphdr *) (packet + 14 + ip_header->ip_hl * 4);
		
		if (ntohs(tcp_hdr->th_sport) == 80		//check if the packet is HTTP
		    || ntohs(tcp_hdr->th_dport) == 80)
	    	{
			pckt = new HTTP((const char *)packet);
			
		} 
		else if (ntohs(tcp_hdr->th_sport) == FTP_PORT	//check if the packet is FTP
		      || ntohs(tcp_hdr->th_dport) == FTP_PORT)
	   	{
			pckt = new FTP((const char *)packet);
		}
		else{
		
		}

	} else if (ip_header->ip_p == IPPROTO_UDP) {
		struct udphdr *udp_hdr = (struct udphdr *) (packet + 14 + ip_header->ip_hl * 4);

		if (ntohs(udp_hdr->uh_sport) == DNS_PORT	//check if the packet is DNS
		 || ntohs(udp_hdr->uh_dport) == DNS_PORT)
	 	{
			
			pckt = new DNS((const char *)packet);
		}


	} else if (ip_header->ip_p == IPPROTO_ICMP) {
		pckt = new ICMP((const char *)packet);
		
	}
	
	/****************************Process the packet*****************************/
	if(NULL != pckt){
		pckt->digest_ip();
		pckt->digest_protocol();
		pckt->digest_applayer();
	}	
	
	/****************************desstruct the packet**************************/
	delete pckt;
	
	printf
	    ("==============================================================\n");

	pcap_dumper_t *pcap_dumper = (pcap_dumper_t *) user_data;
	if (pcap_dumper != NULL) {
		pcap_dump((unsigned char *)pcap_dumper, pkthdr, packet);

	}

}
