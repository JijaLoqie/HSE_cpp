#include <bits/stdc++.h>

//List for soldier group
struct IdList
{
    std::string destination_;
    std::string job_;
    int NumberOfCompany_;

    IdList(const std::string &destination, const std::string &job, const int &NumberOfCompany)
        : destination_(destination), job_(job), NumberOfCompany_(NumberOfCompany) {}
    ~IdList() = default;

    friend std::ostream &operator<<(std::ostream &stream, const IdList &IL)
    {
        return stream << "\nIdList\n";
    }
};

//List of own properties
struct OwnProperty
{
    std::string name_;
    std::string grade_;
    int skill_;

    OwnProperty(const std::string &name, const std::string &grade, const int &skill)
        : name_(name), grade_(grade), skill_(skill) {}
    ~OwnProperty() = default;

    friend std::ostream &operator<<(std::ostream &stream, const OwnProperty &OP)
    {
        return stream << "\nOwnProperty\n";
    }
};

//Soldier (Flyweigth)
class Soldier
{
	private:
	    IdList *ID_LIST_;

	public:
	    Soldier(const IdList *IL) : ID_LIST_(new IdList(*IL)) {}
	    Soldier(const Soldier &other) : ID_LIST_(new IdList(*other.ID_LIST_)) {}
	    ~Soldier()
	    {
	        delete ID_LIST_;
	    }

	    IdList *IL() const
	    {
	        return ID_LIST_;
	    }
	    void Operation(const OwnProperty &OWN_PROPERTY) const
	    {
	        std::cout << "\nOperation\t" << OWN_PROPERTY.name_ << '\n';
	    }
};

//Group of soldiers for init (Factory)
class SoldierGroup
{
	private:
	    std::unordered_map<std::string, Soldier> soldiers;
	    std::string GetKey(const IdList &IL) const
	    {
	        return IL.destination_ + "_" + IL.job_ + "_" + std::to_string(IL.NumberOfCompany_);
	    }

	public:
	    SoldierGroup(std::initializer_list<IdList> LIST)
	    {
	        for (const IdList &temp : LIST)
	            this->soldiers.insert(std::make_pair<std::string, Soldier>(this->GetKey(temp), Soldier(&temp)));
	    }
	    ~SoldierGroup() = default;

	    Soldier GetSoldier(const IdList &IL)
	    {
	        std::string key = this->GetKey(IL);
	        if (this->soldiers.find(key) == this->soldiers.end()) {
	            std::cout << "SoldierGroup: It doesn't exist, We will create new.\n";
	            this->soldiers.insert(std::make_pair(key, Soldier(&IL)));
	        }
	        else {
	            std::cout << "SoldierGroup: It exists.\n";
	        }
	        return this->soldiers.at(key);
	    }
	    void PrintSoldiers() const
	    {
	        for (const auto &man : this->soldiers)
	            std::cout << man.first << "\n";
	    }
	    void AddSoldierToArmedForces (
				const std::string &destination,
				const std::string &job,
				const int &NumberOfCompany,
				const std::string &name,
				const std::string &
			) const
		{
			  std::cout << "\nAdding soldier\n";
		}
};

inline void solve(std::ifstream &cin, std::ofstream &cout) {

	  cout << "testing our patern Flyweigth\n\n";
	
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
