﻿#ifndef __RING_BUFFER__
#define __RING_BUFFER__

/** @file
 *  本文件中包含了环形队列库的所有外部接口宏。
 *
 *  环形队列库的所有外部接口都是以宏的形式出现的。实际上整个环形队列库仅由本头文件构成。
 *  <p>一个环形队列逻辑上是由一个数组、一个读指针和一个写指针构成的。
 *  <p>读指针指示的是下一次将被读取的元素的下标，写指针指示的是下一次被写入队列的元素的下标。
 *  <p>当读指针等于写指针时，表示队列为空。当写指针将指向的下一个为位置为读指针指示位置时，表示队列为满。
 *  <p>每次向队列中写入一个元素时，直接将写入的元素被放置到写指针所在位置，然后写指针将向前移动一个位置。
 *  <p>每次从队列读取一个元素时，将直接取读指针所指位置的元素，然后读指针将向前移动一个位置。
 *  
 *  <p>在本次实现环形队列的时候，除了环形队列的基本功能之外，还考虑到了下列2个常见的需求：
 *  <ol>
 *	<li>放置在环形队列中的元素应该可以是任何类型。对于环形队列来说，数据类型之间的区别仅表现为所占空间的大小不同。如一个由整数构成的环形队列和一个由短整数构成的环形队列从逻辑上说可执行的操作是相同，只是在实现时需要考虑到数据类型的不同；</li>
 *  <li>为了将环形队列与其他应用方便的集成起来，不总是需要由环形队列自己来分配内存。</li>
 *  </ol>
 * 
 *  <p>在本次实现中，环形队列在内存中的结构如下图所示：
 *  <pre>
 *┌─────────┐
 *│       rsize      │
 *├─────────┤
 *│       bsize      │
 *├─────────┤
 *│        wp        │
 *├─────────┤
 *│        rp        │
 *├─────────┤
 *│  环形队列的元素  │
 *│    ..........    │
 *│                  │
 *│                  │
 *│                  │
 *│                  │
 *│                  │
 *│                  │
 *└─────────┘
 * </pre>
 */

#include <malloc.h>

/** 代表环形队列的结构。
 *  用户使用环形队列库时并不需要直接使用该结构。
 */
typedef struct __ring_buffer
{
	int rsize;	/**< 保存环形队列中元素的个数。在一个环形队列中能够保存元素的最大数量是rsize-1。*/
	int bsize;	/**< 保存环形队列中每个元素所占空间的大小。*/
	volatile int wp;	/**< wp是写指针。 */
	volatile int rp;	/**< rp是读指针。 */
}RING_BUFFER;

/** PRING_BUFFER被定义为RING_BUFFER*	*/
typedef RING_BUFFER* PRING_BUFFER;

/** @def rb_memory_required(rs, bs)
 *  计算一个包含\a rs 个\a bs 大小的元素的环形队列所需要占用的内存大小。
 *  该宏的值就是所需内存大小。
 */
#define rb_memory_required(rs, bs) (sizeof(RING_BUFFER) + (bs) * ((rs)+1))

/** @def rb_initialize(rs, bs, pbuf)
 *  在\a pbuf 所指向的内存中，初始化一个包括\a rs 个\a bs 大小的元素的环形队列。所有环形队列在使用之前都必须首先由\a rb_initialize 进行初始化。
 *  该宏的值为0时表示初始化不成功，否则表示初始化成功。成功初始化之后，rp和wp都为0，表示队列为空。
 */
#define rb_initialize(rs, bs, pbuf)	\
	((pbuf)==0 ? 0 : (((PRING_BUFFER)(pbuf))->bsize = (bs), ((PRING_BUFFER)(pbuf))->rsize = (rs)+1, ((PRING_BUFFER)(pbuf))->rp = ((PRING_BUFFER)(pbuf))->wp = 0, (pbuf)))

/** @def rb_create(rs, bs, pbuf)
 *  根据\a rs 和 \a bs 生成一个环形队列，\a pbuf 指向生成之后的环形队列。
 *  该宏的值为0时表示生成不成功，否则表示生成成功。
 */ 
#define rb_create(rs, bs, pbuf) (pbuf=malloc(rb_memory_required(rs, bs)), rb_initialize(rs, bs, pbuf))

/** @def rb_incPtr(prb, ptr)
 *  将\a prb 的值向加1，如果加1之后\a prb 的值不小于\a rsize 则\a prb 置为0。\a ptr 指向一个成功初始化的环形队列。
 *  该宏的值为增1之后prb的值。
 */
#define rb_incPtr(prb, ptr) ((ptr)=(((ptr)+1)%(((PRING_BUFFER)(prb))->rsize)))   //

/** @def rb_canRead(prb)
 *  判断是否可从\a prb 所指向的环形队列中读出元素。
 *  该宏的值为0时，表示不可读。否则表示可读。
 */
#define rb_canRead(prb) (((PRING_BUFFER)(prb))->wp != ((PRING_BUFFER)(prb))->rp)  //读指针等于写指针，表示队列为空

/** @def rb_canWrite(prb)
 *  判断是否可以向\a prb 所指向的环形队列中写入元素。
 *  该宏的值为0时，表示不可写。否则表示可以写。
 */
#define rb_canWrite(prb) (((((PRING_BUFFER)(prb))->wp + 1) % (((PRING_BUFFER)(prb))->rsize)) != ((PRING_BUFFER)(prb))->rp)  //因为环形队列空出一个位置，不放元素，所以判断队列满时,(wp+1)%rsize == rp

/** @def rb_dataBuffer(prb, T)
 *  返回环形队列中队列元素数组的首地址。\a prb 指向环形队列，\a T 为元素的类型。
 */
#define rb_dataBuffer(prb, T) ((T*)(((unsigned char*)(prb))+sizeof(RING_BUFFER)))  //队列头部有一个结构体RING_BUFFER

/** @def rb_writePeek(prb, T)
 *  取回将写的元素。\a prb 指向环形队列，\a T 为元素的类型。
 */ 
#define rb_writePeek(prb, T) (rb_dataBuffer(prb, T)[((PRING_BUFFER)(prb))->wp]) //运用[]运算符

/** @def rb_readPeek(prb, T)
 *  取回将读的元素。\a prb 指向环形队列，\a T 为元素的类型。
 */ 
#define rb_readPeek(prb, T) (rb_dataBuffer(prb, T)[((PRING_BUFFER)(prb))->rp])   //运用[]运算符

/** @def rb_writeIn(prb)
 *  向前移动写指针，完成写操作。\a prb 指向环形队列。
 */ 
#define rb_writeIn(prb) rb_incPtr((prb), ((PRING_BUFFER)(prb))->wp)

/** @def rb_readOut(prb)
 *  向前移动读指针，完成读操作。\a prb 指向环形队列。
 */
#define rb_readOut(prb) rb_incPtr((prb), ((PRING_BUFFER)(prb))->rp) 

/** @def rb_writeInValue(prb, T, V)
 *  向\a prb 所指向的环形队列中写入一个类型为\a T ，值为\a V 的元素。
 */ 
#define rb_writeInValue(prb, T, V) (rb_canWrite(prb) ? ((rb_writePeek(prb, T))=(V), rb_writeIn(prb), 1): 0) //写入元素，并且写指针++

/** @def rb_readOutValue(prb, T, V)
 *  从\a prb 所指向的环形队列中读取一个类型为\a T ，值为\a V 的元素。
 */
#define rb_readOutValue(prb, T, V) (rb_canRead(prb)  ? ((V)=(rb_readPeek(prb,T)), rb_readOut(prb), 1): 0)

#define rb_occupied_slots(prb) ((((PRING_BUFFER)(prb))->wp - ((PRING_BUFFER)(prb))->rp+((PRING_BUFFER)(prb))->rsize) % (((PRING_BUFFER)(prb))->rsize))
#define rb_empty_slots(prb) (((PRING_BUFFER)(prb))->rsize - rb_occupied_slots(prb) - 1)
#endif

