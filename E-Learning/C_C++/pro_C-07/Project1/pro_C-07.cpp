#include<stdio.h>
#include<limits.h>

// ����x���̃Z�b�g���ꂽ�r�b�g����Ԃ��֐�
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

// unsigned�^�̃r�b�g����Ԃ�
int int_bits(void) {
	return (count_bits(~0U));
}

// unsigned�^�̃r�b�g���e��\��
void print_bits(unsigned x) {
	for (int i = int_bits()- 1; i >= 0; i--) {
		putchar(((x >> i) & 1U) ? '1' : '0');
	}
}

// unsigned�^�̃r�b�g���e��\��
void print_bits(unsigned x, int n) {
	for (int i = n - 1; i >= 0; i--) {
		putchar(((x >> i) & 1U) ? '1' : '0');
	}
}

// ������������x��pos�r�b�g�ڂ���n�̃r�b�g���A1�ɂ����l��Ԃ��֐�
unsigned set_n(unsigned x, int pos, int n) {
	int count = 0;
	while (count < n) {
		x |= (1 << (pos + count - 1));
		count++;
	}
	return x;
}

// ������������x��pos�r�b�g�ڂ���n�̃r�b�g���A0�ɂ����l��Ԃ��֐�
unsigned reset_n(unsigned x, int pos, int n) {
	int count = 0;
	while (count < n) {
		x &= ~(1 << (pos + count - 1));
		count++;
	}
	return x;
}

// ������������x��pos�r�b�g�ڂ���n�̃r�b�g���A���]�����l��Ԃ��֐�
unsigned inverse_n(unsigned x, int pos, int n) {
	int count = 0;
	while (count < n) {
		x ^= (1 << (pos + count - 1));
		count++;
	}
	return x;
}

// ������������x���E��n�r�b�g��]�����l��Ԃ��֐�
unsigned rrotate(unsigned x, int n) {
	int i = int_bits();
	return (x >> n) | (x << (i - n));
}

// ������������x������n�r�b�g��]�����l��Ԃ��֐�
unsigned lrotate(unsigned x, int n) {
	int i = int_bits();
	return (x << n) | (x >> (i - n));
}

int main(void) {
	unsigned nx;
	int pos, bit, n;

	unsigned no, snum, tmp;
	int tmp_no, tmp_snum, rnum;

	printf("2�i����bit�T�C�Y����͂��Ă�������:");
	scanf("%d", &bit);
	printf("�ő�65535�Ŕ񕉂̐�������͂��Ă�������:");
	scanf("%u", &nx);
	printf("�ϊ����J�n����r�b�g�ԍ�����͂��Ă�������:");
	scanf("%d", &pos);
	printf("�ϊ�����r�b�g������͂��Ă�������:");
	scanf("%d", &n);

	printf("���͂�������                = ");
	print_bits(nx, bit);
	printf(" [%d]\n", nx);
	printf("�w��r�b�g���Z�b�g�����l    = ");
	print_bits(set_n(nx, pos, n), bit);
	printf(" [%d]\n", set_n(nx, pos, n));
	printf("�w��r�b�g�����Z�b�g�����l  = ");
	print_bits(reset_n(nx, pos, n), bit);
	printf(" [%d]\n", reset_n(nx, pos, n));
	printf("�w��r�b�g�𔽓]����        = ");
	print_bits(inverse_n(nx, pos, n), bit);
	printf(" [%d]\n", inverse_n(nx, pos, n));

	// Drill 07-01
	printf("�񕉂̐�������͂��Ă�������: ");
	scanf("%d", &tmp_no);
	no = (unsigned)tmp_no;
	printf("�V�t�g���鐔(�񕉂̐���): ");
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
	printf("���E�ɂ�����]���܂���(�񕉂̐���): ");
	scanf("%d", &rnum);
	putchar('\n');

	printf("���͂������̃r�b�g���e : "); 
	print_bits(no);
	putchar('\n');
	printf("�E��%d��]�����r�b�g���e: ", rnum);
	print_bits(rrotate(no, rnum));
	putchar('\n');
	printf("����%d��]�����r�b�g���e: ", rnum);
	print_bits (lrotate(no, rnum));
	putchar('\n');
	return 0;
}