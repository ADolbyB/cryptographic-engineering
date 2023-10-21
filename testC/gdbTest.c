#include <stdio.h>

/** NOT FOR DEVELOPMENT
 * Only to verify VSCode is working with 'gcc' and 'gdb'
 * to install gdb in Ubuntu, open terminal, run: 'sudo apt install gdb'
 * 'gcc' will likely be available as 'gcc-9'
 * After it all works, delete this file.
 *  
 * This is a test with GDB Debugger.
 * Reference: https://www.youtube.com/watch?v=Dq8l1_-QgAc
 * 
 * bash command format:
 * `gcc -o [Binary fileName] [Source.c filename] -g`
 * `gcc -o gdbTest gdbTest.c -g'
 * 
 * To debug & enable all warnings at compilation time:
 * `gcc -g -Wall -Werror gdbTest.c -o gdbTest`
 * 
 * other useful bash commands:
 * `wc -c [Binary fileName]`        // shows size of binary file
 * `file [Binary fileName]`         // shows elf-file details (should say 'with debug_info')
 * `objdump -t ./binaryName`        // Display debug compile symbol table
 * 
 * To set output to radix-16 while running GDB (e.g. for `info locals` command)
 * (gdb) set output-radix 16
 * 
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