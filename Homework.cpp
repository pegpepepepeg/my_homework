#include <__msvc_all_public_headers.hpp>

using namespace std;


struct lli {
	int MAXSIZE = 10;
	vector<bool> num;
	lli() { num.resize(MAXSIZE); }
	lli convert(string s) {
		num.resize(MAXSIZE);
		// placeholder;
	}
	int pref0() {
		for (int i = 0; i < MAXSIZE - 1; ++i)
			if (num[i])
				return i;
		return MAXSIZE;
	}
	void chs() {
		int r = 1;
		for (int i = 0; i < MAXSIZE; ++i) {
			int temp = !num[i] + r;
			num[i] = temp % 2, r = temp >= 2;
		}
	}
	bool empty() {
		for (int i = 0; i < MAXSIZE - 1; ++i) {
			if (num[i])
				return 0;
		}
		return 1;
	}
};

lli operator >> (lli a, int n) {
	for (int i = 0; i < a.MAXSIZE - 1; ++i)
		if (i + n < a.MAXSIZE - 1)
			a.num[i] = a.num[i + n];
		else
			a.num[i] = 0;
	return a;
}

lli operator << (lli a, int n) {
	for (int i = a.MAXSIZE - 1; i >= 0; --i)
		if (i - n >= 0)
			a.num[i] = a.num[i - n];
		else
			a.num[i] = 0;
	return a;
}

lli operator ^ (lli a, lli b){
	for (int i = 0; i < a.MAXSIZE; ++i)
		a.num[i] = (a.num[i] ^ b.num[i]);
	return a;
}

lli operator | (lli a, lli b) {
	for (int i = 0; i < a.MAXSIZE; ++i)
		a.num[i] = (a.num[i] || b.num[i]);
	return a;
}

lli operator & (lli a, lli b) {
	for (int i = 0; i < a.MAXSIZE; ++i)
		a.num[i] = (a.num[i] && b.num[i]);
	return a;
}

lli operator + (lli a, lli b) {
	lli c = lli();
	int r = 0;
	for (int i = 0; i < a.MAXSIZE; ++i) {
		int cnt = a.num[i] + b.num[i] + r;
		c.num[i] = (cnt % 2);
		r = cnt >= 2;
	}
	return c;
}

lli operator - (lli a, lli b) {
	b.chs();
	return a + b;
}

bool operator < (lli a, lli b) {
	return (a - b).num[a.MAXSIZE - 1];
}

bool operator == (lli a, lli b) {
	for (int i = 0; i < a.MAXSIZE; ++i)
		if (a.num[i] != b.num[i])
			return 0;
	return 1;
}

bool operator > (lli a, lli b) {
	return b < a;
}

bool operator <= (lli a, lli b) {
	return a < b || a == b;
}

bool operator >= (lli a, lli b) {
	return a > b || a == b;
}

bool operator != (lli a, lli b) {
	return !(a == b);
}

lli operator * (lli a, lli b) {
	bool sign = a.num[a.MAXSIZE - 1] != b.num[a.MAXSIZE - 1];
	if (a.num[a.MAXSIZE - 1] == 1)
		a.chs();
	if (b.num[a.MAXSIZE - 1] == 1)
		b.chs();
	int cnt = 0;
	lli a_shifted = a;
	lli result = lli();
	while (cnt < a.MAXSIZE) {
		if (b.num[cnt])
			result = result + a_shifted;
		a_shifted = (a_shifted + a_shifted);
		cnt++;
	}
	if (sign)
		result.chs();
	return result;
}

lli operator / (lli a, lli b) {
	bool sign = a.num[a.MAXSIZE - 1] != b.num[a.MAXSIZE - 1];
	if (a.num[a.MAXSIZE - 1] == 1)
		a.chs();
	if (b.num[a.MAXSIZE - 1] == 1)
		b.chs();
	lli result = lli(), mask = lli();
	mask.num[0] = 1;
	while (b < a) {
		b = (b << 1), mask = (mask << 1);
	}
	while (!mask.empty()) {
		if (a >= b)
			a = (a - b), result = (result + mask);
		b = (b >> 1), mask = (mask >> 1);
	}
	return result;
}

struct llr {
	lli d;
	int precision;
	llr() {};
	void normalize(int pref, int post) {
		while (precision < post)
			precision += 1, d.num.push_back(0);
		reverse(d.num.begin(), d.num.end());
		while (d.num.size() < pref + post)
			d.num.push_back(0);
		reverse(d.num.begin(), d.num.end());
	}
	int get_pref() {
		return d.num.size() - precision;
	}
};

bool operator < (llr a, llr b) {
	int pref, post;
	pref = max(a.get_pref(), b.get_pref());
	post = max(a.precision, b.precision);
	a.normalize(pref, post);
	b.normalize(pref, post);
	return (a.d < b.d);
}

bool operator > (llr a, llr b) {
	return b > a;
}

bool operator == (llr a, llr b) {
	return !(a > b) && !(a < b);
}

bool operator <= (llr a, llr b) {
	return (a < b) || (a == b);
}

bool operator >= (llr a, llr b) {
	return (a > b) || (a == b);
}

llr operator + (llr a, llr b) {
	int pref, post;
	pref = max(a.get_pref(), b.get_pref()) + 1;
	post = max(a.precision, b.precision);
	a.normalize(pref, post);
	b.normalize(pref, post);
	llr result = llr();
	result.d = a.d + b.d;
	result.precision = post;
	return result;
}

llr operator - (llr a, llr b) {
	b.d.chs();
	return a + b;
}

llr operator * (llr a, llr b) {
	int pref, post;
	pref = max(a.get_pref(), b.get_pref()) + 1;
	post = a.precision + b.precision;
	a.normalize(pref, post);
	b.normalize(pref, post);
	llr result = llr();
	result.d = a.d * b.d;
	result.precision = post;
	return result;
}

llr operator / (llr a, llr b) {
	int pref, post;
	pref = max(a.get_pref(), b.get_pref());
	post = max(a.precision, b.precision);
	a.normalize(pref, post);
	b.normalize(pref, post);
	llr result = llr();
	result.d = a.d / b.d;
	result.precision = post;
	return result;
}

int main()
{
	
}
