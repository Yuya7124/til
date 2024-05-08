#include<stdio.h>

int main(void) {
	// Drill 03-01
	int num1, num2;
	printf("整数A:");
	scanf("%d", &num1);
	printf("整数A:");
	scanf("%d", &num2);
	if (num1 / num2) {
		puts("BはAの約数です");
	}
	else {
		puts("BはAの約数ではありません");
	}

	// Drill 03-02
	printf("10 == 10:%d\n", 10 == 10);
	printf("10 == 9:%d\n", 10 == 9);
	printf("10 != 10:%d\n", 10 != 10);
	printf("10 != 9:%d\n", 10 != 9);
	printf("10 > 9:%d\n", 10 > 9);
	printf("10 < 9:%d\n", 10 < 9);
	
	//Drill 03-03
	int num3;
	printf("整数を入力してください:");
	scanf("%d", &num3);
	if (num3 < 0) {
		num3 = num3 * (-1);
	}
	printf("絶対値は%dです", num3);
	
	//Drill 03-04
	int num4, num5;
	puts("二つの整数を入力してください。");
	printf("整数A:");
	scanf("%d", &num4);
	printf("整数B:");
	scanf("%d", &num5);
	if (num4 == num5) {
		puts("AとBは等しい");
	}
	else if (num4 < num5) {
		puts("ＡはＢより小さい");
	}
	else {
		puts("ＡはＢより大きい");
	}

	//Drill 03-05
	int num6, num7, num8, min;
	puts("三つの整数を入力してください。");
	printf("整数1:");
	scanf("%d", &num6);
	printf("整数2:");
	scanf("%d", &num7);
	printf("整数3:");
	scanf("%d", &num8);
	min = num6;
	if (num7 < min) {
		min = num7;
	}
	if (num8 < min) {
		min = num8;
	}
	printf("最小値は%dです。\n", min);

	//Drill 03-06
	int num9, num10, num11, num12, max;
	puts("四つの整数を入力してください。");
	printf("整数1:");
	scanf("%d", &num9);
	printf("整数2:");
	scanf("%d", &num10);
	printf("整数3:");
	scanf("%d", &num11);
	printf("整数4:");
	scanf("%d", &num12);
	max = num9;
	if (num10 > max) {
		max = num10;
	}
	if (num11 > max) {
		max = num11;
	}
	if (num12 > max) {
		max = num12;
	}
	printf("最大値は%dです。\n", max);

	//Drill 03-07
	int num13, num14, ans;
	puts("二つの整数を入力してください。");
	printf("整数1:");
	scanf("%d", &num13);
	printf("整数2:");
	scanf("%d", &num14);
	printf("それらの差は%dです。\n", (num13 > num14) ? num13 - num14 : num14 - num13);
	if (num13 > num14) {
		ans = num13 - num14;
	}
	else {
		ans = num14 - num13;
	}
	printf("それらの差は%dです。\n", ans);

	// Drill 03-08
	min = (num6 < num7) ? num6 : num7;
	min = (num3 < min) ? num3 : min;
	printf("最小値は%dです。\n", min);

	// Drill 03-09
	int num15, num16, num17;
	int sum = 0;
	printf("整数1:");
	scanf("%d", &num15);
	printf("整数2:");
	scanf("%d", &num16);
	printf("整数3:");
	scanf("%d", &num17);
	if (num15 == num16 && num16 == num17 && num17 == num15) {
		puts("三つの値は等しい");
	}
	else if (num15 != num16 && num16 != num17 && num17 != num15) {
		puts("三つの値は異なる");
	}
	else {
		puts("二つの値は等しい");
	}

	// Drill 03-10
	int num18, num19;
	puts("二つの整数を入力してください。");
	printf("整数A:");
	scanf("%d", &num18);
	printf("整数B:");
	scanf("%d", &num19);
	if ((num18 - num19) > 10 || (num19 - num18) > 10){
		puts("差は11以上です");
	}
	else {
		puts("差は10以下です");
	}

	// Drill 03-11
	int num20;
	printf("整数を入力してください:");
	scanf("%d", &num20);
	switch (num20 % 2) {
		case 0:
			puts("その数は奇数です");
			break;
		case 1:
			puts("その数は奇数です");
			break;
		default:
			puts("その数は対象外です");
			break;
	}

	// Drill 03-12
	int month;
	printf("何月ですか:");
	scanf("%d", &month);
	switch (month) {
		case 3:
		case 4:
		case 5:
			puts("春です");
			break;
		case 6:
		case 7:
		case 8:
			puts("夏です");
			break;
		case 9:
		case 10:
		case 11:
			puts("秋です");
			break;
		case 12:
		case 1:
		case 2:
			puts("冬です");
			break;
		default: puts("そんな月ありませんよ！！\a");
	}
	return 0;
}