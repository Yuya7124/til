#include<stdio.h>

int main(void) {
	// Drill 04-01,02,04,05
	int num1;
	int dig;
	do {
		printf("�񕉂̐�������͂��Ă�������:");
		scanf("%d", &num1);
		if (num1 < 0) {
			puts("\a���̐�����͂��Ȃ��ł��������B");
		}
	} 
	while (num1 < 0);
	dig = 0;
	printf("%d��", num1);
		printf("%d���t����ǂނ�", num1);
	do {
		printf("%d", num1 % 10);
		num1 /= 10;
		dig ++;
	} 
	while (num1 > 0); {
		puts("�ł��B");
	}
	printf("%d���ł�\n", dig);

	// Drill 04-03
	int max, min;
	int sum1 = 0;
	int num2, num3;
	printf("����1:"); 
	scanf("%d", &num2);
	printf("����2:");
	scanf("%d", &num3);

	puts("��̐�������͂��Ă�������");
	if (num2 > num3) {
		max = num2;
		min = num3;
	}
	else {
		max = num3;
		min = num2;
	}
	printf("%d�ȏ�%d�ȉ��̐����̘a��\n", min, max);
	do
	{
		sum1 = sum1 + min;
		min = min + 1;
	} while (min < max); {
		printf("%d�ł�\n", sum1);
	}

	//Drill 04-06
	int num4, num5, num6, num7, num8, num9, i;
	printf("��������͂��Ă�������:");
	scanf("%d", &num4);
	while (num4 >= 0) {
		printf("%d ", num4);
		num4--;
		if (num4 < 0) {
			putchar('\n');
		}
	}

	// Drill 04-07
	printf("��������͂��Ă�������:");
	scanf("%d", &num5);
	while (num5 >= 1) {
		printf("%d ", num5--);		
	}
	putchar('\n');

	// Drill 04-08
	printf("��������͂��Ă�������:");
	scanf("%d", &num6);
	i = 1;
	while (i <= num6) {
		printf("%d ", i++);
		if (i == num6 + 1) {
			putchar('\n');
		}
	}

	// Drill 04-09
	printf("��������͂��Ă�������:");
	scanf("%d", &num7);
	if (num7 >= 2) {
		i = 1;
		while (i*2 <= num7) {
			printf("%d ", 2*i++);
		}
		putchar('\n');
	}

	// Drill 04-10
	printf("��������͂��Ă�������:");
	scanf("%d", &num8);
	if (num8 >= 2) {
		i = 2;
		while (i <= num8) {
			printf("%d ", i);
			i *= 2;
		}
		putchar('\n');
	}

	// Drill 04-11
	printf("��������͂��Ă�������:");
	scanf("%d", &num9);
	while (num9--> 0) {
		puts("*");
	}

	// Drill 04-12
	int sum2 = 0;
	for (int i = 1; i < 6; i++) {
		sum2 += i;
	}
	printf("1����5�܂ł𑫂����l��%d�ł��B\n", sum2);

	// Drill 04-13
	int num10;
	printf("��������͂��Ă�������:");
	scanf("%d", &num10);
	for (int i = 1; i <= num10; i++) {
		printf("%d", i % 10);
	}
	putchar('\n');

	// Drill 04-14
	int start, end, digree;
	printf("��cm����:");
	scanf("%d", &start);
	printf("��cm�܂�:");
	scanf("%d", &end);
	printf("��cm����:");
	scanf("%d", &digree);
	for (int i = start; i <= end; i += digree) {
		printf("%d cm�@%fkg\n",i ,(i - 100)* 0.90);
	}

	// Drill 04-15
	printf("   |");
	for (int i = 1; i <= 9; i++) {
		printf("%3d", i);
	}
	putchar('\n');
	printf("----");
	for (int i = 1; i <= 9; i++) {
		printf("---");
	}
	putchar('\n');
	for (int i = 1; i <= 9; i++) {
		printf("%2d |", i);
		for (int j = 1; j <= 9; j++) {
			printf("%3d", i * j);
		}
		putchar('\n');
	}
	return 0;
}