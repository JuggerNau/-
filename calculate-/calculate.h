#include <cmath>
#include <string.h>
const double e=2.718281828459;
int errnum=0;
char *line;
double outresult=0;
char fuhao[17] = {'\n', ')', '+', '-', '*', '/', '%', '^','Q',/*开方*/ 'C',/*cos*/ 'S', /*sin*/'T', /*tan*/'c', /*acos*/'s', /*asin*/'t', /*atan*/'('};
class node//为了处理符号而建立的类(如: 1+(-2))
{
    public:
	char data;
	node *next;
};

class num//存储 数 的栈
{
    public:
	double *top;
	double *base;
};

class ope//存储 运算符号 的栈
{
    public:
	char *top;
	char *base;
};
class calculator: public node, public num, public ope
{
    private:
    num num1;//定义
    ope ope1;
    int compare[1000];                       //处理各运算符号的优先级
    double shu[1000];                        //存储 "数" 的数组
    //char line[1000];
    //char fuhao[17];

    public:
    void set();//初始化
    void push_num(double n);//数字进栈
    void push_ope(char c);//运算符号进栈
    double pop_num();//数字出栈
    char pop_ope();//运算符号出栈
    char get_top_ope();//得到运算符号的栈中最顶端的运算符号
    double operate(double y, char c, double x);//对两个数计算(含是双目运算符:如 *, / 等等)
    double operate_one(double one, char cc);//对一个数运算(含单目运算符:如log(L), sin(S) 等等)
    double compute();//对整个表达式的计算
    int checkbracket();//检查表达式括号是否匹配
    int checkope();//检查运算符号是否合法(如: 1 +* 4)
    void output(double result);//打出结果
    void check();//检查表达式是否合法
    void chulifuhao();//处理负号
    void input();//输入
};

void calculator::set()                               //输入函数（初始化）
{
	compare[fuhao[0]] = -2;                 //用数字的大小表现出符号的优先级
	compare[fuhao[1]] = -1;
	compare[fuhao[2]] = 2;
	compare[fuhao[3]] = 2;
	compare[fuhao[4]] = 4;
	compare[fuhao[5]] = 4;
	compare[fuhao[6]] = 4;
	compare[fuhao[7]] = 5;
	for(int i = 8; i <= 14; i++)
		compare[fuhao[i]] = 6;
	compare[fuhao[15]] = 7;

	num1.base = new double[1000];       //为栈开辟空间
	ope1.base = new char[1000];           //同上
	num1.top = num1.base;
	ope1.top = ope1.base;
}
void calculator::push_num(double n)                                     //数字进栈
{
	* ++num1.top = n;
}

void calculator::push_ope(char c)                                      //运算符号进栈
{
	* ++ope1.top = c;
}
double calculator::pop_num()                                           //数字出栈
{
	double m = *num1.top;
	num1.top--;
	return m;
}

char calculator::pop_ope()                                            //运算符号出栈
{
	char cc = *ope1.top;
	ope1.top--;
	return cc;
}

char calculator::get_top_ope()                                       //得到运算符号的栈中最顶端的运算符号
{
	return *ope1.top;
}
double calculator::operate(double y, char c, double x)               //对两个数计算(含是双目运算符:如 *, / 等等)
{
	double r;
	if(c == '-')
		r = x - y;
	else if(c == '+')
		r = x + y;
	else if(c == '/' && y != 0)
		r = x / y;
	else if(c == '*')
		r = x * y;
	else if(c == '^')
	{
		r = 1;
		for(int i = 1; i <= y; i++)
			r *= x;
	}
	else if(c == '%')
	{
		int r0 = (int)x % (int)y;
		r = double(r0);
	}
	return r;
}

double calculator::operate_one(double one, char cc)                //对一个数运算(含单目运算符:如log(L), sin(S) 等等)
{
	double r;
	if(cc == 'Q')
		r = sqrt(one);
	else if(cc == 'C')
		r = cos(one);
	else if(cc == 'S')
		r = sin(one);
	else if(cc == 'T')
		r = tan(one);
	else if(cc == 'c')
		r = acos(one);
	else if(cc == 's')
		r = asin(one);
	else if(cc == 't')
		r = atan(one);

	return r;
}
double calculator::compute()                                        //对整个表达式的计算
{
	char c;                                             //表示运算符号
	int p = 0;                                          //用于shu[++p], 先初始化
	int i, j;

	set();                                              //读取算式（进行初始化）

	push_ope('\n');
	line[strlen(line)] = '\n';
	line[strlen(line)+1] = '\0';
	for(i = 0; line[i] != '\0';)                        //把表达式中的数字字符串转化成可计算的数字
	{
		int flag = 0;
		int flag1 = 1;                                  //标记是否是运算符号
		double h = 0;
		int ge;                                         //位数
		int biao_dian = 0;                              //判断是否是小数的类型，再进行转化

		while(1)
		{
			flag1 = 1;
			for(j = 0; j <= 16; j++)
			{
				if(line[i] == fuhao[j])
				{
					flag1 = 0;
					break;
				}
			}
			if(line[i] == '.')
			{
				i++;
				ge = 0;
				biao_dian = 1;
			}
			if(flag1)
			{
				h = h * 10 + (line[i] - '0');
				flag = 1;
				i++;
				if(biao_dian)
					ge++;
			}
			else
				break;
		}
		if(flag)
		{
			if(biao_dian)
			{
				int r = 1;
				int k;
				for(k = 1; k <= ge; k++)
					r *= 10;
				h /= r;
			}
			shu[++p] = h;                                              //把转化而来的数字存于数组
		}
		if(line[i] == '+')
			shu[++p] = -1;
		else if(line[i] == '-')
			shu[++p] = -2;
		else if(line[i] == '*')
			shu[++p] = -3;
		else if(line[i] == '/')
			shu[++p] = -4;
		else if(line[i] == '%')
			shu[++p] = -5;
		else if(line[i] == '^')
			shu[++p] = -6;
		else if(line[i] == 'Q')
			shu[++p] = -7;
		else if(line[i] == 'C')
			shu[++p] = -9;
		else if(line[i] == 'S')
			shu[++p] = -10;
		else if(line[i] == 'T')
			shu[++p] = -11;
		else if(line[i] == 'c')
			shu[++p] = -12;
		else if(line[i] == 's')
			shu[++p] = -13;
		else if(line[i] == 't')
			shu[++p] = -14;
		else if(line[i] == '(')
			shu[++p] = -15;
		else if(line[i] == ')')
			shu[++p] = -16;
		else if(line[i] == '\n')
			shu[++p] = -17;
		i++;
	}
	i = 1;

	while(shu[i] != -17 || get_top_ope() != '\n')
	{
		double m = shu[i];

		if(m >= 0)
		{
			push_num(m);
			i++;
		}
		else
		{
			if(m == -1)
				c = '+';
			else if(m == -2)
				c = '-';
			else if(m == -3)
				c = '*';
			else if(m == -4)
				c = '/';
			else if(m == -5)
				c = '%';
			else if(m == -6)
				c = '^';
			else if(m == -7)
				c = 'Q';
			else if(m == -8)
				c = 'L';
			else if(m == -9)
				c = 'C';
			else if(m == -10)
				c = 'S';
			else if(m == -11)
				c = 'T';
			else if(m == -12)
				c = 'c';
			else if(m == -13)
				c = 's';
			else if(m == -14)
				c = 't';
			else if(m == -15)
				c = '(';
			else if(m == -16)
				c = ')';
			else if(m == -17)
				c = '\n';
			char ch = get_top_ope();                                //得到最顶端运算符号
			if(compare[ch] < compare[c])                            //判断运算优先级（运算符号级别的比较）
			{
				push_ope(c);
				i++;
			}
			else if(ch == '(' && c == ')')
			{
				pop_ope();
				i++;
			}
			else if(compare[ch] >= compare[c] && ch != '(' && ch != '\n')
			{
				if(ch == 'Q' || ch == 'C' || ch == 'S'|| ch == 'T'
					|| ch == 'c' || ch == 's' || ch == 't')
				{
					double one = pop_num();
					char dian = pop_ope();
					push_num(operate_one(one, dian));
				}
				else
				{
					double x = pop_num();
					double y = pop_num();
					char dian = pop_ope();
					if(dian == '/' && x == 0)                            //判断是否除了"零"
					{
						//cout<<"不能除以0，计算错误，请退出重新输入"<<endl;
						errnum=1;
						return -88888;
					}
					push_num(operate(x, dian, y));                       //把进行一次计算的结果入栈
				}
			}
			else
			{
				push_ope(c);
				i++;
			}
		}
	}
	double result = pop_num();                                           //得到结果

	return result;
}
int calculator::checkbracket()                                                             //检查表达式括号是否匹配
{
	int i, f = 0;
	int kuo[1000], key = 1;

	memset(kuo, 0, sizeof(kuo));
	for(i = 0; line[i] != '\0'; i++)
	{
		if(line[i] == '(')
			kuo[++f] = 1;
		else if(line[i] == ')')
		{
			if(kuo[f] == 1)
			{
				kuo[f] = 0;
				f--;
			}
			else
			{
				key = 0;
				break;
			}
		}
	}
	if(key && f == 0)
		return 1;
	else
		return 0;
}

int calculator::checkope()                                                              //检查运算符号是否合法(如: 1 +* 4)
{
	int i, ge;
	for(i = 0; line[i] != '\0'; )
	{
		ge = 0;
		while(line[i] == '+' || line[i] == '-' || line[i] == '*'
			|| line[i] == '/' || line[i] == '%' || line[i] == '^'
			|| line[i] == 'Q' || line[i] == 'S'
			|| line[i] == 'C' || line[i] == 'T' || line[i] == 's'
			|| line[i] == 'c' || line[i] == 't')
		{
			ge++;
			i++;
		}
		i++;
	}
	if(ge >= 2)
		return 0;
	else
		return 1;
}

void calculator::check()                                                                    //检查表达式是否合法
{
	if( checkbracket() && checkope() )                                         //看是否合法, 合法则计算
	{
		outresult = compute();
		return;
	}
	else                                                                       //不合法，分两种不合法
	{
		if(checkbracket() == 0 && checkope() == 1)
		{
		    errnum=2;
			return;
		}
		else
		{
		    errnum=3;
			return;
		}
	}
}
void calculator::chulifuhao()                                                            //处理负号
{
	node *root, *head, *p, *q, *p1;
	root = head = new node;
	head->next = NULL;
	int i;
	for(i = 0; line[i] != '\0'; i++)                                         //建立链表
	{
		p = new node;
		p->data = line[i];
		p->next = head->next;
		head->next = p;
		head = p;
	}
	q = new node;
	head = root;
	if(root->next->data == '+' || root->next->data == '-')//处理第一个字符
	{
		p = new node;
		p->data = '0';
		p->next = head->next;
		head->next = p;
	}
	if(root->next != NULL)
	{
		for(q = root->next; q; q = q->next)
		{
			if(q->data == '(' && (q->next->data == '-' || q->next->data == '+'))
			{
				p = new node;
				p->data = '0';
				p->next = q->next;
				q->next = p;
			}
		}
	}
	p1 = new node;
	int qi = -1;
	for(p1 = root->next; p1; p1 = p1->next)
	{
		line[++qi] = p1->data;
	}
	line[++qi] = '\0';
}
