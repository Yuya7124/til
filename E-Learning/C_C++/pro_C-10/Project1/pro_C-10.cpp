#include <stdio.h>
enum {
	January = 1,
	February = 2,
	March = 3,
	April = 4,
	May = 5,
	June = 6,
	July = 7,
	August = 8,
	September = 9,
	October = 10,
	November = 11,
	December = 12
};

// Drill 10-01

// 閏年か判別する関数
int leap_year(int year) {
	int leap_day;
	if (year % 400 == 0 && year % 100 != 0 && year % 4 == 0) {
		leap_day = 29;
	}
	else {
		leap_day = 28;
	}
	return leap_day;
}

// 月末日を取得する関数
int daylimit(int year, int month) {
	int limit;
	switch (month)
	{
	case February:
		limit = leap_year(year);
		break;
	case April:
	case June:
	case September:
	case November:
		limit = 30;
		break;
	default:
		limit = 31;
		break;
	}
	return limit;
}

// 設定した日付の前日を取得する関数
void yesterday(int* y, int* m, int* d) {
	if (*d != 1) {
		(*d)--;
	}
	else {
		if (*m == 1) {
			(*y)--;
			*m = 12;
		}
		else {
			(*m)--;
		}
		*d = daylimit(*y, *m);
	}
}

// 設定した日付の翌日を取得する関数
void tomorrow(int* y, int* m, int* d) {
	if (*d != daylimit(*y, *m)) {
		(*d)++;
	}
	else {
		if (*m == 12) {
			(*y)++;
			*m = 1;
			*d = 1;
		}
		else {
			(*m)++;
			*d = 1;
		}
	}
}

// 設定した日付が存在するか確認する関数
bool dateExist(int year, int month, int day) {
	if (year >= 0) {
		if (month <= 12 && month >= 1) {
			if (day >= 1) {
				if (day <= daylimit(year, month)) {
					return true;
				}
			}
		}
	}
	return false;
}

// Drill 10-02
// 整数を昇順に並べ替える関数
void swap(int *nx, int *ny) {
	int tmp = *nx;
	*nx = *ny;
	*ny = tmp;
}

// 2つ整数を比較し昇順に並べ替える関数
void sort2(int *n1, int *n2) {
	if (*n1 > *n2) {
		swap(n1, n2);
	}
}

// 3つの整数を昇順に並べ替える関数
void sort3(int *n1, int *n2, int *n3) {
	sort2(n1, n2);
	sort2(n2, n3); // 最大値がn3に決定
	sort2(n1, n2);
}

int main(void) {
	// Drill 10-01
	int year, month, day;
	while (true) {
		puts("好きな日付を入力してください。");
		printf("西暦:");
		scanf("%d", &year);
		printf("月　:");
		scanf("%d", &month);
		printf("日　:");
		scanf("%d", &day);
		if (dateExist(year, month, day) == false) {
			printf("そのような日付は存在しません\n\a");
			break;
		}
		printf("入力した日付: %d年%2d月%2d日\n", year, month, day);
		tomorrow(&year, &month, &day);
		printf("その翌日　　:%d年%2d月%2d日\n", year, month, day);
		yesterday(&year, &month, &day);
		yesterday(&year, &month, &day);
		printf("その前日　　:%d年%2d月%2d日\n", year, month, day);
	}

	// Drill 10-02
	int num1, num2, num3;
	puts("三つの整数を入力してください。");
	printf("整数1:");
	scanf("%d", &num1);
	printf("整数2:");
	scanf("%d", &num2);
	printf("整数3:");
	scanf("%d", &num3);
	putchar('\n');

	sort3(&num1, &num2, &num3);

	puts("これらを昇順に並べ替えました。");
	printf("整数1: %d\n", num1);
	printf("整数2: %d\n", num2);
	printf("整数3: %d\n", num3);

	return 0;
}