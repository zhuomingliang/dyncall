#include <stddef.h>
#include <stdio.h>
void arm();
void thumb();

int main(int argc, char* argv[])
{
	arm();
	thumb();
        printf("arm: %d\n", (ptrdiff_t) &arm);
        printf("thumb: %d\n", (ptrdiff_t) &thumb);
	return 0;
}
