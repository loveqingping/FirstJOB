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
#include <stdlib.h>
#include <time.h>
#include <pcap.h>
#include "checksum.h"
#include "pcap_dump.h"
#include "ring_buffer.h"
#include <pthread.h>
#define     MSS         1460
#define     NET_DEVICE  "eth1"
#define     APP         "port 80"
#define     SRC_MAC     "90:b1:1c:3a:d3:3d"
#define     DST_MAC     "00:a8:20:fe:00:ff"
#define     SIP         "192.168.32.1"
#define     DIP         "192.168.48.1"
#define     DPORT       80
#define     H_IP        0x0800
#define     H_TCP       6
#define     TCP_FIN     0x01
#define     TCP_SYN     0X02
#define     TCP_RST     0x04
#define     TCP_PUSH    0X08
#define     TCP_ACK     0X10
#define     TCP_URG     0x20
typedef struct _pkt_key
{
    char saddr[16];
    char daddr[16];
    char dmac[32];
    char smac[32];

    uint16_t dport;
    uint16_t l3_protocol;

    int8_t trans_protocol;
}pkt_key_t;
typedef struct _stack_apd
{
    char buf[2048];
    uint32_t buf_len;
}stack_apd_t;
stack_apd_t* write_apd = NULL;
stack_apd_t* read_apd = NULL;
/*
typedef struct __send_pkt_handle
{
    char dev[64];
    bpf_u_int32 mask;
    bpf_u_int32 net;
    char filter_exp[64];
    pcap_t* sp_handle;
}send_pkt_handle_t;
*/
uint32_t private_seq = 0;     //这两个变量用来跟踪seq 与 ack
uint32_t private_ack = 0;
int32_t  syn_flag = 0;       //0 代表没有进行三次握手
#if 0
char option[64] = {0};
uint32_t option_len = 0;
int option_flag = 0;
#endif
static int get_ip_id()
{
    static int32_t id = 0;
    int tmp = 0;
    tmp = id;
    id++;
    return htons(tmp);
}
static int get_src_port()
{
    int a = 0;
    int b = 0;
    srand((unsigned int)time(NULL));
    a = rand()%10000;
    a = a + 40000;
    b = htons(a);
    return b;  
}
static uint32_t init_seq()
{
    uint32_t a = 0;
    uint32_t b = 0;
    srand( (unsigned int)time(NULL));
    a = rand()%10000;
    b = (1<<24) + a;
    return htonl(b);
}
static int get_seq(char* pkt)
{
    if(pkt == NULL)
    {
        return -1;
    }
    char* p = pkt;
    struct tcphdr* p_tcp = NULL;
    
    p = pkt + sizeof(struct ether_header) + sizeof(struct iphdr);

    p_tcp = (struct tcphdr*)p;
    uint32_t tmp = p_tcp->ack_seq;   //因为p_tcp->ack_seq为网络字节序，要发送的数据包的seq等于ack_seq, 不用再转换了！ 
    return tmp;
}
static int get_ack(char* pkt)
{
    if(pkt == NULL)
    {
        return -1;
    }
    struct iphdr* p_ip = NULL;

    struct tcphdr* p_tcp = NULL;
    char* p = pkt;

    p = pkt + sizeof(struct ether_header);
    p_ip = (struct iphdr*)p;

    p = p + sizeof(struct iphdr);

    p_tcp = (struct tcphdr*)p;
    int total_len = 0;
    total_len = ntohs(p_ip->tot_len);

    int apd_len = total_len - sizeof(struct iphdr) - (p_tcp->doff<<2); //(p_tcp->doff<<2) 真正的头部长度
    uint32_t tmp;
    if(apd_len == 0)
    {
        tmp = ntohl(p_tcp->seq) + 1;
    }
    else
    {    
        tmp = ntohl(p_tcp->seq) + apd_len;
    }

    return htonl(tmp);
}
/*
static int get_option(char* raw)
{
    struct tcphdr* p_tcp;
    struct iphdr* p_ip;
    char* p = raw;

    p = raw + sizeof(struct ether_header) + sizeof(struct iphdr);

    p_tcp = (struct tcphdr*)p;

    option_len = ((p_tcp->doff)<<2)  - sizeof(struct tcphdr);
    
    if(option_len > 0)
    {
        char* src = (char*)p_tcp + sizeof(struct tcphdr);
        memcpy(option, src, option_len);
    }
    else
    {
        return -1;
    }
    return 0;
}
*/
static int mac_aton(char* mac_src,uint8_t* mac, int len)
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
int build_ether(char* pkt, char* dmac, char* smac, int type, int len)
{
    if( len < 1500)
    {
        fprintf(stderr, "buffer is too small!\n");
        return -1;
    }
    uint8_t s_mac[8];
    bzero(s_mac, 8);
    mac_aton(smac, s_mac, 8);
    uint8_t d_mac[8];
    bzero(d_mac, 8);
    mac_aton(dmac, d_mac, 8);
    struct ether_header eth_header;
    memcpy(eth_header.ether_dhost, d_mac, 6);
    memcpy(eth_header.ether_shost, s_mac, 6);
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
        total_len = (ip_header.ihl<<2) + sizeof(struct udphdr) +  apd_len;
    }
    ip_header.tot_len = htons(total_len); 
    ip_header.id = get_ip_id();  //标识字段
    ip_header.frag_off = htons(0x4000);  //不分片
    ip_header.ttl = 64;
    ip_header.protocol = protocol;
    ip_header.check = 0; 
    ip_header.saddr = inet_addr(sip);
    ip_header.daddr = inet_addr(dip);
    ip_header.check = ip_check_ext((uint16_t*)&ip_header, ip_header.ihl<<2, 0); 
    memcpy(p_ip, &ip_header, sizeof(ip_header));
    return 0;
}
int build_tcp(char* p_tcp, char* sip, char* dip, uint16_t dport, int8_t flags, char* apd, int apd_len)
{
    struct tcphdr tcp_header;
    //int max_segment_len = 0;
    uint32_t saddr = inet_addr(sip);
    uint32_t daddr = inet_addr(dip);
    bzero(&tcp_header, sizeof(tcp_header));
    tcp_header.source = get_src_port(); 
    tcp_header.dest = htons(dport);
    if( flags == TCP_SYN)
    {
        tcp_header.seq = init_seq();
    }
    else
    {
        tcp_header.seq = private_seq;
    }
    if(flags == TCP_SYN)
    {
        tcp_header.ack_seq = 0;
    }
    else
    {
        tcp_header.ack_seq = private_ack;
    }
    /*
    if(option_flag == 1)
    {
        max_segment_len  = ntohl(MSS);
        option_len = 4;
        tcp_header.doff = ( (uint32_t)sizeof(struct tcphdr) + option_len) >> 2;
    }
    else
    {
        tcp_header.doff = ( (uint32_t)sizeof(struct tcphdr))>>2;
    }
    */
    tcp_header.doff = ( (uint32_t)sizeof(struct tcphdr))>>2;
    memcpy((char*)&tcp_header + 13, &flags, 1);   //tcp_flags 置位 注意&tcp_header + 13移动的不是13个字节 
    tcp_header.window = htons(4096);
    tcp_header.check = 0;
    tcp_header.urg_ptr = 0;
    //tcp_header.check = my_tcp_check((char*)&tcp_header, (tcp_header.doff <<2)+apd_len , saddr,  daddr);
    memcpy(p_tcp, &tcp_header, sizeof(tcp_header));
    //if(option_len > 0)
    //{
        //memcpy(p_tcp + sizeof(tcp_header), &max_segment_len, option_len);
        //option_len = 0;
    //}
    if(apd != NULL && apd_len != 0)
    { 
        memcpy(p_tcp + sizeof(tcp_header), apd, apd_len);
    } 
    tcp_header.check = my_tcp_check(p_tcp, (tcp_header.doff <<2)+apd_len , saddr,  daddr);
    ( (struct tcphdr*)p_tcp )->check = tcp_header.check;  
    return 0;
}
int build_l2_packet(pkt_key_t* key, char* pkt, int buf_len,  char* apd, int apd_len, int* pkt_len,  uint8_t flags)
{ 
    if(flags == -1 && key->trans_protocol == 6)
    {
        fprintf(stderr, "flags don't matcher trans_protocol!\n");
        return -1;
    }
    uint8_t tcp_flags;    
    tcp_flags = flags; 
    if(buf_len < apd_len || apd_len > 1460)
    {
        fprintf(stderr, "apd_len is too long!\n");
        return -1;
    }
    build_ether(pkt, key->dmac, key->smac, htons(key->l3_protocol), 2048);
    build_ipv4(pkt + sizeof(struct ether_header),key->saddr, key->daddr,  6, apd_len ); 
    build_tcp(pkt + sizeof(struct ether_header)+sizeof(struct iphdr), key->saddr, key->daddr, key->dport, tcp_flags, apd, apd_len);
    *pkt_len = sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct tcphdr) + apd_len;
    return 0;
}
int init_pkt_key(pkt_key_t* key, char* saddr, char* daddr, char* smac, char* dmac, int16_t dport, uint16_t ether_type, uint8_t protocol)
{
    bzero(key, sizeof(key));   
    strcpy(key->saddr, saddr); 
    strcpy(key->daddr, daddr);
    strcpy(key->smac, smac);
    strcpy(key->dmac, dmac);
    key->dport = dport;

    key->l3_protocol = ether_type;

    key->trans_protocol = protocol;
    return 0;
}
/*
int send_l2_packet(char* dev, char* apd, int apd_len, uint8_t flags)
{
    pkt_key_t key;
    init_pkt_key(&key, SIP, DIP, SRC_MAC, DST_MAC, DPORT, H_IP, H_TCP); 
    char pkt[2048];
    bzero(pkt, 2048);
    int pkt_len = 0;
    build_l2_packet(&key, pkt, 2048, NULL, 0, &pkt_len, TCP_SYN);
    pcap_t* handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    bzero(errbuf, PCAP_ERRBUF_SIZE);
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if(handle == NULL)
    {
        fprintf(stderr, "Couldn't open device %s:%s\n", dev, errbuf);
        return -1;
    }
    struct bpf_program fp;
    
    char filter_exp[64];
    bzero(filter_exp, 64);
    sprintf(filter_exp, "port %d", DPORT);

    return 0;
}
*/
static stack_apd_t* get_apd_wptr()
{
    if(rb_canWrite(write_apd) == 1)
    {
        return (& (rb_writePeek(write_apd, stack_apd_t) ) );
    }
    else
    {
        return NULL;
    }
}
static stack_apd_t* get_apd_rptr()
{
    if(rb_canRead(read_apd) == 1)
    {
        return &(rb_readPeek(read_apd, stack_apd_t) ); 
    }
    else
    {
        return NULL;
    }
}
int init_stack(pcap_t** phandle)
{
    pcap_t* handle;
    char dev[] = NET_DEVICE;

    char errbuf[PCAP_ERRBUF_SIZE];
    
    struct bpf_program fp;

    char filter_exp[] = APP;

    bpf_u_int32 mask;

    bpf_u_int32 net;
    //struct pcap_pkthdr header;

    //const u_char* raw;
    if(pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
    {
        fprintf(stderr, "Can't get netmask for device %s\n", dev);
        net = 0;
        mask = 0;
    }
    handle = pcap_open_live(dev, BUFSIZ, 1, 100, errbuf);
    if(handle == NULL)
    {
        fprintf(stderr, "Couldn't open device %s:%s\n", dev, errbuf);
        return -1;
    }
    if(pcap_compile(handle, &fp, filter_exp, 0, net) == -1)
    {
        fprintf(stderr, "Couldn't parse filter %s:%s\n", filter_exp, pcap_geterr(handle));
        return -1;
    }

    if(pcap_setfilter(handle, &fp) == -1)
    {
        fprintf(stderr, "Couldn't install filter %s:%s\n", filter_exp, pcap_geterr(handle));
        return -1;
    }
    write_apd = rb_create(4096, sizeof(stack_apd_t), write_apd);//初始化协议栈缓冲区
    read_apd = rb_create(4096, sizeof(stack_apd_t), read_apd); //初始化协议栈缓冲区
    *phandle = handle;              //初始化
    return 0;
}
void* stack_run(void* arg)
{
    pcap_t* handle;
    init_stack(&handle);
    
    int ret = 0;
    pkt_key_t key;
    init_pkt_key(&key, SIP, DIP, SRC_MAC, DST_MAC, DPORT, H_IP, H_TCP); 
    char pkt[2048];
    int pkt_len = 0;
    char* raw;
    struct ether_header* p_eth;
    struct iphdr* p_ip;
    struct tcphdr* p_tcp;
    struct pcap_pkthdr header;
    stack_apd_t* pwrite = NULL;
    stack_apd_t* pread = NULL;
    char* apd = NULL;
    uint32_t apd_len = 0;
    while(1)
    {
        bzero(pkt, 2048);
        if(syn_flag == 0)    //还没发送SYN包
        {
            build_l2_packet(&key, pkt, 2048, NULL, 0, &pkt_len, TCP_SYN);
            ret = pcap_sendpacket(handle, pkt, pkt_len);
            if(ret < 0) 
            {
                fprintf(stderr, "send packet failed!\n");
            }
            raw = pcap_next(handle, &header);       
            private_seq = get_seq(raw);        //写入全局变量中
            private_ack = get_ack(raw);
            //第三个握手包
            build_l2_packet(&key, pkt, 2048, NULL, 0, &pkt_len, TCP_ACK);
            ret = pcap_sendpacket(handle, pkt, pkt_len);
            if(ret < 0)
            {
                fprintf(stderr, "send packet failed!\n");
            }
            syn_flag = 1;   //三次握手成功之后，设置为1
        }
        if(syn_flag == 1)
        {
                pread = get_apd_rptr();
                if(pread != NULL)
                {
                    apd = pread->buf;
                    apd_len = pread->buf_len;
                    build_l2_packet(&key, pkt, 2048, apd, apd_len, &pkt_len,  TCP_ACK);
                    ret = pcap_sendpacket(handle, pkt, pkt_len);
                    if(ret < 0)
                    {
                        fprintf(stderr, "send packet failed!\n");
                    }
                }
                else                 //如果没有发送任务
                {
                    raw = pcap_next(handle, &header);       
                    if(raw == NULL) //100ms之内都没有数据包到来
                    {
                        continue;   
                    }
                    else
                    {
                        private_seq = get_seq(raw);        //写入全局变量中
                        private_ack = get_ack(raw);
                        build_l2_packet(&key, pkt, 2048, NULL, 0, &pkt_len, TCP_ACK);
                        ret = pcap_sendpacket(handle, pkt, pkt_len);
                        if(ret < 0)
                        {
                            fprintf(stderr, "send pakcket failed! [%s:%d]\n",
                                    __func__, __LINE__);
                        }

                    }
                    
                }
        }
    }
    
}

int main(int argc, char* argv[])
{
    //write_pcap_handle_t handle;

   //init_pcap_handle_line(&handle, "test.pcap");
  //write_pcap_data_line(&handle, pkt, pkt_len);
    pthread_t th1;
    pthread_create(&th1, NULL, stack_run, NULL);    
    pthread_join(th1, NULL);    
    return 0;
    

}
