#include<iostream>
#include<string>
#include<cstdlib> // random()����
#include<ctime> // ���ؾ���ĳĳ�����ֵ
#include<unordered_map>
//#include<algorithm> // begin �� end ����������ô???
#define N 11 // 0 - 10
#define INF 1e10
using namespace std;

//void getId(auto&);
// ��Ԫ���������ΰ�....
string sltName();
int rtRand(); // constexpr ����ô....��Ȼ������ô...

class Per{
    // ����friend
    // ��������Ҳ����friend��...
  //  friend void getId(auto&);
public:
    using num = string::size_type;
    //Per() = default;
    // ���캯�������麯��ô....
    Per() { static int ctr = 1; this->id = ctr++;} // ����ú����б��е���???
    virtual void setGame(unordered_map<int,int>&){}; // �麯����Ҫʵ����?
    // TM�麯��ҲҪʵ��...������Ӹ�{}
    auto setGes( num ,unordered_map<int,int>& )->Per&; // ����auto, ����Ҫ��������
    auto setName( string _name )->Per&;
    num getGes(){ return this->Ges ; }
    num getId(){ return this->id ; }
    const string& getName(){ return this->name ;  }
private:
    num Ges;
    num id;
    string name;
   //  mutable int ctr = 0; mutable�����û�ð�....
};

Per& Per::setGes( num _Ges , unordered_map<int,int>& info ){
    this->Ges = _Ges;
    info[_Ges]++; // Ҫ��û�еĻ���ʼ��Ϊ0ô????
    return *this;
}

Per& Per::setName(string _name){
    this->name = _name;
    return *this;
}

/**<  Per���� */

class Agst:public Per{
public:
    Agst():Per() {}; // ���*this �ĵ������Agst�ǰ�...
    // id�趨
    void setGame(unordered_map<int,int>& info) override{
        this->setGes( rtRand()%N, info ).setName(sltName());
    };// override ��д����Ҫд��������ô....
};

/**< Agst */
class Ated:public Per{ // �����public����public�� private����private
public:
    Ated():Per() {};
    void setGame(unordered_map<int,int>&info) override{ // override����Ҫд�ں�����������ô....ʲô�ƹ涨...
        string _name;
    // ������ĺ����ܷ��ʻ���ı���?
        num _Ges; // ����ı�����������ô,ֱ�ӵ���ô...
        cout<<"pls enter Name and number"<<endl
            <<"Name: ";
        cin>>_name;
        cout<<"Number: ";

        while(  cin>>_Ges  ){ // ���������ֵ?
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
    void prtWr()const;//���޸����Ա
private:
    int wrId = -1;
    num wrGes = INF;
    string wrName = "";
};

void Jur::prtAsltWr(Agst *player,int len,unordered_map<int,int>&info){ // begin()  end() ���ص��ǵ�����ô,����ָ��???�������ǲ���ָ��???
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
    if(this->wrId == -1)//û��ʤ��
        cout<<"There is no winner!."<<endl;
    else
        cout<<"winner: "<<this->wrId<<" "<<this->wrName<<" "<<this->wrGes;
}

/**< Jur */

int rtRand(){
    static int ctr = 1;
    srand( static_cast<unsigned int>(time(0)) + (ctr++));
    return rand(); // random rand() ���ǳ���ô...
    // rand()��Ȼ����const expressionô....
}

string sltName(){
    static string names[] = { "GaoHaoRan","YH","LuYu","XinYu","007","butYuHao","ChenYuNing","ZhouZeYu","ZhaoKai"  };
    // end(names) - begin(names) �����鳤��
    // ֻ�ó�ʼ��һ�Σ����Ҳ���ı�
    return names[   rtRand() % ( end(names) - begin(names) )   ];
}
/*
void getId(auto& per){
    static int ctr = 1;
    per.id = ctr++; // Ӧ�ÿ��Եİ�....
}
*/
int main(){
    int n; unordered_map<int , int > info;
    cout<<"pls enter number of players: ";
    cin>>n;
    Agst players[n]; // ����ǲ��ǹ��������Ѿ�Ĭ�Ϲ�������????
    for(int i=0; i<n; i++ )
        players[i].setGame(info);

    Ated role;
    role.setGame(info);
    // �ó�Ӯ����...
    Jur judge;
    judge.prtAsltWr(players,n,info);
    judge.prtWr();
    return 0;
}

