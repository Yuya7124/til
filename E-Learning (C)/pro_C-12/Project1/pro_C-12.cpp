#include <time.h>
#include <stdio.h>

// Drill-12-01
// ���݂̎�����\������֐�
void put_time(void) {
	time_t current;
	struct tm* local;
	time(&current);
	local = localtime(&current);
	printf("%02d��%02d��%02d�b", 
		local -> tm_hour, 
		local -> tm_min, 
		local -> tm_sec);
}

// ��������Adouble�^�ɕϊ�����֐�
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
	puts("���݂̎�����");
	put_time();
	puts("�ł��B");

	return 0;
}