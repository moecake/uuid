#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mem_dump(void *p, const unsigned int n, const unsigned int m);

int main(int argc, char* argv[])
{
	
	unsigned char *x  = (unsigned char *)malloc(100);
	unsigned char *p = x;
	unsigned short i = 4131;
	memset(x, 0, 100);
	p[12]=15;
	mem_dump(p, 25, 20);
	
	free(x);

	return 0;
}

int mem_dump(void *p, const unsigned int n, unsigned int m)
{
	if(!m) m=10;
	
	unsigned int x=0;
	unsigned int y=0;
	unsigned int w=0;
	unsigned int z=0;
	
	unsigned int t = n/m;
	unsigned int r = n%m;
	
	for(x=0; x<t; x++){
		for(y=0; y<m; y++) printf("%02d ", w++);
		printf("\n");
		for(y=0; y<m; y++) printf("%02x ", ((unsigned char *)p)[z++]);
		printf("\n\n");
	}
	if(r){
		for(y=0; y<r; y++) printf("%02d ", w++);
		printf("\n");
		for(y=0; y<r; y++) printf("%02x ", ((unsigned char *)p)[z++]);
		printf("\n");
	}
	
	return 0;
}
