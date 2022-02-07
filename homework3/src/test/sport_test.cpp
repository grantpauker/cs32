#include <iostream>
#include <sstream>
#include <cassert>

#include "sport.cpp"

void display(const Sport *sp)
{
    std::cout << sp->name() << " is ";
    if (sp->isOutdoor())
    {
        std::cout << "an outdoor sport ";
    }
    else
    {
        std::cout << "an indoor sport ";
    }
    std::cout << "with an icon showing " << sp->icon() << "." << std::endl;
}

int main()
{
    Sport *sports[4];
    sports[0] = new Snowboarding("Women's halfpipe");
    sports[1] = new Biathlon("Men's pursuit", 12.5);
    sports[2] = new Biathlon("Women's sprint", 7.5);
    sports[3] = new FigureSkating("Pair skating free");

    // Sport* bad = new Sport("Football"); // THIS SHOULDN'T COMPILE

    std::ostringstream oss;
    std::streambuf *tmp_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    std::cout << "Here are the sports." << std::endl;
    for (int k = 0; k < 4; k++)
    {
        display(sports[k]);
    }
    std::cout << "Cleaning up." << std::endl;
    for (int k = 0; k < 4; k++)
    {
        delete sports[k];
    }
    std::cout.rdbuf(tmp_cout_streambuf);

    std::string spec_cout = "Here are the sports.\nWomen's halfpipe is an outdoor sport with an icon showing a descending snowboarder.\nMen's pursuit is an outdoor sport with an icon showing a skier with a rifle.\nWomen's sprint is an outdoor sport with an icon showing a skier with a rifle.\nPair skating free is an indoor sport with an icon showing a skater in the Biellmann position.\nCleaning up.\nDestroying the Snowboarding object named Women's halfpipe.\nDestroying the Biathlon object named Men's pursuit, distance 12.5 km.\nDestroying the Biathlon object named Women's sprint, distance 7.5 km.\nDestroying the FigureSkating object named Pair skating free.\n";
    assert(oss && (oss.str() == spec_cout));
}
