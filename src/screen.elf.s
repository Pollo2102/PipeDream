
screen.elf:     file format elf32-bigmips


Disassembly of section .text:

00400000 <start>:
  400000:	3c1d7fff 	lui	sp,0x7fff
  400004:	37bdfffc 	ori	sp,sp,0xfffc
  400008:	0c100004 	jal	400010 <main>
  40000c:	08100003 	j	40000c <start+0xc>

00400010 <main>:
  400010:	27bdffe8 	addiu	sp,sp,-24
  400014:	afbf0014 	sw	ra,20(sp)
  400018:	0c1005d6 	jal	401758 <game_start>
  40001c:	8fbf0014 	lw	ra,20(sp)
  400020:	00001025 	move	v0,zero
  400024:	27bd0018 	addiu	sp,sp,24
  400028:	03e00008 	jr	ra

0040002c <generate_rand>:
  40002c:	3c021001 	lui	v0,0x1001
  400030:	90430069 	lbu	v1,105(v0)
  400034:	24630001 	addiu	v1,v1,1
  400038:	306300ff 	andi	v1,v1,0xff
  40003c:	2c640056 	sltiu	a0,v1,86
  400040:	10800007 	beqz	a0,400060 <generate_rand+0x34>
  400044:	a0430069 	sb	v1,105(v0)
  400048:	90420069 	lbu	v0,105(v0)
  40004c:	3c031001 	lui	v1,0x1001
  400050:	2463000c 	addiu	v1,v1,12
  400054:	00431021 	addu	v0,v0,v1
  400058:	90420000 	lbu	v0,0(v0)
  40005c:	03e00008 	jr	ra
  400060:	a0400069 	sb	zero,105(v0)
  400064:	1000fff8 	b	400048 <generate_rand+0x1c>

00400068 <getTime>:
  400068:	3c02ffff 	lui	v0,0xffff
  40006c:	8c420008 	lw	v0,8(v0)
  400070:	03e00008 	jr	ra

00400074 <generate_initial_pipe>:
  400074:	27bdffe8 	addiu	sp,sp,-24
  400078:	afbf0014 	sw	ra,20(sp)
  40007c:	0c10000b 	jal	40002c <generate_rand>
  400080:	8fbf0014 	lw	ra,20(sp)
  400084:	30420003 	andi	v0,v0,0x3
  400088:	27bd0018 	addiu	sp,sp,24
  40008c:	03e00008 	jr	ra

00400090 <set_initial_square>:
  400090:	27bdffe8 	addiu	sp,sp,-24
  400094:	afbf0014 	sw	ra,20(sp)
  400098:	0c10000b 	jal	40002c <generate_rand>
  40009c:	00402825 	move	a1,v0
  4000a0:	0c10000b 	jal	40002c <generate_rand>
  4000a4:	30460006 	andi	a2,v0,0x6
  4000a8:	0c10001d 	jal	400074 <generate_initial_pipe>
  4000ac:	00061880 	sll	v1,a2,0x2
  4000b0:	00661821 	addu	v1,v1,a2
  4000b4:	3c041001 	lui	a0,0x1001
  4000b8:	00031840 	sll	v1,v1,0x1
  4000bc:	2484007c 	addiu	a0,a0,124
  4000c0:	00643021 	addu	a2,v1,a0
  4000c4:	00c53021 	addu	a2,a2,a1
  4000c8:	a0c20000 	sb	v0,0(a2)
  4000cc:	8fbf0014 	lw	ra,20(sp)
  4000d0:	00651021 	addu	v0,v1,a1
  4000d4:	00821021 	addu	v0,a0,v0
  4000d8:	3c031001 	lui	v1,0x1001
  4000dc:	ac620070 	sw	v0,112(v1)
  4000e0:	27bd0018 	addiu	sp,sp,24
  4000e4:	03e00008 	jr	ra

004000e8 <generate_initial_PQueue>:
  4000e8:	27bdffe8 	addiu	sp,sp,-24
  4000ec:	afbf0014 	sw	ra,20(sp)
  4000f0:	0c10000b 	jal	40002c <generate_rand>
  4000f4:	3c051001 	lui	a1,0x1001
  4000f8:	a0a20078 	sb	v0,120(a1)
  4000fc:	0c10000b 	jal	40002c <generate_rand>
  400100:	24a50078 	addiu	a1,a1,120
  400104:	a0a20001 	sb	v0,1(a1)
  400108:	0c10000b 	jal	40002c <generate_rand>
  40010c:	a0a20002 	sb	v0,2(a1)
  400110:	0c10000b 	jal	40002c <generate_rand>
  400114:	a0a20003 	sb	v0,3(a1)
  400118:	8fbf0014 	lw	ra,20(sp)
  40011c:	27bd0018 	addiu	sp,sp,24
  400120:	03e00008 	jr	ra

00400124 <push_queue>:
  400124:	27bdffe8 	addiu	sp,sp,-24
  400128:	afbf0014 	sw	ra,20(sp)
  40012c:	0c10000b 	jal	40002c <generate_rand>
  400130:	8fbf0014 	lw	ra,20(sp)
  400134:	3c031001 	lui	v1,0x1001
  400138:	a062007b 	sb	v0,123(v1)
  40013c:	27bd0018 	addiu	sp,sp,24
  400140:	03e00008 	jr	ra

00400144 <shift_queue>:
  400144:	3c031001 	lui	v1,0x1001
  400148:	24620078 	addiu	v0,v1,120
  40014c:	90440001 	lbu	a0,1(v0)
  400150:	a0640078 	sb	a0,120(v1)
  400154:	90430002 	lbu	v1,2(v0)
  400158:	a0430001 	sb	v1,1(v0)
  40015c:	90430003 	lbu	v1,3(v0)
  400160:	a0430002 	sb	v1,2(v0)
  400164:	03e00008 	jr	ra

00400168 <pop_queue>:
  400168:	3c021001 	lui	v0,0x1001
  40016c:	90420078 	lbu	v0,120(v0)
  400170:	27bdffe0 	addiu	sp,sp,-32
  400174:	afbf001c 	sw	ra,28(sp)
  400178:	afa20010 	sw	v0,16(sp)
  40017c:	0c100051 	jal	400144 <shift_queue>
  400180:	0c100049 	jal	400124 <push_queue>
  400184:	8fbf001c 	lw	ra,28(sp)
  400188:	8fa20010 	lw	v0,16(sp)
  40018c:	27bd0020 	addiu	sp,sp,32
  400190:	03e00008 	jr	ra

00400194 <end_game>:
  400194:	27bdffe8 	addiu	sp,sp,-24
  400198:	24050022 	li	a1,34
  40019c:	2404000a 	li	a0,10
  4001a0:	afbf0014 	sw	ra,20(sp)
  4001a4:	0c100654 	jal	401950 <set_cursor>
  4001a8:	24040004 	li	a0,4
  4001ac:	2405000f 	li	a1,15
  4001b0:	0c100646 	jal	401918 <set_color>
  4001b4:	8fbf0014 	lw	ra,20(sp)
  4001b8:	3c041001 	lui	a0,0x1001
  4001bc:	24840000 	addiu	a0,a0,0
  4001c0:	27bd0018 	addiu	sp,sp,24
  4001c4:	0810067e 	j	4019f8 <puts>

004001c8 <reset_map>:
  4001c8:	3c021001 	lui	v0,0x1001
  4001cc:	2442007c 	addiu	v0,v0,124
  4001d0:	24440046 	addiu	a0,v0,70
  4001d4:	24050007 	li	a1,7
  4001d8:	2406000a 	li	a2,10
  4001dc:	00001825 	move	v1,zero
  4001e0:	00433821 	addu	a3,v0,v1
  4001e4:	24630001 	addiu	v1,v1,1
  4001e8:	a0e50000 	sb	a1,0(a3)
  4001ec:	1466fffc 	bne	v1,a2,4001e0 <reset_map+0x18>
  4001f0:	2442000a 	addiu	v0,v0,10
  4001f4:	1444fff9 	bne	v0,a0,4001dc <reset_map+0x14>
  4001f8:	03e00008 	jr	ra

004001fc <generate_map>:
  4001fc:	27bdffe8 	addiu	sp,sp,-24
  400200:	afbf0014 	sw	ra,20(sp)
  400204:	0c100072 	jal	4001c8 <reset_map>
  400208:	0c10003a 	jal	4000e8 <generate_initial_PQueue>
  40020c:	0c100024 	jal	400090 <set_initial_square>
  400210:	8fbf0014 	lw	ra,20(sp)
  400214:	3c021001 	lui	v0,0x1001
  400218:	3c031001 	lui	v1,0x1001
  40021c:	2442007c 	addiu	v0,v0,124
  400220:	ac620074 	sw	v0,116(v1)
  400224:	27bd0018 	addiu	sp,sp,24
  400228:	03e00008 	jr	ra

0040022c <game_init>:
  40022c:	27bdffe8 	addiu	sp,sp,-24
  400230:	afbf0014 	sw	ra,20(sp)
  400234:	0c10007f 	jal	4001fc <generate_map>
  400238:	8fbf0014 	lw	ra,20(sp)
  40023c:	27bd0018 	addiu	sp,sp,24
  400240:	08100617 	j	40185c <keypad_init>

00400244 <set_cursor_position>:
  400244:	00041080 	sll	v0,a0,0x2
  400248:	00441021 	addu	v0,v0,a0
  40024c:	00021040 	sll	v0,v0,0x1
  400250:	00451021 	addu	v0,v0,a1
  400254:	3c051001 	lui	a1,0x1001
  400258:	24a5007c 	addiu	a1,a1,124
  40025c:	00a21021 	addu	v0,a1,v0
  400260:	3c031001 	lui	v1,0x1001
  400264:	ac620074 	sw	v0,116(v1)
  400268:	03e00008 	jr	ra

0040026c <count_pipes>:
  40026c:	3c081001 	lui	t0,0x1001
  400270:	24090001 	li	t1,1
  400274:	240a0002 	li	t2,2
  400278:	240b0003 	li	t3,3
  40027c:	240c0004 	li	t4,4
  400280:	240d0005 	li	t5,5
  400284:	24060006 	li	a2,6
  400288:	2407fffd 	li	a3,-3
  40028c:	91030068 	lbu	v1,104(t0)
  400290:	24620001 	addiu	v0,v1,1
  400294:	a1020068 	sb	v0,104(t0)
  400298:	90a20000 	lbu	v0,0(a1)
  40029c:	14400010 	bnez	v0,4002e0 <count_pipes+0x74>
  4002a0:	90a2fff6 	lbu	v0,-10(a1)
  4002a4:	00471824 	and	v1,v0,a3
  4002a8:	10600008 	beqz	v1,4002cc <count_pipes+0x60>
  4002ac:	2442fffb 	addiu	v0,v0,-5
  4002b0:	2c420002 	sltiu	v0,v0,2
  4002b4:	14400005 	bnez	v0,4002cc <count_pipes+0x60>
  4002b8:	90a2000a 	lbu	v0,10(a1)
  4002bc:	10400003 	beqz	v0,4002cc <count_pipes+0x60>
  4002c0:	2442fffe 	addiu	v0,v0,-2
  4002c4:	2c420003 	sltiu	v0,v0,3
  4002c8:	1040005d 	beqz	v0,400440 <count_pipes+0x1d4>
  4002cc:	24a3000a 	addiu	v1,a1,10
  4002d0:	24a2fff6 	addiu	v0,a1,-10
  4002d4:	1083003b 	beq	a0,v1,4003c4 <count_pipes+0x158>
  4002d8:	1082003a 	beq	a0,v0,4003c4 <count_pipes+0x158>
  4002dc:	03e00008 	jr	ra
  4002e0:	14490011 	bne	v0,t1,400328 <count_pipes+0xbc>
  4002e4:	90a2ffff 	lbu	v0,-1(a1)
  4002e8:	2443ffff 	addiu	v1,v0,-1
  4002ec:	2c630002 	sltiu	v1,v1,2
  4002f0:	14600008 	bnez	v1,400314 <count_pipes+0xa8>
  4002f4:	2442fffc 	addiu	v0,v0,-4
  4002f8:	2c420002 	sltiu	v0,v0,2
  4002fc:	14400005 	bnez	v0,400314 <count_pipes+0xa8>
  400300:	90a30001 	lbu	v1,1(a1)
  400304:	2462ffff 	addiu	v0,v1,-1
  400308:	2c420003 	sltiu	v0,v0,3
  40030c:	14400001 	bnez	v0,400314 <count_pipes+0xa8>
  400310:	1466004b 	bne	v1,a2,400440 <count_pipes+0x1d4>
  400314:	24a30001 	addiu	v1,a1,1
  400318:	24a2ffff 	addiu	v0,a1,-1
  40031c:	10830029 	beq	a0,v1,4003c4 <count_pipes+0x158>
  400320:	10820028 	beq	a0,v0,4003c4 <count_pipes+0x158>
  400324:	03e00008 	jr	ra
  400328:	144a001b 	bne	v0,t2,400398 <count_pipes+0x12c>
  40032c:	24a2ffff 	addiu	v0,a1,-1
  400330:	14440007 	bne	v0,a0,400350 <count_pipes+0xe4>
  400334:	90a30001 	lbu	v1,1(a1)
  400338:	2462ffff 	addiu	v0,v1,-1
  40033c:	2c420003 	sltiu	v0,v0,3
  400340:	14400001 	bnez	v0,400348 <count_pipes+0xdc>
  400344:	1466003e 	bne	v1,a2,400440 <count_pipes+0x1d4>
  400348:	24a20001 	addiu	v0,a1,1
  40034c:	1000001d 	b	4003c4 <count_pipes+0x158>
  400350:	24a30001 	addiu	v1,a1,1
  400354:	14830006 	bne	a0,v1,400370 <count_pipes+0x104>
  400358:	90a3ffff 	lbu	v1,-1(a1)
  40035c:	2464ffff 	addiu	a0,v1,-1
  400360:	2c840002 	sltiu	a0,a0,2
  400364:	14800017 	bnez	a0,4003c4 <count_pipes+0x158>
  400368:	2463fffc 	addiu	v1,v1,-4
  40036c:	10000021 	b	4003f4 <count_pipes+0x188>
  400370:	24a2fff6 	addiu	v0,a1,-10
  400374:	24a3000a 	addiu	v1,a1,10
  400378:	14440019 	bne	v0,a0,4003e0 <count_pipes+0x174>
  40037c:	90a2000a 	lbu	v0,10(a1)
  400380:	10400003 	beqz	v0,400390 <count_pipes+0x124>
  400384:	2442fffe 	addiu	v0,v0,-2
  400388:	2c420003 	sltiu	v0,v0,3
  40038c:	1040002c 	beqz	v0,400440 <count_pipes+0x1d4>
  400390:	24a2000a 	addiu	v0,a1,10
  400394:	1000000b 	b	4003c4 <count_pipes+0x158>
  400398:	144b000d 	bne	v0,t3,4003d0 <count_pipes+0x164>
  40039c:	24a2ffff 	addiu	v0,a1,-1
  4003a0:	24a3fff6 	addiu	v1,a1,-10
  4003a4:	14440025 	bne	v0,a0,40043c <count_pipes+0x1d0>
  4003a8:	90a2fff6 	lbu	v0,-10(a1)
  4003ac:	00471824 	and	v1,v0,a3
  4003b0:	10600003 	beqz	v1,4003c0 <count_pipes+0x154>
  4003b4:	2442fffb 	addiu	v0,v0,-5
  4003b8:	2c420002 	sltiu	v0,v0,2
  4003bc:	10400020 	beqz	v0,400440 <count_pipes+0x1d4>
  4003c0:	24a2fff6 	addiu	v0,a1,-10
  4003c4:	00a02025 	move	a0,a1
  4003c8:	00402825 	move	a1,v0
  4003cc:	1000ffaf 	b	40028c <count_pipes+0x20>
  4003d0:	144c000b 	bne	v0,t4,400400 <count_pipes+0x194>
  4003d4:	24a2fff6 	addiu	v0,a1,-10
  4003d8:	24a30001 	addiu	v1,a1,1
  4003dc:	1044ffd5 	beq	v0,a0,400334 <count_pipes+0xc8>
  4003e0:	14830017 	bne	a0,v1,400440 <count_pipes+0x1d4>
  4003e4:	90a3fff6 	lbu	v1,-10(a1)
  4003e8:	00672024 	and	a0,v1,a3
  4003ec:	2463fffb 	addiu	v1,v1,-5
  4003f0:	1080fff4 	beqz	a0,4003c4 <count_pipes+0x158>
  4003f4:	2c630002 	sltiu	v1,v1,2
  4003f8:	10600011 	beqz	v1,400440 <count_pipes+0x1d4>
  4003fc:	1000fff1 	b	4003c4 <count_pipes+0x158>
  400400:	144d000a 	bne	v0,t5,40042c <count_pipes+0x1c0>
  400404:	24a20001 	addiu	v0,a1,1
  400408:	1044ffdc 	beq	v0,a0,40037c <count_pipes+0x110>
  40040c:	24a3000a 	addiu	v1,a1,10
  400410:	1483000b 	bne	a0,v1,400440 <count_pipes+0x1d4>
  400414:	90a40001 	lbu	a0,1(a1)
  400418:	2483ffff 	addiu	v1,a0,-1
  40041c:	2c630003 	sltiu	v1,v1,3
  400420:	1460ffe8 	bnez	v1,4003c4 <count_pipes+0x158>
  400424:	1086ffe7 	beq	a0,a2,4003c4 <count_pipes+0x158>
  400428:	03e00008 	jr	ra
  40042c:	14460005 	bne	v0,a2,400444 <count_pipes+0x1d8>
  400430:	24a2ffff 	addiu	v0,a1,-1
  400434:	24a3000a 	addiu	v1,a1,10
  400438:	1044ffd0 	beq	v0,a0,40037c <count_pipes+0x110>
  40043c:	1083ffc6 	beq	a0,v1,400358 <count_pipes+0xec>
  400440:	03e00008 	jr	ra
  400444:	a1030068 	sb	v1,104(t0)
  400448:	1000fffd 	b	400440 <count_pipes+0x1d4>

0040044c <count_first_pipe>:
  40044c:	3c0e1001 	lui	t6,0x1001
  400450:	27bdffe8 	addiu	sp,sp,-24
  400454:	3c021001 	lui	v0,0x1001
  400458:	8dc40070 	lw	a0,112(t6)
  40045c:	a0400068 	sb	zero,104(v0)
  400460:	afbf0014 	sw	ra,20(sp)
  400464:	90820000 	lbu	v0,0(a0)
  400468:	14400002 	bnez	v0,400474 <count_first_pipe+0x28>
  40046c:	2485fff6 	addiu	a1,a0,-10
  400470:	0c10009b 	jal	40026c <count_pipes>
  400474:	8dc40070 	lw	a0,112(t6)
  400478:	24020001 	li	v0,1
  40047c:	90830000 	lbu	v1,0(a0)
  400480:	14620002 	bne	v1,v0,40048c <count_first_pipe+0x40>
  400484:	24850001 	addiu	a1,a0,1
  400488:	0c10009b 	jal	40026c <count_pipes>
  40048c:	8dc40070 	lw	a0,112(t6)
  400490:	24020002 	li	v0,2
  400494:	90830000 	lbu	v1,0(a0)
  400498:	14620002 	bne	v1,v0,4004a4 <count_first_pipe+0x58>
  40049c:	2485000a 	addiu	a1,a0,10
  4004a0:	0c10009b 	jal	40026c <count_pipes>
  4004a4:	8dc40070 	lw	a0,112(t6)
  4004a8:	24020003 	li	v0,3
  4004ac:	90830000 	lbu	v1,0(a0)
  4004b0:	14620004 	bne	v1,v0,4004c4 <count_first_pipe+0x78>
  4004b4:	8fbf0014 	lw	ra,20(sp)
  4004b8:	2485ffff 	addiu	a1,a0,-1
  4004bc:	27bd0018 	addiu	sp,sp,24
  4004c0:	0810009b 	j	40026c <count_pipes>
  4004c4:	8fbf0014 	lw	ra,20(sp)
  4004c8:	27bd0018 	addiu	sp,sp,24
  4004cc:	03e00008 	jr	ra

004004d0 <place_pipe>:
  4004d0:	3c021001 	lui	v0,0x1001
  4004d4:	8c450074 	lw	a1,116(v0)
  4004d8:	3c021001 	lui	v0,0x1001
  4004dc:	8c420070 	lw	v0,112(v0)
  4004e0:	10a20007 	beq	a1,v0,400500 <place_pipe+0x30>
  4004e4:	27bdffe8 	addiu	sp,sp,-24
  4004e8:	afbf0014 	sw	ra,20(sp)
  4004ec:	0c10005a 	jal	400168 <pop_queue>
  4004f0:	a0a20000 	sb	v0,0(a1)
  4004f4:	8fbf0014 	lw	ra,20(sp)
  4004f8:	27bd0018 	addiu	sp,sp,24
  4004fc:	03e00008 	jr	ra
  400500:	03e00008 	jr	ra

00400504 <moveCursor>:
  400504:	24020001 	li	v0,1
  400508:	1482001a 	bne	a0,v0,400574 <moveCursor+0x70>
  40050c:	3c041001 	lui	a0,0x1001
  400510:	3c031001 	lui	v1,0x1001
  400514:	8c820074 	lw	v0,116(a0)
  400518:	2463007c 	addiu	v1,v1,124
  40051c:	10430039 	beq	v0,v1,400604 <moveCursor+0x100>
  400520:	3c031001 	lui	v1,0x1001
  400524:	24630086 	addiu	v1,v1,134
  400528:	10430036 	beq	v0,v1,400604 <moveCursor+0x100>
  40052c:	3c031001 	lui	v1,0x1001
  400530:	24630090 	addiu	v1,v1,144
  400534:	10430033 	beq	v0,v1,400604 <moveCursor+0x100>
  400538:	3c031001 	lui	v1,0x1001
  40053c:	2463009a 	addiu	v1,v1,154
  400540:	10430030 	beq	v0,v1,400604 <moveCursor+0x100>
  400544:	3c031001 	lui	v1,0x1001
  400548:	246300a4 	addiu	v1,v1,164
  40054c:	1043002d 	beq	v0,v1,400604 <moveCursor+0x100>
  400550:	3c031001 	lui	v1,0x1001
  400554:	246300ae 	addiu	v1,v1,174
  400558:	1043002a 	beq	v0,v1,400604 <moveCursor+0x100>
  40055c:	3c031001 	lui	v1,0x1001
  400560:	246300b8 	addiu	v1,v1,184
  400564:	10430027 	beq	v0,v1,400604 <moveCursor+0x100>
  400568:	2442ffff 	addiu	v0,v0,-1
  40056c:	ac820074 	sw	v0,116(a0)
  400570:	03e00008 	jr	ra
  400574:	24020002 	li	v0,2
  400578:	14820019 	bne	a0,v0,4005e0 <moveCursor+0xdc>
  40057c:	3c041001 	lui	a0,0x1001
  400580:	3c031001 	lui	v1,0x1001
  400584:	8c820074 	lw	v0,116(a0)
  400588:	24630085 	addiu	v1,v1,133
  40058c:	1043001d 	beq	v0,v1,400604 <moveCursor+0x100>
  400590:	3c031001 	lui	v1,0x1001
  400594:	2463008f 	addiu	v1,v1,143
  400598:	1043001a 	beq	v0,v1,400604 <moveCursor+0x100>
  40059c:	3c031001 	lui	v1,0x1001
  4005a0:	24630099 	addiu	v1,v1,153
  4005a4:	10430017 	beq	v0,v1,400604 <moveCursor+0x100>
  4005a8:	3c031001 	lui	v1,0x1001
  4005ac:	246300a3 	addiu	v1,v1,163
  4005b0:	10430014 	beq	v0,v1,400604 <moveCursor+0x100>
  4005b4:	3c031001 	lui	v1,0x1001
  4005b8:	246300ad 	addiu	v1,v1,173
  4005bc:	10430011 	beq	v0,v1,400604 <moveCursor+0x100>
  4005c0:	3c031001 	lui	v1,0x1001
  4005c4:	246300b7 	addiu	v1,v1,183
  4005c8:	1043000e 	beq	v0,v1,400604 <moveCursor+0x100>
  4005cc:	3c031001 	lui	v1,0x1001
  4005d0:	246300c1 	addiu	v1,v1,193
  4005d4:	1043000b 	beq	v0,v1,400604 <moveCursor+0x100>
  4005d8:	24420001 	addiu	v0,v0,1
  4005dc:	1000ffe3 	b	40056c <moveCursor+0x68>
  4005e0:	24020003 	li	v0,3
  4005e4:	14820008 	bne	a0,v0,400608 <moveCursor+0x104>
  4005e8:	3c041001 	lui	a0,0x1001
  4005ec:	8c830074 	lw	v1,116(a0)
  4005f0:	3c021001 	lui	v0,0x1001
  4005f4:	244200b8 	addiu	v0,v0,184
  4005f8:	0062102b 	sltu	v0,v1,v0
  4005fc:	2463000a 	addiu	v1,v1,10
  400600:	1440000a 	bnez	v0,40062c <moveCursor+0x128>
  400604:	03e00008 	jr	ra
  400608:	24020004 	li	v0,4
  40060c:	14820009 	bne	a0,v0,400634 <moveCursor+0x130>
  400610:	3c041001 	lui	a0,0x1001
  400614:	8c830074 	lw	v1,116(a0)
  400618:	3c021001 	lui	v0,0x1001
  40061c:	24420085 	addiu	v0,v0,133
  400620:	0043102b 	sltu	v0,v0,v1
  400624:	1040fff7 	beqz	v0,400604 <moveCursor+0x100>
  400628:	2463fff6 	addiu	v1,v1,-10
  40062c:	ac830074 	sw	v1,116(a0)
  400630:	03e00008 	jr	ra
  400634:	24020005 	li	v0,5
  400638:	1482fff2 	bne	a0,v0,400604 <moveCursor+0x100>
  40063c:	08100134 	j	4004d0 <place_pipe>

00400640 <is_initial_pipe>:
  400640:	00041880 	sll	v1,a0,0x2
  400644:	00641821 	addu	v1,v1,a0
  400648:	00031840 	sll	v1,v1,0x1
  40064c:	3c021001 	lui	v0,0x1001
  400650:	00651821 	addu	v1,v1,a1
  400654:	2442007c 	addiu	v0,v0,124
  400658:	00431821 	addu	v1,v0,v1
  40065c:	3c021001 	lui	v0,0x1001
  400660:	8c420070 	lw	v0,112(v0)
  400664:	00431026 	xor	v0,v0,v1
  400668:	2c420001 	sltiu	v0,v0,1
  40066c:	03e00008 	jr	ra

00400670 <print_pipe_queue>:
  400670:	27bdffd0 	addiu	sp,sp,-48
  400674:	afb20018 	sw	s2,24(sp)
  400678:	3c121001 	lui	s2,0x1001
  40067c:	afb3001c 	sw	s3,28(sp)
  400680:	afb00010 	sw	s0,16(sp)
  400684:	00809825 	move	s3,a0
  400688:	00a08025 	move	s0,a1
  40068c:	00002025 	move	a0,zero
  400690:	24050008 	li	a1,8
  400694:	26520078 	addiu	s2,s2,120
  400698:	afb10014 	sw	s1,20(sp)
  40069c:	afbf002c 	sw	ra,44(sp)
  4006a0:	afb60028 	sw	s6,40(sp)
  4006a4:	afb50024 	sw	s5,36(sp)
  4006a8:	afb40020 	sw	s4,32(sp)
  4006ac:	00c08825 	move	s1,a2
  4006b0:	0c100646 	jal	401918 <set_color>
  4006b4:	02531021 	addu	v0,s2,s3
  4006b8:	90420000 	lbu	v0,0(v0)
  4006bc:	14400031 	bnez	v0,400784 <print_pipe_queue+0x114>
  4006c0:	02202825 	move	a1,s1
  4006c4:	02002025 	move	a0,s0
  4006c8:	26360001 	addiu	s6,s1,1
  4006cc:	0c100654 	jal	401950 <set_cursor>
  4006d0:	32d600ff 	andi	s6,s6,0xff
  4006d4:	2404007e 	li	a0,126
  4006d8:	0c10065d 	jal	401974 <put_char>
  4006dc:	26350002 	addiu	s5,s1,2
  4006e0:	02c02825 	move	a1,s6
  4006e4:	02002025 	move	a0,s0
  4006e8:	0c100654 	jal	401950 <set_cursor>
  4006ec:	32b500ff 	andi	s5,s5,0xff
  4006f0:	24040083 	li	a0,131
  4006f4:	0c10065d 	jal	401974 <put_char>
  4006f8:	26340003 	addiu	s4,s1,3
  4006fc:	02a02825 	move	a1,s5
  400700:	02002025 	move	a0,s0
  400704:	0c100654 	jal	401950 <set_cursor>
  400708:	329400ff 	andi	s4,s4,0xff
  40070c:	24040082 	li	a0,130
  400710:	0c10065d 	jal	401974 <put_char>
  400714:	02802825 	move	a1,s4
  400718:	02002025 	move	a0,s0
  40071c:	26100001 	addiu	s0,s0,1
  400720:	321000ff 	andi	s0,s0,0xff
  400724:	0c100654 	jal	401950 <set_cursor>
  400728:	2404007e 	li	a0,126
  40072c:	0c10065d 	jal	401974 <put_char>
  400730:	02202825 	move	a1,s1
  400734:	02002025 	move	a0,s0
  400738:	0c100654 	jal	401950 <set_cursor>
  40073c:	2404007e 	li	a0,126
  400740:	0c10065d 	jal	401974 <put_char>
  400744:	02c02825 	move	a1,s6
  400748:	02002025 	move	a0,s0
  40074c:	0c100654 	jal	401950 <set_cursor>
  400750:	24040083 	li	a0,131
  400754:	0c10065d 	jal	401974 <put_char>
  400758:	02a02825 	move	a1,s5
  40075c:	02002025 	move	a0,s0
  400760:	0c100654 	jal	401950 <set_cursor>
  400764:	24040082 	li	a0,130
  400768:	0c10065d 	jal	401974 <put_char>
  40076c:	02802825 	move	a1,s4
  400770:	02002025 	move	a0,s0
  400774:	0c100654 	jal	401950 <set_cursor>
  400778:	2404007e 	li	a0,126
  40077c:	0c10065d 	jal	401974 <put_char>
  400780:	02808825 	move	s1,s4
  400784:	02531021 	addu	v0,s2,s3
  400788:	90430000 	lbu	v1,0(v0)
  40078c:	24020001 	li	v0,1
  400790:	14620031 	bne	v1,v0,400858 <print_pipe_queue+0x1e8>
  400794:	02202825 	move	a1,s1
  400798:	02002025 	move	a0,s0
  40079c:	26360001 	addiu	s6,s1,1
  4007a0:	0c100654 	jal	401950 <set_cursor>
  4007a4:	32d600ff 	andi	s6,s6,0xff
  4007a8:	2404007f 	li	a0,127
  4007ac:	0c10065d 	jal	401974 <put_char>
  4007b0:	26350002 	addiu	s5,s1,2
  4007b4:	02c02825 	move	a1,s6
  4007b8:	02002025 	move	a0,s0
  4007bc:	0c100654 	jal	401950 <set_cursor>
  4007c0:	32b500ff 	andi	s5,s5,0xff
  4007c4:	2404007f 	li	a0,127
  4007c8:	0c10065d 	jal	401974 <put_char>
  4007cc:	26340003 	addiu	s4,s1,3
  4007d0:	02a02825 	move	a1,s5
  4007d4:	02002025 	move	a0,s0
  4007d8:	0c100654 	jal	401950 <set_cursor>
  4007dc:	329400ff 	andi	s4,s4,0xff
  4007e0:	2404007f 	li	a0,127
  4007e4:	0c10065d 	jal	401974 <put_char>
  4007e8:	02802825 	move	a1,s4
  4007ec:	02002025 	move	a0,s0
  4007f0:	26100001 	addiu	s0,s0,1
  4007f4:	321000ff 	andi	s0,s0,0xff
  4007f8:	0c100654 	jal	401950 <set_cursor>
  4007fc:	2404007f 	li	a0,127
  400800:	0c10065d 	jal	401974 <put_char>
  400804:	02202825 	move	a1,s1
  400808:	02002025 	move	a0,s0
  40080c:	0c100654 	jal	401950 <set_cursor>
  400810:	24040084 	li	a0,132
  400814:	0c10065d 	jal	401974 <put_char>
  400818:	02c02825 	move	a1,s6
  40081c:	02002025 	move	a0,s0
  400820:	0c100654 	jal	401950 <set_cursor>
  400824:	24040084 	li	a0,132
  400828:	0c10065d 	jal	401974 <put_char>
  40082c:	02a02825 	move	a1,s5
  400830:	02002025 	move	a0,s0
  400834:	0c100654 	jal	401950 <set_cursor>
  400838:	24040084 	li	a0,132
  40083c:	0c10065d 	jal	401974 <put_char>
  400840:	02802825 	move	a1,s4
  400844:	02002025 	move	a0,s0
  400848:	0c100654 	jal	401950 <set_cursor>
  40084c:	24040084 	li	a0,132
  400850:	0c10065d 	jal	401974 <put_char>
  400854:	02808825 	move	s1,s4
  400858:	02531021 	addu	v0,s2,s3
  40085c:	90430000 	lbu	v1,0(v0)
  400860:	24020002 	li	v0,2
  400864:	14620031 	bne	v1,v0,40092c <print_pipe_queue+0x2bc>
  400868:	02202825 	move	a1,s1
  40086c:	02002025 	move	a0,s0
  400870:	26360001 	addiu	s6,s1,1
  400874:	0c100654 	jal	401950 <set_cursor>
  400878:	32d600ff 	andi	s6,s6,0xff
  40087c:	2404007f 	li	a0,127
  400880:	0c10065d 	jal	401974 <put_char>
  400884:	26350002 	addiu	s5,s1,2
  400888:	02c02825 	move	a1,s6
  40088c:	02002025 	move	a0,s0
  400890:	0c100654 	jal	401950 <set_cursor>
  400894:	32b500ff 	andi	s5,s5,0xff
  400898:	24040080 	li	a0,128
  40089c:	0c10065d 	jal	401974 <put_char>
  4008a0:	26340003 	addiu	s4,s1,3
  4008a4:	02a02825 	move	a1,s5
  4008a8:	02002025 	move	a0,s0
  4008ac:	0c100654 	jal	401950 <set_cursor>
  4008b0:	329400ff 	andi	s4,s4,0xff
  4008b4:	24040081 	li	a0,129
  4008b8:	0c10065d 	jal	401974 <put_char>
  4008bc:	02802825 	move	a1,s4
  4008c0:	02002025 	move	a0,s0
  4008c4:	26100001 	addiu	s0,s0,1
  4008c8:	321000ff 	andi	s0,s0,0xff
  4008cc:	0c100654 	jal	401950 <set_cursor>
  4008d0:	2404007f 	li	a0,127
  4008d4:	0c10065d 	jal	401974 <put_char>
  4008d8:	02202825 	move	a1,s1
  4008dc:	02002025 	move	a0,s0
  4008e0:	0c100654 	jal	401950 <set_cursor>
  4008e4:	24040084 	li	a0,132
  4008e8:	0c10065d 	jal	401974 <put_char>
  4008ec:	02c02825 	move	a1,s6
  4008f0:	02002025 	move	a0,s0
  4008f4:	0c100654 	jal	401950 <set_cursor>
  4008f8:	24040086 	li	a0,134
  4008fc:	0c10065d 	jal	401974 <put_char>
  400900:	02a02825 	move	a1,s5
  400904:	02002025 	move	a0,s0
  400908:	0c100654 	jal	401950 <set_cursor>
  40090c:	24040085 	li	a0,133
  400910:	0c10065d 	jal	401974 <put_char>
  400914:	02802825 	move	a1,s4
  400918:	02002025 	move	a0,s0
  40091c:	0c100654 	jal	401950 <set_cursor>
  400920:	24040084 	li	a0,132
  400924:	0c10065d 	jal	401974 <put_char>
  400928:	02808825 	move	s1,s4
  40092c:	02531021 	addu	v0,s2,s3
  400930:	90430000 	lbu	v1,0(v0)
  400934:	24020003 	li	v0,3
  400938:	14620031 	bne	v1,v0,400a00 <print_pipe_queue+0x390>
  40093c:	02202825 	move	a1,s1
  400940:	02002025 	move	a0,s0
  400944:	26360001 	addiu	s6,s1,1
  400948:	0c100654 	jal	401950 <set_cursor>
  40094c:	32d600ff 	andi	s6,s6,0xff
  400950:	2404007f 	li	a0,127
  400954:	0c10065d 	jal	401974 <put_char>
  400958:	26350002 	addiu	s5,s1,2
  40095c:	02c02825 	move	a1,s6
  400960:	02002025 	move	a0,s0
  400964:	0c100654 	jal	401950 <set_cursor>
  400968:	32b500ff 	andi	s5,s5,0xff
  40096c:	24040080 	li	a0,128
  400970:	0c10065d 	jal	401974 <put_char>
  400974:	26340003 	addiu	s4,s1,3
  400978:	02a02825 	move	a1,s5
  40097c:	02002025 	move	a0,s0
  400980:	0c100654 	jal	401950 <set_cursor>
  400984:	329400ff 	andi	s4,s4,0xff
  400988:	24040082 	li	a0,130
  40098c:	0c10065d 	jal	401974 <put_char>
  400990:	02802825 	move	a1,s4
  400994:	02002025 	move	a0,s0
  400998:	26100001 	addiu	s0,s0,1
  40099c:	321000ff 	andi	s0,s0,0xff
  4009a0:	0c100654 	jal	401950 <set_cursor>
  4009a4:	2404007e 	li	a0,126
  4009a8:	0c10065d 	jal	401974 <put_char>
  4009ac:	02202825 	move	a1,s1
  4009b0:	02002025 	move	a0,s0
  4009b4:	0c100654 	jal	401950 <set_cursor>
  4009b8:	24040084 	li	a0,132
  4009bc:	0c10065d 	jal	401974 <put_char>
  4009c0:	02c02825 	move	a1,s6
  4009c4:	02002025 	move	a0,s0
  4009c8:	0c100654 	jal	401950 <set_cursor>
  4009cc:	24040084 	li	a0,132
  4009d0:	0c10065d 	jal	401974 <put_char>
  4009d4:	02a02825 	move	a1,s5
  4009d8:	02002025 	move	a0,s0
  4009dc:	0c100654 	jal	401950 <set_cursor>
  4009e0:	2404007e 	li	a0,126
  4009e4:	0c10065d 	jal	401974 <put_char>
  4009e8:	02802825 	move	a1,s4
  4009ec:	02002025 	move	a0,s0
  4009f0:	0c100654 	jal	401950 <set_cursor>
  4009f4:	2404007e 	li	a0,126
  4009f8:	0c10065d 	jal	401974 <put_char>
  4009fc:	02808825 	move	s1,s4
  400a00:	02531021 	addu	v0,s2,s3
  400a04:	90430000 	lbu	v1,0(v0)
  400a08:	24020004 	li	v0,4
  400a0c:	14620031 	bne	v1,v0,400ad4 <print_pipe_queue+0x464>
  400a10:	02202825 	move	a1,s1
  400a14:	02002025 	move	a0,s0
  400a18:	26360001 	addiu	s6,s1,1
  400a1c:	0c100654 	jal	401950 <set_cursor>
  400a20:	32d600ff 	andi	s6,s6,0xff
  400a24:	2404007e 	li	a0,126
  400a28:	0c10065d 	jal	401974 <put_char>
  400a2c:	26350002 	addiu	s5,s1,2
  400a30:	02c02825 	move	a1,s6
  400a34:	02002025 	move	a0,s0
  400a38:	0c100654 	jal	401950 <set_cursor>
  400a3c:	32b500ff 	andi	s5,s5,0xff
  400a40:	24040083 	li	a0,131
  400a44:	0c10065d 	jal	401974 <put_char>
  400a48:	26340003 	addiu	s4,s1,3
  400a4c:	02a02825 	move	a1,s5
  400a50:	02002025 	move	a0,s0
  400a54:	0c100654 	jal	401950 <set_cursor>
  400a58:	329400ff 	andi	s4,s4,0xff
  400a5c:	24040081 	li	a0,129
  400a60:	0c10065d 	jal	401974 <put_char>
  400a64:	02802825 	move	a1,s4
  400a68:	02002025 	move	a0,s0
  400a6c:	26100001 	addiu	s0,s0,1
  400a70:	321000ff 	andi	s0,s0,0xff
  400a74:	0c100654 	jal	401950 <set_cursor>
  400a78:	2404007f 	li	a0,127
  400a7c:	0c10065d 	jal	401974 <put_char>
  400a80:	02202825 	move	a1,s1
  400a84:	02002025 	move	a0,s0
  400a88:	0c100654 	jal	401950 <set_cursor>
  400a8c:	2404007e 	li	a0,126
  400a90:	0c10065d 	jal	401974 <put_char>
  400a94:	02c02825 	move	a1,s6
  400a98:	02002025 	move	a0,s0
  400a9c:	0c100654 	jal	401950 <set_cursor>
  400aa0:	2404007e 	li	a0,126
  400aa4:	0c10065d 	jal	401974 <put_char>
  400aa8:	02a02825 	move	a1,s5
  400aac:	02002025 	move	a0,s0
  400ab0:	0c100654 	jal	401950 <set_cursor>
  400ab4:	24040084 	li	a0,132
  400ab8:	0c10065d 	jal	401974 <put_char>
  400abc:	02802825 	move	a1,s4
  400ac0:	02002025 	move	a0,s0
  400ac4:	0c100654 	jal	401950 <set_cursor>
  400ac8:	24040084 	li	a0,132
  400acc:	0c10065d 	jal	401974 <put_char>
  400ad0:	02808825 	move	s1,s4
  400ad4:	02531021 	addu	v0,s2,s3
  400ad8:	90430000 	lbu	v1,0(v0)
  400adc:	24020005 	li	v0,5
  400ae0:	14620031 	bne	v1,v0,400ba8 <print_pipe_queue+0x538>
  400ae4:	02202825 	move	a1,s1
  400ae8:	02002025 	move	a0,s0
  400aec:	26360001 	addiu	s6,s1,1
  400af0:	0c100654 	jal	401950 <set_cursor>
  400af4:	32d600ff 	andi	s6,s6,0xff
  400af8:	2404007e 	li	a0,126
  400afc:	0c10065d 	jal	401974 <put_char>
  400b00:	26350002 	addiu	s5,s1,2
  400b04:	02c02825 	move	a1,s6
  400b08:	02002025 	move	a0,s0
  400b0c:	0c100654 	jal	401950 <set_cursor>
  400b10:	32b500ff 	andi	s5,s5,0xff
  400b14:	2404007e 	li	a0,126
  400b18:	0c10065d 	jal	401974 <put_char>
  400b1c:	26340003 	addiu	s4,s1,3
  400b20:	02a02825 	move	a1,s5
  400b24:	02002025 	move	a0,s0
  400b28:	0c100654 	jal	401950 <set_cursor>
  400b2c:	329400ff 	andi	s4,s4,0xff
  400b30:	2404007f 	li	a0,127
  400b34:	0c10065d 	jal	401974 <put_char>
  400b38:	02802825 	move	a1,s4
  400b3c:	02002025 	move	a0,s0
  400b40:	26100001 	addiu	s0,s0,1
  400b44:	321000ff 	andi	s0,s0,0xff
  400b48:	0c100654 	jal	401950 <set_cursor>
  400b4c:	2404007f 	li	a0,127
  400b50:	0c10065d 	jal	401974 <put_char>
  400b54:	02202825 	move	a1,s1
  400b58:	02002025 	move	a0,s0
  400b5c:	0c100654 	jal	401950 <set_cursor>
  400b60:	2404007e 	li	a0,126
  400b64:	0c10065d 	jal	401974 <put_char>
  400b68:	02c02825 	move	a1,s6
  400b6c:	02002025 	move	a0,s0
  400b70:	0c100654 	jal	401950 <set_cursor>
  400b74:	24040083 	li	a0,131
  400b78:	0c10065d 	jal	401974 <put_char>
  400b7c:	02a02825 	move	a1,s5
  400b80:	02002025 	move	a0,s0
  400b84:	0c100654 	jal	401950 <set_cursor>
  400b88:	24040085 	li	a0,133
  400b8c:	0c10065d 	jal	401974 <put_char>
  400b90:	02802825 	move	a1,s4
  400b94:	02002025 	move	a0,s0
  400b98:	0c100654 	jal	401950 <set_cursor>
  400b9c:	24040084 	li	a0,132
  400ba0:	0c10065d 	jal	401974 <put_char>
  400ba4:	02808825 	move	s1,s4
  400ba8:	02539021 	addu	s2,s2,s3
  400bac:	92430000 	lbu	v1,0(s2)
  400bb0:	24020006 	li	v0,6
  400bb4:	14620039 	bne	v1,v0,400c9c <print_pipe_queue+0x62c>
  400bb8:	02202825 	move	a1,s1
  400bbc:	02002025 	move	a0,s0
  400bc0:	26340001 	addiu	s4,s1,1
  400bc4:	0c100654 	jal	401950 <set_cursor>
  400bc8:	329400ff 	andi	s4,s4,0xff
  400bcc:	2404007f 	li	a0,127
  400bd0:	0c10065d 	jal	401974 <put_char>
  400bd4:	26330002 	addiu	s3,s1,2
  400bd8:	02802825 	move	a1,s4
  400bdc:	02002025 	move	a0,s0
  400be0:	0c100654 	jal	401950 <set_cursor>
  400be4:	327300ff 	andi	s3,s3,0xff
  400be8:	2404007f 	li	a0,127
  400bec:	0c10065d 	jal	401974 <put_char>
  400bf0:	26320003 	addiu	s2,s1,3
  400bf4:	02602825 	move	a1,s3
  400bf8:	02002025 	move	a0,s0
  400bfc:	0c100654 	jal	401950 <set_cursor>
  400c00:	325200ff 	andi	s2,s2,0xff
  400c04:	2404007e 	li	a0,126
  400c08:	0c10065d 	jal	401974 <put_char>
  400c0c:	02402825 	move	a1,s2
  400c10:	02002025 	move	a0,s0
  400c14:	26100001 	addiu	s0,s0,1
  400c18:	0c100654 	jal	401950 <set_cursor>
  400c1c:	321000ff 	andi	s0,s0,0xff
  400c20:	2404007e 	li	a0,126
  400c24:	0c10065d 	jal	401974 <put_char>
  400c28:	02202825 	move	a1,s1
  400c2c:	02002025 	move	a0,s0
  400c30:	0c100654 	jal	401950 <set_cursor>
  400c34:	24040084 	li	a0,132
  400c38:	0c10065d 	jal	401974 <put_char>
  400c3c:	02802825 	move	a1,s4
  400c40:	02002025 	move	a0,s0
  400c44:	0c100654 	jal	401950 <set_cursor>
  400c48:	24040086 	li	a0,134
  400c4c:	0c10065d 	jal	401974 <put_char>
  400c50:	02602825 	move	a1,s3
  400c54:	02002025 	move	a0,s0
  400c58:	0c100654 	jal	401950 <set_cursor>
  400c5c:	24040082 	li	a0,130
  400c60:	0c10065d 	jal	401974 <put_char>
  400c64:	02002025 	move	a0,s0
  400c68:	02402825 	move	a1,s2
  400c6c:	0c100654 	jal	401950 <set_cursor>
  400c70:	8fbf002c 	lw	ra,44(sp)
  400c74:	8fb60028 	lw	s6,40(sp)
  400c78:	8fb50024 	lw	s5,36(sp)
  400c7c:	8fb40020 	lw	s4,32(sp)
  400c80:	8fb3001c 	lw	s3,28(sp)
  400c84:	8fb20018 	lw	s2,24(sp)
  400c88:	8fb10014 	lw	s1,20(sp)
  400c8c:	8fb00010 	lw	s0,16(sp)
  400c90:	2404007e 	li	a0,126
  400c94:	27bd0030 	addiu	sp,sp,48
  400c98:	0810065d 	j	401974 <put_char>
  400c9c:	8fbf002c 	lw	ra,44(sp)
  400ca0:	8fb60028 	lw	s6,40(sp)
  400ca4:	8fb50024 	lw	s5,36(sp)
  400ca8:	8fb40020 	lw	s4,32(sp)
  400cac:	8fb3001c 	lw	s3,28(sp)
  400cb0:	8fb20018 	lw	s2,24(sp)
  400cb4:	8fb10014 	lw	s1,20(sp)
  400cb8:	8fb00010 	lw	s0,16(sp)
  400cbc:	27bd0030 	addiu	sp,sp,48
  400cc0:	03e00008 	jr	ra

00400cc4 <print_initial_pipe>:
  400cc4:	00041080 	sll	v0,a0,0x2
  400cc8:	00441021 	addu	v0,v0,a0
  400ccc:	00022040 	sll	a0,v0,0x1
  400cd0:	3c021001 	lui	v0,0x1001
  400cd4:	2442007c 	addiu	v0,v0,124
  400cd8:	27bdffc8 	addiu	sp,sp,-56
  400cdc:	00821821 	addu	v1,a0,v0
  400ce0:	00651821 	addu	v1,v1,a1
  400ce4:	afb70030 	sw	s7,48(sp)
  400ce8:	afb6002c 	sw	s6,44(sp)
  400cec:	afb50028 	sw	s5,40(sp)
  400cf0:	afb40024 	sw	s4,36(sp)
  400cf4:	afb30020 	sw	s3,32(sp)
  400cf8:	afb2001c 	sw	s2,28(sp)
  400cfc:	afb10018 	sw	s1,24(sp)
  400d00:	afb00014 	sw	s0,20(sp)
  400d04:	afbf0034 	sw	ra,52(sp)
  400d08:	90630000 	lbu	v1,0(v1)
  400d0c:	00852821 	addu	a1,a0,a1
  400d10:	00c0a025 	move	s4,a2
  400d14:	00e0a825 	move	s5,a3
  400d18:	0045b821 	addu	s7,v0,a1
  400d1c:	3c161001 	lui	s6,0x1001
  400d20:	24f30001 	addiu	s3,a3,1
  400d24:	24f20002 	addiu	s2,a3,2
  400d28:	24f10003 	addiu	s1,a3,3
  400d2c:	24d00001 	addiu	s0,a2,1
  400d30:	1460002d 	bnez	v1,400de8 <print_initial_pipe+0x124>
  400d34:	24050008 	li	a1,8
  400d38:	00002025 	move	a0,zero
  400d3c:	0c100646 	jal	401918 <set_color>
  400d40:	02802025 	move	a0,s4
  400d44:	02a02825 	move	a1,s5
  400d48:	0c100654 	jal	401950 <set_cursor>
  400d4c:	8ec20074 	lw	v0,116(s6)
  400d50:	24040087 	li	a0,135
  400d54:	10570001 	beq	v0,s7,400d5c <print_initial_pipe+0x98>
  400d58:	2404007e 	li	a0,126
  400d5c:	327300ff 	andi	s3,s3,0xff
  400d60:	0c10065d 	jal	401974 <put_char>
  400d64:	02602825 	move	a1,s3
  400d68:	02802025 	move	a0,s4
  400d6c:	0c100654 	jal	401950 <set_cursor>
  400d70:	325200ff 	andi	s2,s2,0xff
  400d74:	24040083 	li	a0,131
  400d78:	0c10065d 	jal	401974 <put_char>
  400d7c:	02402825 	move	a1,s2
  400d80:	02802025 	move	a0,s4
  400d84:	0c100654 	jal	401950 <set_cursor>
  400d88:	323100ff 	andi	s1,s1,0xff
  400d8c:	24040082 	li	a0,130
  400d90:	0c10065d 	jal	401974 <put_char>
  400d94:	02202825 	move	a1,s1
  400d98:	02802025 	move	a0,s4
  400d9c:	0c100654 	jal	401950 <set_cursor>
  400da0:	321000ff 	andi	s0,s0,0xff
  400da4:	2404007e 	li	a0,126
  400da8:	0c10065d 	jal	401974 <put_char>
  400dac:	02a02825 	move	a1,s5
  400db0:	02002025 	move	a0,s0
  400db4:	0c100654 	jal	401950 <set_cursor>
  400db8:	2404007e 	li	a0,126
  400dbc:	0c10065d 	jal	401974 <put_char>
  400dc0:	02002025 	move	a0,s0
  400dc4:	02602825 	move	a1,s3
  400dc8:	0c100654 	jal	401950 <set_cursor>
  400dcc:	2404007e 	li	a0,126
  400dd0:	0c10065d 	jal	401974 <put_char>
  400dd4:	02002025 	move	a0,s0
  400dd8:	02402825 	move	a1,s2
  400ddc:	0c100654 	jal	401950 <set_cursor>
  400de0:	2404007e 	li	a0,126
  400de4:	1000006c 	b	400f98 <print_initial_pipe+0x2d4>
  400de8:	24020001 	li	v0,1
  400dec:	1462003c 	bne	v1,v0,400ee0 <print_initial_pipe+0x21c>
  400df0:	24050008 	li	a1,8
  400df4:	00002025 	move	a0,zero
  400df8:	0c100646 	jal	401918 <set_color>
  400dfc:	02802025 	move	a0,s4
  400e00:	02a02825 	move	a1,s5
  400e04:	0c100654 	jal	401950 <set_cursor>
  400e08:	8ec20074 	lw	v0,116(s6)
  400e0c:	24040087 	li	a0,135
  400e10:	10570001 	beq	v0,s7,400e18 <print_initial_pipe+0x154>
  400e14:	2404007e 	li	a0,126
  400e18:	327300ff 	andi	s3,s3,0xff
  400e1c:	0c10065d 	jal	401974 <put_char>
  400e20:	02602825 	move	a1,s3
  400e24:	02802025 	move	a0,s4
  400e28:	0c100654 	jal	401950 <set_cursor>
  400e2c:	325200ff 	andi	s2,s2,0xff
  400e30:	2404007e 	li	a0,126
  400e34:	0c10065d 	jal	401974 <put_char>
  400e38:	02402825 	move	a1,s2
  400e3c:	02802025 	move	a0,s4
  400e40:	0c100654 	jal	401950 <set_cursor>
  400e44:	323100ff 	andi	s1,s1,0xff
  400e48:	2404007f 	li	a0,127
  400e4c:	0c10065d 	jal	401974 <put_char>
  400e50:	02202825 	move	a1,s1
  400e54:	02802025 	move	a0,s4
  400e58:	321000ff 	andi	s0,s0,0xff
  400e5c:	0c100654 	jal	401950 <set_cursor>
  400e60:	2404007f 	li	a0,127
  400e64:	0c10065d 	jal	401974 <put_char>
  400e68:	02a02825 	move	a1,s5
  400e6c:	02002025 	move	a0,s0
  400e70:	0c100654 	jal	401950 <set_cursor>
  400e74:	2404007e 	li	a0,126
  400e78:	0c10065d 	jal	401974 <put_char>
  400e7c:	02602825 	move	a1,s3
  400e80:	02002025 	move	a0,s0
  400e84:	0c100654 	jal	401950 <set_cursor>
  400e88:	2404007e 	li	a0,126
  400e8c:	0c10065d 	jal	401974 <put_char>
  400e90:	02402825 	move	a1,s2
  400e94:	02002025 	move	a0,s0
  400e98:	0c100654 	jal	401950 <set_cursor>
  400e9c:	24040084 	li	a0,132
  400ea0:	0c10065d 	jal	401974 <put_char>
  400ea4:	02002025 	move	a0,s0
  400ea8:	02202825 	move	a1,s1
  400eac:	0c100654 	jal	401950 <set_cursor>
  400eb0:	24040084 	li	a0,132
  400eb4:	8fbf0034 	lw	ra,52(sp)
  400eb8:	8fb70030 	lw	s7,48(sp)
  400ebc:	8fb6002c 	lw	s6,44(sp)
  400ec0:	8fb50028 	lw	s5,40(sp)
  400ec4:	8fb40024 	lw	s4,36(sp)
  400ec8:	8fb30020 	lw	s3,32(sp)
  400ecc:	8fb2001c 	lw	s2,28(sp)
  400ed0:	8fb10018 	lw	s1,24(sp)
  400ed4:	8fb00014 	lw	s0,20(sp)
  400ed8:	27bd0038 	addiu	sp,sp,56
  400edc:	0810065d 	j	401974 <put_char>
  400ee0:	24020002 	li	v0,2
  400ee4:	24050008 	li	a1,8
  400ee8:	00002025 	move	a0,zero
  400eec:	14620030 	bne	v1,v0,400fb0 <print_initial_pipe+0x2ec>
  400ef0:	0c100646 	jal	401918 <set_color>
  400ef4:	02802025 	move	a0,s4
  400ef8:	02a02825 	move	a1,s5
  400efc:	0c100654 	jal	401950 <set_cursor>
  400f00:	8ec20074 	lw	v0,116(s6)
  400f04:	24040087 	li	a0,135
  400f08:	10570001 	beq	v0,s7,400f10 <print_initial_pipe+0x24c>
  400f0c:	2404007e 	li	a0,126
  400f10:	327300ff 	andi	s3,s3,0xff
  400f14:	0c10065d 	jal	401974 <put_char>
  400f18:	02602825 	move	a1,s3
  400f1c:	02802025 	move	a0,s4
  400f20:	0c100654 	jal	401950 <set_cursor>
  400f24:	325200ff 	andi	s2,s2,0xff
  400f28:	2404007e 	li	a0,126
  400f2c:	0c10065d 	jal	401974 <put_char>
  400f30:	02402825 	move	a1,s2
  400f34:	02802025 	move	a0,s4
  400f38:	0c100654 	jal	401950 <set_cursor>
  400f3c:	323100ff 	andi	s1,s1,0xff
  400f40:	2404007e 	li	a0,126
  400f44:	0c10065d 	jal	401974 <put_char>
  400f48:	02202825 	move	a1,s1
  400f4c:	02802025 	move	a0,s4
  400f50:	0c100654 	jal	401950 <set_cursor>
  400f54:	321000ff 	andi	s0,s0,0xff
  400f58:	2404007e 	li	a0,126
  400f5c:	0c10065d 	jal	401974 <put_char>
  400f60:	02a02825 	move	a1,s5
  400f64:	02002025 	move	a0,s0
  400f68:	0c100654 	jal	401950 <set_cursor>
  400f6c:	2404007e 	li	a0,126
  400f70:	0c10065d 	jal	401974 <put_char>
  400f74:	02602825 	move	a1,s3
  400f78:	02002025 	move	a0,s0
  400f7c:	0c100654 	jal	401950 <set_cursor>
  400f80:	24040083 	li	a0,131
  400f84:	0c10065d 	jal	401974 <put_char>
  400f88:	02002025 	move	a0,s0
  400f8c:	02402825 	move	a1,s2
  400f90:	0c100654 	jal	401950 <set_cursor>
  400f94:	24040082 	li	a0,130
  400f98:	0c10065d 	jal	401974 <put_char>
  400f9c:	02002025 	move	a0,s0
  400fa0:	02202825 	move	a1,s1
  400fa4:	0c100654 	jal	401950 <set_cursor>
  400fa8:	2404007e 	li	a0,126
  400fac:	1000ffc1 	b	400eb4 <print_initial_pipe+0x1f0>
  400fb0:	0c100646 	jal	401918 <set_color>
  400fb4:	02802025 	move	a0,s4
  400fb8:	02a02825 	move	a1,s5
  400fbc:	0c100654 	jal	401950 <set_cursor>
  400fc0:	8ec20074 	lw	v0,116(s6)
  400fc4:	24040088 	li	a0,136
  400fc8:	10570001 	beq	v0,s7,400fd0 <print_initial_pipe+0x30c>
  400fcc:	2404007f 	li	a0,127
  400fd0:	327300ff 	andi	s3,s3,0xff
  400fd4:	0c10065d 	jal	401974 <put_char>
  400fd8:	02602825 	move	a1,s3
  400fdc:	02802025 	move	a0,s4
  400fe0:	0c100654 	jal	401950 <set_cursor>
  400fe4:	325200ff 	andi	s2,s2,0xff
  400fe8:	2404007f 	li	a0,127
  400fec:	0c10065d 	jal	401974 <put_char>
  400ff0:	02402825 	move	a1,s2
  400ff4:	02802025 	move	a0,s4
  400ff8:	0c100654 	jal	401950 <set_cursor>
  400ffc:	323100ff 	andi	s1,s1,0xff
  401000:	2404007e 	li	a0,126
  401004:	0c10065d 	jal	401974 <put_char>
  401008:	02202825 	move	a1,s1
  40100c:	02802025 	move	a0,s4
  401010:	0c100654 	jal	401950 <set_cursor>
  401014:	321000ff 	andi	s0,s0,0xff
  401018:	2404007e 	li	a0,126
  40101c:	0c10065d 	jal	401974 <put_char>
  401020:	02a02825 	move	a1,s5
  401024:	02002025 	move	a0,s0
  401028:	0c100654 	jal	401950 <set_cursor>
  40102c:	24040084 	li	a0,132
  401030:	0c10065d 	jal	401974 <put_char>
  401034:	02002025 	move	a0,s0
  401038:	02602825 	move	a1,s3
  40103c:	0c100654 	jal	401950 <set_cursor>
  401040:	24040084 	li	a0,132
  401044:	1000ff62 	b	400dd0 <print_initial_pipe+0x10c>

00401048 <print_pipe>:
  401048:	27bdffc8 	addiu	sp,sp,-56
  40104c:	afb10018 	sw	s1,24(sp)
  401050:	afb00014 	sw	s0,20(sp)
  401054:	00a08825 	move	s1,a1
  401058:	00808025 	move	s0,a0
  40105c:	24050008 	li	a1,8
  401060:	00002025 	move	a0,zero
  401064:	afb6002c 	sw	s6,44(sp)
  401068:	afb50028 	sw	s5,40(sp)
  40106c:	afb40024 	sw	s4,36(sp)
  401070:	afbf0034 	sw	ra,52(sp)
  401074:	afb70030 	sw	s7,48(sp)
  401078:	afb30020 	sw	s3,32(sp)
  40107c:	afb2001c 	sw	s2,28(sp)
  401080:	00c0a025 	move	s4,a2
  401084:	00e0a825 	move	s5,a3
  401088:	0c100646 	jal	401918 <set_color>
  40108c:	00101080 	sll	v0,s0,0x2
  401090:	00501021 	addu	v0,v0,s0
  401094:	00021040 	sll	v0,v0,0x1
  401098:	3c051001 	lui	a1,0x1001
  40109c:	3c031001 	lui	v1,0x1001
  4010a0:	0051b021 	addu	s6,v0,s1
  4010a4:	24a5007c 	addiu	a1,a1,124
  4010a8:	8c630070 	lw	v1,112(v1)
  4010ac:	00b6b021 	addu	s6,a1,s6
  4010b0:	12c30038 	beq	s6,v1,401194 <print_pipe+0x14c>
  4010b4:	00451021 	addu	v0,v0,a1
  4010b8:	00512821 	addu	a1,v0,s1
  4010bc:	90a20000 	lbu	v0,0(a1)
  4010c0:	3c171001 	lui	s7,0x1001
  4010c4:	26b30001 	addiu	s3,s5,1
  4010c8:	26b20002 	addiu	s2,s5,2
  4010cc:	26b10003 	addiu	s1,s5,3
  4010d0:	26900001 	addiu	s0,s4,1
  4010d4:	1440003e 	bnez	v0,4011d0 <print_pipe+0x188>
  4010d8:	02802025 	move	a0,s4
  4010dc:	02a02825 	move	a1,s5
  4010e0:	0c100654 	jal	401950 <set_cursor>
  4010e4:	8ee20074 	lw	v0,116(s7)
  4010e8:	24040087 	li	a0,135
  4010ec:	10560001 	beq	v0,s6,4010f4 <print_pipe+0xac>
  4010f0:	2404007e 	li	a0,126
  4010f4:	327300ff 	andi	s3,s3,0xff
  4010f8:	0c10065d 	jal	401974 <put_char>
  4010fc:	02602825 	move	a1,s3
  401100:	02802025 	move	a0,s4
  401104:	0c100654 	jal	401950 <set_cursor>
  401108:	325200ff 	andi	s2,s2,0xff
  40110c:	24040083 	li	a0,131
  401110:	0c10065d 	jal	401974 <put_char>
  401114:	02402825 	move	a1,s2
  401118:	02802025 	move	a0,s4
  40111c:	0c100654 	jal	401950 <set_cursor>
  401120:	323100ff 	andi	s1,s1,0xff
  401124:	24040082 	li	a0,130
  401128:	0c10065d 	jal	401974 <put_char>
  40112c:	02202825 	move	a1,s1
  401130:	02802025 	move	a0,s4
  401134:	0c100654 	jal	401950 <set_cursor>
  401138:	321000ff 	andi	s0,s0,0xff
  40113c:	2404007e 	li	a0,126
  401140:	0c10065d 	jal	401974 <put_char>
  401144:	02a02825 	move	a1,s5
  401148:	02002025 	move	a0,s0
  40114c:	0c100654 	jal	401950 <set_cursor>
  401150:	2404007e 	li	a0,126
  401154:	0c10065d 	jal	401974 <put_char>
  401158:	02002025 	move	a0,s0
  40115c:	02602825 	move	a1,s3
  401160:	0c100654 	jal	401950 <set_cursor>
  401164:	24040083 	li	a0,131
  401168:	0c10065d 	jal	401974 <put_char>
  40116c:	02002025 	move	a0,s0
  401170:	02402825 	move	a1,s2
  401174:	0c100654 	jal	401950 <set_cursor>
  401178:	24040082 	li	a0,130
  40117c:	0c10065d 	jal	401974 <put_char>
  401180:	02002025 	move	a0,s0
  401184:	02202825 	move	a1,s1
  401188:	0c100654 	jal	401950 <set_cursor>
  40118c:	2404007e 	li	a0,126
  401190:	1000003f 	b	401290 <print_pipe+0x248>
  401194:	8fbf0034 	lw	ra,52(sp)
  401198:	8fb70030 	lw	s7,48(sp)
  40119c:	8fb6002c 	lw	s6,44(sp)
  4011a0:	8fb30020 	lw	s3,32(sp)
  4011a4:	8fb2001c 	lw	s2,28(sp)
  4011a8:	02a03825 	move	a3,s5
  4011ac:	02803025 	move	a2,s4
  4011b0:	8fb50028 	lw	s5,40(sp)
  4011b4:	8fb40024 	lw	s4,36(sp)
  4011b8:	02202825 	move	a1,s1
  4011bc:	02002025 	move	a0,s0
  4011c0:	8fb10018 	lw	s1,24(sp)
  4011c4:	8fb00014 	lw	s0,20(sp)
  4011c8:	27bd0038 	addiu	sp,sp,56
  4011cc:	08100331 	j	400cc4 <print_initial_pipe>
  4011d0:	24030001 	li	v1,1
  4011d4:	14430039 	bne	v0,v1,4012bc <print_pipe+0x274>
  4011d8:	02802025 	move	a0,s4
  4011dc:	02a02825 	move	a1,s5
  4011e0:	0c100654 	jal	401950 <set_cursor>
  4011e4:	8ee20074 	lw	v0,116(s7)
  4011e8:	24040088 	li	a0,136
  4011ec:	10560001 	beq	v0,s6,4011f4 <print_pipe+0x1ac>
  4011f0:	2404007f 	li	a0,127
  4011f4:	327300ff 	andi	s3,s3,0xff
  4011f8:	0c10065d 	jal	401974 <put_char>
  4011fc:	02602825 	move	a1,s3
  401200:	02802025 	move	a0,s4
  401204:	0c100654 	jal	401950 <set_cursor>
  401208:	325200ff 	andi	s2,s2,0xff
  40120c:	2404007f 	li	a0,127
  401210:	0c10065d 	jal	401974 <put_char>
  401214:	02402825 	move	a1,s2
  401218:	02802025 	move	a0,s4
  40121c:	0c100654 	jal	401950 <set_cursor>
  401220:	323100ff 	andi	s1,s1,0xff
  401224:	2404007f 	li	a0,127
  401228:	0c10065d 	jal	401974 <put_char>
  40122c:	02202825 	move	a1,s1
  401230:	02802025 	move	a0,s4
  401234:	0c100654 	jal	401950 <set_cursor>
  401238:	321000ff 	andi	s0,s0,0xff
  40123c:	2404007f 	li	a0,127
  401240:	0c10065d 	jal	401974 <put_char>
  401244:	02a02825 	move	a1,s5
  401248:	02002025 	move	a0,s0
  40124c:	0c100654 	jal	401950 <set_cursor>
  401250:	24040084 	li	a0,132
  401254:	0c10065d 	jal	401974 <put_char>
  401258:	02002025 	move	a0,s0
  40125c:	02602825 	move	a1,s3
  401260:	0c100654 	jal	401950 <set_cursor>
  401264:	24040084 	li	a0,132
  401268:	0c10065d 	jal	401974 <put_char>
  40126c:	02002025 	move	a0,s0
  401270:	02402825 	move	a1,s2
  401274:	0c100654 	jal	401950 <set_cursor>
  401278:	24040084 	li	a0,132
  40127c:	0c10065d 	jal	401974 <put_char>
  401280:	02002025 	move	a0,s0
  401284:	02202825 	move	a1,s1
  401288:	0c100654 	jal	401950 <set_cursor>
  40128c:	24040084 	li	a0,132
  401290:	8fbf0034 	lw	ra,52(sp)
  401294:	8fb70030 	lw	s7,48(sp)
  401298:	8fb6002c 	lw	s6,44(sp)
  40129c:	8fb50028 	lw	s5,40(sp)
  4012a0:	8fb40024 	lw	s4,36(sp)
  4012a4:	8fb30020 	lw	s3,32(sp)
  4012a8:	8fb2001c 	lw	s2,28(sp)
  4012ac:	8fb10018 	lw	s1,24(sp)
  4012b0:	8fb00014 	lw	s0,20(sp)
  4012b4:	27bd0038 	addiu	sp,sp,56
  4012b8:	0810065d 	j	401974 <put_char>
  4012bc:	24030002 	li	v1,2
  4012c0:	1443002a 	bne	v0,v1,40136c <print_pipe+0x324>
  4012c4:	02802025 	move	a0,s4
  4012c8:	02a02825 	move	a1,s5
  4012cc:	0c100654 	jal	401950 <set_cursor>
  4012d0:	8ee20074 	lw	v0,116(s7)
  4012d4:	24040088 	li	a0,136
  4012d8:	10560001 	beq	v0,s6,4012e0 <print_pipe+0x298>
  4012dc:	2404007f 	li	a0,127
  4012e0:	327300ff 	andi	s3,s3,0xff
  4012e4:	0c10065d 	jal	401974 <put_char>
  4012e8:	02602825 	move	a1,s3
  4012ec:	02802025 	move	a0,s4
  4012f0:	0c100654 	jal	401950 <set_cursor>
  4012f4:	325200ff 	andi	s2,s2,0xff
  4012f8:	24040080 	li	a0,128
  4012fc:	0c10065d 	jal	401974 <put_char>
  401300:	02402825 	move	a1,s2
  401304:	02802025 	move	a0,s4
  401308:	0c100654 	jal	401950 <set_cursor>
  40130c:	323100ff 	andi	s1,s1,0xff
  401310:	24040081 	li	a0,129
  401314:	0c10065d 	jal	401974 <put_char>
  401318:	02202825 	move	a1,s1
  40131c:	02802025 	move	a0,s4
  401320:	0c100654 	jal	401950 <set_cursor>
  401324:	321000ff 	andi	s0,s0,0xff
  401328:	2404007f 	li	a0,127
  40132c:	0c10065d 	jal	401974 <put_char>
  401330:	02a02825 	move	a1,s5
  401334:	02002025 	move	a0,s0
  401338:	0c100654 	jal	401950 <set_cursor>
  40133c:	24040084 	li	a0,132
  401340:	0c10065d 	jal	401974 <put_char>
  401344:	02002025 	move	a0,s0
  401348:	02602825 	move	a1,s3
  40134c:	0c100654 	jal	401950 <set_cursor>
  401350:	24040086 	li	a0,134
  401354:	0c10065d 	jal	401974 <put_char>
  401358:	02002025 	move	a0,s0
  40135c:	02402825 	move	a1,s2
  401360:	0c100654 	jal	401950 <set_cursor>
  401364:	24040085 	li	a0,133
  401368:	1000ffc4 	b	40127c <print_pipe+0x234>
  40136c:	24030003 	li	v1,3
  401370:	1443002a 	bne	v0,v1,40141c <print_pipe+0x3d4>
  401374:	02802025 	move	a0,s4
  401378:	02a02825 	move	a1,s5
  40137c:	0c100654 	jal	401950 <set_cursor>
  401380:	8ee20074 	lw	v0,116(s7)
  401384:	24040088 	li	a0,136
  401388:	10560001 	beq	v0,s6,401390 <print_pipe+0x348>
  40138c:	2404007f 	li	a0,127
  401390:	327300ff 	andi	s3,s3,0xff
  401394:	0c10065d 	jal	401974 <put_char>
  401398:	02602825 	move	a1,s3
  40139c:	02802025 	move	a0,s4
  4013a0:	0c100654 	jal	401950 <set_cursor>
  4013a4:	325200ff 	andi	s2,s2,0xff
  4013a8:	24040080 	li	a0,128
  4013ac:	0c10065d 	jal	401974 <put_char>
  4013b0:	02402825 	move	a1,s2
  4013b4:	02802025 	move	a0,s4
  4013b8:	0c100654 	jal	401950 <set_cursor>
  4013bc:	323100ff 	andi	s1,s1,0xff
  4013c0:	24040082 	li	a0,130
  4013c4:	0c10065d 	jal	401974 <put_char>
  4013c8:	02202825 	move	a1,s1
  4013cc:	02802025 	move	a0,s4
  4013d0:	0c100654 	jal	401950 <set_cursor>
  4013d4:	321000ff 	andi	s0,s0,0xff
  4013d8:	2404007e 	li	a0,126
  4013dc:	0c10065d 	jal	401974 <put_char>
  4013e0:	02a02825 	move	a1,s5
  4013e4:	02002025 	move	a0,s0
  4013e8:	0c100654 	jal	401950 <set_cursor>
  4013ec:	24040084 	li	a0,132
  4013f0:	0c10065d 	jal	401974 <put_char>
  4013f4:	02002025 	move	a0,s0
  4013f8:	02602825 	move	a1,s3
  4013fc:	0c100654 	jal	401950 <set_cursor>
  401400:	24040084 	li	a0,132
  401404:	0c10065d 	jal	401974 <put_char>
  401408:	02002025 	move	a0,s0
  40140c:	02402825 	move	a1,s2
  401410:	0c100654 	jal	401950 <set_cursor>
  401414:	2404007e 	li	a0,126
  401418:	1000ff58 	b	40117c <print_pipe+0x134>
  40141c:	24030004 	li	v1,4
  401420:	14430025 	bne	v0,v1,4014b8 <print_pipe+0x470>
  401424:	02802025 	move	a0,s4
  401428:	02a02825 	move	a1,s5
  40142c:	0c100654 	jal	401950 <set_cursor>
  401430:	8ee20074 	lw	v0,116(s7)
  401434:	24040087 	li	a0,135
  401438:	10560001 	beq	v0,s6,401440 <print_pipe+0x3f8>
  40143c:	2404007e 	li	a0,126
  401440:	327300ff 	andi	s3,s3,0xff
  401444:	0c10065d 	jal	401974 <put_char>
  401448:	02602825 	move	a1,s3
  40144c:	02802025 	move	a0,s4
  401450:	0c100654 	jal	401950 <set_cursor>
  401454:	325200ff 	andi	s2,s2,0xff
  401458:	24040083 	li	a0,131
  40145c:	0c10065d 	jal	401974 <put_char>
  401460:	02402825 	move	a1,s2
  401464:	02802025 	move	a0,s4
  401468:	0c100654 	jal	401950 <set_cursor>
  40146c:	323100ff 	andi	s1,s1,0xff
  401470:	24040081 	li	a0,129
  401474:	0c10065d 	jal	401974 <put_char>
  401478:	02202825 	move	a1,s1
  40147c:	02802025 	move	a0,s4
  401480:	0c100654 	jal	401950 <set_cursor>
  401484:	321000ff 	andi	s0,s0,0xff
  401488:	2404007f 	li	a0,127
  40148c:	0c10065d 	jal	401974 <put_char>
  401490:	02a02825 	move	a1,s5
  401494:	02002025 	move	a0,s0
  401498:	0c100654 	jal	401950 <set_cursor>
  40149c:	2404007e 	li	a0,126
  4014a0:	0c10065d 	jal	401974 <put_char>
  4014a4:	02002025 	move	a0,s0
  4014a8:	02602825 	move	a1,s3
  4014ac:	0c100654 	jal	401950 <set_cursor>
  4014b0:	2404007e 	li	a0,126
  4014b4:	1000ff6c 	b	401268 <print_pipe+0x220>
  4014b8:	24030005 	li	v1,5
  4014bc:	14430025 	bne	v0,v1,401554 <print_pipe+0x50c>
  4014c0:	02802025 	move	a0,s4
  4014c4:	02a02825 	move	a1,s5
  4014c8:	0c100654 	jal	401950 <set_cursor>
  4014cc:	8ee20074 	lw	v0,116(s7)
  4014d0:	24040087 	li	a0,135
  4014d4:	10560001 	beq	v0,s6,4014dc <print_pipe+0x494>
  4014d8:	2404007e 	li	a0,126
  4014dc:	327300ff 	andi	s3,s3,0xff
  4014e0:	0c10065d 	jal	401974 <put_char>
  4014e4:	02602825 	move	a1,s3
  4014e8:	02802025 	move	a0,s4
  4014ec:	0c100654 	jal	401950 <set_cursor>
  4014f0:	325200ff 	andi	s2,s2,0xff
  4014f4:	2404007e 	li	a0,126
  4014f8:	0c10065d 	jal	401974 <put_char>
  4014fc:	02402825 	move	a1,s2
  401500:	02802025 	move	a0,s4
  401504:	0c100654 	jal	401950 <set_cursor>
  401508:	323100ff 	andi	s1,s1,0xff
  40150c:	2404007f 	li	a0,127
  401510:	0c10065d 	jal	401974 <put_char>
  401514:	02202825 	move	a1,s1
  401518:	02802025 	move	a0,s4
  40151c:	0c100654 	jal	401950 <set_cursor>
  401520:	321000ff 	andi	s0,s0,0xff
  401524:	2404007f 	li	a0,127
  401528:	0c10065d 	jal	401974 <put_char>
  40152c:	02a02825 	move	a1,s5
  401530:	02002025 	move	a0,s0
  401534:	0c100654 	jal	401950 <set_cursor>
  401538:	2404007e 	li	a0,126
  40153c:	0c10065d 	jal	401974 <put_char>
  401540:	02002025 	move	a0,s0
  401544:	02602825 	move	a1,s3
  401548:	0c100654 	jal	401950 <set_cursor>
  40154c:	24040083 	li	a0,131
  401550:	1000ff80 	b	401354 <print_pipe+0x30c>
  401554:	24030006 	li	v1,6
  401558:	02a02825 	move	a1,s5
  40155c:	02802025 	move	a0,s4
  401560:	14430023 	bne	v0,v1,4015f0 <print_pipe+0x5a8>
  401564:	0c100654 	jal	401950 <set_cursor>
  401568:	8ee20074 	lw	v0,116(s7)
  40156c:	24040088 	li	a0,136
  401570:	10560001 	beq	v0,s6,401578 <print_pipe+0x530>
  401574:	2404007f 	li	a0,127
  401578:	327300ff 	andi	s3,s3,0xff
  40157c:	0c10065d 	jal	401974 <put_char>
  401580:	02602825 	move	a1,s3
  401584:	02802025 	move	a0,s4
  401588:	0c100654 	jal	401950 <set_cursor>
  40158c:	325200ff 	andi	s2,s2,0xff
  401590:	2404007f 	li	a0,127
  401594:	0c10065d 	jal	401974 <put_char>
  401598:	02402825 	move	a1,s2
  40159c:	02802025 	move	a0,s4
  4015a0:	0c100654 	jal	401950 <set_cursor>
  4015a4:	323100ff 	andi	s1,s1,0xff
  4015a8:	2404007e 	li	a0,126
  4015ac:	0c10065d 	jal	401974 <put_char>
  4015b0:	02202825 	move	a1,s1
  4015b4:	02802025 	move	a0,s4
  4015b8:	0c100654 	jal	401950 <set_cursor>
  4015bc:	321000ff 	andi	s0,s0,0xff
  4015c0:	2404007e 	li	a0,126
  4015c4:	0c10065d 	jal	401974 <put_char>
  4015c8:	02a02825 	move	a1,s5
  4015cc:	02002025 	move	a0,s0
  4015d0:	0c100654 	jal	401950 <set_cursor>
  4015d4:	24040084 	li	a0,132
  4015d8:	0c10065d 	jal	401974 <put_char>
  4015dc:	02002025 	move	a0,s0
  4015e0:	02602825 	move	a1,s3
  4015e4:	0c100654 	jal	401950 <set_cursor>
  4015e8:	24040086 	li	a0,134
  4015ec:	1000fede 	b	401168 <print_pipe+0x120>
  4015f0:	0c100654 	jal	401950 <set_cursor>
  4015f4:	8ee20074 	lw	v0,116(s7)
  4015f8:	24040087 	li	a0,135
  4015fc:	10560001 	beq	v0,s6,401604 <print_pipe+0x5bc>
  401600:	2404007e 	li	a0,126
  401604:	327300ff 	andi	s3,s3,0xff
  401608:	0c10065d 	jal	401974 <put_char>
  40160c:	02602825 	move	a1,s3
  401610:	02802025 	move	a0,s4
  401614:	0c100654 	jal	401950 <set_cursor>
  401618:	325200ff 	andi	s2,s2,0xff
  40161c:	2404007e 	li	a0,126
  401620:	0c10065d 	jal	401974 <put_char>
  401624:	02402825 	move	a1,s2
  401628:	02802025 	move	a0,s4
  40162c:	0c100654 	jal	401950 <set_cursor>
  401630:	323100ff 	andi	s1,s1,0xff
  401634:	2404007e 	li	a0,126
  401638:	0c10065d 	jal	401974 <put_char>
  40163c:	02202825 	move	a1,s1
  401640:	02802025 	move	a0,s4
  401644:	0c100654 	jal	401950 <set_cursor>
  401648:	321000ff 	andi	s0,s0,0xff
  40164c:	2404007e 	li	a0,126
  401650:	0c10065d 	jal	401974 <put_char>
  401654:	02a02825 	move	a1,s5
  401658:	02002025 	move	a0,s0
  40165c:	0c100654 	jal	401950 <set_cursor>
  401660:	2404007e 	li	a0,126
  401664:	0c10065d 	jal	401974 <put_char>
  401668:	02002025 	move	a0,s0
  40166c:	02602825 	move	a1,s3
  401670:	0c100654 	jal	401950 <set_cursor>
  401674:	2404007e 	li	a0,126
  401678:	1000ff62 	b	401404 <print_pipe+0x3bc>

0040167c <print_map>:
  40167c:	27bdffd8 	addiu	sp,sp,-40
  401680:	24060003 	li	a2,3
  401684:	24050008 	li	a1,8
  401688:	24040003 	li	a0,3
  40168c:	afbf0024 	sw	ra,36(sp)
  401690:	afb40020 	sw	s4,32(sp)
  401694:	afb3001c 	sw	s3,28(sp)
  401698:	afb20018 	sw	s2,24(sp)
  40169c:	afb10014 	sw	s1,20(sp)
  4016a0:	afb00010 	sw	s0,16(sp)
  4016a4:	0c10019c 	jal	400670 <print_pipe_queue>
  4016a8:	24060003 	li	a2,3
  4016ac:	2405000b 	li	a1,11
  4016b0:	24040002 	li	a0,2
  4016b4:	0c10019c 	jal	400670 <print_pipe_queue>
  4016b8:	24060003 	li	a2,3
  4016bc:	2405000e 	li	a1,14
  4016c0:	24040001 	li	a0,1
  4016c4:	0c10019c 	jal	400670 <print_pipe_queue>
  4016c8:	24060003 	li	a2,3
  4016cc:	24050011 	li	a1,17
  4016d0:	00002025 	move	a0,zero
  4016d4:	0c10019c 	jal	400670 <print_pipe_queue>
  4016d8:	2412000b 	li	s2,11
  4016dc:	24130005 	li	s3,5
  4016e0:	00008025 	move	s0,zero
  4016e4:	00008825 	move	s1,zero
  4016e8:	24140007 	li	s4,7
  4016ec:	2e02000a 	sltiu	v0,s0,10
  4016f0:	10400012 	beqz	v0,40173c <print_map+0xc0>
  4016f4:	02403825 	move	a3,s2
  4016f8:	02002825 	move	a1,s0
  4016fc:	02603025 	move	a2,s3
  401700:	02202025 	move	a0,s1
  401704:	26520005 	addiu	s2,s2,5
  401708:	26100001 	addiu	s0,s0,1
  40170c:	0c100412 	jal	401048 <print_pipe>
  401710:	325200ff 	andi	s2,s2,0xff
  401714:	321000ff 	andi	s0,s0,0xff
  401718:	1634fff4 	bne	s1,s4,4016ec <print_map+0x70>
  40171c:	8fbf0024 	lw	ra,36(sp)
  401720:	8fb40020 	lw	s4,32(sp)
  401724:	8fb3001c 	lw	s3,28(sp)
  401728:	8fb20018 	lw	s2,24(sp)
  40172c:	8fb10014 	lw	s1,20(sp)
  401730:	8fb00010 	lw	s0,16(sp)
  401734:	27bd0028 	addiu	sp,sp,40
  401738:	03e00008 	jr	ra
  40173c:	26730003 	addiu	s3,s3,3
  401740:	26310001 	addiu	s1,s1,1
  401744:	327300ff 	andi	s3,s3,0xff
  401748:	323100ff 	andi	s1,s1,0xff
  40174c:	2412000b 	li	s2,11
  401750:	00008025 	move	s0,zero
  401754:	1000fff0 	b	401718 <print_map+0x9c>

00401758 <game_start>:
  401758:	27bdffd0 	addiu	sp,sp,-48
  40175c:	afbf002c 	sw	ra,44(sp)
  401760:	afb50028 	sw	s5,40(sp)
  401764:	afb40024 	sw	s4,36(sp)
  401768:	afb30020 	sw	s3,32(sp)
  40176c:	afb2001c 	sw	s2,28(sp)
  401770:	afb10018 	sw	s1,24(sp)
  401774:	afb00014 	sw	s0,20(sp)
  401778:	0c10008b 	jal	40022c <game_init>
  40177c:	3c02ffff 	lui	v0,0xffff
  401780:	8c510008 	lw	s1,8(v0)
  401784:	34109c40 	li	s0,0x9c40
  401788:	0c10059f 	jal	40167c <print_map>
  40178c:	3c12ffff 	lui	s2,0xffff
  401790:	3c131001 	lui	s3,0x1001
  401794:	34149c40 	li	s4,0x9c40
  401798:	24157530 	li	s5,30000
  40179c:	8e420008 	lw	v0,8(s2)
  4017a0:	00511023 	subu	v0,v0,s1
  4017a4:	0050102b 	sltu	v0,v0,s0
  4017a8:	1040000d 	beqz	v0,4017e0 <game_start+0x88>
  4017ac:	0c10061b 	jal	40186c <keypad_getkey>
  4017b0:	1040fffa 	beqz	v0,40179c <game_start+0x44>
  4017b4:	0c10061b 	jal	40186c <keypad_getkey>
  4017b8:	00402025 	move	a0,v0
  4017bc:	0c100141 	jal	400504 <moveCursor>
  4017c0:	00002825 	move	a1,zero
  4017c4:	00002025 	move	a0,zero
  4017c8:	0c100646 	jal	401918 <set_color>
  4017cc:	0c10068c 	jal	401a30 <clear_screen>
  4017d0:	0c10059f 	jal	40167c <print_map>
  4017d4:	24040096 	li	a0,150
  4017d8:	0c10060c 	jal	401830 <delay_ms>
  4017dc:	1000ffef 	b	40179c <game_start+0x44>
  4017e0:	0c100113 	jal	40044c <count_first_pipe>
  4017e4:	92620068 	lbu	v0,104(s3)
  4017e8:	2c420008 	sltiu	v0,v0,8
  4017ec:	14400007 	bnez	v0,40180c <game_start+0xb4>
  4017f0:	0c10007f 	jal	4001fc <generate_map>
  4017f4:	12140003 	beq	s0,s4,401804 <game_start+0xac>
  4017f8:	1615ffe8 	bne	s0,s5,40179c <game_start+0x44>
  4017fc:	24104e20 	li	s0,20000
  401800:	1000ffe6 	b	40179c <game_start+0x44>
  401804:	24107530 	li	s0,30000
  401808:	1000ffe4 	b	40179c <game_start+0x44>
  40180c:	8fbf002c 	lw	ra,44(sp)
  401810:	8fb50028 	lw	s5,40(sp)
  401814:	8fb40024 	lw	s4,36(sp)
  401818:	8fb30020 	lw	s3,32(sp)
  40181c:	8fb2001c 	lw	s2,28(sp)
  401820:	8fb10018 	lw	s1,24(sp)
  401824:	8fb00014 	lw	s0,20(sp)
  401828:	27bd0030 	addiu	sp,sp,48
  40182c:	08100065 	j	400194 <end_game>

00401830 <delay_ms>:
  401830:	3c08ffff 	lui	t0,0xffff
  401834:	8d090008 	lw	t1,8(t0)
  401838:	00000000 	nop
  40183c:	01244820 	add	t1,t1,a0

00401840 <.dm_loop>:
  401840:	8d0a0008 	lw	t2,8(t0)
  401844:	00000000 	nop
  401848:	0149582b 	sltu	t3,t2,t1
  40184c:	1560fffc 	bnez	t3,401840 <.dm_loop>
  401850:	00000000 	nop
  401854:	03e00008 	jr	ra
  401858:	00000000 	nop

0040185c <keypad_init>:
  40185c:	3c081001 	lui	t0,0x1001
  401860:	ad000064 	sw	zero,100(t0)
  401864:	03e00008 	jr	ra
  401868:	00000000 	nop

0040186c <keypad_getkey>:
  40186c:	3c08ffff 	lui	t0,0xffff
  401870:	81080004 	lb	t0,4(t0)
  401874:	24090008 	li	t1,8
  401878:	240b0001 	li	t3,1
  40187c:	00005025 	move	t2,zero

00401880 <.gk_loop>:
  401880:	11490018 	beq	t2,t1,4018e4 <.gk_end_loop>
  401884:	00000000 	nop
  401888:	010b6024 	and	t4,t0,t3
  40188c:	000b5840 	sll	t3,t3,0x1
  401890:	11800011 	beqz	t4,4018d8 <.gk_inc_loop>
  401894:	00000000 	nop
  401898:	3c081001 	lui	t0,0x1001
  40189c:	8d080064 	lw	t0,100(t0)
  4018a0:	3c09ffff 	lui	t1,0xffff
  4018a4:	8d290008 	lw	t1,8(t1)
  4018a8:	00000000 	nop
  4018ac:	0128582b 	sltu	t3,t1,t0
  4018b0:	11600002 	beqz	t3,4018bc <.set_key>
  4018b4:	00000000 	nop
  4018b8:	00001025 	move	v0,zero

004018bc <.set_key>:
  4018bc:	252900c8 	addiu	t1,t1,200
  4018c0:	3c081001 	lui	t0,0x1001
  4018c4:	ad090064 	sw	t1,100(t0)
  4018c8:	01401025 	move	v0,t2
  4018cc:	24420001 	addiu	v0,v0,1
  4018d0:	03e00008 	jr	ra
  4018d4:	00000000 	nop

004018d8 <.gk_inc_loop>:
  4018d8:	254a0001 	addiu	t2,t2,1
  4018dc:	08100620 	j	401880 <.gk_loop>
  4018e0:	00000000 	nop

004018e4 <.gk_end_loop>:
  4018e4:	00001025 	move	v0,zero
  4018e8:	03e00008 	jr	ra
  4018ec:	00000000 	nop

004018f0 <divide>:
  4018f0:	acc00000 	sw	zero,0(a2)
  4018f4:	0085102b 	sltu	v0,a0,a1
  4018f8:	10400002 	beqz	v0,401904 <divide+0x14>
  4018fc:	ace40000 	sw	a0,0(a3)
  401900:	03e00008 	jr	ra
  401904:	8cc20000 	lw	v0,0(a2)
  401908:	00852023 	subu	a0,a0,a1
  40190c:	24420001 	addiu	v0,v0,1
  401910:	acc20000 	sw	v0,0(a2)
  401914:	1000fff7 	b	4018f4 <divide+0x4>

00401918 <set_color>:
  401918:	00052900 	sll	a1,a1,0x4
  40191c:	3084000f 	andi	a0,a0,0xf
  401920:	00a42825 	or	a1,a1,a0
  401924:	3c021001 	lui	v0,0x1001
  401928:	a04500c4 	sb	a1,196(v0)
  40192c:	03e00008 	jr	ra

00401930 <get_color>:
  401930:	3c031001 	lui	v1,0x1001
  401934:	906200c4 	lbu	v0,196(v1)
  401938:	3042000f 	andi	v0,v0,0xf
  40193c:	a0820000 	sb	v0,0(a0)
  401940:	906200c4 	lbu	v0,196(v1)
  401944:	00021102 	srl	v0,v0,0x4
  401948:	a0a20000 	sb	v0,0(a1)
  40194c:	03e00008 	jr	ra

00401950 <set_cursor>:
  401950:	2c820028 	sltiu	v0,a0,40
  401954:	10400006 	beqz	v0,401970 <set_cursor+0x20>
  401958:	2ca20050 	sltiu	v0,a1,80
  40195c:	10400004 	beqz	v0,401970 <set_cursor+0x20>
  401960:	3c021001 	lui	v0,0x1001
  401964:	a04400c3 	sb	a0,195(v0)
  401968:	3c021001 	lui	v0,0x1001
  40196c:	a04500c2 	sb	a1,194(v0)
  401970:	03e00008 	jr	ra

00401974 <put_char>:
  401974:	3c071001 	lui	a3,0x1001
  401978:	2403000a 	li	v1,10
  40197c:	90e200c3 	lbu	v0,195(a3)
  401980:	3c061001 	lui	a2,0x1001
  401984:	14830006 	bne	a0,v1,4019a0 <put_char+0x2c>
  401988:	2c430027 	sltiu	v1,v0,39
  40198c:	10600002 	beqz	v1,401998 <put_char+0x24>
  401990:	24420001 	addiu	v0,v0,1
  401994:	a0e200c3 	sb	v0,195(a3)
  401998:	a0c000c2 	sb	zero,194(a2)
  40199c:	03e00008 	jr	ra
  4019a0:	3c031001 	lui	v1,0x1001
  4019a4:	906300c4 	lbu	v1,196(v1)
  4019a8:	90c500c2 	lbu	a1,194(a2)
  4019ac:	00031a00 	sll	v1,v1,0x8
  4019b0:	00642025 	or	a0,v1,a0
  4019b4:	00021880 	sll	v1,v0,0x2
  4019b8:	00621821 	addu	v1,v1,v0
  4019bc:	00031900 	sll	v1,v1,0x4
  4019c0:	00651821 	addu	v1,v1,a1
  4019c4:	00031840 	sll	v1,v1,0x1
  4019c8:	3408b800 	li	t0,0xb800
  4019cc:	01031821 	addu	v1,t0,v1
  4019d0:	a4640000 	sh	a0,0(v1)
  4019d4:	2ca3004f 	sltiu	v1,a1,79
  4019d8:	10600003 	beqz	v1,4019e8 <put_char+0x74>
  4019dc:	24a50001 	addiu	a1,a1,1
  4019e0:	a0c500c2 	sb	a1,194(a2)
  4019e4:	03e00008 	jr	ra
  4019e8:	24420001 	addiu	v0,v0,1
  4019ec:	a0c000c2 	sb	zero,194(a2)
  4019f0:	a0e200c3 	sb	v0,195(a3)
  4019f4:	03e00008 	jr	ra

004019f8 <puts>:
  4019f8:	00804825 	move	t1,a0
  4019fc:	80840000 	lb	a0,0(a0)
  401a00:	14800001 	bnez	a0,401a08 <puts+0x10>
  401a04:	03e00008 	jr	ra
  401a08:	27bdffe8 	addiu	sp,sp,-24
  401a0c:	afbf0014 	sw	ra,20(sp)
  401a10:	308400ff 	andi	a0,a0,0xff
  401a14:	25290001 	addiu	t1,t1,1
  401a18:	0c10065d 	jal	401974 <put_char>
  401a1c:	81240000 	lb	a0,0(t1)
  401a20:	1480fffb 	bnez	a0,401a10 <puts+0x18>
  401a24:	8fbf0014 	lw	ra,20(sp)
  401a28:	27bd0018 	addiu	sp,sp,24
  401a2c:	03e00008 	jr	ra

00401a30 <clear_screen>:
  401a30:	3c021001 	lui	v0,0x1001
  401a34:	904200c4 	lbu	v0,196(v0)
  401a38:	3403b800 	li	v1,0xb800
  401a3c:	00021200 	sll	v0,v0,0x8
  401a40:	34420020 	ori	v0,v0,0x20
  401a44:	3404cac0 	li	a0,0xcac0
  401a48:	a4620000 	sh	v0,0(v1)
  401a4c:	24630002 	addiu	v1,v1,2
  401a50:	1464fffd 	bne	v1,a0,401a48 <clear_screen+0x18>
  401a54:	3c021001 	lui	v0,0x1001
  401a58:	a04000c3 	sb	zero,195(v0)
  401a5c:	3c021001 	lui	v0,0x1001
  401a60:	a04000c2 	sb	zero,194(v0)
  401a64:	03e00008 	jr	ra

Disassembly of section .data:

10010000 <randPipes-0xc>:
10010000:	47414d45 	c1	0x1414d45
10010004:	204f5645 	addi	t7,v0,22085
10010008:	52210000 	0x52210000

1001000c <randPipes>:
1001000c:	00010306 	0x10306
10010010:	05020101 	0x5020101
10010014:	00000306 	0x306
10010018:	00000105 	0x105
1001001c:	01040501 	0x1040501
10010020:	06040606 	0x6040606
10010024:	00060501 	0x60501
10010028:	05060006 	0x5060006
1001002c:	06000200 	bltz	s0,10010830 <chr_attr+0x76c>
10010030:	06050000 	0x6050000
10010034:	05060003 	0x5060003
10010038:	02000506 	0x2000506
1001003c:	01020306 	0x1020306
10010040:	01060103 	0x1060103
10010044:	02010506 	0x2010506
10010048:	02030005 	0x2030005
1001004c:	06010506 	bgez	s0,10011468 <chr_attr+0x13a4>
10010050:	06040605 	0x6040605
10010054:	03060504 	0x3060504
10010058:	01060501 	0x1060501
1001005c:	03000605 	0x3000605
10010060:	04010000 	b	10010064 <next_key_time>

10010064 <next_key_time>:
10010064:	00000000 	nop

10010068 <num_of_pipes>:
	...

10010069 <randPipeCounter>:
	...

1001006a <score>:
	...

1001006c <secondPipePosition>:
1001006c:	00000000 	nop

10010070 <initialPipePosition>:
10010070:	00000000 	nop

10010074 <cursorPosition>:
10010074:	00000000 	nop

10010078 <pipeQueue>:
10010078:	00000000 	nop

Disassembly of section .gnu.attributes:

00000000 <.gnu.attributes>:
   0:	41000000 	bc0f	4 <_gp+0x4>
   4:	0f676e75 	jal	d9db9d4 <clear_screen+0xd5d9fa4>
   8:	00010000 	sll	zero,at,0x0
   c:	00070401 	0x70401

Disassembly of section .bss:

1001007c <pipeMap>:
	...

100100c2 <cursor_col>:
	...

100100c3 <cursor_row>:
	...

100100c4 <chr_attr>:
	...
