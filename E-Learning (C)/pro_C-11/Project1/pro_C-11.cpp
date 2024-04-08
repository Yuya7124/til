#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// 1�����������_���Ŏ擾����֐�
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
// �������\�� (���s�͂��Ȃ�)�֐�(�|�C���^�֐�)
void put_string(const char* str) {
	while (*str) {
		putchar(*str++);
	}
}

// Drill 11-02
// ������str�̒��ɁA����c���܂܂�Ă���΁A���̕����ւ̃|�C���^��Ԃ��A�܂܂�Ă��Ȃ���΁ANULL��Ԃ��֐�
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
// ��������̉p����啶���ɕϊ�
void str_toupper(char* str) {
	while (*str = toupper(*str)) {
		*str++;
	}
}

// ��������̉p�����������ɕϊ�
void str_tolower(char* str) {
	while (*str = tolower(*str)) {
		*str++;
	}
}

// Drill 11-04
// ������ str ���̑S�Ă̐����������폜����֐�
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
// ��������Along�^�ɕϊ�����֐�
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

// ��������Adouble�^�ɕϊ�����֐�
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
	printf("���������͂��Ă�������:");
	scanf("%s", str1);
	put_string(str1);
	putchar('\n');

	// Drill 11-02
	char str2[100] = { '0' };
	char search = rand_char(1);
	char* find;
	printf("���������͂��Ă�������:");
	scanf("%s", str2);
	printf("��������: %c\n", search);
	find = str_chr(str2, search);
	if (find == NULL) {
		puts("�������������͌�����܂���ł����B");
	}
	else {
		printf("������������%c��\"%p\"�ɂ���܂��B\n", *find, find);
	}

	// Drill 11-03
	str_toupper(str1);
	printf("�啶��: %s\n", str1);
	str_tolower(str1);
	printf("������: %s\n", str1);

	// Drill 11-04
	del_digit(str1);
	printf("�����������폜�������e:%s\n", str1);

	// Drill 11-05
	char str3[100];
	int i_num = 0;
	double d_num = 0.00;

	printf("��������͂��Ă�������:");
	scanf("%s", str3);
	i_num = strtoi(str3);
	printf("����: %d\n", i_num);

	printf("��������͂��Ă�������:");
	scanf("%s", str3);
	d_num = strtof(str3);
	printf("���������_��: %f\n", d_num);
	printf("���������_��: %f\n", atof(str3));

	return 0;
}