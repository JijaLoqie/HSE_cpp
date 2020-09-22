#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

class SegmentTree
{
	private:
		struct node {
			node* left_child;
			node* rigth_child;
			int left, right, sum;
			node() {
				left_child = nullptr;
				rigth_child = nullptr;
			}
			~node() {
				delete left_child;
				delete rigth_child;
			}
		};
		node* ROOT;
		node* Build(int left, int right, std::vector <int> &arr) {
			node *T = new node();
			T->left = left;
			T->right = right;
			if (left == right) {
				T->sum = arr[left];
			} else {
				int mid = (left + right) >> 1;
				T->left_child = Build(left, mid, arr);
				T->rigth_child = Build(mid + 1, right, arr);
				T->sum = T->left_child->sum + T->rigth_child->sum;
			}
			return T;
		}
		int Query(node* T, int left, int right) {
			if (T == nullptr)
				return 0;
			if (T->left > right || T->right < left)
				return 0;
			if (left <= T->left && T->right <= right)
				return T->sum;
			int ans1 = Query(T->left_child, left, right);
			int ans2 = Query(T->rigth_child, left, right);
			return ans1 + ans2;
		}
	public:
		SegmentTree() {
			ROOT = nullptr;
		}
		SegmentTree(size_t SIZE) {
			std::vector <int> temporary(SIZE, 0);
			ROOT = Build(0, int(SIZE - 1), temporary);
		}
		SegmentTree(std::vector <int> &arr) {
			ROOT = Build(0, (int)arr.size() - 1, arr);
		}
		int Query(int left, int right) {
			return Query(ROOT, left, right);
		}
		~SegmentTree() = default;
};

//0-indexing realization
inline void solve(std::ifstream &input, std::ofstream &output) {
	std::vector <int> arr = { 1, 3, 15, 19, 2, 7};
	SegmentTree MyTree(arr);
	output << MyTree.Query(0, 2) << std::endl; //19
	output << MyTree.Query(1, 2) << std::endl; //18
	output << MyTree.Query(0, 4) << std::endl; //40
	output << MyTree.Query(3, 5) << std::endl; //28
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
