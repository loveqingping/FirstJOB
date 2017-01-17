#ifndef MY_STACK_H
#define MY_STACK_H
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <string.h>
#include "pcap.h"
#include "user_session.h"
#include "node.h"
#define C2S_DATA 1
#define S2C_DATA 2
typedef struct _tcp_stream
{
	int flag;
	char toserver[2048];
	uint32_t toserver_len;
	char toclient[2048];
	uint32_t toclient_len;
}tcp_stream_t;
typedef int (*tcp_callback) (tcp_stream_t* ts,void** pme);
int stack_run(char* net_interface, node_pool* pool,user_session_pool* us,tcp_callback tcp_cb);
#endif
