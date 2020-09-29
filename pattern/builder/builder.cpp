#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

//константы цветов
enum Colors {
	BLUE,
	BLACK,
	WHITE,
	GREEN,
	YELLOW
};

//структура вагона
struct Van
{	
	std::string _wind_form;
	int _color;
	int _length;
	int _height;
	int _width;
	int _weight;
	int _kol_seats;
	std::vector <int> _seats;
	Van() = default;
	~Van() = default;
};

//строитель - описание интерфейса в родительском классе
class Builder
{
	private:
		static std::string message;
		static void show_message() { 
			std::cout << Builder::message << std::endl;
		}
	public:
		Builder() = default;
		virtual ~Builder() = default;
		virtual void reset(int num) { Builder::show_message(); }
		virtual void set_wind_form(std::string value) { Builder::show_message(); }
		virtual void set_color(int value) { Builder::show_message(); }
		virtual void set_length(int value) { Builder::show_message(); }
		virtual void set_height(int value) { Builder::show_message(); }
		virtual void set_width(int value) { Builder::show_message(); }
		virtual void set_weight(int value) { Builder::show_message(); }
		virtual void set_kol_seats(int value) { Builder::show_message(); }
		virtual void set_seats_color(int value) { Builder::show_message(); }
		virtual Van getResult() {}
};

std::string Builder::message = "Parent class Builder";

//строитель вагона типа "голубой"
class BlueVanBuilder : public Builder
{	
	private:
		Van object;
	public:
		BlueVanBuilder() = default;
		~BlueVanBuilder() = default;
		virtual void reset(int num) { 
			std::cout << "Van created : " << num << std::endl;
		}
		virtual void set_wind_form(std::string value) {
			this->object._wind_form = value;
		}
		virtual void set_color(int value) {
			this->object._color = value;
		}
		virtual void set_length(int value) {
			this->object._length = value;
		}
		virtual void set_height(int value) {
			this->object._height = value;
		}
		virtual void set_width(int value) {
			this->object._width = value;
		}
		virtual void set_weight(int value) {
			this->object._weight = value;
		}
		virtual void set_kol_seats(int value) {
			this->object._kol_seats = value;
		}
		virtual void set_seats_color(int value) {
			this->object._seats.resize(this->object._kol_seats, value);
		}
		Van getResult() override {
			return this->object;
		}
};

//поезд
class Train
{
	private:
		int _x, _y, _z;
		std::vector <Van> _vans;
		std::string _number;
	public:
		Train() = default;
		~Train() = default;
		//функция создания поезда
		void make_default_train(std::string number, int len = 1) {
			this->_number = number;
			for (size_t i = 0; i < len; i++) {
				//построение голубого вагона
				Builder* maker = new BlueVanBuilder();
				maker->reset(i + 1);
				maker->set_wind_form("circle");
				maker->set_color(Colors::BLUE);
				maker->set_length(1);
				maker->set_height(2);
				maker->set_width(3);
				maker->set_weight(4);
				maker->set_kol_seats(35);
				maker->set_seats_color(Colors::WHITE);
				_vans.push_back(maker->getResult());
			}
			std::cout << "Train created" << std::endl;
			std::cout << "Train number : " << number << std::endl;
		}
		//функция инициализации координат поезда
		void init_coordinates(int x, int y, int z) {
			this->_x = x;
			this->_y = y;
			this->_z = z;
		}
		friend std::ostream& operator <<(std::ostream& stream, const Train& obj) {
			stream << "number : " << obj._number << std::endl;
			stream << "position : " << obj._x << ' ' << obj._y << ' ' << obj._z << std::endl;
			stream << "len : " << (int)obj._vans.size() << std::endl << std::endl;
			return stream;
		}
};

//демонстрация создания поезда
inline void solve(std::ifstream &cin, std::ofstream &cout)
{

	cout << "testing our patern Builder\n\n";

	Train blue_train;
	blue_train.make_default_train("cr7", 5);
	blue_train.init_coordinates(34, 56, 78);
	cout << blue_train;
	
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
