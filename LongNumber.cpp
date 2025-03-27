#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include "LongNumber.hpp"

const long double eps = 1e-12;
LongNumber::LongNumber(int size) {
	post = size, sign = 0;
	d.resize(size * 2);
}

LongNumber::LongNumber(double num) {
	post = 256;
	sign = (num <= 0);
	num = abs(num);
	d.resize(512);
	long double whole, fract;
	fract = modfl(num, &whole);
	int pointer = 256;
	while (pointer < 512 && (whole - 0) > eps)
		d[pointer] = fmodl(whole, 2) >= 0.999999, whole = std::truncl(whole / 2.0), pointer++;
	pointer = 255;
	while (pointer >= 0 && (fract - 0) > eps)
		fract *= 2.0, d[pointer] = std::truncl(fract) >= 0.999999, fract -= std::truncl(fract), pointer--;
}
LongNumber::LongNumber(long double num) {
	post = 256;
	sign = (num <= 0);
	num = abs(num);
	d.resize(512);
	long double whole, fract;
	fract = modfl(num, &whole);
	int pointer = 256;
	while (pointer < 512 && (whole - 0) > eps)
		d[pointer] = fmodl(whole, 2) >= 0.999999, whole = std::truncl(whole / 2.0), pointer++;
	pointer = 255;
	while (pointer >= 0 && (fract - 0) > eps)
		fract *= 2.0, d[pointer] = std::truncl(fract) >= 0.999999, fract -= std::truncl(fract), pointer--;
}

std::vector<bool> LongNumber::chs(const std::vector<bool> num) {
	int r = 1; std::vector<bool> res(num.size());
	for (int i = 0; i < num.size(); ++i) {
		int temp = !num[i] + r;
		res[i] = temp % 2, r = temp >= 2;
	}
	return res;
}

bool LongNumber::normalize(LongNumber a, LongNumber b) {
	assert(a.d.size() == b.d.size() && a.post == b.post);
	return true;
	// indian pogramin
}

bool LongNumber::vec_bool_lesser(std::vector<bool> a, std::vector<bool> b) {
	for (int i = a.size() - 1; i >= 0; --i) {
		if (a[i] > b[i])
			return 0;
		if (a[i] < b[i])
			return 1;
	}
	return 0;
}

bool LongNumber::operator < (LongNumber b) {
	LongNumber a = *this;
	normalize(a, b);
	if (a.sign == 0)
		if (b.sign == 0)
			return vec_bool_lesser(a.d, b.d);
		else
			return 0;
	else
		if (b.sign == 0)
			return 1;
		else
			return vec_bool_lesser(b.d, a.d);
}

bool LongNumber::operator > (LongNumber b) {
	LongNumber a = *this;
	return b < a;
}

bool LongNumber::operator == (LongNumber b) {
	LongNumber a = *this;
	return !(a > b) && !(a < b);
}

bool LongNumber::operator <= (LongNumber b) {
	LongNumber a = *this;
	return (a < b) || (a == b);
}

bool LongNumber::operator >= (LongNumber b) {
	LongNumber a = *this;
	return (a > b) || (a == b);
}

bool LongNumber::operator !=(LongNumber b) {
	LongNumber a = *this;
	return !(a == b);
}

bool LongNumber::vec_bool_greater(std::vector<bool> a, std::vector<bool> b) {
	return vec_bool_lesser(b, a);
}

bool LongNumber::vec_bool_equal(std::vector<bool> a, std::vector<bool> b) {
	return (!vec_bool_lesser(a, b) && !vec_bool_greater(a, b));
}

std::vector<bool> LongNumber::sub_add(std::vector<bool> a, std::vector<bool> b) {
	std::vector<bool> c = std::vector<bool>(a.size(), 0);
	int r = 0;
	for (int i = 0; i < a.size(); ++i) {
		int cnt = a[i] + b[i] + r;
		c[i] = (cnt % 2);
		r = (cnt >= 2);
	}
	return c;
}

std::vector<bool> LongNumber::sub_sub(std::vector<bool> a, std::vector<bool> b) {
	return sub_add(a, chs(b));
}

LongNumber LongNumber::operator + (LongNumber b) {
	LongNumber a = *this;
	normalize(a, b);
	LongNumber result = LongNumber();
	result.d = sub_add(a.d, b.d);
	result.post = a.post;
	if (a.sign == 0) {
		if (b.sign == 0) {
			// a > 0, b > 0

			result.d = sub_add(a.d, b.d);
			result.sign = 0;
			//a + b
			//a > 0, b > 0 -> (a + b) > 0
		}
		else {
			// a > 0, b < 0

			if (vec_bool_greater(a.d, b.d))
				result.d = sub_sub(a.d, b.d);
			else
				result.d = sub_sub(b.d, a.d);
			result.sign = (vec_bool_lesser(a.d, b.d) || vec_bool_equal(a.d, b.d));
			//a - b
			// a <= b -> a - b <= 0
		}
	}
	else {
		if (b.sign == 0) {
			// a < 0, b > 0

			if (vec_bool_greater(b.d, a.d))
				result.d = sub_sub(b.d, a.d);
			else
				result.d = sub_sub(a.d, b.d);

			result.sign = !vec_bool_lesser(a.d, b.d);
			//b - a
			//a < b -> b - a > 0
		}
		else {
			// a < 0, b < 0

			result.d = sub_add(a.d, b.d);
			result.sign = 1;
			//-(a + b)
			// a >= 0, b >= 0 -> -(a + b) < 0
		}
	}
	return result;
}

LongNumber LongNumber::operator - (LongNumber b) {
	LongNumber a = *this;
	normalize(a, b);
	LongNumber result = LongNumber();
	result.d = sub_sub(a.d, b.d);
	result.post = a.post;
	if (a.sign == 0) {
		if (b.sign == 0) {

			//a > 0, b > 0

			if (vec_bool_greater(a.d, b.d))
				result.d = sub_sub(a.d, b.d);
			else
				result.d = sub_sub(b.d, a.d);
			result.sign = (vec_bool_lesser(a.d, b.d) || vec_bool_equal(a.d, b.d));
			//a - b
			// a <= b -> a - b <= 0
		}
		else {

			//a > 0, b < 0
			
			result.d = sub_add(a.d, b.d);
			result.sign = 0;
			// a - (-b) = a + b
			// a > 0, - (-b) >= 0 -> a + b > 0
		}
	}
	else {
		if (b.sign == 0) {

			//a < 0, b > 0

			result.d = sub_add(a.d, b.d);
			result.sign = 1;
			// -a -(+b) = -(a + b)
			// a >= 0, b > 0 -> a + b >= 0, -(a + b) <= 0
		}
		else {

			//a < 0, b < 0

			if (vec_bool_greater(b.d, a.d))
				result.d = sub_sub(b.d, a.d);
			else
				result.d = sub_sub(a.d, b.d);
			result.sign = !vec_bool_lesser(a.d, b.d);
			//-a -(-b) = -a + b = b - a

		}
	}
	return result;
}

std::vector<bool> LongNumber::sub_mul(std::vector<bool> a, std::vector<bool> b) {
	int cnt = 0;
	std::vector<bool> a_shifted = a;
	std::vector<bool> result(a.size(), 0);
	while (cnt < a.size()) {
		if (b[cnt])
			result = sub_add(result, a_shifted);
		a_shifted = sub_add(a_shifted, a_shifted);
		cnt++;
	}
	for (int i = 0; i < a.size() / 2; i++)
		result = sub_div_vec_shlr(result, 1);
	return result;
}

LongNumber LongNumber::operator * (LongNumber b) {
	LongNumber a = *this;
	normalize(a, b);
	LongNumber result = LongNumber();
	result.d = sub_mul(a.d, b.d);
	result.post = a.post;
	result.sign = (a.sign != b.sign);
	return result;
}

std::vector<bool> LongNumber::sub_div_vec_shlr(std::vector<bool> num, int side) {
	if (side == 1) {
		for (int i = 0; i < num.size() - 1; ++i)
			num[i] = num[i + 1];
		num[num.size() - 1] = 0;
		return num;
	}
	else {
		for (int i = num.size() - 1; i > 0; --i)
			num[i] = num[i - 1];
		num[0] = 0;
		return num;
	}
}

bool LongNumber::vecbool_empty(std::vector<bool> num) {
	for (int i = 0; i < num.size(); ++i)
		if (num[i] != 0)
			return 0;
	return 1;
}

std::vector<bool> LongNumber::sub_div(std::vector<bool> a, std::vector<bool> b) {
	std::vector<bool> result(a.size(), 0), mask = result;
	mask[32] = 1;
	while (vec_bool_lesser(b, a))
		b = sub_div_vec_shlr(b, -1), mask = sub_div_vec_shlr(mask, -1);
	while (!vecbool_empty(mask)) {
		if (vec_bool_lesser(b, a) || vec_bool_equal(a, b))
			a = sub_sub(a, b), result = sub_add(result, mask);
		b = sub_div_vec_shlr(b, 1), mask = sub_div_vec_shlr(mask, 1);
	}
	return result;
}

LongNumber LongNumber::operator / (LongNumber b) {
	LongNumber a = *this;
	normalize(a, b);
	LongNumber result = LongNumber();
	result.d = sub_div(a.d, b.d);
	result.post = a.post;
	result.sign = (a.sign ^ b.sign);
	return result;
}