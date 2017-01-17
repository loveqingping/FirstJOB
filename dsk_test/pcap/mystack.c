#include "mystack.h"
#include "checksum.h"
#define APP_PORT 80
int stack_run(char* net_interface, node_pool* pool, user_session_pool* us, tcp_callback tcp_cb)
{
	char error_content[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr protocol_header;
	pcap_t* pcap_handle;
	const u_char* packet_content;
	bpf_u_int32 net_mask;
	bpf_u_int32 net_ip;
	
	struct in_addr saddr;
	struct in_addr daddr;
	
	char source_ip[64];
	char dest_ip[64];

	struct ether_header* eptr;  //以太网帧
	struct iphdr* ipptr;   //ip数据报
	struct in_addr addr;
	struct tcphdr* tcpptr; //tcp
	char* data;
	tuple5 t5;	
	int app_len;
	void** session;
	tcp_stream_t stream;
	node* pnode;
	pcap_handle = pcap_open_live(net_interface, BUFSIZ, 1,0,error_content);
	fprintf(stderr,"pcap_handle %p\n",pcap_handle);
	while(1)
	{
		
		packet_content = pcap_next(pcap_handle, &protocol_header);
		//fprintf(stderr,"packet_content %p\n",packet_content);
		eptr = (struct ether_header*)packet_content;

		if(ntohs(eptr->ether_type ) == ETHERTYPE_IP)  //IP类型
		{
			ipptr = (struct ipptr*)((char*)packet_content + sizeof(struct ether_header));  //IP数据报
			//t5.saddr = ntohl(ipptr->saddr);
			//t5.daddr = ntohl(ipptr->daddr);
			fprintf(stdout,"check_sum:%d\n",ipptr->check);
			int iphdr_len = (ipptr->ihl << 2);
			fprintf(stdout,"header len %d\n",iphdr_len);
			uint16_t checksum = ip_check_ext((uint16_t*)ipptr, iphdr_len,0);
			fprintf(stdout,"check_sum2:%d\n",checksum);
			t5.saddr = ipptr->saddr;
			t5.daddr = ipptr->daddr;
			saddr.s_addr = t5.saddr;
			daddr.s_addr = t5.daddr;
			if(ipptr->protocol == 6)  //这里是不是有点问题
			{
				
				tcpptr = (struct tcphdr*)(packet_content + sizeof(struct ether_header) + sizeof(struct iphdr));
					
				if( (tcpptr->syn == 1) && (tcpptr->ack == 0) )  //客户端发起的新连接
				{
						
				}
				t5.source = ntohs(tcpptr->source);   //获取源端口
				t5.dest = ntohs(tcpptr->dest);     //获取目的端口
				t5.protocol = (uint32_t)ipptr->protocol;  //获取协议号 
				bzero(source_ip,64);
				bzero(dest_ip,64);
				memcpy(source_ip,inet_ntoa(saddr),strlen(inet_ntoa(saddr)) );
				memcpy(dest_ip,inet_ntoa(daddr),strlen(inet_ntoa(saddr)) );
				
				fprintf(stderr,"source :%d dest:%d saddr:%s daddr:%s protocol:%d\n",t5.source,t5.dest,source_ip,dest_ip,t5.protocol);
				if( (pnode = node_pool_find(pool,&t5)) != NULL )   //源地址和目的地址对调，也算是
				{
					session = &(pnode->user_session->self);
				}
				else
				{
					pnode = node_pool_get(pool);  //加入到t5链表
					pnode->key = t5;
					pnode->user_session = user_session_pool_get(us);
					session = &(pnode->user_session->self);
				}
				if(ntohs(tcpptr->dest) == APP_PORT || ntohs(tcpptr->source) == APP_PORT)
				{
					data = (char*)(packet_content + sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct tcphdr));
				
					if( (tcpptr->syn == 1) && (tcpptr->ack == 0) )  //客户端发起的新连接
					{
						pnode->user_session->stream_flag = t5;      //将C2S 的DIR保存 
					}
					if(0 == memcmp(&(pnode->user_session->stream_flag), &t5,sizeof(t5)) )   //将当前数据包的五元组同之前保存的五元组进行比较
					{
						stream.flag = C2S_DATA;
						printf("C2S_DATA\n");
					}
					else
					{
						stream.flag = S2C_DATA;
						printf("S2C_DATA\n");
					}
					/*
					if(t5.dest > 1024)
					{
						stream.flag = C2S_DATA;
						fprintf(stderr,"C2S_DATA\n");
						app_len = ntohs(ipptr->tot_len) - (ipptr->ihl)*4 - sizeof(struct tcphdr);
						if(app_len > 0);
						{
							memcpy(stream.toserver,data,app_len);
							stream.toserver_len = app_len;
						}
					}
					else
					{
						fprintf(stderr,"S2C_DATA\n");
						stream.flag = S2C_DATA;
						app_len = ntohs(ipptr->tot_len) - (ipptr->ihl)*4 - sizeof(struct tcphdr);
						if(app_len > 0);
						{
							memcpy(stream.toclient,data,app_len);
							stream.toclient_len = app_len;
						}

					}
					*/
					if(app_len > 0)
					{
						tcp_cb(&stream,session);
					}
				}
			}
		}
	}
	return 0;
}
