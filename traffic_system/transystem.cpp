#include "transystem.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////


void Graph::InsertEdgtim(const int v1,const int v2,double weight)  //存储为矩阵
{
    if(v1!=-1&&v2!=-1)
    {
        Edgtim [v1][v2] = weight;
        Edgtim [v2][v1] = weight;
    }
}
void Graph::InsertEdgtra(const int v1,const int v2,int weight)
{
    Edgtra [v1][v2] = weight;
    Edgtra [v2][v1] = weight;
}
void Graph::InsertEdgdis(const int v1,const int v2,int weight)
{
    if(v1!=-1&&v2!=-1)
    {
        Edgdis [v1][v2] = weight;
        Edgdis [v2][v1] = weight;
    }
}
void Graph::InsertEdgmon(const int v1,const int v2,int weight)
{
    Edgmon [v1][v2] = weight;
    Edgmon [v2][v1] = weight;
}

void Graph::get()                           //从文件读取距离、时间
{
    ifstream f1;
    f1.open("inform.txt",ios::in);
    string ch;
    int d,A1;
    double A2;
    f1 >> n;
    for(i = 0;i < n;i++)
    {
        f1 >> ch;
        vex[i] = ch;
    }
    for(i = 0;i < n;i++)
    {
        f1 >> d;        //读取邻接点
        while(d!=-1)
        {
            f1 >> A1 >> A2;  //读取权值
            InsertEdgdis(i,d,A1);
            InsertEdgtim(i,d,A2);
            f1 >> d;
        }
    }
    f1.close();
    gettran();
    getmon();
}

void Graph::gettran()                        //从文件读取换乘
{
    ifstream f2;
    f2.open("transport.txt",ios::in);
    int d;
    for(i = 0;i < n;i++)
    {
        for(j=0;j<n;j++)
        {
            f2 >> d;  //读取权值
            if(i!=j) d=99999;
            InsertEdgtra(i,j,d);
        }
    }
    f2.close();
}

void Graph::getmon()                        //从文件读取金钱
{
    ifstream f3;
    f3.open("money.txt",ios::in);
    int d;
    for(i = 0;i < n;i++)
    {
        for(j=0;j<n;j++)
        {
            f3 >> d;  //读取权值
            if(i!=j) d=99999;
            InsertEdgmon(i,j,d);
        }
    }
    f3.close();
}

void Graph::Floyd(int a,int b)              //Floyd函数
{
    int temp;
    for(k=0;k<n;k++)//k是中间节点，i是起点j是中点。其实就是枚举中间节点，来求i j 的最短路径
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                t1=c[i][k];
                t2=c[k][j];
                t3=c[i][j];
                if(t1!=99999&&t2!=99999&&(t3==99999||t1+t2<t3)) //松弛 覆盖原来的最短路
                {c[i][j]=t1+t2,parth[i][j]=k;}//记录i j的中间点是k
            }
        }
    }
    k=0;
    savepass[k++]=b;
    while(parth[a][b]!=0)
    {
        savepass[k++]=parth[a][b];
        b=parth[a][b];
    }
    savepass[k]=a;
    for(i=0;i<k/2+1;i++)
    {
        temp=savepass[i];
        savepass[i]=savepass[k-i];
        savepass[k-i]=temp;
    }
    trannum=k;
    for(i=0;i<=k;i++) cout<<savepass[i]<<" ";
    cout<<endl<<endl;                       /**************************/
}

/*void Graph::quicksort(int a[],int left,int right)
{
    if(left >= right)
        return;
    int i = left,j = right;
    int temp;
    //int key = a[left];//取首元素为关键值
    int key = a[(left + right) / 2];
    while(1)
    {
        while(a[j] > key)       //这里不能使用>=，有可能导致前半部分二次排序不起作用
            j--;
        while(a[i] < key)
            i++;
        if(i >= j)
            break;//do nothing
        //swap
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    quicksort(a,left,j);     //取j不取i，因为后走的i有可能超过了j
    quicksort(a,j+1,right);
}
*/

//zjy
int Graph::chazhao(string s)
{
    for(i = 0;i < 50;i++)
    {
        if(vex[i] == s) break;
    }
    return i;
}

void Graph::Deleteroutine()
{
    string routine;
    cout << "请输入删除的公交或地铁线路：";
    cin >> routine;
    int w;
    for(w = 0;w < n;w++)
    {
        if(VEX[w].data == routine) break;
    }
    Edge *p = VEX[w].link;
    Edge *q = p -> next;
    int s1,s2;
    while(p != NULL && q != NULL)
    {
        s1 = chazhao(p -> name);
        s2 = chazhao(q -> name);
        deleteedge(s1,s2);
        p = p -> next;
        q = q -> next;
    }
}

void Graph::deleteedge(int s1,int s2)
{
    Edgdis[s1][s2] = 0;
    Edgdis[s2][s1] = 0;
    Edgtim[s1][s2] = 0;
    Edgtim[s2][s1] = 0;
    Edgmon[s1][s2] = 0;
    Edgmon[s2][s1] = 0;
    Edgtra[s1][s2] = 0;
    Edgtra[s2][s1] = 0;
}

void Graph::insert()
{
    string c1,c2;
    int s1,s2,d,t,money,x;
    cout << "请输入要添加的路线的起点和终点：";
    cin >> c1 >> c2;
    cout << "情输入两地点的距离：";
    cin >> d;
    cout << "输入0为插入新公交，输入1为插入新地铁：";
    cin >> x;
    if(x == 0)
    {
        t = d/200;
        money = 1;
    }
    if(x == 1)
    {
        t = d/1000;
        money = 2;
    }
    s1 = chazhao(c1);
    s2 = chazhao(c2);
    insertroutine(s1,s2,d,t,money);
}

void Graph::insertroutine(int s1,int s2,int d,double t,int money)
{
    Edgdis[s1][s2] = d;
    Edgdis[s2][s1] = d;
    if(Edgtim[s1][s2] == 0 || t < Edgtim[s1][s2])
    {
        Edgtim[s1][s2] = t;
        Edgtim[s2][s1] = t;
    }
    if(Edgmon[s1][s2] == 0 || money < Edgmon[s1][s2])
    {
        Edgmon[s1][s2] = money;
        Edgmon[s2][s1] = money;
    }
    Edgtra[s1][s2] = 1;
    Edgtra[s2][s1] = 1;
}

//zl
void Graph::Inserttran(string s1,string s2,string num)
{
    string ch;
    InsertVertex(num);
    InsertEdge(n1-1,s1);
    InsertEdge(n1-1,s2);
    fstream f1("tran.txt",ios::out);
    f1<<n1<<endl;
    for(int i = 0;i < n1;i++)
    {
        ch=VEX[i].data;
        f1 << ch;
    }
    string c;
    for(int i = 0;i < n1;i++)
    {
        Edge *p = VEX[i].link;
        while(p!=NULL)
        {
            c=p->name;
            f1 << c<<" ";
            p=p->next;
        }
        f1<<"1"<<endl;
    }
    f1.close();
}
void Graph::Deletetran(string num1)
{
    int i;
    for( i=0;i<n1;i++)
    {
        if(VEX[i].data==num1)  //?????strcmp(VEX[i].data,num1)
        {
            break;
        }
    }
    for( ;i+1<n1;i++)
    {
        VEX[i].data=VEX[i+1].data;
        VEX[i].link = VEX[i+1].link;
    }
    //delete VEX[n1-1];
    string ch;
    fstream f1("tran.txt",ios::out);
    f1<<n1-1<<endl;
    for(int i = 0;i < n1-1;i++)
    {
        ch=VEX[i].data;
        f1 << ch;
    }
    string c;
    for(int i = 0;i < n1-1;i++)
    {
        Edge *p = VEX[i].link;
        while(p!=NULL)
        {
            c=p->name;
            f1 << c<<" ";
            p=p->next;
        }
        f1<<"1"<<endl;
    }
    f1.close();
}

void Graph::InsertVertex(string ch)
{
    n1++;
    curNum++;
    if(curNum<=n1) VEX[curNum-1].data=ch;
    VEX[curNum-1].link = NULL;
}

void Graph::InsertEdge(int v1,string c)
{
        Edge *p = new Edge;
        if(VEX[v1].link!=NULL)
        {
            VEX[v1].link->qnext=p;
        }
        p->next=VEX[v1].link;
        VEX[v1].link=p;
        p->qnext=VEX[v1].link;
        p->name=c;
        for(i=0;i<n;i++)
        {
            if(vex[i]==c) break;
        }
        p->dename=i;
        e++;
}

void Graph::set()             //从文件中读取公交线路，调用Vertex和Edge
{
    ifstream f1;
    f1.open("tran.txt",ios::in);
    int ns;
    string ch;
    f1 >> ns;
    for(int i = 0;i < ns;i++)
    {
        f1 >> ch;
        InsertVertex(ch);
    }
    string c;
    for(int i = 0;i < n;i++)
    {
        f1 >> c;                     //读取邻接点
        while(c[0]!='1')
        {
            InsertEdge(i,c);
            f1 >> c;
        }
    }
    f1.close();
}


//zj
void Graph::findtran()
{
    int fi,fj;
    Edge *p,*q;
    for(i=0;i<trannum;i++)
    {
        k=0;
        for(fi=0;fi<n1;fi++)
        {
            for(p=VEX[fi].link;p!=NULL;p=p->next)
            {
                if(p->dename==savepass[i])
                {
                    for(q=p;q!=NULL;q=q->next)
                    {
                        if(q->dename==savepass[i+1])
                        {
                            comtran[i][k++]=VEX[fi].dedata;
                            break;
                        }
                    }
                    if(q==NULL)
                    for(q=p;q!=NULL;q=q->qnext)
                    {
                        if(q->dename==savepass[i+1])
                        {
                            comtran[i][k++]=VEX[fi].dedata;
                            break;
                        }
                    }
                    break;
                }
            }
            if(k!=0) break;
        }
    }
}

void Graph::combine()
{
    int ci=0;
    findtran();
    for(i=0;i<trannum;i++)
        outtran[i]=comtran[i][0];
}

void Graph::calculate(int a,int b,int x)      //计算最短所有距离，x为最短什么，已调用Floyd
{
    for(i=0;i<n;i++) //初始化路径
        for(j=i;j<n;j++)
            parth[i][j]=0;
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
        {
            if(x==1) c[i][j]=Edgtim[i][j];
            if(x==2) c[i][j]=Edgtra[i][j];
            if(x==3) c[i][j]=Edgdis[i][j];
            if(x==4) c[i][j]=Edgmon[i][j];
        }
    Floyd(a,b);
}

void Graph::show()
{
    int a,b;
    for(a=0;a<30;a++)
    {
        for(b=0;b<30;b++)
        {
            cout<<Edgdis [a][b]<<" ";
        }
            cout<<endl;
    }
    for(a=0;a<30;a++)
    {
        for(b=0;b<30;b++)
        {
            cout<<Edgtim [a][b]<<" ";
        }
            cout<<endl;
    }
    for(a=0;a<30;a++)
    {
        for(b=0;b<30;b++)
        {
            cout<<Edgtra [a][b]<<" ";
        }
            cout<<endl;
    }
    for(a=0;a<30;a++)
    {
        for(b=0;b<30;b++)
        {
            cout<<Edgmon [a][b]<<" ";
        }
            cout<<endl;
    }
}
/*
int main()
{
    int x;
    Graph g;
    g.get();
    g.set();
    cout<<"欢迎光临北京线路公交系统"<<endl;
    cout<<"****3、最小路径****"<<endl;
    cout<<"****1、最少时间****"<<endl;
    cout<<"****2、最小转乘****"<<endl;
    cout<<"****4、最小花费****"<<endl;
    cout<<"****5、添加公交****"<<endl;
    cout<<"****6、删除公交****"<<endl;
    cin>>x;
    if(x<5) g.calculate(0,20,x);
    if(x==3)
    {
        g.combine();
    }
    if(x==5)
    {
        g.insert();
        g.Inserttran("车公庄","西单","888路");
    }
    if(x==6)
    {
        g.Deleteroutine();
        g.Deletetran("998路");
    }
    //g.show();
    //g.insert();
    return 0;
}
*/
