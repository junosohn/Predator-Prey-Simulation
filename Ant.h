#ifndef ANT_H
#define ANT_H
#include <iostream>
#include <ostream>
#include "Organism.h"

using namespace std;

class Ant : public Organism
{
public:
    Ant();
    Ant(string type, int x_coordinate, int y_coordinate, int step_count, bool alive);
    virtual ~Ant();

    void remove(int num, int dead_ant);
    virtual void move(int x, int y, int direction);
    void breed(int x, int y, int steps);

    virtual void print(ostream&);

protected:

private:

};

#endif // ANT_H
