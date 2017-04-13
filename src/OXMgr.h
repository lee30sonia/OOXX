//
//  OXMgr.h
//  OOXX
//
//  Created by Sonia on 2017/4/12.
//  Copyright © 2017年 Sonia. All rights reserved.
//

#ifndef OXMgr_h
#define OXMgr_h

#include <iostream>
#include <vector>

using namespace std;
#define DEFAULT_SIZE 3

class OXPlayer
{
public:
    OXPlayer( string name, char sym ): _name(name), _symbol(sym) { }
    ~OXPlayer() { }
    
    string getName() { return _name; }
    char getSym() { return _symbol; }
    
private:
    string _name;
    char _symbol;
};


class OXMgr
{
public:
    OXMgr(int n)
    {
        for (int i=0; i<n; ++i)
            add_player(i+1);
    }
    ~OXMgr() { }
    
    void initialize();
    void add_player(int);
    bool add_row(bool end);
    bool add_column(bool end);
    
    void play();
    int  action(int player); //returns the winner, or -1 if none, -2 if tie
    bool put(int row, int col, int player); //return false if already occupied
    int  check_winner(int player);
    
    void print_winner(int winner)
    { cout<<_player.at(winner).getName()<<" wins!!"<<endl; }
    void print_tie()
    { cout<<"The board is full and nobody wins. Game ended."<<endl; }
    void print_board();
    
private:
    vector< vector<int> > _board; // a vector of many rows
    //in each row, -1 means blank, i means occupied by _player.at(i)
    vector<OXPlayer> _player;
};

#endif /* OXMgr_h */
