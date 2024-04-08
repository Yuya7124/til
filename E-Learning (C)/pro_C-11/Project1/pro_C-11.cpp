#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// 1文字をランダムで取得する関数
char rand_char(int text) {
	char c = 'a';
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
	for (int i = 0; i < text; i++) {
		c = rand() % 26 + 'a';
	}
	return c;
}

// Drill 11-01
// 文字列を表示 (改行はしない)関数(ポインタ関数)
void put_string(const char* str) {
	while (*str) {
		putchar(*str++);
	}
}

// Drill 11-02
// 文字列strの中に、文字cが含まれていれば、その文字へのポインタを返し、含まれていなければ、NULLを返す関数
char* str_chr(const char* str, char c) {
	char* find;
	find = NULL;
	do {
		if (*str == c) {
			find = (char*)str;
			break;
		}
	} while (*str++); {
		return find;
	}
}

// Drill 11-03
// 文字列内の英字を大文字に変換
void str_toupper(char* str) {
	while (*str = toupper(*str)) {
		*str++;
	}
}

// 文字列内の英字を小文字に変換
void str_tolower(char* str) {
	while (*str = tolower(*str)) {
		*str++;
	}
}

// Drill 11-04
// 文字列 str 内の全ての数字文字を削除する関数
void del_digit(char* str) {
	int count = 0;
	do {
		if (*str >= '0' && *str <= '9') {
			count++;
		}
		else {
			*(str - count) = *str;
		}
	}
	while (*str++); {}
}

// Drill 11-05
// 文字列を、long型に変換する関数
int strtoi(const char* nptr) {
	int number = 0;
	do {
		if (*nptr <= '9' && *nptr >= '0') {
			number *= 10;
			number += (*nptr - '0');
		}
	} while (*nptr++); {
		return number;
	}
}

// 文字列を、double型に変換する関数
double strtof(const char* nptr) {
	int flag = 0;
	double number=0;
	int count = 0;
	do {
		if (*nptr == '.') { 
			flag = -1; 
		}
		if (*nptr <= '9' && *nptr >= '0') {
			if (flag) {
				double temp = (*nptr - '0');
				count++;
				for (int i = 0; i < count; i++) {
					temp /= 10;
				}
				number += temp;
			}
			else {
				number *= 10;
				number += (*nptr - '0');
			}
		}
	} while (*nptr++);
	return number;
}

int main(void) {

	// Drill 11-01
	char str1[100];
	printf("文字列を入力してください:");
	scanf("%s", str1);
	put_string(str1);
	putchar('\n');

	// Drill 11-02
	char str2[100] = { '0' };
	char search = rand_char(1);
	char* find;
	printf("文字列を入力してください:");
	scanf("%s", str2);
	printf("検索文字: %c\n", search);
	find = str_chr(str2, search);
	if (find == NULL) {
		puts("検索した文字は見つかりませんでした。");
	}
	else {
		printf("検索した文字%cは\"%p\"にあります。\n", *find, find);
	}

	// Drill 11-03
	str_toupper(str1);
	printf("大文字: %s\n", str1);
	str_tolower(str1);
	printf("小文字: %s\n", str1);

	// Drill 11-04
	del_digit(str1);
	printf("数字文字を削除した内容:%s\n", str1);

	// Drill 11-05
	char str3[100];
	int i_num = 0;
	double d_num = 0.00;

	printf("整数を入力してください:");
	scanf("%s", str3);
	i_num = strtoi(str3);
	printf("整数: %d\n", i_num);

	printf("実数を入力してください:");
	scanf("%s", str3);
	d_num = strtof(str3);
	printf("浮動小数点数: %f\n", d_num);
	printf("浮動小数点数: %f\n", atof(str3));

	return 0;
}