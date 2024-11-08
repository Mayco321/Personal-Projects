///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////
#include "Arena.h"
#include "Robot.h"
#include "Player.h"

#include <iostream>

using namespace std;


class Player;

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
}

Arena::~Arena()
{
    for(int i = 0 ; i < m_nRobots; i++){
        delete m_robots[i];
    }
    delete m_player;
    
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{   
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const
{  
    int count = 0;

    for(int i = 0; i < m_nRobots; i++){
        if(m_robots[i]->row() == r && m_robots[i]->col() == c){
            count++;
        }
    }

    return count; 
}

void Arena::display(string msg) const
{
      // Position (row,col) in the arena coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++){
        for (c = 0; c < cols(); c++){
            grid[r][c] = '.';
        }
    }
    
    for(r = 0; r < rows(); r++){
        for(c = 0; c < cols(); c++){
            if(grid[r][c] == '.' && nRobotsAt(r, c) == 1){
                grid[r][c] = 'R';
            }
            else if(grid[r][c] == '.' && nRobotsAt(r, c) >= 2 && nRobotsAt(r, c) <= 8){
                grid[r][c] = '0' + nRobotsAt(r, c);
            }
            else if(grid[r][c] == '.' && nRobotsAt(r, c) >= 9){
                grid[r][c] = '9';
            }
        }
    }
        // Indicate each robot's position


        // Indicate player's position
    if (m_player != nullptr)
    {
          // Set the char to '@', unless there's also a robot there,
          // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{   
    if(m_nRobots >= MAXROBOTS ){
        return false;
    }

    Robot* newRobot = new Robot(this, r, c);
    m_robots[m_nRobots] = newRobot;
    m_nRobots++;
    return true;

}

bool Arena::addPlayer(int r, int c)
{
      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

void Arena::damageRobotAt(int r, int c)
{   
    for(int i = 0; i < m_nRobots; i++){
        if(m_robots[i]->row() == r && m_robots[i]->col() == c){
            if(m_robots[i]->takeDamageAndLive() == false){
                delete m_robots[i];
                m_robots[i] = m_robots[m_nRobots - 1];
                m_nRobots--;
            }
        }
    }
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {
        m_robots[k]->move();
        if(m_robots[k]->row() == m_player->row() && m_robots[k]->col() == m_player->col()){
            m_player->setDead();
        }
    }
    return ! m_player->isDead();
}
