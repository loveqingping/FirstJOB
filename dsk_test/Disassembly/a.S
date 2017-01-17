
a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000400358 <_init>:
  400358:	48 83 ec 08          	sub    $0x8,%rsp
  40035c:	e8 5b 00 00 00       	callq  4003bc <call_gmon_start>
  400361:	e8 ea 00 00 00       	callq  400450 <frame_dummy>
  400366:	e8 05 02 00 00       	callq  400570 <__do_global_ctors_aux>
  40036b:	48 83 c4 08          	add    $0x8,%rsp
  40036f:	c3                   	retq   

Disassembly of section .plt:

0000000000400370 <__libc_start_main@plt-0x10>:
  400370:	ff 35 ea 04 20 00    	pushq  0x2004ea(%rip)        # 600860 <_GLOBAL_OFFSET_TABLE_+0x8>
  400376:	ff 25 ec 04 20 00    	jmpq   *0x2004ec(%rip)        # 600868 <_GLOBAL_OFFSET_TABLE_+0x10>
  40037c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400380 <__libc_start_main@plt>:
  400380:	ff 25 ea 04 20 00    	jmpq   *0x2004ea(%rip)        # 600870 <_GLOBAL_OFFSET_TABLE_+0x18>
  400386:	68 00 00 00 00       	pushq  $0x0
  40038b:	e9 e0 ff ff ff       	jmpq   400370 <_init+0x18>

Disassembly of section .text:

0000000000400390 <_start>:
  400390:	31 ed                	xor    %ebp,%ebp
  400392:	49 89 d1             	mov    %rdx,%r9
  400395:	5e                   	pop    %rsi
  400396:	48 89 e2             	mov    %rsp,%rdx
  400399:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40039d:	50                   	push   %rax
  40039e:	54                   	push   %rsp
  40039f:	49 c7 c0 d0 04 40 00 	mov    $0x4004d0,%r8
  4003a6:	48 c7 c1 e0 04 40 00 	mov    $0x4004e0,%rcx
  4003ad:	48 c7 c7 97 04 40 00 	mov    $0x400497,%rdi
  4003b4:	e8 c7 ff ff ff       	callq  400380 <__libc_start_main@plt>
  4003b9:	f4                   	hlt    
  4003ba:	90                   	nop
  4003bb:	90                   	nop

00000000004003bc <call_gmon_start>:
  4003bc:	48 83 ec 08          	sub    $0x8,%rsp
  4003c0:	48 8b 05 89 04 20 00 	mov    0x200489(%rip),%rax        # 600850 <_DYNAMIC+0x190>
  4003c7:	48 85 c0             	test   %rax,%rax
  4003ca:	74 02                	je     4003ce <call_gmon_start+0x12>
  4003cc:	ff d0                	callq  *%rax
  4003ce:	48 83 c4 08          	add    $0x8,%rsp
  4003d2:	c3                   	retq   
  4003d3:	90                   	nop
  4003d4:	90                   	nop
  4003d5:	90                   	nop
  4003d6:	90                   	nop
  4003d7:	90                   	nop
  4003d8:	90                   	nop
  4003d9:	90                   	nop
  4003da:	90                   	nop
  4003db:	90                   	nop
  4003dc:	90                   	nop
  4003dd:	90                   	nop
  4003de:	90                   	nop
  4003df:	90                   	nop

00000000004003e0 <__do_global_dtors_aux>:
  4003e0:	55                   	push   %rbp
  4003e1:	48 89 e5             	mov    %rsp,%rbp
  4003e4:	53                   	push   %rbx
  4003e5:	48 83 ec 08          	sub    $0x8,%rsp
  4003e9:	80 3d 90 04 20 00 00 	cmpb   $0x0,0x200490(%rip)        # 600880 <completed.6347>
  4003f0:	75 4b                	jne    40043d <__do_global_dtors_aux+0x5d>
  4003f2:	bb b0 06 60 00       	mov    $0x6006b0,%ebx
  4003f7:	48 8b 05 8a 04 20 00 	mov    0x20048a(%rip),%rax        # 600888 <dtor_idx.6349>
  4003fe:	48 81 eb a8 06 60 00 	sub    $0x6006a8,%rbx
  400405:	48 c1 fb 03          	sar    $0x3,%rbx
  400409:	48 83 eb 01          	sub    $0x1,%rbx
  40040d:	48 39 d8             	cmp    %rbx,%rax
  400410:	73 24                	jae    400436 <__do_global_dtors_aux+0x56>
  400412:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  400418:	48 83 c0 01          	add    $0x1,%rax
  40041c:	48 89 05 65 04 20 00 	mov    %rax,0x200465(%rip)        # 600888 <dtor_idx.6349>
  400423:	ff 14 c5 a8 06 60 00 	callq  *0x6006a8(,%rax,8)
  40042a:	48 8b 05 57 04 20 00 	mov    0x200457(%rip),%rax        # 600888 <dtor_idx.6349>
  400431:	48 39 d8             	cmp    %rbx,%rax
  400434:	72 e2                	jb     400418 <__do_global_dtors_aux+0x38>
  400436:	c6 05 43 04 20 00 01 	movb   $0x1,0x200443(%rip)        # 600880 <completed.6347>
  40043d:	48 83 c4 08          	add    $0x8,%rsp
  400441:	5b                   	pop    %rbx
  400442:	c9                   	leaveq 
  400443:	c3                   	retq   
  400444:	66 66 66 2e 0f 1f 84 	data32 data32 nopw %cs:0x0(%rax,%rax,1)
  40044b:	00 00 00 00 00 

0000000000400450 <frame_dummy>:
  400450:	48 83 3d 60 02 20 00 	cmpq   $0x0,0x200260(%rip)        # 6006b8 <__JCR_END__>
  400457:	00 
  400458:	55                   	push   %rbp
  400459:	48 89 e5             	mov    %rsp,%rbp
  40045c:	74 12                	je     400470 <frame_dummy+0x20>
  40045e:	b8 00 00 00 00       	mov    $0x0,%eax
  400463:	48 85 c0             	test   %rax,%rax
  400466:	74 08                	je     400470 <frame_dummy+0x20>
  400468:	bf b8 06 60 00       	mov    $0x6006b8,%edi
  40046d:	c9                   	leaveq 
  40046e:	ff e0                	jmpq   *%rax
  400470:	c9                   	leaveq 
  400471:	c3                   	retq   
  400472:	90                   	nop
  400473:	90                   	nop

0000000000400474 <test>:
#include <stdio.h>
int test(int a, int b)
{
  400474:	55                   	push   %rbp
  400475:	48 89 e5             	mov    %rsp,%rbp
  400478:	89 7d fc             	mov    %edi,-0x4(%rbp)
  40047b:	89 75 f8             	mov    %esi,-0x8(%rbp)
	a = 3;
  40047e:	c7 45 fc 03 00 00 00 	movl   $0x3,-0x4(%rbp)
	b = 4;
  400485:	c7 45 f8 04 00 00 00 	movl   $0x4,-0x8(%rbp)
	return a + b;
  40048c:	8b 45 f8             	mov    -0x8(%rbp),%eax
  40048f:	8b 55 fc             	mov    -0x4(%rbp),%edx
  400492:	8d 04 02             	lea    (%rdx,%rax,1),%eax
}
  400495:	c9                   	leaveq 
  400496:	c3                   	retq   

0000000000400497 <main>:
int main(int argc, char* argv[])
{
  400497:	55                   	push   %rbp
  400498:	48 89 e5             	mov    %rsp,%rbp
  40049b:	48 83 ec 20          	sub    $0x20,%rsp
  40049f:	89 7d ec             	mov    %edi,-0x14(%rbp)
  4004a2:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
	int a = 1;
  4004a6:	c7 45 f8 01 00 00 00 	movl   $0x1,-0x8(%rbp)
	int b = 2;
  4004ad:	c7 45 fc 02 00 00 00 	movl   $0x2,-0x4(%rbp)
	test(1, 2);
  4004b4:	be 02 00 00 00       	mov    $0x2,%esi
  4004b9:	bf 01 00 00 00       	mov    $0x1,%edi
  4004be:	e8 b1 ff ff ff       	callq  400474 <test>
	return 0;
  4004c3:	b8 00 00 00 00       	mov    $0x0,%eax
}
  4004c8:	c9                   	leaveq 
  4004c9:	c3                   	retq   
  4004ca:	90                   	nop
  4004cb:	90                   	nop
  4004cc:	90                   	nop
  4004cd:	90                   	nop
  4004ce:	90                   	nop
  4004cf:	90                   	nop

00000000004004d0 <__libc_csu_fini>:
  4004d0:	f3 c3                	repz retq 
  4004d2:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  4004d9:	1f 84 00 00 00 00 00 

00000000004004e0 <__libc_csu_init>:
  4004e0:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  4004e5:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  4004ea:	48 8d 2d a3 01 20 00 	lea    0x2001a3(%rip),%rbp        # 600694 <__init_array_end>
  4004f1:	4c 8d 25 9c 01 20 00 	lea    0x20019c(%rip),%r12        # 600694 <__init_array_end>
  4004f8:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  4004fd:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  400502:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  400507:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  40050c:	48 83 ec 38          	sub    $0x38,%rsp
  400510:	4c 29 e5             	sub    %r12,%rbp
  400513:	41 89 fd             	mov    %edi,%r13d
  400516:	49 89 f6             	mov    %rsi,%r14
  400519:	48 c1 fd 03          	sar    $0x3,%rbp
  40051d:	49 89 d7             	mov    %rdx,%r15
  400520:	e8 33 fe ff ff       	callq  400358 <_init>
  400525:	48 85 ed             	test   %rbp,%rbp
  400528:	74 1c                	je     400546 <__libc_csu_init+0x66>
  40052a:	31 db                	xor    %ebx,%ebx
  40052c:	0f 1f 40 00          	nopl   0x0(%rax)
  400530:	4c 89 fa             	mov    %r15,%rdx
  400533:	4c 89 f6             	mov    %r14,%rsi
  400536:	44 89 ef             	mov    %r13d,%edi
  400539:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40053d:	48 83 c3 01          	add    $0x1,%rbx
  400541:	48 39 eb             	cmp    %rbp,%rbx
  400544:	72 ea                	jb     400530 <__libc_csu_init+0x50>
  400546:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  40054b:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  400550:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  400555:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  40055a:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  40055f:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  400564:	48 83 c4 38          	add    $0x38,%rsp
  400568:	c3                   	retq   
  400569:	90                   	nop
  40056a:	90                   	nop
  40056b:	90                   	nop
  40056c:	90                   	nop
  40056d:	90                   	nop
  40056e:	90                   	nop
  40056f:	90                   	nop

0000000000400570 <__do_global_ctors_aux>:
  400570:	55                   	push   %rbp
  400571:	48 89 e5             	mov    %rsp,%rbp
  400574:	53                   	push   %rbx
  400575:	48 83 ec 08          	sub    $0x8,%rsp
  400579:	48 8b 05 18 01 20 00 	mov    0x200118(%rip),%rax        # 600698 <__CTOR_LIST__>
  400580:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  400584:	74 19                	je     40059f <__do_global_ctors_aux+0x2f>
  400586:	bb 98 06 60 00       	mov    $0x600698,%ebx
  40058b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400590:	48 83 eb 08          	sub    $0x8,%rbx
  400594:	ff d0                	callq  *%rax
  400596:	48 8b 03             	mov    (%rbx),%rax
  400599:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  40059d:	75 f1                	jne    400590 <__do_global_ctors_aux+0x20>
  40059f:	48 83 c4 08          	add    $0x8,%rsp
  4005a3:	5b                   	pop    %rbx
  4005a4:	c9                   	leaveq 
  4005a5:	c3                   	retq   
  4005a6:	90                   	nop
  4005a7:	90                   	nop

Disassembly of section .fini:

00000000004005a8 <_fini>:
  4005a8:	48 83 ec 08          	sub    $0x8,%rsp
  4005ac:	e8 2f fe ff ff       	callq  4003e0 <__do_global_dtors_aux>
  4005b1:	48 83 c4 08          	add    $0x8,%rsp
  4005b5:	c3                   	retq   
