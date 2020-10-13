#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

class Component {
    public:
        virtual ~Component() {}
        virtual void Work() = 0;
        void Set_Parent(Component* _Parent) {
            this->Parent = _Parent;
        }
    protected:
        std::string name;
        Component* Parent;
    private:
        static void message() { std::cout << "Component\t"; }
};

class Composite : public Component {
    public:
        void Add_Worker(Component* _Worker) {
            this->Workers.emplace_back(_Worker);
        }
    protected:
        std::vector <Component*> Workers;
};

class Managing_Director : public Composite {
    private:
        static void message() { std::cout << "Managing_Director\t"; }
    public:
        Managing_Director() = default;
        ~Managing_Director() = default;
        void Drink_Coffee() const {
            Managing_Director::message();
            std::cout << "Drink_Coffee" << std::endl;
        }
        void Work() override {
            for (const auto element : Workers) {
                element->Work();
            }
            Drink_Coffee();
        }
};

class Senior_VC_President : public Composite {
    private:
        static void message() { std::cout << "Senior_VC_President\t"; }
    public:
        Senior_VC_President() = default;
        ~Senior_VC_President() = default;
        void Prepare_Meeting() const {
            Senior_VC_President::message();
            std::cout << "Prepare_Meeting" << std::endl;
        }
        void Work() override {
            for (const auto element : Workers) {
                element->Work();
            }
            Prepare_Meeting();
        }
};

class VC_President : public Composite {
    private:
        static void message() { std::cout << "VC_President\t"; }
    public:
        VC_President() = default;
        ~VC_President() = default;
        void Prepare_Pitch_Book() const {
            VC_President::message();
            std::cout << "Prepare_Pitch_Book" << std::endl;
        }
        void Work() override {
            for (const auto element : Workers) {
                element->Work();
            }
            Prepare_Pitch_Book();
        }
};

class Bank_Assosiate : public Composite {
    private:
        static void message() { std::cout << "Bank_Assosiate\t"; }
    public:
        Bank_Assosiate() = default;
        ~Bank_Assosiate() = default;
        void Gather_Companies_Indicators() const {
            Bank_Assosiate::message();
            std::cout << "Gather_Companies_Indicators" << std::endl;
        }
        void Put_Company_Indicator() const {
            Bank_Assosiate::message();
            std::cout << "Put_Company_Indicator" << std::endl;
        }
        void Work() override {
            for (const auto element : Workers) {
                element->Work();
            }
            Gather_Companies_Indicators();
            Put_Company_Indicator();
        }
};

class Bank_Analyst : public Composite {
    private:
        static void message() { std::cout << "Bank_Analyst\t"; }
    public:
        Bank_Analyst() = default;
        ~Bank_Analyst() = default;
        void Make_Presentation() const {
            Bank_Analyst::message();
            std::cout << "Make_Presentation" << std::endl;
        }
        void Get_Company_Indicator() const {
            Bank_Analyst::message();
            std::cout << "Get_Company_Indicator" << std::endl;
        }
        void Work() override {
            for (const auto element : Workers) {
                element->Work();
            }
            Make_Presentation();
            Get_Company_Indicator();
        }
};

void dfs(Component* man, Component* _parent = nullptr, int depth = 0) {
    if (depth == 4) return;
    man->Set_Parent(_parent);
    for (size_t i = 0; i < 1; i++) {
        Component* new_child = nullptr;
        switch (depth) {
            case 0 : {
                new_child = new Senior_VC_President();
                break;
            }
            case 1 : {
                new_child = new VC_President();
                break;
            }
            case 2 : {
                new_child = new Bank_Assosiate();
                break;
            }
            case 3 : {
                new_child = new Bank_Analyst();
                break;
            }
            default : {
                assert(false);
            }
        }
        dynamic_cast<Composite*>(man)->Add_Worker(new_child);
        dfs(new_child, man, depth + 1);
    }
}

namespace testing_code {
    inline void test() {
        assert(true);
        Managing_Director* dir_ptr = new Managing_Director();
        dfs(dir_ptr);
        dir_ptr->Work();
        std::cout << "[---OK---]" << std::endl;
    }
}

signed main(int argc, char* args[]) {

    testing_code::test();

    return 0;
}
