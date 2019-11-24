24点游戏：

一、题目说明
24点游戏是经典的纸牌益智游戏。
常见游戏规则：
从扑克中每次取出4张牌。使用加减乘除，第一个能得出24者为赢。（其中，J代表11，Q代表12，K代表13，A代表1），按照要求编程解决24点游戏。
基本要求： 随机生成4个代表扑克牌牌面的数字字母，程序自动列出所有可能算出24的表达式，用擅长的语言（C/C++/Java或其他均可）实现程序解决问题。
1.程序风格良好(使用自定义注释模板)
2.列出表达式无重复。
二、算法设计思路
此次作业可以自己设置4个数字保存在input.txt文件中，然后在期间添加运算符和括号，计算结果是否等于24。其中加了括号涉及一个优先级的问题，即确定对哪4个数进行运算。
我们首先要确定相邻的两个数的计算，计算完成后，就剩下了3个数字，然后再决定剩下的这3个数中相邻的两个数进行计算。括号的优先级高于加减乘除。在循环过程中，我们可以依次进行三次计算，然后得到结果，判断结果是否为24。
三、源程序
#include<iostream>
#include<fstream>
#include<cmath> 
using namespace std;
char oper[4]={'+','-','*','/'};
class Game	//24点游戏 
{
	private:
	double a[4];	//可以精确计算 
	public:
	Game();	//构造函数 
	double calcute(double,double,char);	//计算函数 
	void search();	//搜索函数，找到合适解 
	void print();	//打印4张牌数值 
};
Game::Game()
{
	char ch[4];
	ifstream infile("input.txt");
	if(!infile)
	{
		cout<<"打开文件input.txt失败"<<endl;
		exit(1); 
	}
	for(int i=0;i<4;i++)
		infile>>ch[i];
	cout<<"*********************************"<<endl;
	cout<<"****正在从input.txt中读取数据****"<<endl;
	for(int i=0;i<4;i++)
	{
		if(ch[i]=='A') a[i]=1;
		else if(ch[i]=='2') a[i]=2;
		else if(ch[i]=='3') a[i]=3;
		else if(ch[i]=='4') a[i]=4;
		else if(ch[i]=='5') a[i]=5;
		else if(ch[i]=='6') a[i]=6;
		else if(ch[i]=='7') a[i]=7;
		else if(ch[i]=='8') a[i]=8;
		else if(ch[i]=='9') a[i]=9;
		else if(ch[i]=='10') a[i]=10;
		else if(ch[i]=='J') a[i]=11;
		else if(ch[i]=='Q') a[i]=12;
		else if(ch[i]=='K') a[i]=13;
		else
		{
			cout<<"第"<<i+1<<"个数据输入有误"<<endl;
			exit(1); 
		}
	 } 
	 infile.close();
}
double Game::calcute(double a,double b,char index)
{
	if(index=='+') return a+b;	//若为+，则返回相应结果 
	else if(index='-') return a-b;	
	else if(index='*') return a*b;
	else if(index='/') if(b!=0) return a/b;	//只有当分母为0时，返回结果 
}
void Game::search()
{
	double temp[3],tem[2];	//第一个符号放置后，经过计算后相当于剩下三个数，这个数组用于存储这三个数 
	double sum;
	int judge=0;
	ofstream outfile("output.txt",ios::app);
	if(!outfile)
	{
		cout<<"打开文件output.txt失败"<<endl;
		exit(1); 
	}
	cout<<"*********************************"<<endl;
	cout<<"正在计算结果"<<endl;
	outfile<<"================="<<endl;
	outfile<<"本次24点游戏结果如下："<<endl;
	for(int i=0;i<4;i++)  //第一次放置的符号 
	{
		for(int j=0;j<4;j++)  //第二次放置的符号 
		{
			for(int k=0;k<4;k++)  //第三次放置的符号 
			{
				for(int m=0;m<3;m++)	//首先计算两个相邻数字有三种情况，相当于括号的作用 
				{
					if(a[m+1]==0&&oper[i]=='/') break;
					temp[m]=calcute(a[m],a[m+1],oper[i]);
					temp[(m+1)%3]=a[(m+2)%4];
					temp[(m+2)%3]=a[(m+3)%4];
					for(int n=0;n<2;n++)	//三个数中选出先计算的相邻的两个数，两种情况，相当于第二个括号 
					{
					if(temp[n+1]==0&&oper[i]=='/') break;
					tem[n]=calcute(temp[n],temp[n=1],oper[j]);
					temp[(n+1)%2]=temp[(n+2)%3]; 
					if(tem[1]==0&&oper[k]=='/') break;
					sum=calcute(tem[0],tem[1],oper[k]);
					if(sum==24)
					{
						judge=1;	//已求得解 
						if(m==0&&n==0)
						outfile<<"(("<<a[0]<<oper[i]<<a[1]<<")"<<oper[j]<<a[2]<<")"<<oper[k]<<a[3]<<"="<<sum<<endl;
						else if(m==0&&n==1)
						outfile<<"("<<a[0]<<oper[i]<<a[1]<<")"<<oper[k]<<"("<<a[2]<<oper[j]<<a[3]<<")="<<sum<<endl;
						else if(m==1&&n==0)
						outfile<<"("<<a[0]<<oper[j]<<"("<<a[1]<<oper[i]<<a[2]<<")"<<oper[k]<<a[3]<<"="<<sum<<endl;
						else if(m==1&&n==1)
						outfile<<a[0]<<oper[k]<<"(("<<a[1]<<oper[i]<<a[2]<<")"<<oper[j]<<a[3]<<")="<<sum<<endl;
						else if(m==2&&n==0)
						outfile<<"("<<a[0]<<oper[j]<<a[1]<<")"<<oper[k]<<"("<<a[2]<<oper[i]<<a[3]<<")="<<sum<<endl;
						else if(m==2&&n==0)
						outfile<<a[0]<<oper[k]<<"("<<a[1]<<oper[j]<<"("<<a[2]<<")"<<oper[i]<<a[3]<<"))="<<sum<<endl;
					}
				}
			}
		}
	 } 
}
	 if(judge==0) outfile<<"这四张扑克牌无解"<<endl;
	 outfile.close();
	 cout<<"计算完成，结果已保存在output.txt文件中"<<endl; 
}
void Game::print()
{
	cout<<"读取成功"<<endl;
	for(int i=0;i<4;i++)
	{
		cout<<"第"<<i+1<<"张牌"<<a[i]<<endl; 
	 } 
}
int main(void)
{
	Game obj;
	obj.print();
	cout<<endl;
	obj.search();
	cout<<endl;
	system("pause");
	return 0；
}
四、总结
实现本次24点游戏的过程中，要结合现实情况中的13张扑克牌式样，还要求能算出24的表达式，运算符有+，-，*，/，
若有解则输出正确解，如果无解则输出相应信息。
此次使用input.txt来保存信息，然后在程序运行后在output.txt中输出结果，可以查漏补缺。
在编码过程中，要结合多方面知识与考虑，在处理符号与优先级问题方面经过了很长时间的思考，
先提一个符号与两个数计算，再依次计算下面的3位数，这种想法比较巧妙。程序看起来繁琐，不简洁，这也是以后所需要优化的地方。

