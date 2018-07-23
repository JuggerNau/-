// stdafx.cpp : source file that includes just the standard includes
//	btsystem.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


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
            if(A1==0) A1=99999;
            if(A2==0) A2=99999;
            if(i==d) d=0;
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
            if(d==0) d=99999;
            if(i==j) d=0;
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
            if(d==0) d=99999;
            if(i==j) d=0;
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
    value=c[a][b];

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
}


//zjy
int Graph::chazhao(string s)
{
    for(i = 0;i < 50;i++)
    {
        if(vex[i] == s) break;
    }
    return i;
}

void Graph::Deleteroutine(string routine,string c1,string c2)
{
    Deletetran(c2,c1);
    int s1,s2,w;
    s1 = chazhao(c1);
    s2 = chazhao(c2);
    for(w = 0;w < 50;w++)
    {
        if(VEX[w].data == routine) break;
    }
    Edge *p = VEX[w].link;
    //Edge *q = p -> next;
    //int s1,s2;
    int max =0,s[30];
    s[30] = 0;
    w = 0;
    while(p != NULL)
    {
        s[w++] = p -> dename;
        p = p -> next;
        max++;
    }
    for(w = 0;w < max ;w++)
    {
        Edgtra[s[w]][s2] = 0;
        Edgtra[s2][s[w]] = 0;
    }
    for(w = 0;w < 30;w++)
    {
        Edgmon[w][s2] = 0;
        Edgmon[s2][w] = 0;
    }
    deleteedge(s1,s2);
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

void Graph::insert(string c1,string c2,int d,int x,string num)
{
    int s1,s2,t,money;
    Inserttran(c1,c2,num);
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
    int si;
    InsertVertex(num);
    InsertEdge(n1-1,s1);
    InsertEdge(n1-1,s2);
    fstream f1("tran.txt",ios::out);
    f1<<n1<<endl;
    for(si = 0;si < n;si++)
    {
        ch=VEX[si].data;
        f1 << ch<<" ";
    }
    f1<<endl;
    string c;
    for(si = 0;si < n1;si++)
    {
        Edge *p = VEX[si].link;
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

void Graph::Deletetran(string num1,string num2)/*第一个要删除的*/
{
    int si;
    int flat=0;
    for( si=0;si<n1;si++)
    {
        Edge *p=VEX[si].link;
        if(p->name==num1&&p->next->name==num2)
        {
            VEX[si].link=p->next;
            flat=1;
        }
    }
    if(flat==0)
    {   Edge *q;
        for( si=0;si<n1;si++)
        {
            q=VEX[si].link;
            while(q!=NULL)
            {
                if(q->name==num2&&q->next->name==num1)
                {
                    q->next=NULL;
                }
                q=q->next;
            }
        }
    }
    string ch;
    fstream f1("tran.txt",ios::out);
    f1<<n1<<endl;
    for(si = 0;si < n1;si++)
    {
        ch=VEX[si].data;
        f1 << ch<<" ";
    }
    f1<<endl;
    string c;
    for(si = 0;si < n1;si++)
    {
        Edge *p = VEX[si].link;
        while(p!=NULL)
        {
            c=p->name;
            f1 <<c<<" ";
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
    int si;
        Edge *p = new Edge;
        if(VEX[v1].link!=NULL)
        {
            VEX[v1].link->qnext=p;
        }
        p->next=VEX[v1].link;
        VEX[v1].link=p;
        p->qnext=NULL;
        p->name=c;
        for(si=0;si<n;si++)
        {
            if(vex[si]==c) break;
        }
        p->dename=si;
}

void Graph::set()             //从文件中读取公交线路，调用Vertex和Edge
{
    ifstream f1;
    f1.open("tran.txt",ios::in);
    int ns;
    string ch;
    f1 >> ns;
    int si;
    for(si = 0;si < ns;si++)
    {
        f1 >> ch;
        InsertVertex(ch);
    }
    string c;
    for(si = 0;si < ns;si++)
    {
        f1 >> c;                     //读取邻接点
        while(c!="1")
        {
            InsertEdge(si,c);
            f1 >> c;
        }
    }
    f1.close();
}


//zj
void Graph::findtran()
{
    int fi;
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

                            comtran[i]=VEX[fi].data;
                            k=1;
                            break;
                        }
                    }
                    if(k!=0) break;
                    if(q==NULL)
                    for(q=p;q!=NULL;q=q->qnext)
                    {
                        if(q->dename==savepass[i+1])
                        {
                            if(comtran[i-1]!=VEX[fi].data)
                            {comtran[i]=VEX[fi].data;
                            k=1;
                            break;}
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

void Graph::searchl(string x1)
{
    int i;
    int j=0;
    for(i=0;i<15;i++) a[i]="0";
    for(i=0; ; i++)
    {
        if(VEX[i].data==x1)
        {
            Edge *p = VEX[i].link;
            while(p != NULL)
            {
                //cout << p->name << " ";
                a[j]=p->name;
                j++;
                p = p->next;
            }
            break;
        }
        if(i==n1)
        {
            a[0]= "无此公交或地铁线路";
            break;
        }
    }
}

void Graph::searchp(string x1)
{
    int i;
    Edge *p;
    int j=0;
    for(i=0; i<15; i++) a[i] = "0";
    for(i=0; i<n1; i++)
    {
        p = VEX[i].link;
        while(p != NULL)
        {
            if(p->name == x1)
            {
                //cout << VEX[i].data << " ";
                a[j]= VEX[i].data;
                j++;
                break;
            }
            else
            {
                p = p ->next;
            }
        }
    }
}

void Graph::Preserve()           //保存
{
    string ch1,ch2;           //ch1是inform地名，ch2线路地名
    int d1,d2,A1;
    double A2;
    ofstream f4;                        //距离和时间
    f4.open("inform.txt",ios::out);
    f4 << n << endl;
    for(i = 0;i < n;i++)
    {
        ch1 = vex[i];
        f4 << ch1 << " ";
    }
    f4 << endl;
    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            if(j>i)
            {
                A1 = Edgdis [i][j];
                if(A1!=0&&A1!=99999) f4 << j << " " << A1 << " ";
                A2 = Edgtim [i][j];
                if(A1!=0&&A1!=99999) f4 <<A2 << " ";
            }
        }
        f4 << "-1" << endl;
    }
    f4.close();
    ofstream f5;                 //换乘
    f5.open("transport.txt",ios::out);
    for(i = 0;i < n;i++)
    {
        for(j=0;j<n;j++)
        {
            d1 = Edgtra [i][j];
            if(d1 == 99999) d1=0;
            f5 << d1 << " ";
        }
        f5 << endl;
    }
    f5.close();
    ofstream f6;                 //金钱
    f6.open("money.txt",ios::out);
    for(i = 0;i < n;i++)
    {
        for(j=0;j<n;j++)
        {
            d2 = Edgmon [i][j];
            if(d2 == 99999) d2=0;
            f6 << d2 << " ";
        }
        f6 << endl;
    }
    f6.close();
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
    for(i=0;i<n;i++)
    {
        for(j=1;j<=i;j++)
            c[i][j]=c[j][i];
    }
    Floyd(a,b);
}


Graph g;
