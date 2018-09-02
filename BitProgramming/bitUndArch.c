#include <stdio.h>

void showBit(unsigned char *a) {
	for(int i = (sizeof(*a)*8)-1; i >= 0; i--) {
		( 1u & ((*a)>>i)) ? putchar('1'): putchar('0'); 
	}
	printf("\n\n");
}

int main() {
	unsigned int a;
	printf("\nGeben Sie eine Nummer ein : ");
	scanf("%u",&a);
	printf("\n");
	unsigned char *byte = (unsigned char*) &a;
	for(int i = 0; i < sizeof(a);i++) {
		printf("Byte in %d position : ",i);
		showBit(byte+i);
	}
	a = 0xFFBBCCEE;
	if(byte[0] == ((a >> 0) & 0xFF))
		printf("Little Endian Architecture\n\n");
	if(byte[0] == ((a >> 24) & 0xFF)) 
		printf("Big Endian Architecture\n\n");		
	return 0;
}
