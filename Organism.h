#ifndef ORGANISM_H
#define ORGANISM_H
#include <iostream>
#include <ostream>

const int GRID_SIZE = 20;

using namespace std;

class Organism
{
public:

    Organism();
    Organism(string type, int x_coordinate, int y_coordinate);
    Organism(string type, int x_coordinate, int y_coordinate, int step_count, bool alive);
    virtual ~Organism();

    void set_type(string);
    string get_type() const;
    int get_x_coordinate() const;
    int get_y_coordinate() const;
    void set_step_count(int);
    int get_step_count() const;
    void set_alive(bool);
    bool get_alive() const;

    void move(int& x, int& y, int direction);
    void breed();
    void print(ostream&);

protected:
    string type;
    int x_coordinate;
    int y_coordinate;
    int step_count;
    bool alive;

private:

};

#endif // ORGANISM_H
