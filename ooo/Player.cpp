///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////
#include "Arena.h"
#include "Player.h"
#include "globals.h"

#include <iostream>

using namespace std;

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

string Player::takeComputerChosenTurn()
{  
    int dir = rand() % 4;
    if (shoot(dir)){
        return "Shot and hit!";
    }
    else{
        return "Shot and missed!";
    }

    // If no robots are in shooting range, move in a random direction.
    move(rand() % 4);
    return "Moved.";
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
      case UP: if(m_row > 1){m_row--;}break;
      case DOWN: if(m_row < m_arena->rows()){m_row++;} break;
      case LEFT: if(m_col > 1){m_col--;}break;
      case RIGHT: if(m_col < m_arena->cols()){m_col++;}break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;
    if (rand() % 3 == 0){  // miss with 1/3 probability
        return false;
    }

    switch(dir){
        case 0: for(int i = 0; i < MAXSHOTLEN; i++){
            int tempRow = m_row - i;
            if(tempRow< 1){
                return false;
            }
            if(m_arena -> nRobotsAt(tempRow, m_col) > 0){
                m_arena->damageRobotAt(tempRow, m_col);
                return true;
            }
        }
        break;
        case 1: for(int i = 0; i < MAXSHOTLEN; i++){
            int tempRow = m_row + i;
            if(tempRow > m_arena -> rows()){
                return false;
            }
            if(m_arena -> nRobotsAt(tempRow, m_col) > 0){
                m_arena->damageRobotAt(tempRow, m_col);
                return true;
            }
        }
        break;
        case 2: for(int i = 0; i < MAXSHOTLEN; i++){
            int tempCol = m_col - i;
            if(tempCol < 1){
                return false;
            }
            if(m_arena->nRobotsAt(m_row, tempCol) > 0){
                m_arena -> damageRobotAt(m_row, tempCol);
                return true;
            }
        }
        break;
        case 3:for(int i = 0; i < MAXSHOTLEN; i++){
            int tempCol = m_col + i;
            if(tempCol > m_arena->cols()){
                return false;
            }
            if(m_arena->nRobotsAt(m_row, tempCol) > 0){
                m_arena -> damageRobotAt(m_row, tempCol);
                return true;
            }
        }
        break;
        
        default: return false;
    }
    return false;
      // TODO:  Damage the nearest robot in direction dir, returning
      // true if a robot is hit and damaged, false if not hit.
        // This implementation compiles, but is incorrect.
}

bool Player::isDead() const
{
    return m_dead;  
}

void Player::setDead()
{
    m_dead = true;
}