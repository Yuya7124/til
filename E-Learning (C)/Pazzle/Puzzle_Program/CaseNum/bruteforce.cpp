#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void permutation(const vector<string>& cards, vector<string>& result, unsigned n) {
	if (result.size() == n) {
		for (auto& i : result) cout << i;
		cout << endl;
	}
	else {
		for (auto& i : cards) {
			if (find(result.cbegin(), result.cend(), i) == result.cend()) {
				result.push_back(i);
				permutation(cards, result, n);
				result.pop_back();
			}
		}
	}
}

void combination(const vector<string>& cards, vector<string>& result, unsigned n) {
	if (result.size() == n) {
		for (auto& i : result) cout << i;
		cout << endl;
	}
	else {
		vector<string>::const_iterator i;
		if (result.empty()) i = cards.cbegin();
		else i = find(cards.cbegin(), cards.cend(), result.back()) + 1;
		while (i != cards.end()) {
			result.push_back(*i);
			combination(cards, result, n);
			result.pop_back();
			++i;
		}
	}
}

int main(void) {
	int case_n = 0;
	vector<string> cards = { "A", "B", "C", "D", "E" };
	/*do {
		for (auto& i : cards) cout << i;
		case_n++;
		cout << endl;
	} while (next_permutation(cards.begin(), cards.end()));
	cout << case_n << "’Ê‚è" << endl;*/
	vector<string> result;
	permutation(cards, result, 3);
	combination(cards, result, 3);
}