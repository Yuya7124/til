#include<stdio.h>
#include<limits.h>

// 整数x中のセットされたビット数を返す関数
int count_bits(unsigned x) {
	int count = 0;
	while (x) {
		if (x & 1U) {
			count++;
			x >>= 1;
		}
	}
	return count;
}

// unsigned型のビット数を返す
int int_bits(void) {
	return (count_bits(~0U));
}

// unsigned型のビット内容を表示
void print_bits(unsigned x) {
	for (int i = int_bits()- 1; i >= 0; i--) {
		putchar(((x >> i) & 1U) ? '1' : '0');
	}
}

// unsigned型のビット内容を表示
void print_bits(unsigned x, int n) {
	for (int i = n - 1; i >= 0; i--) {
		putchar(((x >> i) & 1U) ? '1' : '0');
	}
}

// 符号無し整数xのposビット目からn個のビットを、1にした値を返す関数
unsigned set_n(unsigned x, int pos, int n) {
	int count = 0;
	while (count < n) {
		x |= (1 << (pos + count - 1));
		count++;
	}
	return x;
}

// 符号無し整数xのposビット目からn個のビットを、0にした値を返す関数
unsigned reset_n(unsigned x, int pos, int n) {
	int count = 0;
	while (count < n) {
		x &= ~(1 << (pos + count - 1));
		count++;
	}
	return x;
}

// 符号無し整数xのposビット目からn個のビットを、反転した値を返す関数
unsigned inverse_n(unsigned x, int pos, int n) {
	int count = 0;
	while (count < n) {
		x ^= (1 << (pos + count - 1));
		count++;
	}
	return x;
}

// 符号無し整数xを右にnビット回転した値を返す関数
unsigned rrotate(unsigned x, int n) {
	int i = int_bits();
	return (x >> n) | (x << (i - n));
}

// 符号無し整数xを左にnビット回転した値を返す関数
unsigned lrotate(unsigned x, int n) {
	int i = int_bits();
	return (x << n) | (x >> (i - n));
}

int main(void) {
	unsigned nx;
	int pos, bit, n;

	unsigned no, snum, tmp;
	int tmp_no, tmp_snum, rnum;

	printf("2進数のbitサイズを入力してください:");
	scanf("%d", &bit);
	printf("最大65535で非負の整数を入力してください:");
	scanf("%u", &nx);
	printf("変換を開始するビット番号を入力してください:");
	scanf("%d", &pos);
	printf("変換するビット数を入力してください:");
	scanf("%d", &n);

	printf("入力した整数                = ");
	print_bits(nx, bit);
	printf(" [%d]\n", nx);
	printf("指定ビットをセットした値    = ");
	print_bits(set_n(nx, pos, n), bit);
	printf(" [%d]\n", set_n(nx, pos, n));
	printf("指定ビットをリセットした値  = ");
	print_bits(reset_n(nx, pos, n), bit);
	printf(" [%d]\n", reset_n(nx, pos, n));
	printf("指定ビットを反転した        = ");
	print_bits(inverse_n(nx, pos, n), bit);
	printf(" [%d]\n", inverse_n(nx, pos, n));

	// Drill 07-01
	printf("非負の整数を入力してください: ");
	scanf("%d", &tmp_no);
	no = (unsigned)tmp_no;
	printf("シフトする数(非負の整数): ");
	scanf("%d", &tmp_snum);
	snum = (unsigned)tmp_snum;
	putchar('\n');
	tmp = no;
	for (int i = 0; i < snum; i++) {
		tmp *= 2;
	}
	printf("%u << %u = %u\n", no, snum, no << snum);
	printf("%u * (2 ^ %u) = %u\n", no, snum, tmp);
	putchar('\n');
	tmp = no;
	for (int i = 0; i < snum; i++) {
		tmp /= 2;
	}
	printf("%u >> %u = %u\n", no, snum, no >> snum);
	printf("%u / (2 ^ %u) = %u\n", no, snum, tmp);

	// Drill 07-02
	printf("左右にいくつ回転しますか(非負の整数): ");
	scanf("%d", &rnum);
	putchar('\n');

	printf("入力した数のビット内容 : "); 
	print_bits(no);
	putchar('\n');
	printf("右に%d回転したビット内容: ", rnum);
	print_bits(rrotate(no, rnum));
	putchar('\n');
	printf("左に%d回転したビット内容: ", rnum);
	print_bits (lrotate(no, rnum));
	putchar('\n');
	return 0;
}