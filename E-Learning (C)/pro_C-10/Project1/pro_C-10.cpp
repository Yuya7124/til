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

// �[�N�����ʂ���֐�
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

// ���������擾����֐�
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

// �ݒ肵�����t�̑O�����擾����֐�
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

// �ݒ肵�����t�̗������擾����֐�
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

// �ݒ肵�����t�����݂��邩�m�F����֐�
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
// �����������ɕ��בւ���֐�
void swap(int *nx, int *ny) {
	int tmp = *nx;
	*nx = *ny;
	*ny = tmp;
}

// 2�������r�������ɕ��בւ���֐�
void sort2(int *n1, int *n2) {
	if (*n1 > *n2) {
		swap(n1, n2);
	}
}

// 3�̐����������ɕ��בւ���֐�
void sort3(int *n1, int *n2, int *n3) {
	sort2(n1, n2);
	sort2(n2, n3); // �ő�l��n3�Ɍ���
	sort2(n1, n2);
}

int main(void) {
	// Drill 10-01
	int year, month, day;
	while (true) {
		puts("�D���ȓ��t����͂��Ă��������B");
		printf("����:");
		scanf("%d", &year);
		printf("���@:");
		scanf("%d", &month);
		printf("���@:");
		scanf("%d", &day);
		if (dateExist(year, month, day) == false) {
			printf("���̂悤�ȓ��t�͑��݂��܂���\n\a");
			break;
		}
		printf("���͂������t: %d�N%2d��%2d��\n", year, month, day);
		tomorrow(&year, &month, &day);
		printf("���̗����@�@:%d�N%2d��%2d��\n", year, month, day);
		yesterday(&year, &month, &day);
		yesterday(&year, &month, &day);
		printf("���̑O���@�@:%d�N%2d��%2d��\n", year, month, day);
	}

	// Drill 10-02
	int num1, num2, num3;
	puts("�O�̐�������͂��Ă��������B");
	printf("����1:");
	scanf("%d", &num1);
	printf("����2:");
	scanf("%d", &num2);
	printf("����3:");
	scanf("%d", &num3);
	putchar('\n');

	sort3(&num1, &num2, &num3);

	puts("�����������ɕ��בւ��܂����B");
	printf("����1: %d\n", num1);
	printf("����2: %d\n", num2);
	printf("����3: %d\n", num3);

	return 0;
}