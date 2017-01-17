/**
 *  Filename: nbk.h
 *   Created: 2014-10-30 18:28:56
 *      Desc: TODO (some description)
 *    Author: xutao(Tony Xu), xu.tao@ampthon.com
 *   Company: Tianyuan Tetong
 */
#ifndef NBK_H
#define NBK_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <limits.h>
#include <inttypes.h>

#include <sys/time.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <endian.h>
#include <signal.h>
#include <pthread.h>

#include <iconv.h>
#include <zlib.h>

#define NBK_OK      0
#define NBK_ERROR   -1

#define NBK_MAX_FILENAME_LEN 255

#define NBK_BLOCK           0
#define NBK_REINJECTION_ALL 1
#define NBK_WATCH           2
#define NBK_FORCE_PUSH      3
#define NBK_IGNORE          4
#define NBK_BIND            5

/** nbk */
#include "nbk_malloc.h"
#include "nbk_string.h"
#include "nbk_errno.h"
// #include "nbk_log.h"
#include "nbk_util.h"
#include "nbk_chunk.h"
#include "nbk_iconv.h"
#include "nbk_url.h"
#include "nbk_zip.h"
#include "nbk_base64.h"
#include "nbk_inet.h"
#include "nbk_lock.h"
//#include "nbk_rb.h"
#include "nbk_time.h"
#include "nbk_vshell.h"

#endif /* end of include guard: NBK_H */
