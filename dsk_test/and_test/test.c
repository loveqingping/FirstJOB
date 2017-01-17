/**
 *  Filename: test.c
 *   Created: 2016-05-05 10:05:36
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct tcphdr
{
    uint16_t th_sport;          /* source port */
    uint16_t th_dport;          /* destination port */
    uint32_t th_seq;            /* sequence number */
    uint32_t th_ack;            /* acknowledgement number */
    #if __BYTE_ORDER == __LITTLE_ENDIAN
        uint8_t th_x2:4;        /* (unused) */
        uint8_t th_off:4;       /* data offset */
    #elif __BYTE_ORDER == __BIG_ENDIAN
        uint8_t th_off:4;       /* data offset */
        uint8_t th_x2:4;        /* (unused) */
    #endif

    uint8_t th_flags;
    #define TH_FIN    0x01
    #define TH_SYN    0x02
    #define TH_RST    0x04
    #define TH_PUSH   0x08
    #define TH_ACK    0x10
    #define TH_URG    0x20

    uint16_t th_win;            /* window */
    uint16_t th_sum;            /* checksum */
    uint16_t th_urp;            /* urgent pointer */
}tcphdr_t;
int main(int argc, char* argv[])
{
    tcphdr_t tcphdr;
    tcphdr_t* p = &tcphdr;
    p->th_flags  = 0;
    p->th_flags |= TH_FIN;
    if(p->th_flags & TH_SYN)
    {
        printf("This is a syn packet!\n");
    }
    else if(p->th_flags & TH_FIN)
    {
        printf("This is a fin packet!\n");
    }
    return 0;
}
