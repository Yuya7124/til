#include<stdio.h>

int main(void) {
	// Drill 02-01
	double num1, num2;
	puts("��̐�������͂��Ă��������B");
	printf("����A:");
	scanf("%d", &num1);
	printf("����B:");
	scanf("%d", &num2);
	printf("A�̒l��B��%f%%�ł��B\n", (num1 / num2)* 100);
	
	// Drill 02-02
	int num3, num4;
	puts("��̐�������͂��Ă��������B");
	printf("����A:");
	scanf("%d", &num3);
	printf("����B:");
	scanf("%d", &num4);
	printf("�����̘a��%d�Őς�%d�ł��B\n", num3 + num4, num3 * num4);

	// Drill 02-03
	double num5;
	printf("��������͂��Ă��������B:");
	scanf("%lf", &num5);
	printf("���Ȃ���%f�Ɠ��͂��܂����ˁB\n", num5);
	return 0;
}