#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// 文字列strの中に、文字cが含まれていれば(複数ある場合は、最も先頭側)その添字を返し、含まれて居なければ-1を返す関数
int str_char(const char str[], int c) {
	for (int i = 0; str[i] != 0; i++) {
		if (str[i] == c) {
			return i;
		}	
	}
	return -1;
}

// 文字列strの中に、文字tが含まれている個数を返す関数
int str_chnum(const char str[], int c) {
	int count = 0;
	for (int i = 0; str[i]!= '\0'; i++) {
		if (str[i] == c) {
			count++;
		}
	}
	return count;
}

// 文字列を表示 (改行はしない)関数
void put_string(const char str[]) {
	/*unsigned i = 0;
	while (str[i]) {
		putchar(str[i++]);
	}*/
	printf("%s", str);
}

// 文字列strをno回、連続して表示する関数
void put_stringn(const char str[], int no) {
	for (int i = 0; i < no;i++) {
		printf("%s", str);
	}
}

// 文字列を後ろから逆に表示する関数
void put_rstring(const char str[]) {
	unsigned len = 0;
	while (str[len]) {
		len++;
	}
	for (; len > 0; len--) {
		putchar(str[len - 1]);
	}	
}

// 文字列 str を逆順に格納する関数
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

// 文字列 str 内の全ての数字文字を削除する関数
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
	printf("文字列を入力してください:");
	scanf("文字列 str 内の全ての数字文字を削除する関数%s", str2);
	no = str_char(str2, ch1);
	if (no == -1) {
		printf("%cは見つかりませんでした。\n", ch1);
	}
	else {
		printf("%cは添え字%dにあります。\n", ch1, no);
	}

	// Drill 09-03
	printf("%cは%d個ありました。\n", ch2, str_chnum(str2, ch2));

	// Drill 09-04
	char str3[100];
	printf("文字列を入力してください:");
	scanf("%s", str3);
	put_string(str3);
	putchar('\n');

	// Drill 09-05
	int times;
	char str4[128];
	printf("文字列を入力してください:");
	scanf("%s", str4);
	printf("連続回数を入力してください:");
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
	printf("文字列を入力してください:");
	scanf("%s", str5);
	del_digit(str5);
	printf("数字文字を削除した内容:%s\n", str5);

	return 0;
}