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
void print_rule();

int main(int argc, const char * argv[]) {
    cout<<"Welcome to OOXX!!"<<endl;
    cout<<"Do you want to read the game rules?[y/n] ";
    string command;
    cin>>command;
    if (command=="y" || command=="Y" || command=="yes" || command=="YES")
        print_rule();
    cout<<endl<<"Let's start!!"<<endl;
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

void print_rule()
{
    cout<<endl;
    cout<<"緣起："<<endl;
    cout<<"那天在老梅海邊，大家在沙灘上玩起OOXX，威齊把木棍搶去加了三角形符號，「>2人的OOXX」，這是第一個創意。"<<endl;
    cout<<"後來大家又任性地開始把棋盤加大，「可以隨時加行/加列的OOXX」，這是第二個創意。"<<endl;
    cout<<"不料很快地一個浪沖上來，遊戲便提前結束了QQ"<<endl;
    cout<<"因為想送彥廷生日禮物又不知道要送什麼(X)因為期中快到了不想念書(X)因為覺得這個idea實作出來應該滿有趣的(O)"<<endl;
    cout<<"總之就花了一點點時間（大概一場不知道重點是什麼的留美演講的時間吧）寫了這個小程式~"<<endl;
    cout<<"希望你會喜歡XD 還有生日快樂>///<"<<endl;
    cout<<endl;
    cout<<"遊戲規則："<<endl;
    cout<<"0. row是橫的(x)，column是直的(y) XD"<<endl;
    cout<<"1. 每次輪到你的時候，你可以加一個row或column（也可以不加），然後放一個token（畫一個O或X的概念）"<<endl;
    cout<<"2. 棋盤的大小上限是999x999"<<endl;
    cout<<"3. 贏的條件：從一個邊連到對面的邊，直的橫的很直觀，斜的一定要斜率=1或-1，"<<endl;
    cout<<"如果現在棋盤是扁的，就是要從上面第一行連到下面最後一行，但不需要從最左邊連到最右邊。例如："<<endl;
    cout<<"---------------------"<<endl;
    cout<<"|   | O |   |   |   |"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"|   |   | O |   |   |"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"|   |   |   | O |   |"<<endl;
    cout<<"---------------------"<<endl;
    cout<<endl;
    cout<<"備註："<<endl;
    cout<<"1. 每個提示句最後的[a/p]意思就是請輸入a或p來選擇指令。輸入完成請按enter"<<endl;
    cout<<"2. [integer]表示只能輸入整數，如果打非數字的東西程式會掛掉XD 我懶得處理這個error :p"<<endl;
    cout<<"3. 其實沒有花很多時間仔細測試它，如果有發現bug歡迎告訴我XDD （請盡情的玩壞它>//<）"<<endl;
    cout<<"4. 我的程式能力還沒有強到可以輕鬆寫出圖形介面，請忍耐一下醜醜的黑螢幕文字介面QQ"<<endl;
}
