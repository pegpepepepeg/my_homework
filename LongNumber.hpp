#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>

class LongNumber {
public:
	std::vector<bool> d;
	int post;
	bool sign;
	LongNumber() = default;
	LongNumber(int size);
	LongNumber(double num);
	LongNumber(long double num);
	std::vector<bool> chs(const std::vector<bool> num);
	bool normalize(LongNumber a, LongNumber b);
	bool vec_bool_lesser(std::vector<bool> a, std::vector<bool> b);
	bool operator < (LongNumber b);
	bool operator > (LongNumber b);
	bool operator == (LongNumber b);
	bool operator <= (LongNumber b);
	bool operator >= (LongNumber b);
	bool operator != (LongNumber b);
	bool vec_bool_greater(std::vector<bool> a, std::vector<bool> b);

	bool vec_bool_equal(std::vector<bool> a, std::vector<bool> b);

	std::vector<bool> sub_add(std::vector<bool> a, std::vector<bool> b);

	std::vector<bool> sub_sub(std::vector<bool> a, std::vector<bool> b);

	LongNumber operator + (LongNumber b);
	LongNumber operator - (LongNumber b);

	std::vector<bool> sub_mul(std::vector<bool> a, std::vector<bool> b);

	LongNumber operator * (LongNumber b);

	std::vector<bool> sub_div_vec_shlr(std::vector<bool> num, int side);

	bool vecbool_empty(std::vector<bool> num);

	std::vector<bool> sub_div(std::vector<bool> a, std::vector<bool> b);

	LongNumber operator / (LongNumber b);
};

