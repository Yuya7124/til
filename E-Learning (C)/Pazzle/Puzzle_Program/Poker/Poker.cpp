#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <algorithm>

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

//各カード昇順に並べ替え
void card_sort(void) {
	int i, j;
	CARD tmp;
	int jk_count = joker_count();

	// ジョーカーを一番後に移動
	for (int i = 0; i < HAND; i++) {
		if (hand_card[i].joker > 0 && jk_count > 0) {
			tmp = hand_card[i];
			hand_card[i] = hand_card[HAND - jk_count];
			hand_card[HAND - jk_count] = tmp;
			jk_count--;
		}
	}

	// 各カード昇順に並べ替え
	for (int i = 0; i < HAND - joker_count(); i++) {
		for (int j = i; j < HAND - joker_count(); j++) {
			if (hand_card[i].num == hand_card[j].num) {
				if (hand_card[i].mark > hand_card[j].mark) {
					tmp = hand_card[j];
					hand_card[j] = hand_card[i];
					hand_card[i] = tmp;
				}
			}
			else {
				if (hand_card[i].num > hand_card[j].num) {
					tmp = hand_card[j];
					hand_card[j] = hand_card[i];
					hand_card[i] = tmp;
				}
			}
		}
	}
}

// 手札情報
void show(void) {
	for (int i = 0; i < HAND; i++) {
		if (i < HAND - 1) {
			if (hand_card[i].joker == 0) {
				cout << mark_str[hand_card[i].mark] << num_str[hand_card[i].num] << "  ";
			}
			else {
				cout << "JOKER" << "  ";
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
	for (int i = 0; i < HAND; i++) {
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
	for (int i = 0; i < HAND; i++) {
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
	for (int i = 0; i < HAND; i++) {
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
	for (int i = 0; i < HAND; i++) {
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
	int i, j;
	int card_sum = 0;
	int card_min = 0;
	int dif_hand = 0; // 今の手札と次の手札の差
	int cons_num = 0; // 連続した番号の数

	card_min = hand_card[0].num;
	// 手札の最小値が「10」より上の時
	if (card_min > NUMBER - HAND) {
		card_min = NUMBER - HAND;
	}

	for (int k = 0; k < HAND; k++) {
		card_sum += hand_card[k].num + 2;
	}

	if (joker_count() > 0) {
		// ジョーカーあり
		for (int k = 0; k < (HAND - 1) - joker_count(); k++) {
			// 今の手札と次の手札の差
			dif_hand = hand_card[k + 1].num - hand_card[k].num;

			if (dif_hand == 0) {
				break;
			}
			switch (dif_hand) {
			case 1:
				// 差が全て1の時
				if (k == (HAND - 2)) {
					if (joker_count() == 2) {
						if (hand_card[k + 1].num == NUMBER - 1) { // 例 _ _ Q K A
							count_num[NUMBER - 5]++;
							count_num[NUMBER - 4]++;
						}
						else {
							count_num[hand_card[HAND - 2].num + 1]++;
							count_num[hand_card[HAND - 2].num + 2]++;
						}
					}
					if (joker_count() == 1) {
						if (hand_card[k + 1].num == NUMBER - 1) { // 例 _ J Q K A
							count_num[NUMBER - 5]++;
						}
						else {
							count_num[hand_card[HAND - 2].num + 1]++;
						}
					}
				}
				break;
			case 2:
				if (hand_card[k + 1].num == NUMBER - 1) { // 例 10 J Q _ A
					count_num[NUMBER - 2]++;
				}
				else {
					count_num[hand_card[k].num + 1]++;
				}

				break;
			case 3:
				if (joker_count() == 2) { // 例 10 J _ _ A
					if (hand_card[k + 1].num == NUMBER - 1) {
						count_num[NUMBER - 2]++;
						count_num[NUMBER - 3]++;
					}
					else {
						count_num[hand_card[k].num + 1]++;
						count_num[hand_card[k].num + 2]++;
					}
				}
				break;
			}
		}
	}
	
	for (int i = 0; i < NUMBER; i++) {
		if (count_num[i] == 1) {
			cons_num++;
		}
	}
	if (cons_num == HAND) {
		return true;
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
	int change_num = 0;

	if (!Flush()) {
		return false;
	}
	if (count_num[NUMBER - 1] != 1) {
		return false;
	}
	for (int i = (NUMBER - 1) - (HAND - 1); i < NUMBER; i++) {
		if (joker_count() > 0) {
			change_num = joker_count();
			// ジョーカーあり
			if (count_num[i] == 0 && change_num != 0) {
				switch (i) {
				case 8:
					count_num[i]++;
					change_num--;
					break;
				case 9:
					count_num[i]++;
					change_num--;
					break;
				case 10:
					count_num[i]++;
					change_num--;
					break;
				case 11:
					count_num[i]++;
					change_num--;
					break;
				case 12:
					count_num[i]++;
					change_num--;
					break;
				}
			}
		}
		if (count_num[i] != 1) {
			return false;
		}
	}
	return true;
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

	card_sort();
	cout << "あなたの手札:　";
	show();
	cout << endl;

	exchange_player();
	card_sort();
	cout << "あなたの手札:　";
	show();
	cards_count();
	cout << " -> " << hand_strenght() << endl;

	for (int i = 0; i < com_player;i++) {
		exchange_com();
		card_sort();
		cout << "COM_" << i + 1 << " の手札:　";
		show();
		cards_count();
		cout << " -> " << hand_strenght() << endl;
	}
	return 0;
}