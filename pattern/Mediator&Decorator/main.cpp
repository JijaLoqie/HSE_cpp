#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>

std::mt19937 rnd(time(0));

inline int rand_int(int left, int rigth) {
	int RND_NUM = rnd();
	return left + (abs(RND_NUM) % (rigth - left));
}

class Mediator;
class QsortMediator;
class WorkElement;
class DataLoaderWorker;
class SortingWorker;
class QsortingWorker;
class PrinterWorker;

enum Command {
	LOAD,
	SORT,
	PRINT
};

class Mediator {
	public:
		virtual ~Mediator() = default;
		virtual void Notify(Command cmd) = 0;
};

class WorkElement {
	public:
		virtual ~WorkElement() {}
		void SetMediator(Mediator* _med) {
			med = _med;
		}
	protected:
		Mediator* med = nullptr;
};

class DataLoaderWorker : public WorkElement {
	public:
		DataLoaderWorker() = default;
		~DataLoaderWorker() = default;
		void Load(std::string path) {
			std::ifstream stream;
			stream.open(path, std::ios::in);
			int temp_number;
			arr.clear();
			while (!stream.eof() && (stream >> temp_number))
				arr.push_back(temp_number);
			stream.close();
			med->Notify(Command::LOAD);
		}
		std::vector <int>& Get_array() {
			return arr;
		}
	public:
		std::vector <int> arr;
};

class SortingWorker : public WorkElement {
	public:
		SortingWorker() = default;
		virtual ~SortingWorker() = default;
		virtual void Sort(std::vector<int>& vec) = 0;
};

class QsortingWorker : public SortingWorker {
	public:
		QsortingWorker() = default;
		~QsortingWorker() = default;
		void Sort(std::vector<int>& vec) override {
			QUICK_SORT(vec, 0, vec.size());
			med->Notify(Command::SORT);
		}
	private:
		void QUICK_SORT(std::vector <int>& vec, size_t left, size_t right) {
			if (right - left <= 1)
				return;
			size_t rnd_pos = static_cast<size_t>(rand_int(left, right));
			int elem = vec.at(rnd_pos);
			size_t pos = left;
			for (size_t i = left; i < right; i++)
				if (vec.at(i) < elem)
					std::swap(vec.at(i), vec.at(pos++));
			if (pos == left)
				std::swap(vec.at(pos++), vec.at(rnd_pos));
			QUICK_SORT(vec, left, pos);
			QUICK_SORT(vec, pos, right);
		}
};

class PrinterWorker : public WorkElement {
	public:
		PrinterWorker() = default;
		~PrinterWorker() = default;
		void Print(std::vector<int>& vec) {
			for (const auto& element : vec)
				std::cout << element << '\t';
			std::cout << std::endl;
			med->Notify(Command::PRINT);
		}
};

class QsortMediator : public Mediator {
	public:
		QsortMediator(
			DataLoaderWorker* _loader, 
			QsortingWorker* _sorting, 
			PrinterWorker* _printer
		) :
			loader(_loader),
			sorting(_sorting),
			printer(_printer)
		{
			loader->SetMediator(this);
			sorting->SetMediator(this);
			printer->SetMediator(this);
		}
		void Notify(Command cmd) override {
			switch (cmd) {
				case LOAD: {
					std::cout << "vector loaded" <<std::endl;
					sorting->Sort(loader->Get_array());
					break;
				}
				case SORT: {
					std::cout << "vector sorted" << std::endl;
					printer->Print(loader->Get_array());
					break;
				}
				case PRINT: {
					std::cout << "vector printed" << std::endl;
					break;
				}	
				default: {
					std::cout << "undefined operation" << std::endl;
					break;
				}
			}
		}
	private:
		DataLoaderWorker* loader;
		QsortingWorker* sorting;
		PrinterWorker* printer;
};

class Decorator : public QsortingWorker {
	public:
		Decorator(QsortingWorker* _qsorter) : 
			qsorter(_qsorter) {}
		void Sort(std::vector <int>& vec) {
			qsorter->Sort(vec);
		}
	private:
		QsortingWorker* qsorter;
};

class TimerDecorator : public Decorator {
	public:
		TimerDecorator(QsortingWorker* _qsorter) :
			Decorator(_qsorter) {}
		void Sort(std::vector <int>& vec) {
			auto start = std::chrono::high_resolution_clock::now();
        		Decorator::Sort(vec);
          		auto finish = std::chrono::high_resolution_clock::now();
        		std::chrono::duration<double> elapsed = finish - start;
        		std::cout << "time :\t" << elapsed.count() << std::endl;
		}
};

namespace test {
	inline void test_case_Mediator() {

		std::cout << "\n\nMediator_test :\n\n";

		DataLoaderWorker* dlw = new DataLoaderWorker();
		QsortingWorker* qsw = new QsortingWorker();
		PrinterWorker* prw = new PrinterWorker();
		QsortMediator* qsm = new QsortMediator(dlw, qsw, prw);
		dlw->Load("input.txt");

		delete qsm;
		delete prw;
		delete qsw;
		delete dlw;

		std::cout << "OK" << std::endl << std::endl;
	}

	inline void test_case_Decorator() {

		std::cout << "\n\nDecorator_test :\n\n";

		DataLoaderWorker* dlw = new DataLoaderWorker();
		QsortingWorker* qsw = new QsortingWorker();
		PrinterWorker* prw = new PrinterWorker();
		QsortMediator* qsm = new QsortMediator(dlw, qsw, prw);
		TimerDecorator* tmd = new TimerDecorator(qsw);

		std::vector <int> temp = { 4, 5, 2, 1, 0, 23 };
		tmd->Sort(temp);
		prw->Print(temp);

		delete tmd;
		delete qsm;
		delete prw;
		delete qsw;
		delete dlw;

		std::cout << "OK" << std::endl << std::endl;
	}
}

int main()
{        
	test::test_case_Mediator();
	test::test_case_Decorator();

    	return 0;
}
