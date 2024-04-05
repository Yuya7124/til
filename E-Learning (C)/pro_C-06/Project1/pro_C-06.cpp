#include<stdio.h>
#include <math.h>
#define NUMBER 5
#define STUDENTS 5
#define SUBJECTS 3
#define JAPANESE 0
#define MATH 1
#define ENGLISH 2

// 小さい方の値を返す関数
// Drill 06-01
int minof(int x, int y) {
	if (x < y) {
		return x;
	}
	else {
		return y;
	}
}

// 最小値を返す関数
// Drill 06-02
int min3(int x, int y, int z) {
	if (x <= y && x <= z) {
		return x;
	}
	else if (y <= z && y <= x) {
		return y;
	}
	else {
		return z;
	}
}
// 三乗値を返す関数
// Drill 06-03
int cube(int x) {
	return pow(x, 3);
}

// 四乗値を返す関数
// Drill 06-04
int pow4(int x) {
	return pow(x, 4);
}

// 画面に「こんにちは」と表示して改行を行う関数
// Drill 06-05
void hello(void) {
	printf("こんにちは\n");
}

// 要素数がnoであるint型の配列vcの要素の最小値を返す関数
// Drill 06-06
int min_of(const int vc[], int no) {
	int min = vc[--no];
	for (int i = no; i > 0; i--) {
		if (min > vc[i - 1]) {
			min = vc[i - 1];
		}
	}
	return min;
}

// 配列 vc の並びを逆順にする関数
// Drill 06-07
void rev_intary(int vc[], int no) {
	int tmp;
	for (int i = 0; i < (no / 2); i++) {
		tmp = vc[i];
		vc[i] = vc[no - i - 1];
		vc[no - i - 1] = tmp;
	}
}

// 配列 v2 の並びを逆順にしたものを配列 v1 に格納する関数
// Drill 06-08
void intary_rcpy(int v1[], const int v2[], int no) {
	for (int i = 0; i < no; i++) {
		v1[i] = v2[no - i - 1];
	}
}

// 2行3列の行列 ma と3行2列の行列 mb の積を、2行2列の行列 mc に格納する関数
// Drill 06-09
void mul(const int ma[2][3], const int mb[3][2], int mc[2][2]) {
	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 2; k++) {
			for (int j = 0; j < 3; j++) {
				mc[i][k] += ma[i][j] * mb[j][k];
			}
			printf("%4d", mc[i][k]);
		}
		putchar('\n');
	}
}

//科目別の最高点を求める関数
// Drill 06-10
int max_point(const int tensu[STUDENTS][SUBJECTS], int subject) {
	int i = 0;
	int max = tensu[i++][subject];
	for (i = 0; i < STUDENTS; i++) {
		if (max < tensu[i][subject]) {
			max = tensu[i][subject];
		}
	}
	return max;
}

//各学生の平均点を求める関数
void person_av(const int tensu[STUDENTS][SUBJECTS], double ave[STUDENTS]) {
	for (int i = 0; i < STUDENTS; i++) {
		int tmp = 0;
		for (int j = 0; j < SUBJECTS; j++) {
			tmp += tensu[i][j];
		}
		ave[i] = (double)tmp / SUBJECTS;
	}
}

int main(void) {
	int num1, num2, num3;
	puts("二つの整数を入力してください。");
	printf("整数1:");
	scanf("%d", &num1);
	printf("整数2:");
	scanf("%d", &num2);
	printf("整数3:");
	scanf("%d", &num3);
	printf("小さい方の値は%dです。\n", minof(num1, num2));
	printf("最も小さい方の値は%dです。\n", min3(num1, num2, num3));
	printf("その三乗は%dです。\n", cube(num1));
	printf("その四乗は%dです。\n", pow4(num1));
	hello();

	int tensu[NUMBER] = { 0 };
	puts("五つの整数を入力します");
	for (int i = 0; i < NUMBER; i++) {
		printf("整数を入力してください:");
		scanf("%d", &tensu[i]);
	}
	printf("最小の整数は%dです\n", min_of(tensu, NUMBER));
	
	int array[NUMBER] = {};
	for (int i = 0; i < NUMBER; i++) {
		array[i] = i;
		printf("array[%d]=%d\n", i, array[i]);
	}
	putchar('\n');
	rev_intary(array, NUMBER);
	for (int i = 0; i < NUMBER; i++) {
		printf("array[%d]=%d\n", i, array[i]);
	}

	int array1[NUMBER] = { 0 };
	int array2[NUMBER] = { 0 };
	for (int i = 0; i < NUMBER; i++) {
		array2[i] = i;
		printf("array2[%d]=%d\n", i, array2[i]);
	}
	putchar('\n');
	intary_rcpy(array1, array2, NUMBER);
	for (int i = 0; i < NUMBER; i++) {
		printf("array1[%d]=%d\n", i, array1[i]);
	}

	int x[2][3] = { {1,2,3},{4,5,6} };
	int y[3][2] = { {1,5},{5,3},{8,1} };
	int ans[2][2] = {};
	mul(x, y, ans);
	
	int tensu1[STUDENTS][SUBJECTS] = { {88, 90, 73}, {44, 79, 40}, {74, 63, 55}, {95, 89, 99}, {77, 24, 34} };
	double ave[STUDENTS] = { 0 };

	person_av(tensu1, ave);
	puts("各学生の平均点:");
	for (int i = 0; i < STUDENTS; i++) {
		printf("%d番の学生:%2f\n", i, ave[i]);
	}
	puts("各学生の最高点:");
	for (int i = 0; i < SUBJECTS; i++) {
		if (i == JAPANESE) {
			printf("Japanese:");
		}
		else if (i == MATH) {
			printf("Mathematics:");
		}
		else if (i == ENGLISH) {
			printf("English:");
		}
		printf("%d\n", max_point(tensu1, i));
	}
	return 0;
}