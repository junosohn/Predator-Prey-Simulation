/*

VCC CMPT 1020 - Assignment 4

Predator-Prey Simulation

*****************************************
*                                       *
*        PREDATOR-PREY SIMULATOR        *
*                                       *
*****************************************

This program simulates a predator-prey situation where prey are
ants and the predators are doodlebugs. The world in which the
creatures live is a 20 by 20 grid; each cell of the grid can
either be empty or contain a single creature. The creatures are
not allowed to move outside the grid. Time is simulated in steps
in a loop and each creature moves, breeds, and dies (and eats).

Authors: Junho Sohn, Tom Dorval, Eleanor Kim
Date: 04/12/16

*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

using namespace std;

const int S = 20;

class Organism;
typedef Organism* World[S][S];

void intro_message();
void input(int&, int&);
void create_grid(World);
void print_grid(World);
bool check_grid_empty(World, int, int);
int check_grid_next(World, int, int);
int randomize_direction();
int randomize_gridposition();
void randomize_organism(World, int, int, Ant *[], Doodlebug*[]);
int return_direction(World, int, int, string, Doodlebug*[], int);
void clear_slot(World, int, int, int);
void new_organism(World, Ant *[], Doodlebug *[], string, int, int, int, int);
void move(World, Ant *[], Doodlebug *[], string, int);
void breed(string, int, World, Ant *[], int, Doodlebug *[], int, int, int, int);
void step_check(World, string, Ant *[], int, Doodlebug *[], int, int);
int organism_count(World, string);

int main()
{
    srand(time(NULL));
    World w;
    Ant *a_array[10000]; //safeguard for max size
    Doodlebug *db_array[10000]; //same as above
    int NUM_ANT, NUM_DB;

    intro_message();
    cin.ignore();
    system("CLS");
    create_grid(w);
    input(NUM_ANT, NUM_DB);
    randomize_organism(w, NUM_ANT, NUM_DB, a_array, db_array);

///SIMULATION///
    int simulation;
    cout << "INPUT # OF SIMULATION STEPS: ";
    cin >> simulation;
    print_grid(w);
    cin.ignore();
    cin.ignore();

    for(int i=0; i<simulation; i++)
    {
        for(int d=0; d<NUM_DB; d++)
        {
            //if(db_array[d]->get_alive()==true)
            {
                move(w, a_array, db_array, "x", d);
                NUM_DB = organism_count(w, "x");
                step_check(w, "x", a_array, NUM_ANT, db_array, NUM_DB, d);
                NUM_DB = organism_count(w, "x");
            }
        }

        for(int a=0; a<NUM_ANT; a++)
        {
            move(w, a_array, db_array, "o", a);
            NUM_ANT = organism_count(w, "o");
            step_check(w, "o", a_array, NUM_ANT, db_array, NUM_DB, a);
            NUM_ANT = organism_count(w, "o");
        }

        print_grid(w);
        cout << "SIMULATION STEP " << i+1 <<"\nENTER TO CONTINUE: ";
        cin.clear();
        cin.ignore();
    }
    return 0;
}

///FUNCTIONS///
//Intro message
//PRE: NONE
//POST: Displays message
void intro_message()
{
    cout << "*****************************************" << endl
         << "*                                       *" << endl
         << "*        PREDATOR-PREY SIMULATOR        *" << endl
         << "*                                       *" << endl
         << "*           ANTS v. DOODLEBUGS          *" << endl
         << "*                                       *" << endl
         << "*                                       *" << endl
         << "*               ©2016 TELJ              *" << endl
         << "*          All Rights Reserved.         *" << endl
         << "*                                       *" << endl
         << "*****************************************" << endl;
}

//Takes in input of ants/doodlebugs
//PRE: None
//POST: Passes inputs by reference
void input(int& NUM_ANT, int& NUM_DB)
{
    cout << "INPUT # OF ANTS: ";
    cin >> NUM_ANT;
    cout << "INPUT # OF DOODLEBUGS: ";
    cin >> NUM_DB;
}

//Creates empty grid
//PRE: None
//POST:
void create_grid(World w)
{
    int id = 0;
    for(int i=0; i<S; i++)
        for(int j=0; j<S; j++)
            w[i][j] = new Organism("-",i,j,0, false);
}

//Prints grid
//PRE: All slots have a defined 'type'
//POST: Points to the function get_type() in Organism, prints string value
void print_grid(World w)
{
    int c=0;
    system("CLS");
    for(int i=0; i<S; i++)
    {
        for(int j=0; j<S; j++)
            cout << w[i][j]->get_type() << " ";
        cout << endl;
    }
    cout << endl << endl;
}

//Random direction
//PRE: 1=UP, 2=DOWN, 3=LEFT, 4=RIGHT
//POST: Returns random int from 1~4
int randomize_direction()
{
    return (rand() % 4) + 1;
}

//Random grid position
//PRE: None
//POST: Returns random int from 0~19
int randomize_gridposition()
{
    return (rand()%20);
}

//Checks if current grid is empty
//PRE: Grid is empty/filled
//POST: Returns true if empty; false otherwise
bool check_grid_empty(World w, int x, int y)
{
    if(w[x][y]->get_type() == "-")
        return true;
    return false;
}

//Checks if neighbouring grid is empty
//PRE: Grid is empty or filled
//POST: Creates random direction; returns value if slot is empty
int check_grid_next(World w, int x, int y)
{
    int d = randomize_direction();

    if(d==1)
    {
        if(x==0)
            return 0;
        else if(w[x-1][y]->get_type() == "-")
            return d;
        else
            return 0;
    }
    else if(d==2)
    {
        if(x==19)
            return 0;
        else if(w[x+1][y]->get_type() == "-")
            return d;
        else
            return 0;
    }
    else if(d==3)
    {
        if(y==0)
            return 0;
        else if(w[x][y-1]->get_type() == "-")
            return d;
        else
            return 0;
    }
    else if(d==4)
    {
        if(y==19)
            return 0;
        else if(w[x][y+1]->get_type() == "-")
            return d;
        else
            return 0;
    }

    return 0;
}

//Randomize organism placement
//PRE: Grid is filled with empty slots ("-")
//POST: Overwrites empty grid with randomized placement of organisms
void randomize_organism(World w, int NUM_ANT, int NUM_DB, Ant *a_array[], Doodlebug *db_array[])
{
    int temp_x = randomize_gridposition();
    int temp_y = randomize_gridposition();

    for(int count = 0; count<NUM_ANT; count++)
    {
        while(!check_grid_empty(w, temp_x, temp_y))
        {
            temp_x = randomize_gridposition();
            temp_y = randomize_gridposition();
        }

        w[temp_x][temp_y] = new Ant("o",temp_x,temp_y,0, true);
        a_array[count] = new Ant("o",temp_x,temp_y,0, true);
    }

    for(int count = 0; count<NUM_DB; count++)
    {
        while(!check_grid_empty(w, temp_x, temp_y))
        {
            temp_x = randomize_gridposition();
            temp_y = randomize_gridposition();
        }
        w[temp_x][temp_y] = new Doodlebug("x",temp_x,temp_y,0, true, 0);
        db_array[count] = new Doodlebug("x",temp_x,temp_y,0, true, 0);
    }
}

//Returns int value for direction
//PRE: All inputs valid
//POST: Returns a valid direction for organism to move, and resets starve_ticks for DB's
int return_direction(World w, int x, int y, string t, Doodlebug *db_array[], int db)
{
    int d = randomize_direction();

    if(t=="o") ///DOODLEBUG
    {
        if(x!=0 && w[x-1][y]->get_type() == t)
        {
            db_array[db]->set_starve_ticks(0);
            return 1;
        }
        else if(x!=19 && w[x+1][y]->get_type() == t)
        {
            db_array[db]->set_starve_ticks(0);
            return 2;
        }
        else if(y!=0 && w[x][y-1]->get_type() == t)
        {
            db_array[db]->set_starve_ticks(0);
            return 3;
        }
        else if(y!=19 && w[x][y+1]->get_type() == t)
        {
            db_array[db]->set_starve_ticks(0);
            return 4;
        }
        else if( (d==1 && x==0) || (d==2 && x==19) || (d==3 && y==0) || (d==4 && y==19) )
        {
            db_array[db]->set_starve_ticks(db_array[db]->get_starve_ticks()+1);
            return 0;
        }
        else if(d==1)
        {
            db_array[db]->set_starve_ticks(db_array[db]->get_starve_ticks()+1);
            if(w[x-1][y]->get_type() == "-")
                return d;
            else
                return 0;
        }
        else if(d==2)
        {
            db_array[db]->set_starve_ticks(db_array[db]->get_starve_ticks()+1);
            if(w[x+1][y]->get_type() == "-")
                return d;
            else
                return 0;
        }
        else if(d==3)
        {
            db_array[db]->set_starve_ticks(db_array[db]->get_starve_ticks()+1);
            if(w[x][y-1]->get_type() == "-")
                return d;
            else
                return 0;
        }
        else if(d==4)
        {
            db_array[db]->set_starve_ticks(db_array[db]->get_starve_ticks()+1);
            if(w[x][y+1]->get_type() == "-")
                return d;
            else
                return 0;
        }
    }

    if(t=="-") ///ANT
    {
        if(d==1)
        {
            if(x==0)
                return 0;
            else if(w[x-1][y]->get_type() == t)
                return d;
            else
                return 0;
        }
        else if(d==2)
        {
            if(x==19)
                return 0;
            else if(w[x+1][y]->get_type() == t)
                return d;
            else
                return 0;
        }
        else if(d==3)
        {
            if(y==0)
                return 0;
            else if(w[x][y-1]->get_type() == t)
                return d;
            else
                return 0;
        }
        else if(d==4)
        {
            if(y==19)
                return 0;
            else if(w[x][y+1]->get_type() == t)
                return d;
            else
                return 0;
        }
    }
}

//Clears a slot in the grid
//PRE: Valid input parameters
//POST: Deletes the slot from passed values of (x,y) if direction>0
void clear_slot(World w, int x, int y, int direction)
{
    if(direction!=0)
        w[x][y] = new Organism("-",x,y,0, false);
}

//Creates new organism in the grid
//PRE: Either ant/doodlebug selected
//POST: Creates either ant/doodlebug in grid
void new_organism(World w, Ant *a_array[], Doodlebug *db_array[], string type, int temp_x, int temp_y, int id, int steps, int db_s_t)
{
    if(type == "o") ///ANT
    {
        w[temp_x][temp_y] = new Ant("o",temp_x,temp_y,steps, true);
        a_array[id] = new Ant("o",temp_x,temp_y,steps, true);
    }
    if(type == "x") ///DOODLEBUG
    {
        w[temp_x][temp_y] = new Doodlebug("x",temp_x,temp_y,steps, true, db_s_t);
        db_array[id] = new Doodlebug("x",temp_x,temp_y,steps, true, db_s_t);
    }
}

//Move function
//PRE: Organism is cleared to move
//POST: Moves organism by creating new 'slot' and deleting the original
void move(World w, Ant *a_array[], Doodlebug *db_array[], string type, int id)
{
    int t_x, t_y, direction;

    if(type == "x") ///DOODLEBUG
    {
        direction = return_direction(w, db_array[id]->get_x_coordinate(), db_array[id]->get_y_coordinate(), "o", db_array, id);
        t_x = db_array[id]->get_x_coordinate();
        t_y = db_array[id]->get_y_coordinate();

        clear_slot(w, t_x, t_y, direction);
        db_array[id]->move(db_array[id]->get_x_coordinate(), db_array[id]->get_y_coordinate(), direction);

        new_organism(w, a_array, db_array, "x", db_array[id]->get_x_coordinate(), db_array[id]->get_y_coordinate(), id, db_array[id]->get_step_count(), db_array[id]->get_starve_ticks());
    }

    if(type == "o") ///ANT
    {
        direction = return_direction(w, a_array[id]->get_x_coordinate(), a_array[id]->get_y_coordinate(), "-", db_array,id);
        t_x = a_array[id]->get_x_coordinate();
        t_y = a_array[id]->get_y_coordinate();

        if(w[t_x][t_y]->get_type()=="o")
        {
            clear_slot(w, t_x, t_y, direction);
            a_array[id]->move(a_array[id]->get_x_coordinate(), a_array[id]->get_y_coordinate(), direction);

            new_organism(w, a_array, db_array, "o", a_array[id]->get_x_coordinate(), a_array[id]->get_y_coordinate(),id, a_array[id]->get_step_count(), 0);
        }
    }
}

//Breed function
//PRE: Step_count = 3 for ant or 8 for doodlebug
//POST: Creates new 'slot' in the grid for ant/doodlebug
void breed(string type, int direction, World w, Ant *a_array[], int NUM_ANT, Doodlebug *db_array[], int NUM_DB, int id, int x, int y)
{
    if(type == "o") ///ANT
    {
        if(direction == 1)
        {
            w[x-1][y] = new Ant("o",x-1,y,0, true);
            a_array[NUM_ANT+1] = new Ant("o",x-1,y,0, true);
        }
        else if(direction == 2)
        {
            w[x+1][y] = new Ant("o",x+1,y,0, true);
            a_array[NUM_ANT+1] = new Ant("o",x+1,y,0, true);
        }
        else if(direction == 3)
        {
            w[x][y-1] = new Ant("o",x,y-1,0, true);
            a_array[NUM_ANT+1] = new Ant("o",x,y-1,0, true);
        }
        else if(direction == 4)
        {
            w[x][y+1] = new Ant("o",x,y+1,0, true);
            a_array[NUM_ANT+1] = new Ant("o",x,y+1,0, true);
        }
    }

    else if(type == "x") ///DOODLEBUG
    {
        if(direction == 1)
        {
            w[x-1][y] = new Doodlebug("x",x-1,y,0, true,0);
            db_array[NUM_DB+1] = new Doodlebug("x",x-1,y,0, true,0);
        }
        else if(direction == 2)
        {
            w[x+1][y] = new Doodlebug("x",x+1,y,0, true,0);
            db_array[NUM_DB+1] = new Doodlebug("x",x+1,y,0, true,0);
        }
        else if(direction == 3)
        {
            w[x][y-1] = new Doodlebug("x",x,y-1,0, true,0);
            db_array[NUM_DB+1] = new Doodlebug("x",x,y-1,0, true,0);
        }
        else if(direction == 4)
        {
            w[x][y+1] = new Doodlebug("x",x,y+1,0, true,0);
            db_array[NUM_DB+1] = new Doodlebug("x",x,y+1,0, true,0);
        }
    }
}

//Check need for breed/death function
//PRE: Breed/death functions are executed for either ant or doodlebug
//POST: Adds/deletes organism from grid
void step_check(World w, string type, Ant *a_array[], int NUM_ANT, Doodlebug *db_array[], int NUM_DB, int id)
{
    int temp_d;
    if(type == "x") ///DOODLEBUG
    {
        if(db_array[id]->get_step_count()==8)
        {
            temp_d = check_grid_next(w, db_array[id]->get_x_coordinate(), db_array[id]->get_y_coordinate());
            breed("x",temp_d, w, a_array, NUM_ANT, db_array, NUM_DB, id, db_array[id]->get_x_coordinate(), db_array[id]->get_y_coordinate());
            db_array[id]->set_step_count(0);
        }

        if(db_array[id]->get_starve_ticks() == 3)
        {
            db_array[id]->set_alive(false);
            db_array[id]->death(db_array[id]->get_x_coordinate(), db_array[id]->get_y_coordinate());
            clear_slot(w,db_array[id]->get_x_coordinate(), db_array[id]->get_y_coordinate(), 5);
        }
    }
    else if(type == "o") ///ANT
    {
        if(a_array[id]->get_step_count() == 3)
        {
            temp_d = check_grid_next(w,a_array[id]->get_x_coordinate(),a_array[id]->get_y_coordinate());
            breed("o",temp_d, w, a_array, NUM_ANT, db_array, NUM_DB, id, a_array[id]->get_x_coordinate(), a_array[id]->get_y_coordinate());
            a_array[id]->set_step_count(0);
        }
    }
}

//Counts # of organisms in the grid
//PRE: Either ant or doodlebug is chosen for count
//POST: Returns int value of the # of selected organism
int organism_count(World w, string type)
{
    int count = 0;
    for(int i=0; i<S; i++)
        for(int j=0; j<S; j++)
            if(w[i][j]->get_type() == type)
                count++;
    return count;
}
