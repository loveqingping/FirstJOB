/**
 *  Filename: raw_socket.c
 *   Created: 2015-10-09 17:17:52
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo), du.shangkun@ampthon.com
 *   Company: Ampthon
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "checksum.h"
#include "pcap_dump.h"
#define SRC_MAC "90:b1:1c:3a:d3:3d"
#define DST_MAC "00:a8:20:fe:00:ff"
int mac_aton(char* mac_src,uint8_t* mac, int len)
{
    if(len < 6)
    {
        return -1;
    }
    size_t src_len = strlen(mac_src);
    char tmp[3] = {0};
    char* src = mac_src;
    char* sp  = NULL;
    uint8_t* dp =  mac;
    int i = 0;
    int parse_len = 0;
    while(i < 6)
    {
        bzero(tmp, 2);
        if(src_len - parse_len < 3)  //说明此时，已经没有":"了,已经到达末尾了
        {
            memcpy(tmp, sp, 2);
            sscanf(tmp, "%x", &dp[i]);
            break;
        }
        sp = strstr(src,":");  //寻找:
        if(sp == NULL)
        {
            return -1;
        }
        
        memcpy(tmp, sp - 2, 2);  //拷贝2个字节
        sscanf(tmp, "%x", &dp[i]);   
        sp = sp + 1;
        src = sp;
        parse_len = parse_len + 3;  //每次解析三个字节
        ++i;
    }
    return 0;
}

int print_mac(uint8_t* p_mac)
{
    int i = 0;
    for(i = 0; i < 6; ++i)
    {
        fprintf(stderr, "%x", p_mac[i]);
    }
    fprintf(stderr, "\n");
    return 0;
}
int build_ether(char* pkt, uint8_t* dmac, uint8_t* smac, int type, int len)
{
    if( len < 1500)
    {
        fprintf(stderr, "buffer is too small!\n");
        return -1;
    }
    struct ether_header eth_header;
    memcpy(eth_header.ether_dhost, dmac, 6);
    memcpy(eth_header.ether_shost, smac, 6);
    eth_header.ether_type = type;
    memcpy(pkt, &eth_header, sizeof(eth_header));
    return 0;    
}
int build_ipv4(char* p_ip, char* sip, char* dip, int protocol,int apd_len)
{
    if(protocol != 6 && protocol != 17)  //只发送tcp/udp的ip包
    {
        return -1;
    }
    int total_len = 0;
    struct iphdr ip_header;
    ip_header.version = 4;
    ip_header.ihl = 0x5;   //没有选项字段
    ip_header.tos = 0;
    if(protocol == 6)
    {
        total_len = (ip_header.ihl<<2) + sizeof(struct tcphdr) + apd_len;
    }
    if( protocol == 17)
    {
        total_len = (ip_header.ihl<<2) + sizeof(struct udphdr) + apd_len;
    }
    ip_header.tot_len = htons(total_len); 
    ip_header.id = 0;  //标识字段
    ip_header.frag_off = htons(0x4000);
    ip_header.ttl = 64;
    ip_header.protocol = protocol;
    ip_header.check = 0; 
    ip_header.saddr = inet_addr(sip);
    ip_header.daddr = inet_addr(dip);
    ip_header.check = ip_check_ext((uint16_t*)&ip_header, ip_header.ihl<<2, 0); 
    memcpy(p_ip, &ip_header, sizeof(ip_header));
    return 0;
}
int build_tcp_syn(char* p_tcp, uint32_t saddr, uint32_t daddr, uint16_t sport, uint16_t dport)
{
    struct tcphdr tcp_header;
    bzero(&tcp_header, sizeof(tcp_header));
    tcp_header.source = htons(sport);
    tcp_header.dest = htons(dport);
    tcp_header.seq = 0;
    tcp_header.ack_seq = 0;
    tcp_header.doff = ( (uint32_t)sizeof(struct tcphdr)) >> 2;
    tcp_header.syn = 1;
    tcp_header.window = htons(4096);
    tcp_header.check = 0;
    tcp_header.urg_ptr = 0;
    tcp_header.check = my_tcp_check((char*)&tcp_header, tcp_header.doff <<2, saddr,  daddr);
    memcpy(p_tcp, &tcp_header, sizeof(tcp_header));
    return 0;
}
int main(int argc, char* argv[])
{
    struct ifreq ifr;
    uint8_t dmac[8];
    uint8_t smac[8];
    uint32_t saddr = 0;
    uint32_t daddr = 0;
    saddr = inet_addr("192.168.32.1");
    daddr = inet_addr("192.168.48.1");
    bzero(smac, 8);
    mac_aton(SRC_MAC, smac, 8);
    print_mac(smac); 
    bzero(dmac, 8);
    mac_aton(DST_MAC, dmac, 8);
    int raw_socket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP)); //创建原始套接字要求有root权限
    if(raw_socket < 0)
    {
       perror("raw_socket create error!\n"); 
    }
    strcpy(ifr.ifr_name, "eth1");
    ioctl(raw_socket, SIOCGIFINDEX, &ifr );
    fprintf(stderr, "%d\n", ifr.ifr_ifindex);
    //fprintf(stderr, "%d\n", sizeof(struct ether_header));
    struct sockaddr_ll my_etheraddr;
    my_etheraddr.sll_family = AF_PACKET;
    my_etheraddr.sll_protocol = htons(ETH_P_IP);
    my_etheraddr.sll_ifindex = ifr.ifr_ifindex;
    my_etheraddr.sll_pkttype = PACKET_HOST;
    my_etheraddr.sll_halen = 6;
    printf("%d\n", sizeof(struct tcphdr));
    memcpy(my_etheraddr.sll_addr, smac, 6 );
    char pkt[2048];
    bzero(pkt, 2048);
    build_ether(pkt, dmac, smac, htons(0x0800), 2048);
    build_ipv4(pkt + sizeof(struct ether_header),"192.168.32.1", "192.168.48.1",  6, 0 );
    build_tcp_syn(pkt + sizeof(struct ether_header)+sizeof(struct iphdr), saddr, daddr, 46074, 443);
    sendto(raw_socket, pkt, 54,  0, (struct sockaddr*)&my_etheraddr, sizeof(my_etheraddr) );
    //write_pcap_handle_t handle;
    //init_pcap_handle_line(&handle, "test.pcap");
    //write_pcap_data_line(&handle, pkt, 54);
    while(1)
    {

    }
    return 0;
}
