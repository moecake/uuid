#include <sys/ioctl.h>
#include <net/if.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

int mem_dump(void *p, const unsigned int n, unsigned int m)
{
	if(!m) m=10;
	
	unsigned int x=0;
	unsigned int y=0;
	unsigned int w=0;
	unsigned int z=0;
	
	unsigned int t = n/m;
	unsigned int r = n%m;
	
	for(x=0; x<t; x++){
		for(y=0; y<m; y++) printf("%02d ", w++);
		printf("\n");
		for(y=0; y<m; y++) printf("%02x ", ((unsigned char *)p)[z++]);
		printf("\n\n");
	}
	if(r){
		for(y=0; y<r; y++) printf("%02d ", w++);
		printf("\n");
		for(y=0; y<r; y++) printf("%02x ", ((unsigned char *)p)[z++]);
		printf("\n");
	}
	
	return 0;
}

int get_MAC(unsigned char mac_address[6])
{
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[1024];
    int success = 0;
    
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1)
    	return -1;
    
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1)
    	return -1;
    
    struct ifreq* it = ifc.ifc_req;
    const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));
    
    for (; it != end; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    success = 1;
                    break;
                }
            }
        } else {
        	return -1;
        }
    }
    
    if (success) 
    	memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
    	
    return 0;
}

int main()
{
    unsigned char mac_address[6];
    get_MAC(mac_address);
    
    mem_dump(mac_address, sizeof(mac_address), 10);
    
    return 0;
}
