#ifndef APPLICATION_LAYER_H_INCLUDED
#define APPLICATION_LAYER_H_INCLUDED

#include "Transport_Layer.h"



class DNS : public UDP{
    private:
    	struct dnshdr *dns_header;
    	void print_domain_name(const char * packet, int offset); 	//helper function to print domain names	
    public:
        DNS(const char *pckt);
        ~DNS(){}
        
        void digest_applayer();	// Function to parse DNS packet operates over udp only 'digest dns'

};


class HTTP : public TCP{
    
    public:
        HTTP(const char *pckt);
        ~HTTP(){}
        
        void digest_applayer();      //digest http
};

class FTP : public TCP{

    public:
        FTP(const char *pckt) ;
        ~FTP(){}
        
        void digest_applayer();    //digest ftp
};




//DNS Header Structure (first 12 bytes)
struct dnshdr
{
  unsigned short id;		// Transaction ID
  unsigned short flags;		// Flags and response codes
  unsigned short qdcount;	// Number of questions
  unsigned short ancount;	// Number of answers
  unsigned short nscount;	// Number of authority records
  unsigned short arcount;	// Number of additional records
};

#endif // APPLICATION_LAYER_H_INCLUDED
