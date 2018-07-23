#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<conio.h>
using namespace std;
class listnode    //类似结构的类
{
    public:
    string ord_num,id,name,sex,age,address,phone;
    int mark;
    listnode *next;
    listnode()
    {
        next=NULL;
    }
};
class System:public listnode    //主类
{
    public:
    //fstream f1;
    listnode *head,*head1;
    listnode *p,*q,*q1;
    private:
    char ch;
    int num;
    int i;
    public:
    System()
    {
		ifstream f1;
        head=new listnode;
        f1.open("c:\\student.txt",ios::in);
        head->next=NULL;
        q=head;
        while(!f1.eof())
        {
            p=new listnode;
            f1>>p->ord_num>>p->id>>p->name>>p->sex>>p->age>>p->address>>p->phone>>p->mark;
            p->next = NULL;
            q->next = p;
            q=q->next;
        }
        f1.close();
    }
    friend bool isNum(string str);
    int Judge(listnode *q);    //判断
    void Obtain();    //获取
    void Query();    //查询
    void Add();    //添加
    void Modify();    //修改
    void Delete();    //删除
    void Sort();    //排序
    void Preserve();    //保存
	int password();    //密码
};
bool isNum(string str) // 判断字符串是不是数字
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}
int System::Judge(listnode *q)    //判断
{
    int j=1;                 //j返回值
    string str1, str2;
    str1 = "男";
    str2 = "女";
    if (q->id.size()!=10||isNum(q->id)!=1)
    {
        j=0;
        cout << "提醒：学号格式可能错误，请输入10位学号" << endl;
    }
    if (q->sex!=str1&&q->sex!=str2)
    {
        j=0;
        cout << "提醒：性别格式可能错误，请输入男/女" << endl;
    }
	if (q->age.size()!=2||isNum(q->age)!=1)
    {
        j=0;
        cout << "提醒：年龄格式可能错误，请输入2位数字" << endl;
    }
    if (q->phone.size()!=11||isNum(q->phone)!=1)
    {
        j=0;
        cout << "提醒：电话格式可能错误，请输入11位数字" << endl;
    }
    if(q->mark>750 || q->mark<0)
    {
        j=0;
        cout << "提醒：成绩数据可能错误，成绩范围在0-750之间" << endl;
    }
    return j;
}
void System::Obtain()    //获取
{
    char a;    //定义回答
    while(1)
	{
	    cout << "是否显示全部的学生信息? 是请输入Y，否请输入N：" <<endl;
        cin >> a;
        if(a!='Y' && a!='y' && a!='N' && a!='n') cout<<"您输入的信息有误，请重新输入。"<<endl;
        else break;
	}
	if(a=='Y' || a=='y')
	{
        q = head->next;
        i=1;
        while ( q != NULL )
        {
            cout<<i++<<" "<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;;
            q = q->next;
        }
	}
}
void System::Query()     //查询
{
	int n,flag=0;
    q = head->next;
    while(1)
	{
        cout<<"请输入您的查询方式（1.学号 2.姓名 3.性别 4.年龄 5.住址 6.电话 7.六级成绩）:";
        cin>>n;
        if(n!=1&&n!=2&&n!=3&&n!=4&&n!=5&&n!=6&&n!=7) cout<<"您输入的信息有误，请重新输入。"<<endl;
        else break;
	}
    if ( n == 1)
	{
		cout<<"请输入所查询学生的学号:";
	    cin>>id;
        while ( q != NULL )
		{
            if ( q->id == id)
		    {
		        flag=1;
                cout<<"该学生信息为："<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;
		    }
            q = q->next;
		}
		if(flag==0) cout<<"无此学生的信息。"<<endl;
	}
    if ( n == 2)
	{
		cout<<"请输入所查询学生的姓名:";
	    cin>>name;
        while ( q != NULL )
		{
		    if ( q->name == name)
		    {
		        flag=1;
                cout<<"该学生信息为："<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;
		    }
            q = q->next;
		}
		if(flag==0) cout<<"无此学生的信息。"<<endl;
	}
	if ( n == 3)
	{
		cout<<"请输入所查询学生的性别:";
	    cin>>sex;
        while ( q != NULL )
		{
		    if ( q->sex == sex)
		    {
		        flag=1;
                cout<<"该学生信息为："<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;
		    }
            q = q->next;
		}
		if(flag==0) cout<<"无此学生的信息。"<<endl;
	}
	if ( n == 4)
	{
		cout<<"请输入所查询学生的年龄:";
	    cin>>age;
        while ( q != NULL )
		{
		    if ( q->age == age)
		    {
		        flag=1;
                cout<<"该学生信息为："<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;
		    }
            q = q->next;
		}
		if(flag==0) cout<<"无此学生的信息。"<<endl;
	}
	if ( n == 5)
	{
		cout<<"请输入所查询学生的住址:";
	    cin>>address;
        while ( q != NULL )
		{
		    if ( q->address == address)
		    {
		        flag=1;
                cout<<"该学生信息为："<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;
		    }
            q = q->next;
		}
		if(flag==0) cout<<"无此学生的信息。"<<endl;
	}
	if ( n == 6)
	{
		cout<<"请输入所查询学生的电话:";
	    cin>>phone;
        while ( q != NULL )
		{
	        if ( q->phone == phone)
		    {
		        flag=1;
                cout<<"该学生信息为："<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;
		    }
            q = q->next;
		}
		if(flag==0) cout<<"无此学生的信息。"<<endl;
	}
	if ( n == 7)
	{
		cout<<"请输入所查询学生的六级成绩(0-750):";
	    cin>>mark;
        while ( q != NULL )
		{
	        if ( q->mark == mark)
		    {
		        flag=1;
                cout<<"该学生信息为："<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;
		    }
            q = q->next;
		}
		if(flag==0) cout<<"无此学生的信息。"<<endl;
	}
}
void System::Add()       //添加
{
	q=new listnode;
	int n=0, x=0, y=0;   //y标志变量
	string j="0";
	while(1)
	{
		cout << "请问您想把此同学放在哪位同学的后面（输入学号，退出请输入0）：" << endl;
		cin >> j;
		if(j == "0") return;
		for (p=head; ; n++)
		{
			if(p->id==j)
			{
				y=1;
				break;
			}
			if(p->next==NULL)
				break;
			p=p->next;

		}
		if(y==1)
			break;
		else
			cout << "未找到，请重新输入" << endl;
	}
	for(p=head; x<n && p->next != NULL; x++)
	{
		p=p->next;
	}
	while(1)
	{
		cout << "请输入要插入的学生的数据(学号，姓名，性别，年龄，地址，电话，六级成绩)：" << endl;
		cout <<"退出请输入0。"<<endl;
		cin >> q->id;
		if(q->id == "0") return;
		cin >> q->name >> q->sex >> q->age >> q->address >> q->phone>>q->mark;
		if (Judge(q)==1)
			break;
	}
	q->next=p->next;
	p->next=q;
	cout << "已成功添加信息。" << endl;
}
void System::Modify()    //修改
{
    string id0;
    q = new listnode;
	char flag;       //flag选择修改方式
    while (1)
    {
        cout << "请输入修改信息的学生学号（退出请输入0）：" << endl;
        cin >> id0;
        if(id0 == "0") return;
        p = head-> next;
        while (p!= NULL && p -> id != id0)
            p = p -> next;
        if (p -> next == NULL && p->id!=id0)
        {
            cout << "未找到此学号。" << endl;
            cout << "请重新输入学号。" << endl;
        }
        else
        {
            cout << "     请选择修改方式：   " << endl;
            cout << "       1.全部修改       " << endl;
            cout << "       2.修改学号       " << endl;
            cout << "       3.修改姓名       " << endl;
            cout << "       4.修改性别       " << endl;
            cout << "       5.修改年龄       " << endl;
            cout << "       6.修改地址       " << endl;
            cout << "       7.修改电话       " << endl;
            cout << "       8.修改六级成绩   " << endl;
            cout << "其他字符.取消修改       " << endl;
            cin >> flag;
            cout<<"正在处理，请稍候……"<<endl;
            if( flag == '1' )
            {
                while(1)
                {
                    cout << "请按照学号，姓名，性别，年龄，住址，电话，六级成绩的顺序输入修改后的学生信息" << endl;
                    cin >> q->id >> q->name >> q->sex >> q->age >> q->address >> q->phone >> q->mark;
                    if ( Judge(q)==1 )
                        break;
                }
                *p=*q;
                cout << "已成功修改信息" << endl;
                break;
            }
            else if( flag == '2' )
            {
                while(1)
                {
                    cout << "请输入修改后学号:";
                    *q = *p;
                    cin >> id0;
                    q->id = id0;
                    if ( Judge(q)==1 )
                        break;
                }
                *p=*q;
                cout << "已成功修改信息" << endl;
                break;
            }
            else if( flag == '3' )
            {
                string name0;
                while(1)
                {
                    cout << "请输入修改后姓名:";
                    *q = *p;
                    cin >> name0;
                    q->name = name0;
                    if ( Judge(q)==1 )
                        break;
                }
                *p=*q;
                cout << "已成功修改信息" << endl;
                break;
            }
            else if( flag == '4' )
            {
                string sex0;
                while(1)
                {
                    cout << "请输入修改后性别:";
                    *q = *p;
                    cin >> sex0;
                    q->sex = sex0;
                    if ( Judge(q)==1 )
                        break;
                }
                *p=*q;
                cout << "已成功修改信息" << endl;
                break;
            }
            else if( flag == '5' )
            {
                string age0;
                while(1)
                {
                    cout << "请输入修改后年龄:";
                    *q = *p;
                    cin >> age0;
                    q->age = age0;
                    if ( Judge(q)==1 )
                        break;
                }
                *p=*q;
                cout << "已成功修改信息" << endl;
                break;
            }
            else if( flag == '6' )
            {
                string address0;
                while(1)
                {
                    cout << "请输入修改后地址:";
                    *q = *p;
                    cin >> address0;
                    q->address = address0;
                    if ( Judge(q)==1 )
                        break;
                }
                *p=*q;
                cout << "已成功修改信息" << endl;
                break;
            }
            else if( flag == '7' )
            {
                string phone0;
                while(1)
                {
                    cout << "请输入修改后电话:";
                    *q = *p;
                    cin >> phone0;
                    q->phone = phone0;
                    if ( Judge(q)==1 )
                        break;
                }
                *p=*q;
                cout << "已成功修改信息" << endl;
                break;
            }
            else if( flag == '8' )
            {
                int mark0;
                while(1)
                {
                    cout << "请输入修改后六级成绩(0-750):";
                    *q = *p;
                    cin >> mark0;
                    q->mark = mark0;
                    if ( Judge(q)==1 )
                        break;
                }
                *p=*q;
                cout << "已成功修改信息" << endl;
                break;
            }
            else break;
        }
    }
}
void System::Delete()    //删除
{
	string  xuehao;
 	while(1)
	{
		cout<<"请输入您要删除学生信息的学号（退出请输入0）：";
		cin>>xuehao;
        if(xuehao == "0") return;
        q= head;
        while(q->next!=NULL&&q->next->id!=xuehao)
            q=q->next;
        if(q->next==NULL)
            cout<<"未找到 "<<xuehao<<" 的学生信息，请确认后重新输入！"<<endl;
        if(q->next!=NULL)
        {
            p=q->next;
            q->next=p->next;
            delete p;
            cout<<"该学生信息已成功删除！"<<endl;
            break;
        }
	}
}
void System::Sort()    //排序
{
    int flag;    //定义回答
    while(1)
	{
        cout << "亲，你打算如何排序呀? 从大到小排序请输入1，从小到大排序请输入2，退出请输入0：";
        cin >> flag;
        if(flag!=0 && flag!=1 && flag!=2) cout<<"您输入的信息有误，请重新输入。"<<endl;
        else break;
	}
	if(flag!=0) {
    head1=new listnode;
    head1->next=NULL;
    p=head->next;
    while( p != NULL )
    {
        q=new listnode;
        q->id=p->id; q->name=p->name; q->sex=p->sex; q->age=p->age;
        q->address=p->address; q->phone=p->phone; q->mark=p->mark;
        q1=head1;
        while(q1->next != NULL)
        {
            if(flag==1)
            {
                if(q->mark > q1->next->mark) break;
                else q1=q1->next;
            }
            if(flag==2)
            {
                if(q->mark < q1->next->mark) break;
                else q1=q1->next;
            }
        }
        q->next = q1->next;
        q1->next = q;
        p = p->next;
    }
    p=head->next; q=head1->next;
    while(p != NULL)
    {
        p->id=q->id; p->name=q->name; p->sex=q->sex; p->age=q->age;
        p->address=q->address; p->phone=q->phone; p->mark=q->mark;
        p=p->next; q=q->next;
    }
    cout<<"文件信息更改成功！"<<endl;
	}
}
void System::Preserve()  //保存
{
	ofstream f2;
    f2.open("c:\\student.txt",ios::out);
    q = head->next;
    i=1;
    while ( q->next != NULL )
    {
        f2<<i++<<" "<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark<<endl;
        q = q->next;
    }
    f2<<i<<" "<<q->id<<" "<<q->name<<" "<<q->sex<<" "<<q->age<<" "<<q->address<<" "<<q->phone<<" "<<q->mark;
    f2.close();
}
int System::password()   //密码
{
	string ss="123456",st="0";
	string psw;//用于存密码的字符串；
    int length;
    char temp_c;
    cout<<"为保证系统安全，请输入密码（退出请输入0）:";
    while(1)
    {
		temp_c=getch();  //输入一个字符
        if(temp_c!=char(13))  //判断该字符是否为回车，如果是则退出while
        {
			switch  (temp_c)
            {
				case 8:
                if(length!=0)
				{
					cout<<"\b \b";
                    psw=psw.substr(0,length-1);
                    length--;
                }
                else ;
                break;
                default:
                    cout<<"*";
                    psw+=temp_c;//连成字符串；
                    length++;
                    break;
            }
          }
          else break;
    }
    if(psw==ss) return 1;
	else if(psw==st) return 0;
	else return -1;
}


int main()
{
    cout<<"您将要访问北京理工大学学生信息管理系统"<<endl;
	int l=0;
	System s1;
	while(1)
	{
		l=s1.password();
		if(l==1)
		{
			cout<<endl<<"密码正确!"<<endl;
			break;
		}
		else if(l==-1) cout<<endl<<"密码错误，请重新输入!"<<endl;
		else
		{
		    cout<<endl<<"欢迎下次光临！"<<endl;
		    break;
		}
	}
	if(l==0) return 0;
	cout<<"欢迎使用信息管理系统，请回复相应的数字选择您需要的服务："<<endl;
	cout<<"                1.获取学生基本信息                      "<<endl;
	cout<<"                2.查询学生基本信息                      "<<endl;
	cout<<"                3.添加学生基本信息                      "<<endl;
	cout<<"                4.修改学生基本信息                      "<<endl;
	cout<<"                5.删除学生基本信息                      "<<endl;
	cout<<"                6.对学生六级成绩进行排序                "<<endl;
	cout<<"                7.退出本系统                            "<<endl;
	int a;
	while(1)
	{
		cin>>a;
        cout<<"正在处理，请稍候……"<<endl;
		switch(a)
		{
		    case 1:
            s1.Obtain();    //获取
            cout<<"请继续选择您需要的服务："<<endl;
            break;
            case 2:
            s1.Query();     //查询
            cout<<"请继续选择您需要的服务："<<endl;
            break;
            case 3:
            s1.Add();       //添加
            cout<<"请继续选择您需要的服务："<<endl;
            break;
            case 4:
            s1.Modify();    //修改
            cout<<"请继续选择您需要的服务："<<endl;
            break;
            case 5:
            s1.Delete();    //删除
            cout<<"请继续选择您需要的服务："<<endl;
            break;
            case 6:
            s1.Sort();    //排序
            cout<<"请继续选择您需要的服务："<<endl;
            break;
            case 7:
            s1.Preserve();    //保存
            cout<<"文件已成功保存，欢迎下次光临！"<<endl;
            return 0;
            default:cout<<"对不起，您输入的信息有误，请重新输入："<<endl;
		}
	}
}
