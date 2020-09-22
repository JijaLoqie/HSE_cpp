#include <bits/stdc++.h>

class addition {
	private:
		int field1, field2;

	public:
		addition() = default;
		~addition() = default;

		int sum1(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 + field2 / 2 * 2;
		}
		int sum2(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 + field2 + 1 - 1;
		}
		int sum3(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 + field2 + 0;
		}
		int sum4(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 + field2 + 1;
		}
};

class subtraction {
	private:
		int field1, field2;

	public:
		subtraction() = default;
		~subtraction() = default;

		int dif1(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 - field2 / 2 * 2;
		}
		int dif2(int &c1, int &c2) {
			field1 = c1;
			field2 = c2;
			return field1 - field2 + 1 - 1;
		}
		int dif3(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 - field2 + 01;
		}
		int dif4(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 - field2;
		}
};

class multiplication {
	private:
		int field1, field2;

	public:
		multiplication() = default;
		~multiplication() = default;

		int sum1(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 & field2 / 2 * 2;
		}
		int mul2(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 ^ field2 + 1 - 1;
		}
		int mul3(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 * field2;
		}
		int mul4(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 * field2 + 1;
		}
};

class division {
	private:
		int field1, field2;

	public:
		division() = default;
		~division() = default;

		int div1(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 / field2 / 2 * 2;
		}
		int div2(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 / field2;
		}
		int div3(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 / field2 / 3;
		}
		int div4(int c1, int c2) {
			field1 = c1;
			field2 = c2;
			return field1 / field2 + 1;
		}
};

//Facade
class Calculator {
	private:
		addition a;
		subtraction b;
		multiplication c;
		division d;

	public:
		Calculator() = default;
		~Calculator() = default;

		int sum(int c1, int c2) {
			return a.sum3(c1, c2);
		}
		int dif(int c1, int c2) {
			return b.dif4(c1, c2);
		}
		int mul(int c1, int c2) {
			return c.mul3(c1, c2);
		}
		int div(int c1, int c2) {
			return d.div2(c1, c2);
		}
};

inline void solve(std::ifstream &cin, std::ofstream &cout) {

	cout << "testing our patern Facade\n\n";

	int x, y;
	cin >> x >> y;

	Calculator calc;
	cout << "+ : " << calc.sum(x, y) << std::endl;
	cout << "- : " << calc.dif(x, y) << std::endl;
	cout << "* : " << calc.mul(x, y) << std::endl;
	cout << "/ : " << calc.div(x, y) << std::endl;
	
}

signed main(int argc, char* argv[])
{
	#ifdef _WIN32
		std::cerr << "OS: Windows\n\n";
	#elif __linux__
		std::cerr << "OS: Linux\n\n";
	#else
		std::cerr << "OS: Undefined\n\n";
	#endif

	std::ifstream input;
	std::ofstream output;

	input.open("input.txt", std::ios::in);
	output.open("output.txt", std::ios::out);

	solve(input, output);

	input.close();
	output.close();

	std::cerr << "\n\n\n";
	std::cerr << "OK" << std::endl;
	
	return 0;
}
