#include<stdio.h>

int main(void) {
	// Drill 02-01
	double num1, num2;
	puts("二つの整数を入力してください。");
	printf("整数A:");
	scanf("%d", &num1);
	printf("整数B:");
	scanf("%d", &num2);
	printf("Aの値はBの%f%%です。\n", (num1 / num2)* 100);
	
	// Drill 02-02
	int num3, num4;
	puts("二つの整数を入力してください。");
	printf("整数A:");
	scanf("%d", &num3);
	printf("整数B:");
	scanf("%d", &num4);
	printf("それらの和は%dで積は%dです。\n", num3 + num4, num3 * num4);

	// Drill 02-03
	double num5;
	printf("実数を入力してください。:");
	scanf("%lf", &num5);
	printf("あなたは%fと入力しましたね。\n", num5);
	return 0;
}