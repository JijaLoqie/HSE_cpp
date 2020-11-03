#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>
enum SquareFigureName{
    STAR,
    PERCENT
};

class SquareFigure;
std::ostream& operator<<(std::ostream& out, const SquareFigure& prot);

const char* name2string[] = {"Star", "Percent"};
class SquareFigure {
public:
    SquareFigure() = default;
    SquareFigure(unsigned short int w_, unsigned short int h_, char s_): width(w_), height(h_), symbol(s_){}
    virtual SquareFigure* Clone() const = 0;
    virtual ~SquareFigure() {}
    void Print() {
        std::cout << *this << '\n';
    }

    unsigned short int GetWidth() const {
        return width;
    }
    unsigned short int GetHeight() const {
        return height;
    }
    char GetSymbol() const {
        return symbol;
    }
protected:
    unsigned short int width;
    unsigned short int height;
    char symbol;
};

std::ostream& operator<<(std::ostream& out, const SquareFigure& prot) {
    std::string row(prot.GetWidth(), prot.GetSymbol());
    for (size_t i = 0; i < prot.GetHeight(); i++) {
        out << row << '\n';
    }
    return out;
}

class StarSquareFigure : public SquareFigure 
{
public:
    StarSquareFigure(unsigned short int w_, unsigned short int h_) : SquareFigure(w_, h_, '*'){}
    StarSquareFigure(){};
    SquareFigure* Clone() const override
    {
        return new StarSquareFigure(*this);
    }


};
class PercentSquareFigure : public SquareFigure 
{
public:
    PercentSquareFigure(unsigned short int w_, unsigned short int h_) : SquareFigure(w_, h_, '%'){}
    SquareFigure* Clone() const override
    {
        return new PercentSquareFigure(*this);
    }


};
class SquareFigureFactory
{
public:
    SquareFigureFactory()
    {
        name2figure[STAR] = nullptr;
        name2figure[PERCENT] = nullptr;
    }
    ~SquareFigureFactory()
    {
        for (auto& [key, value]: name2figure) {
            if (value) {
                delete value;
            }
        }
    }
    SquareFigure* CloneSquareFigure(SquareFigureName symbol) {
        return name2figure[symbol]->Clone();
    }
    void SetPrototype(SquareFigureName symbol, SquareFigure* figure) {
        name2figure[symbol] = figure;
        std::cout << "Prototype is saved!" << std::endl;
    }
private:
    std::unordered_map<SquareFigureName, SquareFigure*, std::hash<int>> name2figure;



    
};

class Proxy : public StarSquareFigure
{
public:
    Proxy()
    {
        SetDefault();

    }
    ~Proxy()
    {
        if (HasFig()) {
            delete fig;
        }
    }
    void Print() {
        fig->Print();
    }
private:
    void SetDefault() {
			//long operation
			fig = new StarSquareFigure(5, 5);
			std::cout << "Creating 0%" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "Creating 33%" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "Creating 66%" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "Creating 100%" << std::endl;
		}
    bool HasFig() {
        return fig;
    }
    StarSquareFigure* fig;
};


int main() {
    SquareFigureFactory Fact;
    SquareFigure* figure = new StarSquareFigure(2, 3);
    std::cout <<  *figure << std::endl;
    Fact.SetPrototype(SquareFigureName::STAR, figure);
    SquareFigure* f1 = Fact.CloneSquareFigure(STAR);
    std::cout << *f1 << std::endl;
    Proxy proxy;
    proxy.Print();
    proxy.Print();
    proxy.Print();

}
