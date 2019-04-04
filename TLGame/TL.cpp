#include<iostream>
#include<string>
#include<cstdlib> // random()函数
#include<ctime> // 返回距离某某年的数值
#include<unordered_map>
//#include<algorithm> 
#define N 11 // 0 - 10
#define INF 1e10
using namespace std;

//void getId(auto&);

string sltName();
int rtRand(); //

class Per{
    // 基类friend
   
  //  friend void getId(auto&);
public:
    using num = string::size_type;
    //Per() = default;
    
    Per() { static int ctr = 1; this->id = ctr++;} 
    virtual void setGame(unordered_map<int,int>&){}; 
    // TM虚函数最起码加个{}...
    auto setGes( num ,unordered_map<int,int>& )->Per&; // 对于auto, 引用要另外声明
    auto setName( string _name )->Per&;
    num getGes(){ return this->Ges ; }
    num getId(){ return this->id ; }
    const string& getName(){ return this->name ;  }
private:
    num Ges;
    num id;
    string name;
   
};

Per& Per::setGes( num _Ges , unordered_map<int,int>& info ){
    this->Ges = _Ges;
    info[_Ges]++; // 要是没有的话初始化为0么
    return *this;
}

Per& Per::setName(string _name){
    this->name = _name;
    return *this;
}

/**<  Per基类 */

class Agst:public Per{
public:
    Agst():Per() {}; // 
    // id设定
    void setGame(unordered_map<int,int>& info) override{
        this->setGes( rtRand()%N, info ).setName(sltName());
    };// override 复写函数要写定义里面...
};

/**< Agst */
class Ated:public Per{ // 基类的public还是public， private还是private
public:
    Ated():Per() {};
    void setGame(unordered_map<int,int>&info) override{ // 
        string _name;
    // 派生类
        num _Ges; // 父类的变量不用声明直接调用...
        cout<<"pls enter Name and number"<<endl
            <<"Name: ";
        cin>>_name;
        cout<<"Number: ";

        while(  cin>>_Ges  ){ 
            if(  _Ges<0 || _Ges >N-1 )
                cout<<"pls enter the Number between 0 and "<<N-1<<": ";
            else break;
        }

        this->setGes( _Ges, info).setName(_name);
    }
};

/**< Ated */
class Jur{
public:
    using num = string::size_type;
    Jur() = default;
    void prtAsltWr(Agst *,int ,unordered_map<int,int>&);
    void prtWr()const;//不修改类成员
private:
    int wrId = -1;
    num wrGes = INF;
    string wrName = "";
};

void Jur::prtAsltWr(Agst *player,int len,unordered_map<int,int>&info){ // 
    for( int i=0 ; i<len; i++ ){
        if( player[i].getGes() < this->wrGes && info[player[i].getGes()]==1  ){
            this->wrGes = player[i].getGes();
            this->wrId = player[i].getId();
            this->wrName = player[i].getName();
        }
        cout<<player[i].getId()<<"  "<<player[i].getName()<<"   "<<player[i].getGes()<<";   "
            <<"times: "<<info[player[i].getGes()]<<endl;
    }
}

void Jur::prtWr()const{
    if(this->wrId == -1)//没有胜者
        cout<<"There is no winner!."<<endl;
    else
        cout<<"winner: "<<this->wrId<<" "<<this->wrName<<" "<<this->wrGes;
}

/**< Jur */

int rtRand(){
    static int ctr = 1;
    srand( static_cast<unsigned int>(time(0)) + (ctr++));
    return rand(); //
    // rand()非const expression
}

string sltName(){
    static string names[] = { "GaoHaoRan","YH","LuYu","XinYu","007","butYuHao","ChenYuNing","ZhouZeYu","ZhaoKai"  };
    // end(names) - begin(names) 求数组长度
    // 只用初始化一次，而且不会改变
    return names[   rtRand() % ( end(names) - begin(names) )   ];
}
/*
void getId(auto& per){
    static int ctr = 1;
    per.id = ctr++; // 
}
*/
int main(){
    int n; unordered_map<int , int > info;
    cout<<"pls enter number of players: ";
    cin>>n;
    Agst players[n]; // 这个构建函数已经默认构建好了
    for(int i=0; i<n; i++ )
        players[i].setGame(info);

    Ated role;
    role.setGame(info);
    // 得出赢家了...
    Jur judge;
    judge.prtAsltWr(players,n,info);
    judge.prtWr();
    return 0;
}

