
licensechk-signed:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 7a 2f 00 00    	push   0x2f7a(%rip)        # 3fa0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 7b 2f 00 00 	bnd jmp *0x2f7b(%rip)        # 3fa8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <.plt>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <.plt>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	push   $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmp 1020 <.plt>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	push   $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmp 1020 <.plt>
    106f:	90                   	nop
    1070:	f3 0f 1e fa          	endbr64 
    1074:	68 04 00 00 00       	push   $0x4
    1079:	f2 e9 a1 ff ff ff    	bnd jmp 1020 <.plt>
    107f:	90                   	nop

Disassembly of section .plt.got:

0000000000001080 <__cxa_finalize@plt>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	f2 ff 25 6d 2f 00 00 	bnd jmp *0x2f6d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    108b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001090 <puts@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 15 2f 00 00 	bnd jmp *0x2f15(%rip)        # 3fb0 <puts@GLIBC_2.2.5>
    109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010a0 <__stack_chk_fail@plt>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	f2 ff 25 0d 2f 00 00 	bnd jmp *0x2f0d(%rip)        # 3fb8 <__stack_chk_fail@GLIBC_2.4>
    10ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010b0 <license_check_ok@plt>:
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	f2 ff 25 05 2f 00 00 	bnd jmp *0x2f05(%rip)        # 3fc0 <license_check_ok>
    10bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010c0 <strcmp@plt>:
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	f2 ff 25 fd 2e 00 00 	bnd jmp *0x2efd(%rip)        # 3fc8 <strcmp@GLIBC_2.2.5>
    10cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010d0 <__isoc99_scanf@plt>:
    10d0:	f3 0f 1e fa          	endbr64 
    10d4:	f2 ff 25 f5 2e 00 00 	bnd jmp *0x2ef5(%rip)        # 3fd0 <__isoc99_scanf@GLIBC_2.7>
    10db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010e0 <_start>:
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	31 ed                	xor    %ebp,%ebp
    10e6:	49 89 d1             	mov    %rdx,%r9
    10e9:	5e                   	pop    %rsi
    10ea:	48 89 e2             	mov    %rsp,%rdx
    10ed:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10f1:	50                   	push   %rax
    10f2:	54                   	push   %rsp
    10f3:	4c 8d 05 86 02 00 00 	lea    0x286(%rip),%r8        # 1380 <__libc_csu_fini>
    10fa:	48 8d 0d 0f 02 00 00 	lea    0x20f(%rip),%rcx        # 1310 <__libc_csu_init>
    1101:	48 8d 3d 33 01 00 00 	lea    0x133(%rip),%rdi        # 123b <main>
    1108:	ff 15 d2 2e 00 00    	call   *0x2ed2(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    110e:	f4                   	hlt    
    110f:	90                   	nop

0000000000001110 <deregister_tm_clones>:
    1110:	48 8d 3d 01 2f 00 00 	lea    0x2f01(%rip),%rdi        # 4018 <__TMC_END__>
    1117:	48 8d 05 fa 2e 00 00 	lea    0x2efa(%rip),%rax        # 4018 <__TMC_END__>
    111e:	48 39 f8             	cmp    %rdi,%rax
    1121:	74 15                	je     1138 <deregister_tm_clones+0x28>
    1123:	48 8b 05 ae 2e 00 00 	mov    0x2eae(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    112a:	48 85 c0             	test   %rax,%rax
    112d:	74 09                	je     1138 <deregister_tm_clones+0x28>
    112f:	ff e0                	jmp    *%rax
    1131:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1138:	c3                   	ret    
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <register_tm_clones>:
    1140:	48 8d 3d d1 2e 00 00 	lea    0x2ed1(%rip),%rdi        # 4018 <__TMC_END__>
    1147:	48 8d 35 ca 2e 00 00 	lea    0x2eca(%rip),%rsi        # 4018 <__TMC_END__>
    114e:	48 29 fe             	sub    %rdi,%rsi
    1151:	48 89 f0             	mov    %rsi,%rax
    1154:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1158:	48 c1 f8 03          	sar    $0x3,%rax
    115c:	48 01 c6             	add    %rax,%rsi
    115f:	48 d1 fe             	sar    %rsi
    1162:	74 14                	je     1178 <register_tm_clones+0x38>
    1164:	48 8b 05 85 2e 00 00 	mov    0x2e85(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    116b:	48 85 c0             	test   %rax,%rax
    116e:	74 08                	je     1178 <register_tm_clones+0x38>
    1170:	ff e0                	jmp    *%rax
    1172:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1178:	c3                   	ret    
    1179:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001180 <__do_global_dtors_aux>:
    1180:	f3 0f 1e fa          	endbr64 
    1184:	80 3d 8d 2e 00 00 00 	cmpb   $0x0,0x2e8d(%rip)        # 4018 <__TMC_END__>
    118b:	75 2b                	jne    11b8 <__do_global_dtors_aux+0x38>
    118d:	55                   	push   %rbp
    118e:	48 83 3d 62 2e 00 00 	cmpq   $0x0,0x2e62(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1195:	00 
    1196:	48 89 e5             	mov    %rsp,%rbp
    1199:	74 0c                	je     11a7 <__do_global_dtors_aux+0x27>
    119b:	48 8b 3d 66 2e 00 00 	mov    0x2e66(%rip),%rdi        # 4008 <__dso_handle>
    11a2:	e8 d9 fe ff ff       	call   1080 <__cxa_finalize@plt>
    11a7:	e8 64 ff ff ff       	call   1110 <deregister_tm_clones>
    11ac:	c6 05 65 2e 00 00 01 	movb   $0x1,0x2e65(%rip)        # 4018 <__TMC_END__>
    11b3:	5d                   	pop    %rbp
    11b4:	c3                   	ret    
    11b5:	0f 1f 00             	nopl   (%rax)
    11b8:	c3                   	ret    
    11b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011c0 <frame_dummy>:
    11c0:	f3 0f 1e fa          	endbr64 
    11c4:	e9 77 ff ff ff       	jmp    1140 <register_tm_clones>

00000000000011c9 <do_license_check_v1>:
    11c9:	f3 0f 1e fa          	endbr64 
    11cd:	55                   	push   %rbp
    11ce:	48 89 e5             	mov    %rsp,%rbp
    11d1:	48 83 ec 10          	sub    $0x10,%rsp
    11d5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    11d9:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    11dd:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    11e1:	48 89 c6             	mov    %rax,%rsi
    11e4:	48 8d 3d 19 0e 00 00 	lea    0xe19(%rip),%rdi        # 2004 <_IO_stdin_used+0x4>
    11eb:	e8 d0 fe ff ff       	call   10c0 <strcmp@plt>
    11f0:	85 c0                	test   %eax,%eax
    11f2:	74 07                	je     11fb <do_license_check_v1+0x32>
    11f4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    11f9:	eb 05                	jmp    1200 <do_license_check_v1+0x37>
    11fb:	b8 00 00 00 00       	mov    $0x0,%eax
    1200:	c9                   	leave  
    1201:	c3                   	ret    

0000000000001202 <do_license_check_v2>:
    1202:	f3 0f 1e fa          	endbr64 
    1206:	55                   	push   %rbp
    1207:	48 89 e5             	mov    %rsp,%rbp
    120a:	48 83 ec 10          	sub    $0x10,%rsp
    120e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1212:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1216:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    121a:	48 89 c6             	mov    %rax,%rsi
    121d:	48 8d 3d fa 0d 00 00 	lea    0xdfa(%rip),%rdi        # 201e <_IO_stdin_used+0x1e>
    1224:	e8 97 fe ff ff       	call   10c0 <strcmp@plt>
    1229:	85 c0                	test   %eax,%eax
    122b:	74 07                	je     1234 <do_license_check_v2+0x32>
    122d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    1232:	eb 05                	jmp    1239 <do_license_check_v2+0x37>
    1234:	b8 00 00 00 00       	mov    $0x0,%eax
    1239:	c9                   	leave  
    123a:	c3                   	ret    

000000000000123b <main>:
    123b:	f3 0f 1e fa          	endbr64 
    123f:	55                   	push   %rbp
    1240:	48 89 e5             	mov    %rsp,%rbp
    1243:	48 83 ec 50          	sub    $0x50,%rsp
    1247:	89 7d bc             	mov    %edi,-0x44(%rbp)
    124a:	48 89 75 b0          	mov    %rsi,-0x50(%rbp)
    124e:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1255:	00 00 
    1257:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    125b:	31 c0                	xor    %eax,%eax
    125d:	48 8d 3d d4 0d 00 00 	lea    0xdd4(%rip),%rdi        # 2038 <_IO_stdin_used+0x38>
    1264:	e8 27 fe ff ff       	call   1090 <puts@plt>
    1269:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
    1270:	00 
    1271:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
    1278:	00 
    1279:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
    1280:	00 
    1281:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
    1288:	00 
    1289:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    128d:	48 89 c6             	mov    %rax,%rsi
    1290:	48 8d 3d c1 0d 00 00 	lea    0xdc1(%rip),%rdi        # 2058 <_IO_stdin_used+0x58>
    1297:	b8 00 00 00 00       	mov    $0x0,%eax
    129c:	e8 2f fe ff ff       	call   10d0 <__isoc99_scanf@plt>
    12a1:	48 8b 15 68 2d 00 00 	mov    0x2d68(%rip),%rdx        # 4010 <check_license>
    12a8:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    12ac:	be 20 00 00 00       	mov    $0x20,%esi
    12b1:	48 89 c7             	mov    %rax,%rdi
    12b4:	ff d2                	call   *%rdx
    12b6:	89 45 cc             	mov    %eax,-0x34(%rbp)
    12b9:	83 7d cc 00          	cmpl   $0x0,-0x34(%rbp)
    12bd:	74 0e                	je     12cd <main+0x92>
    12bf:	48 8d 3d 97 0d 00 00 	lea    0xd97(%rip),%rdi        # 205d <_IO_stdin_used+0x5d>
    12c6:	e8 c5 fd ff ff       	call   1090 <puts@plt>
    12cb:	eb 11                	jmp    12de <main+0xa3>
    12cd:	48 8d 3d 91 0d 00 00 	lea    0xd91(%rip),%rdi        # 2065 <_IO_stdin_used+0x65>
    12d4:	e8 b7 fd ff ff       	call   1090 <puts@plt>
    12d9:	e8 d2 fd ff ff       	call   10b0 <license_check_ok@plt>
    12de:	b8 00 00 00 00       	mov    $0x0,%eax
    12e3:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
    12e7:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
    12ee:	00 00 
    12f0:	74 05                	je     12f7 <main+0xbc>
    12f2:	e8 a9 fd ff ff       	call   10a0 <__stack_chk_fail@plt>
    12f7:	c9                   	leave  
    12f8:	c3                   	ret    

00000000000012f9 <do_nothing>:
    12f9:	f3 0f 1e fa          	endbr64 
    12fd:	55                   	push   %rbp
    12fe:	48 89 e5             	mov    %rsp,%rbp
    1301:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1305:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1309:	b8 00 00 00 00       	mov    $0x0,%eax
    130e:	5d                   	pop    %rbp
    130f:	c3                   	ret    

0000000000001310 <__libc_csu_init>:
    1310:	f3 0f 1e fa          	endbr64 
    1314:	41 57                	push   %r15
    1316:	4c 8d 3d 6b 2a 00 00 	lea    0x2a6b(%rip),%r15        # 3d88 <__frame_dummy_init_array_entry>
    131d:	41 56                	push   %r14
    131f:	49 89 d6             	mov    %rdx,%r14
    1322:	41 55                	push   %r13
    1324:	49 89 f5             	mov    %rsi,%r13
    1327:	41 54                	push   %r12
    1329:	41 89 fc             	mov    %edi,%r12d
    132c:	55                   	push   %rbp
    132d:	48 8d 2d 5c 2a 00 00 	lea    0x2a5c(%rip),%rbp        # 3d90 <__do_global_dtors_aux_fini_array_entry>
    1334:	53                   	push   %rbx
    1335:	4c 29 fd             	sub    %r15,%rbp
    1338:	48 83 ec 08          	sub    $0x8,%rsp
    133c:	e8 bf fc ff ff       	call   1000 <_init>
    1341:	48 c1 fd 03          	sar    $0x3,%rbp
    1345:	74 1f                	je     1366 <__libc_csu_init+0x56>
    1347:	31 db                	xor    %ebx,%ebx
    1349:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1350:	4c 89 f2             	mov    %r14,%rdx
    1353:	4c 89 ee             	mov    %r13,%rsi
    1356:	44 89 e7             	mov    %r12d,%edi
    1359:	41 ff 14 df          	call   *(%r15,%rbx,8)
    135d:	48 83 c3 01          	add    $0x1,%rbx
    1361:	48 39 dd             	cmp    %rbx,%rbp
    1364:	75 ea                	jne    1350 <__libc_csu_init+0x40>
    1366:	48 83 c4 08          	add    $0x8,%rsp
    136a:	5b                   	pop    %rbx
    136b:	5d                   	pop    %rbp
    136c:	41 5c                	pop    %r12
    136e:	41 5d                	pop    %r13
    1370:	41 5e                	pop    %r14
    1372:	41 5f                	pop    %r15
    1374:	c3                   	ret    
    1375:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
    137c:	00 00 00 00 

0000000000001380 <__libc_csu_fini>:
    1380:	f3 0f 1e fa          	endbr64 
    1384:	c3                   	ret    

Disassembly of section .fini:

0000000000001388 <_fini>:
    1388:	f3 0f 1e fa          	endbr64 
    138c:	48 83 ec 08          	sub    $0x8,%rsp
    1390:	48 83 c4 08          	add    $0x8,%rsp
    1394:	c3                   	ret    
