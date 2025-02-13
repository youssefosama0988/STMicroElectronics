#ifndef APPLICATION_LAYER_H_INCLUDED
#define APPLICATION_LAYER_H_INCLUDED
#include "Transport_Layer.h"

class DNS : public UDP{

    public:
        DNS(const char *pckt) : UDP(pckt){}
        ~DNS(){}
        //void digest_dns();

};


class HTTP : public TCP{

    public:
        HTTP(const char *pckt) : TCP(pckt){}
        ~HTTP(){}
        //void digest_http());
};

class FTP : public TCP{

    public:
        FTP(const char *pckt) : TCP(pckt){}
        ~FTP(){}
        //void digest_ftp();
};



#endif // APPLICATION_LAYER_H_INCLUDED
