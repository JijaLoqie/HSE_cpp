#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <ctime>
#include <deque>

std::mt19937 rnd(time(0));

struct Order;
struct Courier;
class Restaurant;
class KFC;
class McDonalds;

struct Order
{
	std::string name;
	bool is_completed = 0;
	Order(const std::string& _name) : name(_name) {}
};

class Restaurant
{	
	public:
		std::unordered_map<Order*, Courier*> orders;
		std::deque<std::pair<Order*, Courier*>> completed;
		virtual void Subscribe(Courier* courier, Order* order) = 0;
		virtual void Unsubscribe(Courier* courier, Order* order) = 0;
		virtual void Notify() = 0;
		virtual void MakePrepared() = 0;
};

struct Courier
{
	std::string name;
	Restaurant* restaurant;
	Courier(const std::string& _name, Restaurant* _restaurant) : 
		name(_name), restaurant(_restaurant) 
	{}
	void Get_order(Order* order)
	{
		std::cout << "Order : " << order->name;
		std::cout << " getted by " << name << std::endl;
		restaurant->Unsubscribe(this, order);
	}
};

class KFC : public Restaurant
{
	public:
		void Subscribe(Courier* courier, Order* order) override
		{
			orders.insert(std::make_pair(order, courier));
		}
		void Unsubscribe(Courier* courier, Order* order) override
		{
			orders.erase(order);
		}
		void Notify() override
		{
			for (auto& element : orders)
			{
				if (element.first->is_completed)
				{
					completed.emplace_back(element.first, element.second);
				}
			}
			for (const auto& element : completed)
			{
				element.second->Get_order(element.first);
			}
			completed.clear();
		}
		void MakePrepared() override
		{
			for (auto& element : orders)
			{
				element.first->is_completed |= bool(rnd() & 1);
			}
		}
};

class McDonalds : public Restaurant
{
	public:
		void Subscribe(Courier* courier, Order* order) override
		{
			orders.insert(std::make_pair(order, courier));
		}
		void Unsubscribe(Courier* courier, Order* order) override
		{
			orders.erase(order);
		}
		void Notify() override
		{
			for (auto& element : orders)
			{
				if (element.first->is_completed)
				{
					completed.emplace_back(element.first, element.second);
				}
			}
			for (const auto& element : completed)
			{
				element.second->Get_order(element.first);
			}
			completed.clear();
		}
		void MakePrepared() override
		{
			for (auto& element : orders)
			{
				element.first->is_completed |= bool(rnd() & 1);
			}
		}
};

namespace test
{
	inline void go_test() 
	{	
		Restaurant* kfc = new KFC;
		Restaurant* mac = new McDonalds;

		Courier* c1 = new Courier("Alex", mac);
		Courier* c2 = new Courier("Alice", kfc);
		Courier* c3 = new Courier("Bob", kfc);
		Courier* c4 = new Courier("Jack", mac);

		Order* o1 = new Order("Chicken");
		Order* o2 = new Order("Salad");
		Order* o3 = new Order("Burger");
		Order* o4 = new Order("Coffee");

		mac->Subscribe(c1, o1);
		kfc->Subscribe(c2, o2);
		kfc->Subscribe(c3, o3);
		mac->Subscribe(c4, o4);

		mac->MakePrepared();
		mac->Notify();
		kfc->MakePrepared();
		kfc->Notify();

		std::cout << "[---OK---]" << std::endl;
	}
}

int main(int argc, char* agrv[])
{
	
	test::go_test();

	return 0;
}
