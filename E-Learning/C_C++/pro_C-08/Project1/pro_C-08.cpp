#include<stdio.h>
#define diff(x, y) ((x > y) ? (x - y) : (y - x))
#define max(x, y) ((x > y) ? x : y)
#define swap(type, a, b) {int tmp; tmp = a; a = b; b =tmp;}

// 整数 n の階乗を返す関数
int factorial(int n) {
	if (n > 0) {
		return n * factorial(n - 1);
	}
	else {
		return 1;
	}
}

// 整数nの階乗を再帰を使わずに返す関数
int factorial_tmp(int n) {
	int tmp = 1;
	for (; n > 1; n--) {
		tmp *= n;
	}
	return tmp;
}

// 異なるn個の整数から r個を取り出す組合せの数nCrを求める関数
int combination(int n, int r) {
	if (n == r || r == 0) {
		return 1;
	}
	else {
		return combination(n - 1, r - 1) + combination(n - 1, r);
	}
}

int main(void) {
	// Drill 08-01
	int num1, num2;
	double num3, num4;
	
	printf("整数A:");
	scanf("%d", &num1);
	printf("整数B:");
	scanf("%d", &num2);
	printf("その差は%dです。\n", diff(num1, num2));

	printf("実数C:");
	scanf("%lf", &num3);
	printf("実数D:");
	scanf("%lf", &num4);
	printf("その差は%lfです。\n", diff(num3, num4));

	// Drill 08-02
	int a, b, c, d;
	for (int i = 0; i < 4; i++) {
		a = i % 4;
		b = (i + 1) % 4;
		c = (i + 2) % 4;
		d = (i + 3) % 4;
		printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
		printf("max(max(a, b), max(c, d)) = %d\n", max(max(a, b), max(c, d)));
		putchar('\n');
	}

	// Drill 08-03
	int e = 2, f = 9;
	double g = 3.33, h = -22.3;
	printf("e = %d, f = %d\n", e, f);
	swap(int, e, f);
	printf("e = %d, f = %d\n", e, f);

	printf("g = %lf, h = %lf\n", g, h);
	swap(double, g, h);
	printf("g = %lf, h = %lf\n", g, h);

	// Drill 08-04
	int num5;
	printf("整数を入力してください:");
	scanf("%d", &num5);
	printf("その数の階乗は%dです。\n", factorial(num5));
	printf("その数の階乗(無再帰で)は%dです。\n", factorial_tmp(num5));

	// Drill 08-05
	int n, r;
	puts("nCrを求めます。");
	printf("n = ");
	scanf("%d", &n);
	printf("r = ");
	scanf("%d", &r);

	if (n >= 0 && r >= 0) {
		if (n > r - 1) {
			printf("%dC%d = %d\n", n, r, combination(n, r));
		}
	}
	else {
		printf("定義できない数です。\n");
	}

	// Drill 08-06
	int ch;
	int cnt[10] = { 0 };
	while (1) {
		ch = getchar();
		if (ch == EOF) {
			break;
		}
		if (ch >= '0' && ch <= '9') {
			cnt[ch - '0']++;
		}
		puts("数字文字の出現回数");
		for (int i = 0; i < 10; i++) {
			// printf("'%d':%d\n", i, cnt[i]);
			printf("'%d':", i);
			for (; cnt[i] > 0; cnt[i]--) {
				putchar('*');
			}
			putchar('\n');
		}
	}
	return 0;
}