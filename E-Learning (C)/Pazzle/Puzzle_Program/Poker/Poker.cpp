#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

const int MARK = 4;
const int NUMBER = 13;
const int JOKER = 2;
const int HAND = 5;

const int TOTAL_CARDS = MARK * NUMBER + JOKER;

// カードの構造体
typedef struct {
	int mark;
	int num;
	int joker;
} CARD;

static CARD card[TOTAL_CARDS];	//トランプ
static CARD hand_card[HAND];	//手札カード
int top;	//配られたカードの一番上の位置

//カード情報
static const char* mark_str[MARK] = { "C","D","H","S" };
static const char* num_str[NUMBER] = { "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K", "A" };
static const char* joker_str[JOKER] = { "", "JOKER" };

//手札の各マークの枚数
static int count_mark[MARK];
//手札の各数字の枚数
static int count_num[NUMBER];

// ゲームの初期化
void init(void) {
	// 乱数の初期化
	srand((unsigned int)time(NULL));

	// カード初期化
	for (int i = 0; i < MARK; i++) {
		for (int j = 0; j < NUMBER; j++) {
			card[i * NUMBER + j].mark = i;
			card[i * NUMBER + j].num = j;
			// cout << "card[" << i * NUMBER + j << "] = " << mark_str[i] << num_str[j] << endl;
		}
	}
	for (int i = 0; i < JOKER; i++) {
		card[TOTAL_CARDS + (i - JOKER)].joker = i - JOKER;
		// cout << "card[" << TOTAL_CARDS + (i - JOKER) << "] = " << joker_str[i] << endl;
	}
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
			if (hand_card[i].joker < 0) {
				cout << "JOKER" << ",";
			}
			else {
				cout << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << ", ";
			}
		}
		else {
			if (hand_card[i].joker < 0) {
				cout << "JOKER" << endl;
			}
			else {
				cout << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << endl;
			}
		}
	}
}

// 手札の交換(プレイヤー)
void exchange_player(void){
	char input;
	bool exchange[HAND];

	// 交換カードの受付
	for (int i = 0;i < HAND;i++) {
		while (true) {
			if (hand_card[i].joker < 0) {
				cout << i + 1 << "枚目: [" << "JOKER" << "] 交換しますか？(Y/N) ";
			}
			else {
				cout << i + 1 << "枚目: [" << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << "] 交換しますか？(Y/N) ";
			}
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

	// カード交換
	for (int i = 0;i < HAND;i++) {
		if (exchange[i] == true) {
			if (top >= TOTAL_CARDS) {
				cout << "カード不足のため、交換できません" << endl;
				continue;
			}
			hand_card[i] = card[top];
			top++;
		}
	}
	cout << endl;
}

// 手札の交換(コンピュータ)
void exchange_com(void) {
	int input;
	bool exchange[HAND];

	// 交換カードの受付
	for (int i = 0;i < HAND;i++) {
		while (true) {
			input = rand() % 1;
			if (input == 0) {
				exchange[i] = true;
				break;
			}
			else if (input == 1) {
				exchange[i] = false;
				break;
			}
		}
	}

	// カード交換
	for (int i = 0;i < HAND;i++) {
		if (exchange[i] == true) {
			if (top >= TOTAL_CARDS) {
				cout << "カード不足のため、交換できません" << endl;
				continue;
			}
			hand_card[i] = card[top];
			top++;
		}
	}
}

int main(void) {
	// プレイヤー人数
	int player = 1;
	int com_player = 3;

	init();
	shuffle();
	for (int i = 0;i < (player + com_player);i++) {
		deal();
	}
	
	cout << "あなたの手札:　";
	show();

	exchange_player();
	cout << "あなたの手札:　";
	show();

	for (int i = 0; i < com_player;i++) {
		exchange_com();
		cout << "COM_" << i + 1 << " の手札:　";
		show();
	}
}