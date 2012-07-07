/*
   Written by phamthechung0@gmail.com
*/

.code16
.text
/* 
	it load mbr to 7c00 31744
	sector 1 7c00->7dff
	sector 2 7e00->7fff
	sector 3 8000->81ff
*/

start:
  mov $0xb,%ah
  xor %bh,%bh
  mov $9,%bl
  int $0x10

  mov %cs,%dx
  mov %dx,%ds

  mov $0xe,%ah
  mov $1,%bl
  mov $VIO,%si /*$0x7db6*/
  loop:
    lodsb
    int $0x10
    cmp $0,%al
    jnz loop


read:
        mov %dx,%es
	mov $0x7e00,%bx /*address of store*/
	mov $0x80,%dl   /*hard drive*/
	mov $0,%al    /*number of sector*/
	mov $2,%cl      /*sector number*/
	mov $1,%ch		/*cylinder number*/
	mov $1,%dh		/*head number*/
	
	mov $0x2,%ah
	int $0x13
	jc error		/*cf set if error */
	jmp dichquan
  
error:
  mov $0x,%si
  mov $0xe,%ah
  sub_error:
  lodsb
  int $0x10
  cmp $0,%al
  jnz sub_error
  jmp reboot  
dichquan:
  mov $0xe,%ah
  mov $loading,%si
  dichquan_sub:
  lodsb
  int $0x10
  jz dichquan_sub
  jmp *%bx

reboot:
/*get key*/
mov $0,%ah
int $0x16
/*reboot*/
mov $0x0,%eax

int $0x19

/*make it null*/
error_string:
	.string "Error Reading"
	.byte 0xa
VIO:
	.string "VIO MBR"
	.byte 0xa
loading:
	.string "loading stage2\n"
.space 446-(.-start),0
.byte 0x80
.space 63,0
sign:
.word 0xaa55
