#include<stdio.h>

int main(void) {
	//Drill 05-01,02
	int vc[5];
	for (int i = 0; i < 5; i++)
	{
		// vc[i] = i;  // Drill 05-01
		vc[i] = 5 - i; // Drill 05-02
	}
	for (int i = 0; i < 5; i++) {
		printf("vc[%d] = %d\n", i, vc[i]);
	}
	
	// Drill 05-03
	int va[5] = { 10,20,30 };
	int vb[5];
	for (int i = 0; i < 5; i++)
	{
		vb[i] = va[4 - i];
	}
	puts(" va vb ");
	puts("-------");
	for (int i = 0; i < 5; i++) {
		printf("%3d%3d\n", va[i], vb[i]);
	}

	// Drill 05-04
	double a;
	int b;
	a = b = 1.5;
	printf("a = %f, b = %d", a, b);

	// Drill 05-05
	int x[2][3] = { {1,2,3},{4,5,6} };
	int y[3][2] = { {1,5},{5,3},{8,1} };
	int ans[2][2] = {};
	int tmp;
	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 2; k++) {
			tmp = 0;
			for (int j = 0; j < 3; j++) {
				tmp += x[i][j] * y[j][k];
				ans[i][k] = tmp;
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				printf("%4d", ans[i][j]);
			}
			putchar('\n');
		}
	}
	return 0;
}