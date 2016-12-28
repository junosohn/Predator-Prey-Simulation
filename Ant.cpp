#include "Ant.h"
#include <iostream>
#include <ostream>

using namespace std;

Ant::Ant()
{
}

Ant::Ant(string type, int x_coordinate, int y_coordinate, int step_count, bool alive)
   : Organism(type, x_coordinate, y_coordinate, step_count, alive)
{
}

Ant::~Ant()
{
    //dtor
}

void Ant::move(int x, int y, int direction)
{
    if(direction==0)
    {
        //do nothing
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

void Ant::breed(int x, int y, int steps)
{

}

void Ant::print(ostream& os)
{
    Organism::print(os);
}
