#include "Organism.h"
#include <iostream>
#include <ostream>
#include <cstdlib>

using namespace std;

Organism::Organism()
{
    type = "";
    x_coordinate = 0;
    y_coordinate = 0;
    step_count = 0;
    alive = true;
}

Organism::Organism(string type, int x, int y)
{
    this->type = type;
    this->x_coordinate = x_coordinate;
    this->y_coordinate = y_coordinate;
}

Organism::Organism(string type, int x_coordinate, int y_coordinate, int step_count, bool alive)
{
    this->type = type;
    this->x_coordinate = x_coordinate;
    this->y_coordinate = y_coordinate;
    this->step_count = step_count;
    this->alive = alive;
}

Organism::~Organism()
{
}

void Organism::set_type(string s)
{
    type = s;
}

string Organism::get_type() const
{
    return type;
}

int Organism::get_x_coordinate() const
{
    return x_coordinate;
}

int Organism::get_y_coordinate() const
{
    return y_coordinate;
}

void Organism::set_step_count(int s)
{
    step_count = s;
}

int Organism::get_step_count() const
{
    return step_count;
}

void Organism::set_alive(bool temp)
{
    alive = temp;
}

bool Organism::get_alive() const
{
    return alive;
}

void Organism::move(int& x, int& y, int direction)
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

void Organism::breed()
{

}

void Organism::print(ostream& os)
{
    os << type << " (" << x_coordinate << "," << y_coordinate << "). steps: " << step_count << "  ";
}

