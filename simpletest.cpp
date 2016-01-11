#include <stdio.h>
#include <stdlib.h>

void simpleTest(float f)
{
	float tempf = 2.59999990463256836e-01;
	float tempff = tempf*tempf;
	float tempff2 = (tempf + 1) * (tempf + 1);
	float ff = f*f;
	bool res0 = tempff == ff;
	bool res1 = tempff2 == ff;
	printf("result is\n\ttempff == ff ? %d\n\ttempff2 == ff ? %d\n", res0, res1);
	printf("f is %.40f\ntempf is %.40f\nff is %.40f\ntempff is %.40f\ntempff2 is %.40f\n", f, tempf, ff, tempff, tempff2);
}

int main()
{
	int s = rand() % 2;
	printf("S = %d\n", s);
	simpleTest(2.59999990463256836e-01 + s) ;
	return 0;
}
