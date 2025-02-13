
#include "packets.h"

static void print_domain_name(const uint8_t * packet, int offset);	//private

static int get_payload_start(const u_char * packet);			//private

void digest_http(const char *packet)
{

	int offset = get_payload_start(packet);

	const char *line = packet + offset;

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

/* print FTP payload and don't handle passive mode */
void print_FTP_data(const u_char * packet)
{
	int payload_len;
	int offset;		//start of payload (FTP)
	int packet_size;

	offset = get_payload_start(packet);
	packet_size = ntohs(((struct ip *)(packet + 14))->ip_len);
	payload_len = packet_size - (offset - 14);	//remove from packet size of (ip_hdr , tcp_hdr) 
	if (payload_len) {
		printf("FTP :\n%.*s\n", payload_len, packet + offset);
	}
}

// Function to parse DNS packet operates over udp only
void digest_dns(const unsigned char *packet)
{
	struct dnshdr *dns_header;
	int dns_payload_offset;
	const unsigned char *dns_payload;
	char domain_name[256];

	// Locate DNS payload
	dns_payload_offset = get_payload_start(packet);

	dns_payload = packet + dns_payload_offset;

	// Extract DNS header
	dns_header = (struct dnshdr *)dns_payload;

	unsigned short id = ntohs(dns_header->id);
	unsigned short flags = ntohs(dns_header->flags);
	unsigned short qdcount = ntohs(dns_header->qdcount);
	unsigned short ancount = ntohs(dns_header->ancount);

	printf("DNS :\n");
	printf("	|-Transaction ID: %u\n", id);
	printf("	|-Flags		: 0x%X\n", flags);
	printf("	|-Questions	: %u, |-Answers: %u\n", qdcount,
	       ancount);

	print_domain_name(dns_payload, DNS_HEADER);
}

void Digest_IP(IP_Packet_t * ip_packet)
{

	struct ip *ip_header = ip_packet->ip_hdr;

	printf("IP Header:\n");
	printf("   |-Version        : %d\n", ip_header->ip_v);
	printf("   |-Header Length  : %d\n", ip_header->ip_hl * 4);
	printf("   |-Total Length   : %d\n", ntohs(ip_header->ip_len));
	printf("   |-Protocol       : %d\n", ip_header->ip_p);
	printf("   |-Source Address : %s\n", inet_ntoa(ip_header->ip_src));
	printf("   |-Destination Address : %s\n", inet_ntoa(ip_header->ip_dst));
}

// Function to print TCP header fields
void digest_tcp(IP_Packet_t * layer)
{

	struct tcphdr *tcp_header = ((TCP_t *) layer)->tcp_hdr;
	printf("TCP Header:\n");
	printf("   |-Source Port     : %d\n", ntohs(tcp_header->th_sport));
	printf("   |-Destination Port: %d\n", ntohs(tcp_header->th_dport));
	printf("   |-Sequence Number : %u\n", ntohl(tcp_header->th_seq));
	printf("   |-Acknowledgment  : %u\n", ntohl(tcp_header->th_ack));
}

// Function to print UDP header fields
void digest_udp(IP_Packet_t * layer)
{
	struct udphdr *udp_header = ((UDP_t *) layer)->udp_hdr;
	printf("UDP Header:\n");
	printf("   |-Source Port     : %d\n", ntohs(udp_header->uh_sport));
	printf("   |-Destination Port: %d\n", ntohs(udp_header->uh_dport));
	printf("   |-Length          : %d\n", ntohs(udp_header->uh_ulen));
}

void digest_icmp(IP_Packet_t * layer)
{

	struct icmphdr *icmp_header = ((ICMP_t *) layer)->icmp_hdr;

	// Print basic ICMP information
	printf("ICMP Packet :\n");
	printf("	|-ICMP Type: %d\n", icmp_header->type);
	printf("	|-ICMP Code: %d\n", icmp_header->code);
	printf("	|-ICMP Checksum: 0x%04x\n",
	       ntohs(icmp_header->checksum));

	// Handle specific types of ICMP messages
	switch (icmp_header->type) {
	case ICMP_ECHO:
		printf("	Type: Echo Request\n");
		break;
	case ICMP_ECHOREPLY:
		printf("	Type: Echo Reply \n");
		break;
	case ICMP_DEST_UNREACH:
		printf("	(Destination Unreachable)\n");
		break;
		break;
	case ICMP_TIME_EXCEEDED:
		printf("	Type: Time Exceeded\n");
		break;
	case ICMP_PARAMPROB:
		printf("	Type: Parameter Problem\n");
		break;
	default:
		printf("	Type: Unknown ICMP Type\n");
		break;
	}

}

void print_applicationPort(int port)
{

	if (port == 80) {
		// HTTP (Port 80)
		printf("		HTTP Application Layer Data:\n");
	}
	// Check for HTTPS (Port 443)
	else if (port == 443) {
		// HTTPS (Port 443) - Encrypted, cannot display actual data
		printf
		    ("		HTTPS Traffic (Encrypted, not printable)\n");
	}
	// Check for SSH (Port 22)
	else if (port == 22) {
		// SSH (Port 22) - Encrypted, cannot display actual data
		printf
		    ("		SSH Traffic (Encrypted, not printable)\n");
	} else {
		printf
		    ("	No supported application layer protocol found for port %d.\n",
		     port);
	}

}

/***************************************************************************************************************************/
IP_Packet_t *Construct_IP_packet(const u_char * packet)
{

	IP_Packet_t *ip_packet = (IP_Packet_t *) malloc(sizeof(IP_Packet_t));
	if (!ip_packet) {
		perror("malloc\n");
		exit(-1);
	}

	ip_packet->eth_hdr = (struct sniff_ethernet *)packet;
	ip_packet->ip_hdr = (struct ip *)(packet + 14);
	ip_packet->digest_ip = Digest_IP;

	return ip_packet;
}

void deconstruct_IP_packet(IP_Packet_t * ip_packet)
{

	free(ip_packet);
}

/***************************************************************************************************************************/

HTTP_t *Construct_HTTP_packet(const u_char * packet)
{

	HTTP_t *http_packet = (HTTP_t *) malloc(sizeof(HTTP_t));
	if (!http_packet) {
		perror("malloc\n");
		exit(-1);
	}
	http_packet->tcp_packet = Construct_TCP_packet(packet);
	http_packet->digest_http = digest_http;

	return http_packet;

}

void deconstruct_HTTP_packet(HTTP_t * http)
{
	deconstruct_TCP_packet(http->tcp_packet);
	free(http);
}

FTP_t *Construct_FTP_packet(const u_char * packet)
{

	FTP_t *ftp_packet = (FTP_t *) malloc(sizeof(FTP_t));
	if (!ftp_packet) {
		perror("malloc\n");
		exit(-1);
	}
	ftp_packet->tcp_packet = Construct_TCP_packet(packet);
	ftp_packet->print_FTP_data = print_FTP_data;

	return ftp_packet;

}

void deconstruct_FTP_packet(FTP_t * ftp)
{
	deconstruct_TCP_packet(ftp->tcp_packet);
	free(ftp);
}

DNS_t *Construct_DNS_packet(const u_char * packet)
{

	DNS_t *dns_packet = (DNS_t *) malloc(sizeof(DNS_t));
	if (!dns_packet) {
		perror("malloc\n");
		exit(-1);
	}
	dns_packet->udp_packet = Construct_UDP_packet(packet);
	dns_packet->digest_dns = digest_dns;

	return dns_packet;

}

void deconstruct_DNS_packet(DNS_t * dns)
{
	deconstruct_UDP_packet(dns->udp_packet);
	free(dns);
}

/***************************************************************************************************************************/

TCP_t *Construct_TCP_packet(const u_char * packet)
{

	TCP_t *tcp_packet = (TCP_t *) malloc(sizeof(TCP_t));
	if (!tcp_packet) {
		perror("malloc\n");
		exit(-1);
	}
	tcp_packet->ip_packet = Construct_IP_packet(packet);
	tcp_packet->tcp_hdr =
	    (struct tcphdr *)(packet + 14 +
			      (tcp_packet->ip_packet->ip_hdr->ip_hl * 4));
	tcp_packet->ip_packet->Digest_Protocol = digest_tcp;	//polymorphism

	return tcp_packet;
}

void deconstruct_TCP_packet(TCP_t * tcp)
{
	deconstruct_IP_packet(tcp->ip_packet);
	free(tcp);

}

/***************************************************************************************************************************/

UDP_t *Construct_UDP_packet(const u_char * packet)
{

	UDP_t *udp_packet = (UDP_t *) malloc(sizeof(UDP_t));
	if (!udp_packet) {
		perror("malloc\n");
		exit(-1);
	}
	udp_packet->ip_packet = Construct_IP_packet(packet);
	udp_packet->udp_hdr =
	    (struct udphdr *)(packet + 14 +
			      (udp_packet->ip_packet->ip_hdr->ip_hl * 4));
	udp_packet->ip_packet->Digest_Protocol = digest_udp;	//polymorphism

	return udp_packet;
}

void deconstruct_UDP_packet(UDP_t * udp)
{
	deconstruct_IP_packet(udp->ip_packet);
	free(udp);

}

/***************************************************************************************************************************/

ICMP_t *Construct_ICMP_packet(const u_char * packet)
{

	ICMP_t *icmp_packet = (ICMP_t *) malloc(sizeof(ICMP_t));
	if (!icmp_packet) {
		perror("malloc\n");
		exit(-1);
	}
	icmp_packet->ip_packet = Construct_IP_packet(packet);
	icmp_packet->icmp_hdr =
	    (struct icmphdr *)(packet + 14 +
			       (icmp_packet->ip_packet->ip_hdr->ip_hl * 4));
	icmp_packet->ip_packet->Digest_Protocol = digest_icmp;	//polymorphism

	return icmp_packet;
}

void deconstruct_ICMP_packet(ICMP_t * icmp)
{
	deconstruct_IP_packet(icmp->ip_packet);
	free(icmp);

}

/***************************************************************************************************************************/

/** This functions are considered private as it is static in the file and has no pointer in the struct */

static int get_payload_start(const u_char * packet)
{

	int iphdr_len, transport_hdr_len, offset;
	struct ip *ip_hdr;

	ip_hdr = (struct ip *)(packet + SIZE_ETHERNET);
	iphdr_len = (ip_hdr->ip_hl) * 4;
	if (ip_hdr->ip_p == IPPROTO_TCP) {

		transport_hdr_len =
		    (((struct tcphdr *)(packet + SIZE_ETHERNET +
					iphdr_len))->doff) * 4;
	} else if (ip_hdr->ip_p == IPPROTO_UDP) {

		transport_hdr_len = UDP_HEADER;	//UDP header is 8 bytes         
	}

	offset = SIZE_ETHERNET + iphdr_len + transport_hdr_len;

	return offset;

}

// Function to print the domain name
static void print_domain_name(const uint8_t * packet, int offset)
{
	int len = packet[offset];
	printf("	");
	while (len != 0) {
		offset++;
		for (int i = 0; i < len; i++) {
			printf("%c", packet[offset + i]);
		}
		printf(".");
		offset += len;
		len = packet[offset];
	}
	offset++;
	printf("\n");
}
