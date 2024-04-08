#include <time.h>
#include <stdio.h>

// Drill-12-01
// 現在の時刻を表示する関数
void put_time(void) {
	time_t current;
	struct tm* local;
	time(&current);
	local = localtime(&current);
	printf("%02d時%02d分%02d秒", 
		local -> tm_hour, 
		local -> tm_min, 
		local -> tm_sec);
}

// 文字列を、double型に変換する関数
double strtof(const char* nptr) {
	int flag = 0;
	double number = 0;
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
	puts("現在の時刻は");
	put_time();
	puts("です。");

	return 0;
}