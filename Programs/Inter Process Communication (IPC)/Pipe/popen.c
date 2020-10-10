#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	FILE* fp = popen("sort", "w");
	fprintf(fp, "This is Popen Program\n");
	fprintf(fp, "This will test the pipe functionality\n");
	fprintf(fp, "InterProcess Communication\n");
	fprintf(fp, "Parth Shah\n");
	pclose(fp);
	return 0;
}
