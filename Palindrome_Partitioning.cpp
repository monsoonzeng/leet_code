//============================================================================
// Name        : Palindrome_Partitioning.cpp
// Author      : yunfengzeng
// Version     :
// Copyright   : yunfengzeng
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
	vector<vector<string> > partition(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		const char* input = s.c_str();
		size_t len = s.length();
		vector<vector<string> > pa_part;
		if (len < 1) {
			return pa_part;
		}
		//init matrix for store palindrome
		bool* p_m = (bool*) calloc(len * len, sizeof(bool));
		bool** pp_m = (bool**) malloc(len * sizeof(bool*));
		for (size_t i = 0; i < len; ++i) {
			pp_m[i] = p_m + (i * len);
		}
		pp_m = init_palindrome_matrix(pp_m, input, len);
		get_palindrome_partition(pa_part, vector<string>(), pp_m, input, 0,
				len - 1);
		free(p_m);
		free(pp_m);
		return pa_part;
	}

private:
	vector<vector<string> >& get_palindrome_partition(
			vector<vector<string> >& pa_part, vector<string> pre_part,
			bool** pp_m, const char* input, size_t start, size_t end) {
		size_t index = start;
		if (start == end) {
			//cur is a min palindrome
			//append cur to pre_part

			pre_part.push_back(string(input + start, 1));
			pa_part.push_back(pre_part);
			return pa_part;
		} else if (start > end) {
			pa_part.push_back(pre_part);
			return pa_part;
		}
		size_t pre_end = pre_part.size();
		for (; index <= end; ++index) {
			if (pp_m[start][index]) {
				//cur substring is palindrome
				string cur_str(input + start, index - start + 1);
				if (pre_part.size() <= pre_end) {
					pre_part.push_back(cur_str);
				} else {
					pre_part[pre_end] = cur_str;
				}
				get_palindrome_partition(pa_part, pre_part, pp_m, input,
						index + 1, end);
			}
		}
		return pa_part;
	}
	bool** init_palindrome_matrix(bool** pp_m, const char* input,
			const size_t len) {

		//set matrix : pp_m[i][j] =true (i<=j)indecate input from i to j is palindrome
		for (size_t row = 0; row < len; ++row) {
			size_t col = row;
			pp_m[row][col] = true;
			for (col = row + 1; col < len; ++col) {
				pp_m[row][col] = is_palindrome(input, row, col);
			}
		}
		return pp_m;
	}

	bool is_palindrome(const char* input, size_t start, size_t end) {
		if (start > end) {
			return false;
		}
		for (; start < end; ++start, --end) {
			if (input[start] != input[end]) {
				return false;
			}
		}
		return true;
	}
};

void print_result(vector<vector<string> >& result) {
	for (size_t i = 0; i < result.size(); ++i) {
		for (size_t j = 0; j < result[i].size(); ++j) {
			printf("%s\t", result[i][j].c_str());
		}
		printf("\n");
	}
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	Solution so;
	vector<vector<string> > r = so.partition("cdd");
	print_result(r);
	return 0;
}
