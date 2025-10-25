/* print.h */

#define JTAG_UART ((volatile unsigned int*) 0x04000040)
#define JTAG_CTRL ((volatile unsigned int*) 0x04000044)

void printc(char s)
{
    while (((*JTAG_CTRL)&0xffff0000) == 0);
    *JTAG_UART = s;
}


