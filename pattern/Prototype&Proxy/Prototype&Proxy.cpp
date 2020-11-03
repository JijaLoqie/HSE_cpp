#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>

enum SquareFigureName {
	STAR,
	PERCENT
};

const char* GetName[] = {"Star", "Percent"};

class SquareFigure;
std::ostream& operator <<(std::ostream& stream, const SquareFigure& object);

class SquareFigure {
	public:
		SquareFigure() = default;
		SquareFigure(
			unsigned short int _height,
			unsigned short int _width,
			char _symbol
		) : 
			height(_height),
			width(_width),
			symbol(_symbol)
		{}
		virtual ~SquareFigure() = default;
		virtual SquareFigure* Clone() const = 0;
		unsigned short int GetWigth() const {
			return width;
		}
		unsigned short int GetHeight() const {
			return height;
		}
		char GetSymbol() const {
			return symbol;
		}
		void Print() {
			std::cout << "Print_method" << std::endl;
			std::cout << (*this) << std::endl;
		}
	protected:
		unsigned short int width;
		unsigned short int height;
		char symbol;
};

std::ostream& operator <<(std::ostream& stream, const SquareFigure& object) {
	for (unsigned short int i = 0; i < object.GetHeight(); ++i)
		stream << std::string(object.GetWigth(), object.GetSymbol()) << std::endl;
	return stream;
}

class StarSquareFigure : public SquareFigure {
	public:
		StarSquareFigure() = default;
		StarSquareFigure(
			unsigned short int _height,
			unsigned short int _width
		) : SquareFigure(_height, _width, '*') {}
		StarSquareFigure(const StarSquareFigure& other) = default;
		~StarSquareFigure() = default;
		SquareFigure* Clone() const override {
			return new StarSquareFigure(*this);
		}
};

class PercentSquareFigure : public SquareFigure {
	public:
		PercentSquareFigure() = default;
		PercentSquareFigure(
			unsigned short int _height,
			unsigned short int _width
		) : SquareFigure(_height, _width, '%') {}
		PercentSquareFigure(const PercentSquareFigure& other) = default;
		~PercentSquareFigure() = default;
		SquareFigure* Clone() const override {
			return new PercentSquareFigure(*this);
		}
};

class SquareFigureFactory {
	public:
		SquareFigureFactory() {
			name2figure[STAR] = nullptr;
			name2figure[PERCENT] = nullptr;
		}
		~SquareFigureFactory() {
			for (auto& key_value : name2figure)
				if (key_value.second != nullptr)
					delete key_value.second;
		}
		void SetPrototype(SquareFigureName symbol, SquareFigure* _figure) {
			name2figure[symbol] = _figure;
			std::cout << "SetPrototype " << GetName[symbol] << std::endl;
		}
		SquareFigure* CloneSquareFigure(SquareFigureName symbol) {
			return name2figure[symbol]->Clone();
		}
	private:
		std::unordered_map <SquareFigureName, SquareFigure*, std::hash<int>> name2figure;
};

class StarProxy : public StarSquareFigure {
	public:
		StarProxy() = default;
		~StarProxy() {
			if (check())
				delete sfig;
		}
		void Print() {
			switch (static_cast<int>(check())) {
				case 1 : {
					std::cout << "ProxyPrinter" << std::endl;
					sfig->Print();
					break;
				}
				default : {
					std::cout << "Creating New Object" << std::endl;
					SetDefault();
					Print();
				}
			}
		}
	private:
		bool check() const {
			return (sfig != nullptr);
		}
		void SetDefault() {
			//long operation
			sfig = new StarSquareFigure(5, 5);
			std::cout << "Creating 0%" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "Creating 33%" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "Creating 66%" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "Creating 100%" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << std::endl;
		}
		StarSquareFigure* sfig = nullptr;
};

namespace test {
	inline void test_case_prototype() {

		std::cout << std::endl;
		std::cout << "test_case_prototype" << std::endl;
		std::cout << std::endl;

		SquareFigureFactory fact;
		SquareFigure* stsf = new StarSquareFigure(3, 7);
		SquareFigure* prsf = new PercentSquareFigure(2, 11);
		
		std::cout << *stsf << std::endl;
		std::cout << *prsf << std::endl;

		fact.SetPrototype(STAR, stsf);
		fact.SetPrototype(PERCENT, prsf);
		std::cout << std::endl;

		SquareFigure* cloneStar = fact.CloneSquareFigure(STAR);
		SquareFigure* clonePercent = fact.CloneSquareFigure(PERCENT);

		std::cout << "cloneStar" << std::endl;
		std::cout << *cloneStar << std::endl;

		std::cout << "clonePercent" << std::endl;
		std::cout << *clonePercent << std::endl;

		std::cout << std::endl << "[---OK---]" << std::endl;
	}

	inline void test_case_proxy() {

		std::cout << std::endl;
		std::cout << "test_case_proxy" << std::endl;
		std::cout << std::endl;

		StarProxy proxy;
		proxy.Print();
		proxy.Print();
		proxy.Print();

		std::cout << std::endl << "[---OK---]" << std::endl;
	}
}

int main()
{   	
	test::test_case_prototype();
	test::test_case_proxy();	

    return 0;
}
