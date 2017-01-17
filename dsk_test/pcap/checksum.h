
#ifndef __CHECKSUM_H
#define __CHECKSUM_H
#include <netinet/in.h>

//#include "tcpbroker.h"

uint16_t 		ip_fast_csum(uint8_t *, uint32_t);
extern uint16_t	ip_compute_csum(char *, int len);
uint16_t 		my_tcp_check(char *, int, uint32_t, uint32_t);
uint16_t 		my_udp_check(void *, int, uint32_t, uint32_t);
int 			ip_options_compile(unsigned char *iph);
uint16_t my_udp6_check( char * udph, uint16_t len,
        struct in6_addr saddr, struct in6_addr addr );
uint16_t my_tcp6_check( char * tcph, uint16_t len,
        struct in6_addr saddr, struct in6_addr addr );
#endif /* __CHECKSUM_H */
