#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int MARK = 4;
const int NUMBER = 13;
const string JOKER = "JOKER";
const int HAND = 5;

const int TOTAL_CARDS = MARK * NUMBER + 1;

// カードの構造体
typedef struct {
	int mark;
	int num;
	string joker;
} CARD;

static CARD card[TOTAL_CARDS];	//トランプ
static CARD hand_card[HAND];	//手札カード
int top;	//配られたカードの一番上の位置

static const char* mark_str[MARK] = { "C","D","H","S" };
static const char* num_str[NUMBER] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };


// ゲームの初期化
void init(void) {
	// 乱数の初期化
	srand((unsigned int)time(NULL));

	// カード初期化
	for (int i = 0; i < MARK; i++) {
		for (int j = 0; j < NUMBER; j++) {
			card[i * NUMBER + j].mark = i;
			card[i * NUMBER + j].num = j;
		}
	}
	card[TOTAL_CARDS - 1].joker = JOKER;
	top = 0;
}

// カードをシャッフル
void shuffle(void) {
	unsigned int i, j;
	CARD tmp;
	i = TOTAL_CARDS;
	while (i > 0) {
		j = rand() % (i + 1);
		tmp = card[j];
		card[j] = card[i];
		card[i] = tmp;

		// シャッフル範囲縮小
		i--;
		
	}
}

// 手札を配る
void deal(void) {
	for (int i = 0; i < HAND; i++) {
		hand_card[i] = card[top];
		top++;
	}
}

// 手札情報
void show(void) {
	for (int i = 0; i < HAND; i++) {
		if (i < HAND - 1) {
			cout << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << ",";
		}
		else {
			cout << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << endl;
		}
	}
}

// 手札の交換
void exchange(void) {
	char input;
	int exchange[HAND];

	for (int i = 0;i < HAND;i++) {
		while (true) {
			cout << i+1 << "枚目:「" << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << "」 交換しますか？(Y/N) ";
			cin >> input;
			if (input == 'y') {
				exchange[i] = true;
				break;
			}
			else if (input == 'n') {
				exchange[i] = false;
				break;
			}
			else {
				cout << "yかnで入力してください" << endl;
			}
		}
	}
	
}


int main(void) {
	/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			cout << mark_str[i] << num_str[j] << endl;
		}
	}
	*/

	init();
	shuffle();
	deal();
	cout << "あなたの手札:";
	show();

	exchange();
}