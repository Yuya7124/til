#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// ������str�̒��ɁA����c���܂܂�Ă����(��������ꍇ�́A�ł��擪��)���̓Y����Ԃ��A�܂܂�ċ��Ȃ����-1��Ԃ��֐�
int str_char(const char str[], int c) {
	for (int i = 0; str[i] != 0; i++) {
		if (str[i] == c) {
			return i;
		}	
	}
	return -1;
}

// ������str�̒��ɁA����t���܂܂�Ă������Ԃ��֐�
int str_chnum(const char str[], int c) {
	int count = 0;
	for (int i = 0; str[i]!= '\0'; i++) {
		if (str[i] == c) {
			count++;
		}
	}
	return count;
}

// �������\�� (���s�͂��Ȃ�)�֐�
void put_string(const char str[]) {
	/*unsigned i = 0;
	while (str[i]) {
		putchar(str[i++]);
	}*/
	printf("%s", str);
}

// ������str��no��A�A�����ĕ\������֐�
void put_stringn(const char str[], int no) {
	for (int i = 0; i < no;i++) {
		printf("%s", str);
	}
}

// ���������납��t�ɕ\������֐�
void put_rstring(const char str[]) {
	unsigned len = 0;
	while (str[len]) {
		len++;
	}
	for (; len > 0; len--) {
		putchar(str[len - 1]);
	}	
}

// ������ str ���t���Ɋi�[����֐�
void rev_string(char str[]) {
	char tmp;
	int len = 0;
	while (str[len]) {
		len++;
		for (int i = 0; i < (len / 2); i++) {
			tmp = str[i];
			str[i] = str[len - 1];
			str[len - 1] = tmp;
		}
	}
	str[len] = '\0';
}

// ������ str ���̑S�Ă̐����������폜����֐�
void del_digit(char str[]) {
	unsigned i = 0, count = 0;
	while (str[i]) {
		if (str[i] >= '0' && str[i] <= '9') {
			count++;
		}
		else {
			str[i - count] = str[i];
			i++;
		}
	}
	str[i - count] = '\0';
}

int main(void) {
	// Drill 09-01
	char str1[] = "ABC";
	printf("%s\n", str1);
	str1[0] = '\0';
	printf("%s\n", str1);

	// Drill 09-02
	char str2[128];
	char ch1 = rand_char(1);
	char ch2 = rand_char(1);
	int no;
	printf("���������͂��Ă�������:");
	scanf("������ str ���̑S�Ă̐����������폜����֐�%s", str2);
	no = str_char(str2, ch1);
	if (no == -1) {
		printf("%c�͌�����܂���ł����B\n", ch1);
	}
	else {
		printf("%c�͓Y����%d�ɂ���܂��B\n", ch1, no);
	}

	// Drill 09-03
	printf("%c��%d����܂����B\n", ch2, str_chnum(str2, ch2));

	// Drill 09-04
	char str3[100];
	printf("���������͂��Ă�������:");
	scanf("%s", str3);
	put_string(str3);
	putchar('\n');

	// Drill 09-05
	int times;
	char str4[128];
	printf("���������͂��Ă�������:");
	scanf("%s", str4);
	printf("�A���񐔂���͂��Ă�������:");
	scanf("%d", &times);
	put_stringn(str4, times);
	putchar('\n');

	// Drill 09-06
	put_rstring(str3);

	// Drill 09-07
	rev_string(str3);
	printf("%s\n", str3);

	// Drill 09-08
	char str5[128];
	printf("���������͂��Ă�������:");
	scanf("%s", str5);
	del_digit(str5);
	printf("�����������폜�������e:%s\n", str5);

	return 0;
}