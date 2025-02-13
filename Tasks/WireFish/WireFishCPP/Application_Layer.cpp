
#include "Application_Layer.h"


DNS::DNS(const char *pckt) : UDP(pckt){
	
	const char *dns_payload;
	int payload_off;
	
	payload_off = get_offset();
	dns_payload = get_packet();
	dns_payload += payload_off;
	
	dns_header = (struct dnshdr *)dns_payload;
	
}


void DNS::digest_applayer(){

	char domain_name[256];
	unsigned short id = ntohs(dns_header->id);
	unsigned short flags = ntohs(dns_header->flags);
	unsigned short qdcount = ntohs(dns_header->qdcount);
	unsigned short ancount = ntohs(dns_header->ancount);

	printf("DNS :\n");
	printf("	|-Transaction ID: %u\n", id);
	printf("	|-Flags		: 0x%X\n", flags);
	printf("	|-Questions	: %u, |-Answers: %u\n", qdcount,
	       ancount);

	print_domain_name((const char *)dns_header, DNS_HEADER);

}

void DNS::print_domain_name(const char* packet, int payload_offset)
{
	int len = packet[payload_offset];
	printf("	");
	while (len != 0) {
		payload_offset++;
		for (int i = 0; i < len; i++) {
			printf("%c", packet[payload_offset + i]);
		}
		printf(".");
		payload_offset += len;
		len = packet[payload_offset];
	}
	payload_offset++;
	printf("\n");
}

/**********************************HTTP Functions*******************************************************/

HTTP::HTTP(const char *pckt) : TCP(pckt){

}


void HTTP::digest_applayer(){

	const char *line ;
	int payload_off = get_offset();
	
	line = get_packet();
	line += payload_off;

	if (*line)
		printf("HTTP Header :\n");

	while (*line) {
		const char *next_line = strstr(line, "\r\n");
		if (!next_line)
			break;

		int length = next_line - line;
		if (length == 0)
			break;					// End of headers

		printf("    %.*s\n", length, line);
		line = next_line + 2;	// Move to the next line
	}

}

/**********************************FTP Functions*******************************************************/



FTP::FTP(const char *pckt) : TCP(pckt){


}


void FTP::digest_applayer(){
	const char* packet = get_packet();
	int payload_len;
	int offset = get_offset();		//start of payload (FTP)
	int packet_size;

	packet_size = ntohs(((struct ip *)(packet + 14))->ip_len);
	payload_len = packet_size - (offset - 14);	//remove from packet size of (ip_hdr , tcp_hdr) 
	if (payload_len) {
		printf("FTP :\n%.*s\n", payload_len, packet + offset);
	}

}






















