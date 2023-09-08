#include <stdio.h>

/** NOT FOR DEVELOPMENT
 * Only to verify VSCode is working with 'gcc' and 'gdb'
 * to install gdb in Ubuntu, open terminal, run: 'sudo apt install gdb'
 * 'gcc' will likely be available as 'gcc-9'
 * After it all works, delete this file.
 */

void main(void)
{
	volatile int a = 1; // Place a breakpoint here
	volatile int b = 2;
	b += a;
	printf(" ▄▄· ▄▄▄   ▄· ▄▌ ▄▄▄·▄▄▄▄▄      ▄▄▄ . ▐ ▄  ▄▄ • ▪   ▐ ▄ ▄▄▄ .▄▄▄ .▄▄▄  ▪   ▐ ▄  ▄▄ • \n");
	printf("▐█ ▌▪▀▄ █·▐█▪██▌▐█ ▄█•██  ▪     ▀▄.▀·•█▌▐█▐█ ▀ ▪██ •█▌▐█▀▄.▀·▀▄.▀·▀▄ █·██ •█▌▐█▐█ ▀ ▪\n");
	printf("██ ▄▄▐▀▀▄ ▐█▌▐█▪ ██▀· ▐█.▪ ▄█▀▄ ▐▀▀▪▄▐█▐▐▌▄█ ▀█▄▐█·▐█▐▐▌▐▀▀▪▄▐▀▀▪▄▐▀▀▄ ▐█·▐█▐▐▌▄█ ▀█▄\n");
	printf("▐███▌▐█•█▌ ▐█▀·.▐█▪·• ▐█▌·▐█▌.▐▌▐█▄▄▌██▐█▌▐█▄▪▐█▐█▌██▐█▌▐█▄▄▌▐█▄▄▌▐█•█▌▐█▌██▐█▌▐█▄▪▐█\n");
	printf("·▀▀▀ .▀  ▀  ▀ • .▀    ▀▀▀  ▀█▄▀▪ ▀▀▀ ▀▀ █▪·▀▀▀▀ ▀▀▀▀▀ █▪ ▀▀▀  ▀▀▀ .▀  ▀▀▀▀▀▀ █▪·▀▀▀▀ \n");
}