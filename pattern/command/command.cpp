#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
 
struct Person
{
    std::string name;
    unsigned short int age;
 
    Person(std::string _name, unsigned short int _age) : name(_name), age(_age) {}
 
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};
 
std::ostream& operator<<(std::ostream& os, const Person& person)
{
    os << "Name: " << person.name << " Age: " << person.age;
    return os;
}
 
class Command
{
public:
    virtual void Execute() = 0;
};
 
class Serialize : public Command {
 
public:
    Serialize(std::string _path) : path(_path) {}
 
    void Execute() override {
        std::remove(path.c_str());
        std::ofstream file(path);
        file << persons.size() << "\n";
 
        for (auto person : persons)
        {
            file << person->name << ":" << person->age << "\n";
        }
    }
 
    void SetPersons(std::vector<Person*> vec) {
        persons = vec;
    }
 
    std::vector<Person*> GetPersons() {
        return persons;
    }
 
 
private:
    std::vector<Person*> persons;
    std::string path;
};
 
class Deserialize : public Command {
 
public:
    Deserialize(std::string _path) : path(_path) {}
 
    void Execute() override {
        persons.clear();
        std::ifstream file(path);
        int am = 0;
        file >> am;
 
        std::string st, name;
        int age;
        for (int i = 0; i < am; i++)
        {
            file >> st;
            size_t splitter = st.find(':');
            
            name = st.substr(0, splitter);
            age = atoi(st.substr(splitter+1).c_str());
 
            persons.push_back(new Person(name, age));
        }
    }
 
    std::vector<Person*> GetPersons() {
        return persons;
    }
 
private:
    std::vector<Person*> persons;
    std::string path;
};
 
class Log
{
private:
    std::vector<Person*> persons;
    Command* on_start;
    Command* on_finish;
public:
    void Print()
    {        
        persons = dynamic_cast<Serialize*>(on_start)->GetPersons();
        persons.push_back(new Person("Hacker", 9));
 
        dynamic_cast<Serialize*>(on_start)->SetPersons(persons);
 
        on_start->Execute();
 
        for (auto person : persons)
        {
            std::cout << *person << std::endl;
        }
 
        on_finish->Execute();
    }
 
    void SetStartCommand(Command* cmd) {
        on_start = cmd;
    }
 
    void SetFinishCommand(Command* cmd) {
        on_finish = cmd;
    }
};
 
int main()
{
    setlocale(LC_ALL, "Russian");
 
    Log* log = new Log;
    Serialize* srlz = new Serialize("info.txt");
    Deserialize* desrlz = new Deserialize("info.txt");
 
    Person* p1 = new Person("Alex", 12);
    Person* p2 = new Person("Misha", 13);
 
    std::vector<Person*> vec;
    vec.push_back(p1);
    vec.push_back(p2);
 
    srlz->SetPersons(vec);
    
    log->SetStartCommand(srlz);
    log->SetFinishCommand(desrlz);
 
    log->Print();
 
    //auto persons = desrlz->GetPersons();
    //for (auto person : persons) {
    //    std::cout << *person << std::endl;
    //}
 
    delete log;
    delete srlz;
    delete desrlz;
}
