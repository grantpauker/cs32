
#include <iostream>
#include <vector>

class Class
{
public:
    Class(std::string nm) : m_name(nm) {}
    std::string name() const { return m_name; }
    const std::vector<Class *> &subclasses() const { return m_subclasses; }
    void add(Class *d) { m_subclasses.push_back(d); }
    ~Class();

private:
    std::string m_name;
    std::vector<Class *> m_subclasses;
};

Class::~Class()
{
    for (size_t k = 0; k < m_subclasses.size(); k++)
        delete m_subclasses[k];
}

#include "list.cpp"

void listAll(const Class *c) // one-parameter overload
{
    if (c != nullptr)
        listAll("", c);
}

int main()
{
    Class *d1 = new Class("Koopa");
    listAll(d1);
    std::cout << "====" << std::endl;

    d1->add(new Class("SoopaKoopa"));
    Class *d2 = new Class("Enemy");
    d2->add(new Class("Piranha"));
    d2->add(d1);
    Class *d3 = new Class("Goodie");
    d3->add(new Class("Flower"));
    d3->add(new Class("Mushroom"));
    d3->add(new Class("Star"));
    listAll(d3);
    std::cout << "====" << std::endl;

    Class *d4 = new Class("Actor");
    d4->add(d2);
    d4->add(new Class("Peach"));
    d4->add(d3);
    listAll(d4);
    delete d4;
}