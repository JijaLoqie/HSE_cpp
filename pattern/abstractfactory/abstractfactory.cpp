#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <ctime>
#include <deque>


struct Picture 
{
	int size;
	int height;
	int width;
	std::string name;
	Picture(int _size, int _height, int _width, std::string _name) :
		size(_size),
		height(_height),
		width(_width),
		name(_name) {}
};

struct JPG : public Picture
{
	JPG(int _size, int _height, int _width, std::string _name) : 
	Picture(_size, _height, _width, _name) {}
	~JPG() = default;
};

struct PNG : public Picture
{
	PNG(int _size, int _height, int _width, std::string _name) : 
	Picture(_size, _height, _width, _name) {}
	PNG() = default;
};

class AbstractFactory
{
	public:
		virtual Picture* CreateJPG(std::string& path) = 0;
		virtual Picture* CreatePNG(std::string& path) = 0;
};

class BredlyFactory : public AbstractFactory
{
	private:
		void algo(Picture* img) {
			std::cout << "Bredly\t:\t";
			std::cout << img->name << std::endl;
		}
	public:
		Picture* CreateJPG(std::string& path) override {
			//load image
			Picture* img = new JPG(1, 2, 3, path);
			algo(img);
			return img;
		}
		Picture* CreatePNG(std::string& path) override {
			//load image
			Picture* img = new PNG(1, 2, 3, path);
			algo(img);
			return img;
		}
};

class NiblackFactory : public AbstractFactory
{
	private:
		void algo(Picture* img) {
			std::cout << "Niblack\t:\t";
			std::cout << img->name << std::endl;
		}
	public:
		Picture* CreateJPG(std::string& path) override {
			//load image
			Picture* img = new JPG(1, 2, 3, path);
			algo(img);
			return img;
		}
		Picture* CreatePNG(std::string& path) override {
			//load image
			Picture* img = new PNG(1, 2, 3, path);
			algo(img);
			return img;
		}
};

namespace test
{
	inline void go_test() 
	{	
		std::string path1 = "path1";
		std::string path2 = "path2";
		std::string path3 = "path3";
		std::string path4 = "path4";

		AbstractFactory* bf = new BredlyFactory;
		AbstractFactory* nf = new NiblackFactory;

		Picture* p1 = bf->CreateJPG(path1);
		Picture* p2 = bf->CreatePNG(path2);
		Picture* p3 = nf->CreatePNG(path3);
		Picture* p4 = nf->CreateJPG(path4);

		std::cout << "[---OK---]" << std::endl;
	}
}

int main(int argc, char* agrv[])
{
	test::go_test();

	return 0;
}
