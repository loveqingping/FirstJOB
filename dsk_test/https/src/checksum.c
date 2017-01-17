
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

/*******
story replace the u_char u_short uint_t with uint8_t uint16_t uint32_t
*********/
struct psuedo_hdr
{
  uint32_t saddr;      
  uint32_t daddr;      
  uint8_t zero;        
  uint8_t protocol;    
  uint16_t len;        
};
struct psuedo_hdr6
{
   	struct in6_addr saddr,daddr;
    uint32_t len;
    uint8_t  zero[3];
    uint8_t  protocol;
};

uint16_t ip_check_ext(register uint16_t *addr, register int len, int addon)
{
  register int nleft = len;
  register uint16_t *w = addr;
  register int sum = addon;
  uint16_t answer = 0;

  /*
   *  Our algorithm is simple, using a 32 bit accumulator (sum),
   *  we add sequential 16 bit words to it, and at the end, fold
   *  back all the carry bits from the top 16 bits into the lower
   *  16 bits.
   */
  while (nleft > 1)  {
    sum += *w++;
    nleft -= 2;
  }
  /* mop up an odd byte, if necessary */
  if (nleft == 1) {
    *(uint8_t *)(&answer) = *(uint8_t *)w;
    sum += answer;
  }  
  /* add back carry outs from top 16 bits to low 16 bits */
  sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
  sum += (sum >> 16);                     /* add carry */
  answer = ~sum;                          /* truncate to 16 bits */
  return (answer);
}

uint16_t ip_fast_csum(uint16_t *addr, int len)
{
  return ip_check_ext(addr, len << 2, 0);
}

uint16_t ip_compute_csum(uint16_t *addr, int len)
{
  return ip_check_ext(addr, len, 0);
}

uint16_t my_tcp_check(char *th, int len, uint32_t saddr, uint32_t daddr)
{

  int i, sum = 0;
  struct psuedo_hdr hdr;
  
  hdr.saddr = saddr;
  hdr.daddr = daddr;
  hdr.zero = 0;
  hdr.protocol = IPPROTO_TCP;
  hdr.len = htons(len);
  for (i = 0; i < sizeof(hdr); i += 2)
    sum += *(uint16_t *)((char *)(&hdr) + i);
  
  return (ip_check_ext((uint16_t *)th, len, sum));
}                     

uint16_t my_udp_check(void *u, int len, uint32_t saddr, uint32_t daddr)
{
  int i, sum = 0;
  struct psuedo_hdr hdr;
  
  hdr.saddr = saddr;
  hdr.daddr = daddr;
  hdr.zero = 0;
  hdr.protocol = IPPROTO_UDP;
  hdr.len = htons(len);
  for (i = 0; i < sizeof(hdr); i += 2)
    sum += *(uint16_t *)((char *)(&hdr) + i);
  
  return (ip_check_ext((uint16_t *)u, len, sum));
}

uint16_t my_udp6_check( char * udph, uint32_t len,
		struct in6_addr saddr, struct in6_addr daddr )
{
  int sum = 0;
  int i;
  struct psuedo_hdr6 hdr;
  
  memcpy(&hdr.saddr,&saddr,sizeof(struct in6_addr));
  memcpy(&hdr.daddr,&daddr,sizeof(struct in6_addr));
  hdr.zero[0] = 0;
  hdr.zero[1] = 0;
  hdr.zero[2] = 0;
  hdr.protocol = IPPROTO_UDP;
  hdr.len = htonl(len);
  for (i = 0; i < sizeof(hdr); i += 2)
    sum += *(uint16_t *)((char *)(&hdr) + i);
  return (ip_check_ext((uint16_t *)udph, (int)len, sum));
}
uint16_t my_tcp6_check( char * tcph, uint32_t len,
		struct in6_addr saddr, struct in6_addr daddr )
{
  int sum = 0;
  int i;
  struct psuedo_hdr6 hdr;
  
  memcpy(&hdr.saddr,&saddr,sizeof(struct in6_addr));
  memcpy(&hdr.daddr,&daddr,sizeof(struct in6_addr));
  hdr.zero[0] = 0;
  hdr.zero[1] = 0;
  hdr.zero[2] = 0;
  hdr.protocol = IPPROTO_TCP;
  hdr.len = htonl(len);
  for (i = 0; i < sizeof(hdr); i += 2)
    sum += *(uint16_t *)((char *)(&hdr) + i);
  return (ip_check_ext((uint16_t *)tcph, (int)len, sum));
}

