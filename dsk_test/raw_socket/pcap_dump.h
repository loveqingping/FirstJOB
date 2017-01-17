#ifndef __MOG_PCAP__
#define __MOG_PCAP__
#include <stdint.h>
#include <pcap.h>
#include <time.h>


typedef struct __write_pcap_handle_t
{
    char filename[256];
    struct pcap_file_header  pcap_header;
    struct pcap_pkthdr       pkthdr;
    pcap_t *pcap;
    pcap_dumper_t *pcap_fp;
}write_pcap_handle_t;

void init_pcap_handle_line(write_pcap_handle_t * wpcap_handle, char * filename);
void write_pcap_data_line(write_pcap_handle_t * wpcap_handle, char * buff, int32_t len);
#endif