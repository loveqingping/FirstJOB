#include "pcap_dump.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init_pcap_handle_line(write_pcap_handle_t *wpcap_handle, char * filename)
{
	strcpy(wpcap_handle->filename, filename);
	wpcap_handle->pcap_header.magic=0xa1b2c3d4;
	wpcap_handle->pcap_header.version_major=0x0002;
	wpcap_handle->pcap_header.version_minor=0x0004;
	wpcap_handle->pcap_header.thiszone=0;
	wpcap_handle->pcap_header.sigfigs=0;
	wpcap_handle->pcap_header.snaplen=65535;
	wpcap_handle->pcap_header.linktype=1;

	wpcap_handle->pcap = NULL;
	wpcap_handle->pcap_fp = NULL;

	wpcap_handle->pcap = pcap_open_dead(1, 4096);
}
void write_pcap_data_line(write_pcap_handle_t *wpcap_handle, char * buff, int32_t len)
{
	uint64_t now;

	now = time(NULL);

	if(strncmp(wpcap_handle->filename, "none", 4) == 0)
	{
		if(wpcap_handle->pcap_fp)
		{
			pcap_dump_close(wpcap_handle->pcap_fp);
			wpcap_handle->pcap_fp = NULL;
		}
	}
	else
	{
		if(!wpcap_handle->pcap_fp)
		{
			wpcap_handle->pcap_fp = pcap_dump_open(wpcap_handle->pcap, wpcap_handle->filename);
			if (wpcap_handle->pcap_fp == NULL)
			{
				return;
			}
		}
		/*写入包头和包体*/
		wpcap_handle->pkthdr.ts.tv_sec=time(NULL);
		wpcap_handle->pkthdr.ts.tv_usec=0;
		wpcap_handle->pkthdr.caplen=len;
		wpcap_handle->pkthdr.len=len;

		pcap_dump((u_char *)wpcap_handle->pcap_fp, &wpcap_handle->pkthdr, (const u_char *)buff);
		
		fflush((FILE *)(wpcap_handle->pcap_fp));
	}
}
