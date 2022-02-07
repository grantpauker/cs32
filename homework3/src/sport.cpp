#include <iostream>
#include <string>

class Sport
{
public:
    Sport(std::string name) : m_name(name) {}
    virtual ~Sport() {}
    std::string name() const
    {
        return m_name;
    }
    virtual bool isOutdoor() const
    {
        return true;
    }
    virtual std::string icon() const = 0;

private:
    std::string m_name;
};

class Snowboarding : public Sport
{
public:
    Snowboarding(std::string name) : Sport(name) {}
    virtual std::string icon() const
    {
        return "a descending snowboarder";
    }
    virtual ~Snowboarding()
    {
        std::cout << "Destroying the Snowboarding object named " << name() << "." << std::endl;
    }
};

class Biathlon : public Sport
{
public:
    Biathlon(std::string name, double distance) : Sport(name), m_distance(distance)
    {
    }
    virtual std::string icon() const
    {
        return "a skier with a rifle";
    }
    virtual ~Biathlon()
    {
        std::cout << "Destroying the Biathlon object named " << name() << ", distance " << m_distance << " km." << std::endl;
    }

private:
    double m_distance;
};

class FigureSkating : public Sport
{
public:
    FigureSkating(std::string name) : Sport(name)
    {
    }
    virtual bool isOutdoor() const
    {
        return false;
    }
    virtual std::string icon() const
    {
        return "a skater in the Biellmann position";
    }
    virtual ~FigureSkating()
    {
        std::cout << "Destroying the FigureSkating object named " << name() << "." << std::endl;
    }
};