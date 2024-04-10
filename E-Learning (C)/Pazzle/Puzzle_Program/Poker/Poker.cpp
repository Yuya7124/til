#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>
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
static const char* num_str[NUMBER] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
static const char* joker_str[JOKER] = { "", "JOKER" };

//手札の各マークの枚数
static int count_mark[MARK];
//手札の各数字の枚数
static int count_num[NUMBER];
//手札のジョーカーの枚数
static int count_joker[JOKER];

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
		card[TOTAL_CARDS + (i - JOKER)].joker = i + 1;
		// cout << "card[" << TOTAL_CARDS + (i - JOKER) << "] = " << joker_str[i] << endl;
	}
	top = 0;
}

// カードをシャッフル
void shuffle(void) {
	unsigned int i, j;
	CARD tmp;
	i = TOTAL_CARDS - 1;
	while (i > 0) {
		j = rand() % (i + 1);
		tmp = card[j];
		card[j] = card[i];
		card[i] = tmp;
		/*if (card[i].joker == 0) {
			cout << "card[" << i - 1 << "] = " << mark_str[card[i].mark] << num_str[card[i].num] << endl;
		}
		else {
			cout << "card[" << i - 1 << "] = JOKER" << endl;
		}*/

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
			if (hand_card[i].joker == 0) {
				cout << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << ", ";
			}
			else {
				cout << "JOKER" << ", ";
			}
		}
		else {
			if (hand_card[i].joker == 0) {
				cout << mark_str[hand_card[i].mark] << num_str[hand_card[i].num];
			}
			else {
				cout << "JOKER";
			}
		}
	}
}

// 手札の交換(プレイヤー)
void exchange_player(void) {
	char input;
	bool exchange[HAND];

	// 交換カードの受付
	for (int i = 0;i < HAND;i++) {
		while (true) {
			if (hand_card[i].joker == 0) {
				cout << i + 1 << "枚目: [" << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << "] 交換しますか？(Y/N) ";
			}
			else {
				cout << i + 1 << "枚目: [" << "JOKER" << "] 交換しますか？(Y/N) ";
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

// ジョーカーの枚数
int joker_count(void) {
	int jk_count = 0;
	// ジョーカーの枚数の初期化
	for (int i = 0; i < JOKER; i++) {
		count_joker[i] = 0;
	}

	for (int i = 0; i < HAND; i++) {
		if (hand_card[i].joker > 0) {
			jk_count++;
		}		
	}
	return jk_count;
}

// 各カードの集計情報閲覧
void card_view(void) {
	cout << endl;
	// 各マークの枚数
	for (int i = 0; i < MARK; i++) {
		cout << mark_str[i] << ": " << count_mark[i] << " ";
	}
	cout << endl;
	// 各数字の枚数
	for (int i = 0; i < NUMBER; i++) {
		cout << num_str[i] << ": " << count_num[i] << " ";
	}
	cout << endl;
	// ジョーカーの枚数
	cout << "JOKER: " << joker_count() << endl;
}

// 各種カードの集計
void cards_count(void) {
	// 各マークの枚数の初期化
	for (int i = 0; i < MARK; i++) {
		count_mark[i] = 0;
	}
	// 各数字の枚数の初期化
	for (int i = 0; i < NUMBER; i++) {
		count_num[i] = 0;
	}
	// 各種類の集計
	for (int i = 0; i < HAND; i++) {
		if (hand_card[i].joker == 0) {
			count_mark[hand_card[i].mark]++;
			count_num[hand_card[i].num]++;
		}
	}
	// card_view();
}

// ワンペア
bool OnePair(void) {
	int pairs = 0;
	for (int i = 0; i < NUMBER; i++) {
		if (count_num[i] == 2) {
			pairs++;
		}	
	}
	if (pairs == 1) {
		return true;
	}
	if (pairs == 0 && joker_count() == 1) {
		return true;
	}
	return false;
}

// ツーペア
bool TwoPairs(void) {
	int pairs = 0;
	for (int i = 0; i < NUMBER; i++) {
		if (count_num[i] == 2) {
			pairs++;
		}
		if (pairs == 2) {
			return true;
		}
	}
	return false;
}

// スリーカード
bool ThreeCards(void) {
	for (int i = 0; i < NUMBER; i++) {
		if (count_num[i] == 3) {
			return true;
		}
		if (count_num[i] == 2 && joker_count() == 1) {
			return true;
		}
		if (count_num[i] == 1 && joker_count() == 2) {
			return true;
		}
	}
	return false;
}

// ストレート
bool Straight(void) {
	for (int j = 0; j < (NUMBER - HAND); j++) {
		for (int i = j; i < j + HAND; i++) {
			if (count_num[i] == 1) {
				if (i == j + HAND) {
					return true;
				}
			}
			if (joker_count() > 0) {
				if (hand_card[i].joker > 0) {
					if (i != j) {
						count_num[hand_card[i].num - 1] = 1;
					}
				}
			}
		}
	}
	return false;
}

// フラッシュ
bool Flush(void) {
	for (int i = 0; i < MARK; i++) {
		if (count_mark[i] == 5) {
			return true;
		}
		if (count_mark[i] == 4 && joker_count() == 1) {
			return true;
		}
		if (count_mark[i] == 3 && joker_count() == 2) {
			return true;
		}
	}
	return false;
}

// フルハウス
bool FullHouse(void) {
	int three_cards = 0;
	int two_cards = 0;
	for (int i = 0; i < NUMBER; i++) {
		if (count_num[i] == 2) {
			two_cards++;
		}
		if (count_num[i] == 3) {
			three_cards++;
		}
	}
	if (three_cards == 1 && two_cards == 1) {
		return true;
	}
	if (two_cards == 2 && joker_count() == 1) {
		return true;
	}
	return false;
}

// フォーカード
bool FourCards(void) {
	for (int i = 0; i < NUMBER; i++) {
		if (count_num[i] == 4) {
			return true;
		}	
		if (count_num[i] == 3 && joker_count() == 1) {
			return true;
		}
		if (count_num[i] == 2 && joker_count() == 2) {
			return true;
		}
	}
	return false;
}

// ストレートフラッシュ
bool StraightFlush(void) {
	if (Straight() && Flush()) {
		return true;
	}
	return false;
}

// ロイヤルストレートフラッシュ
bool RoyalStraightFlush(void) {
	if (Flush()) {
		if (count_num[NUMBER - 1] == 1) {
			for (int i = NUMBER - (HAND - 1); i < NUMBER; i++) {
				if (count_num[i] == 1) {
					return true;
				}
			}
		}
	}
	return false;
}

// ファイブカード
bool FiveCards(void) {
	for (int i = 0; i < NUMBER; i++) {
		if (count_num[i] == 4 && joker_count() == 1) {
			return true;
		}
		if (count_num[i] == 3 && joker_count() == 2) {
			return true;
		}
	}
	return false;
}

string hand_strenght(void) {
	string strenght = "ノーペア"; //　手札の役

	if (FiveCards()) {
		strenght = "ファイブカード";
		return strenght;
	}

	if (RoyalStraightFlush()) {
		strenght = "ロイヤルストレートフラッシュ";
		return strenght;
	}

	if (StraightFlush()) {
		strenght = "ストレートフラッシュ";
		return strenght;
	}

	if (FourCards()) {
		strenght = "フォーカード";
		return strenght;
	}

	if (FullHouse()) {
		strenght = "フルハウス";
		return strenght;
	}

	if (Flush()) {
		strenght = "フラッシュ";
		return strenght;
	}

	if (Straight()) {
		strenght = "ストレート";
		return strenght;
	}

	if (ThreeCards()) {
		strenght = "スリーカード";
		return strenght;
	}

	if (TwoPairs()) {
		strenght = "ツーペア";
		return strenght;
	}

	if (OnePair()) {
		strenght = "ワンペア";
		return strenght;
	}

	return strenght;
}

int main(void) {
	// プレイヤー人数
	int player = 1;
	int com_player = 3;

	init();
	shuffle();
	for (int i = 0; i < (player + com_player); i++) {
		deal();
	}

	cout << "あなたの手札:　";
	show();
	cout << endl;

	exchange_player();
	cout << "あなたの手札:　";
	show();
	cards_count();
	cout << " -> " << hand_strenght() << endl;

	for (int i = 0; i < com_player;i++) {
		exchange_com();
		cout << "COM_" << i + 1 << " の手札:　";
		show();
		cards_count();
		cout << " -> " << hand_strenght() << endl;
	}
}