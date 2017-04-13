//
//  main.cpp
//  OOXX
//
//  Created by Sonia on 2017/4/12.
//  Copyright © 2017年 Sonia. All rights reserved.
//

#include <iostream>
#include "OXMgr.h"

using namespace std;

int main(int argc, const char * argv[]) {
    cout<<"Welcome to OOXX!!"<<endl;
    cout<<"How many people are playing?[integer] ";
    int n;
    cin>>n;
    cout<<endl;
    OXMgr oxmgr(n);

    bool playing=true;
    while(playing)
    {
        oxmgr.play();
        cout<<"Do you want to play again?[y/n] ";
        string str;
        cin>>str;
        if (str=="y" || str=="Y" || str=="yes" || str=="YES")
            playing=true;
        else
            playing=false;
    }
    cout<<"Thank you for playing OOXX!!"<<endl;
    return 0;
}