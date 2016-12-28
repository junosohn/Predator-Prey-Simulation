#include "Doodlebug.h"
#include <iostream>
#include <ostream>

using namespace std;

Doodlebug::Doodlebug()
{
    starve_ticks = 0;
}

Doodlebug::Doodlebug(string type, int x_coordinate, int y_coordinate, int step_count, bool alive, int starve_ticks)
    : Organism(type, x_coordinate, y_coordinate, step_count, alive)
{
    this->starve_ticks = starve_ticks;
}

Doodlebug::~Doodlebug()
{
    //dtor
}

void Doodlebug::set_starve_ticks(int s_temp)
{
    starve_ticks=s_temp;
}

int Doodlebug::get_starve_ticks()
{
    return starve_ticks;
}

void Doodlebug::move(int x, int y, int direction)
{
    if(direction==0)
    {
        //no move
    }
    else if(direction==1)
        x--;
    else if(direction==2)
        x++;
    else if(direction==3)
        y--;
    else if(direction==4)
        y++;

    x_coordinate = x;
    y_coordinate = y;
    step_count++;
}

void Doodlebug::breed()
{

}

void Doodlebug::death(int x, int y)
{
    type = "-";
    x_coordinate = x;
    y_coordinate = y;
    step_count = 0;
    alive = false;
}

void Doodlebug::print(ostream& os)
{
    Organism::print(os);
    os << "starve_ticks: " << starve_ticks << endl;
}
