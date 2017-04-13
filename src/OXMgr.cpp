//
//  OXMgr.cpp
//  OOXX
//
//  Created by Sonia on 2017/4/12.
//  Copyright © 2017年 Sonia. All rights reserved.
//

#include "OXMgr.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void OXMgr::initialize()
{
    _board.clear();
    vector<int> row;
    for (int i=0; i<DEFAULT_SIZE; ++i)
        row.push_back(-1);
    _board.push_back(row); //the first row
    
    for (int i=1; i<DEFAULT_SIZE; ++i)
        add_row(true);
}

void OXMgr::add_player(int i)
{
    cout<<"Set player "<<i<<"'s name: ";
    string str;
    cin>>str;
    cout<<"Set player "<<i<<"'s symbol(only 1 character is allowed): ";
    string sym;
    cin>>sym;
    
    _player.push_back(OXPlayer(str,sym[0]));
    cout<<endl;
}

bool OXMgr::add_row( bool end )
{
    if (_board.size()>=999)
        return false;
    vector<int> row;
    for (int i=0; i<_board.at(0).size(); ++i)
        row.push_back(-1);
    if (end)
        _board.push_back(row);
    else
        _board.insert(_board.begin(), row);
    return true;
}

bool OXMgr::add_column( bool end )
{
    if (_board.at(0).size()>=999)
        return false;
    if (end)
    {
        for (int row=0; row<_board.size(); ++row)
            _board.at(row).push_back(-1);
    }
    else
    {
        for (int row=0; row<_board.size(); ++row)
            _board.at(row).insert(_board.at(row).begin(), -1);
    }
    return true;
}

void OXMgr::play()
{
    initialize();
    cout<<endl<<"Game started!!"<<endl;
    int player=0, winner;
    while (true)
    {
        winner=action(player);
        if (winner==-2) //tie
        {
            print_tie();
            break;
        }
        else if (winner==-1) //continue
        {
            if (player==_player.size()-1)
                player=0;
            else
                ++player;
        }
        else //someone wins
        {
            print_winner(winner);
            break;
        }
    }
}

int OXMgr::action(int player)
{
    cout<<endl<<">>Now is "<<_player.at(player).getName()<<"'s turn:"<<endl;
    print_board();
    bool added=false;
    while (true)
    {
        string command;
        cout<<"[p]ut token or [a]dd row/column?[p/a] ";
        cin>>command;
        if (command=="p" || command=="P" || command=="put" || command=="PUT")
        {
            int row,col;
            cout<<"row num?[integer] ";
            cin>>row;
            cout<<"column num?[integer] ";
            cin>>col;
            
            if (put(row-1,col-1,player))
            {
                print_board();
                cout<<"Are you sure you want to put your symbol here?[y/n] ";
                cin>>command;
                if (command=="y" || command=="Y" || command=="yes" || command=="YES")
                    return check_winner(player);
                else
                {
                    put(row-1,col-1,-1); //undo move
                    print_board();
                    continue;
                }
            }
            else
                continue;
        }
        else if (command=="a" || command=="A" || command=="add" || command=="ADD")
        {
            if (added)
            {
                cout<<"You can only add one column or row in a move!!"<<endl;
                continue;
            }
            cout<<"add [c]olumn or [r]ow?[c/r] ";
            cin>>command;
            if (command=="c" || command=="C" || command=="column" || command=="COLUMN")
            {
                bool end;
                cout<<"add at [f]ront(left) or [e]nd(right)?[f/e] ";
                cin>>command;
                if (command=="f" || command=="F" || command=="front" || command=="FRONT" || command=="left" || command=="LEFT")
                    end=false;
                else if (command=="e" || command=="E" || command=="end" || command=="END" || command=="right" || command=="RIGHT")
                    end=true;
                else
                {
                    cout<<"command error"<<endl;
                    continue;
                }
                if (add_column(end))
                {
                    print_board();
                    added=true;
                }
                else
                {
                    cout<<"Too many columns!!"<<endl;
                    continue;
                }
            }
            else if (command=="r" || command=="R" || command=="row" || command=="ROW")
            {
                bool end;
                cout<<"add at [f]ront(top) or [e]nd(bottom)?[f/e] ";
                cin>>command;
                if (command=="f" || command=="F" || command=="front" || command=="FRONT" || command=="top" || command=="TOP")
                    end=false;
                else if (command=="e" || command=="E" || command=="end" || command=="END" || command=="bottom" || command=="bottom")
                    end=true;
                else
                {
                    cout<<"command error"<<endl;
                    continue;
                }
                if (add_row(end))
                {
                    print_board();
                    added=true;
                }
                else
                {
                    cout<<"Too many rows!!"<<endl;
                    continue;
                }
            }
            else
            {
                cout<<"command error"<<endl;
                continue;
            }
        }
        else
        {
            cout<<"command error"<<endl;
            continue;
        }
    }
}

bool OXMgr::put(int row, int col, int player)
{
    if (row>=_board.size() || row<0 || col>=_board.at(0).size() || col<0)
    {
        cout<<"Out of board range!!"<<endl;
        return false;
    }
    int &block=_board.at(row).at(col);
    
    if (block==-1 || player==-1)
    {
        block=player;
        return true;
    }
    else
    {
        cout<<"This block is already occupied by "<<_player.at(block).getName()
        <<"(symbol "<<_player.at(block).getSym()<<")!!"<<endl;
        return false;
    }
}

int OXMgr::check_winner(int player)
{
    size_t row_count=_board.size();
    size_t col_count=_board.at(0).size();
    bool tie=true;
    for (int row=0; row<row_count; ++row)
    {
        bool win=true;
        for (int col=0; col<col_count; ++col)
        {
            if (_board.at(row).at(col)!=player)
            {
                win=false;
                if (_board.at(row).at(col)==-1)
                {
                    tie=false;
                    break;
                }
            }
        }
        if (win)
            return player;
    }
    for (int col=0; col<col_count; ++col)
    {
        bool win=true;
        for (int row=0; row<row_count; ++row)
        {
            if (_board.at(row).at(col)!=player)
            {
                win=false;
                break;
            }
        }
        if (win)
            return player;
    }
    if (row_count<=col_count) //--
    {
        for (int col=0; col<col_count; ++col)
        {
            if (_board.at(0).at(col)!=player)
                continue;
            
            if (!(col+1<row_count)) //left
            {
                int c=col;
                bool win=true;
                for (int row=1; row<row_count; ++row)
                {
                    --c;
                    if (_board.at(row).at(c)!=player)
                    {
                        win=false;
                        break;
                    }
                }
                if (win)
                    return player;
            }
            
            if (!(col+row_count>col_count)) //right
            {
                int c=col;
                bool win=true;
                for (int row=1; row<row_count; ++row)
                {
                    ++c;
                    if (_board.at(row).at(c)!=player)
                    {
                        win=false;
                        break;
                    }
                }
                if (win)
                    return player;
            }
        }
    }
    else // |
    {
        for (int row=0; row<row_count; ++row)
        {
            if (_board.at(row).at(0)!=player)
                continue;
            
            if (!(row+1<col_count)) //up
            {
                int r=row;
                bool win=true;
                for (int col=1; col<col_count; ++col)
                {
                    --r;
                    if (_board.at(r).at(col)!=player)
                    {
                        win=false;
                        break;
                    }
                }
                if (win)
                    return player;
            }
            
            if (!(row+col_count>row_count)) //down
            {
                int r=row;
                bool win=true;
                for (int col=1; col<col_count; ++col)
                {
                    ++r;
                    if (_board.at(r).at(col)!=player)
                    {
                        win=false;
                        break;
                    }
                }
                if (win)
                    return player;
            }
        }
    }
    
    if (tie)
        return -2;
    else
        return -1;
}

void OXMgr::print_board()
{
    cout<<endl;
    cout<<"    ";
    for (int col=0; col<_board.at(0).size(); ++col)
        cout<<setw(3)<< col+1 <<" ";
    cout<<endl;
    cout<<"    "<<"-";
    for (int col=0; col<_board.at(0).size(); ++col)
        cout<< "----";
    cout<<endl;
    
    for (int i=0; i<_board.size(); ++i)
    {
        cout<<setw(3)<<i+1<<" "<<"| ";
        for (int col=0; col<_board.at(i).size(); ++col)
        {
            if (_board.at(i).at(col) == -1)
                cout<<" "<<" | ";
            else
                cout<< _player.at(_board.at(i).at(col)).getSym() <<" | ";
        }
        cout<<endl;
        
        cout<<"    "<<"-";
        for (int col=0; col<_board.at(0).size(); ++col)
            cout<< "----";
        cout<<endl;
    }
    cout<<endl;
}
