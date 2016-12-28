#ifndef DOODLEBUG_H
#define DOODLEBUG_H
#include <iostream>
#include <ostream>
#include "Organism.h"

using namespace std;

class Doodlebug : public Organism
{
public:
    Doodlebug();
    Doodlebug(string type, int x_coordinate, int y_coordinate, int step_count, bool alive, int starve_ticks);
    virtual ~Doodlebug();

    Doodlebug* set_new_location(int x, int y);
    void set_starve_ticks(int);
    int get_starve_ticks();

    virtual void move(int x, int y, int direction);
    void breed();
    void death(int, int);

    virtual void print(ostream&);

protected:

private:
    int starve_ticks;

};

#endif // DOODLEBUG_H
