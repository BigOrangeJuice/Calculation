#include<bits/stdc++.h>
using namespace std;

#define maxsize 100
#define OK 1
#define ERROR 0
typedef double ElemType;
typedef int Status;

//顺序栈存储定义
typedef struct SqStack {
	ElemType *base;
	int stacksize;
} SqStack;

//链栈存储定义
typedef struct Node {
	ElemType data;
	struct Node *next;
} Node,*LinkStackPtr;
typedef struct LinkStack {
	LinkStackPtr top;
	int count;
} LinkStack;

//顺序栈的相关定义
Status Init_SqStack(SqStack &S);//初始化
bool IsEmpty_SqStack(SqStack &S);//判断空
bool IsFull_SqStack(SqStack &S);//判断满
int Length_SqStack(SqStack &S);//返回长度
Status Push_SqStack(SqStack &S,ElemType data);//入栈
ElemType Pop_SqStack(SqStack &S);//出栈并返回元素
ElemType GetHead_SqStack(SqStack &S);//获取栈顶元素
Status Clear_SqStack(SqStack &S);//清空
Status Traverse_SqStack(SqStack &S);//遍历

//链栈的相关定义
Status Init_LinkStack(LinkStack &S);//初始化
bool IsEmpty_LinkStack(LinkStack &S);//判断空
int Length_LinkStack(LinkStack &S);//返回长度
Status Push_LinkStack(LinkStack &S,ElemType data);//入栈
ElemType Pop_LinkStack(LinkStack &S);//出栈并返回元素
ElemType GetHead_LinkStack(LinkStack &S);//获取栈顶元素
Status Clear_LinkStack(LinkStack &S);//清空
Status Traverse_LinkStack(LinkStack &S);//遍历

//四则运算相关函数
ElemType Calculation_SqStack(SqStack &S,char postfix[]);//计算表达式
bool Infix2Postfix_SqStack(SqStack &S,char infix[],int num,char postfix[]);//中缀表达式转后缀表达式
ElemType Calculation_LinkStack(LinkStack &S,char postfix[]);
bool Infix2Postfix_LinkStack(LinkStack &S,char infix[],int num,char postfix[]);

//大数运算相关函数【用链栈实现】
Status BigData_addtion();//大数加法
Status BigData_minus();//大数减法

//进制转换相关函数【用顺序栈实现】
Status Exchange_10to2();//十进制与二进制之间的转换
Status Exchange_10to8();//十进制与八进制之间的转换
Status Exchange_10to16();//十进制与十六进制之间的转换
Status Exchange_2to10();//二进制与十进制之间的转换
Status Exchange_2to8();//二进制与八进制之间的转换
Status Exchange_2to16();//二进制与十六进制之间的转换
Status Exchange_8to10();//八进制与十进制之间的转换
Status Exchange_8to2();//八进制与二进制之间的转换
Status Exchange_8to16();//八进制与十六进制之间的转换
Status Exchange_16to10();//十六进制与十进制之间的转换
Status Exchange_16to8();//十六进制与八进制之间的转换
Status Exchange_16to2();//十六进制与二进制之间的转换

//实现字符串的部分拷贝
void strmncpy(char *s, int m, int n, char *t);//实现字符数组的部分拷贝
bool check(char ch1, char ch2);//进行操作符优先级的判断

//操作函数
void operation();

//顺序栈的函数实现
Status Init_SqStack(SqStack &S) {
	S.base = (ElemType*)malloc(sizeof(ElemType)*maxsize);
	S.stacksize = 0;
	return OK;
}

bool IsEmpty_SqStack(SqStack &S) {
	return S.stacksize == 0;
}

bool IsFull_SqStack(SqStack &S) {
	return S.stacksize == maxsize;
}

int Length_SqStack(SqStack &S) {
	return S.stacksize;
}

Status Push_SqStack(SqStack &S,ElemType data) {
	if(IsFull_SqStack(S)) {
		cout<<"栈已满，勿再添加内容！"<<endl;
		return ERROR;
	}
	S.base[S.stacksize++] = data;
	return OK;
}

ElemType Pop_SqStack(SqStack &S) {
	if(IsEmpty_SqStack(S)) {
		cout<<"栈为空，无可赠与！"<<endl;
		return -1;
	}
	return S.base[--S.stacksize];
}

ElemType GetHead_SqStack(SqStack &S) {
	if(IsEmpty_SqStack(S)) {
		//cout<<"空"<<endl;
		return -1;
	}
	return S.base[S.stacksize-1];
}

Status Clear_SqStack(SqStack &S) {
	S.stacksize = 0;
	if(S.stacksize==0)	return OK;
	else	return ERROR;
}

Status Traverse_SqStack(SqStack &S) {
	if(IsEmpty_SqStack(S)) {
		cout<<"栈为空，无可遍历！"<<endl;
		return ERROR;
	}
	for(int i=S.stacksize-1; i>=0; --i) {
		cout<<S.base[i]<<endl;
	}
	return OK;
}

bool Infix2Postfix_SqStack(SqStack &S,char infix[],int num,char postfix[]) {
	int i=0;
	int len=num;
	cout<<"表达式长度："<<len<<endl;
	cout<<"对应的后缀表达式：";
	for(int j=0; j<len; ++j) {
		while((infix[j]>='0'&&infix[j]<='9')||infix[j]=='.') { //如果是操作数，直接输出 【并且如果是多位数，则一直判断】
			//cout<<"here1"<<endl;
			postfix[i++]=infix[j];
			cout<<infix[j];
			j++;
			if((infix[j]<'0'||infix[j]>'9')&&infix[j]!='.') {
				postfix[i++]=' ';
				cout<<' ';
			}
		}
		if(infix[j]=='('||IsEmpty_SqStack(S)) { //如果是(或是栈空，先入栈
			//cout<<"here2"<<endl;
			Push_SqStack(S,infix[j]);
		} else if(infix[j]==')') { //如果是)，进行出栈，直到栈顶是(，然后把(踢出去
			//cout<<"here3"<<endl;
			while(GetHead_SqStack(S)!='(') {
				postfix[i]=Pop_SqStack(S);
				cout<<postfix[i]<<' ';
				i++;
				postfix[i++]=' ';
			}
			Pop_SqStack(S);
		} else if(GetHead_SqStack(S)=='('||check(GetHead_SqStack(S),infix[j])) { //如果是操作符，检测优先级，如果高于栈顶则存入
			//cout<<"here4"<<endl;
			Push_SqStack(S,infix[j]);
		} else { //如果优先级低于栈顶操作符，则出栈，直到本操作符大于栈顶操作符的优先级
			while(!(check(GetHead_SqStack(S),infix[j])||IsEmpty_SqStack(S)||GetHead_SqStack(S)=='(')) {
				//cout<<"here5"<<endl;
				postfix[i]=Pop_SqStack(S);
				cout<<postfix[i]<<' ';
				i++;
				postfix[i++]=' ';
			}
			Push_SqStack(S,infix[j]);
		}
	}
	while(!IsEmpty_SqStack(S)) {
		//cout<<"here6"<<endl;
		postfix[i]=Pop_SqStack(S);
		cout<<postfix[i]<<' ';
		i++;
		postfix[i++]=' ';
	}
	postfix[i]='\0';
}

ElemType Calculation_SqStack(SqStack &S,char postfix[]) {
	ElemType a=0,b=0;
	for(int i=0; postfix[i]!='\0'; ++i) {
		int count=i;
		while((postfix[count]>='0'&&postfix[count]<='9')||postfix[count]=='.') { //如果是数字或小数点，连续判断得出位数，将其转化入栈
			count++;
			if((postfix[count]<'0'||postfix[count]>'9')&&postfix[count]!='.') { //判断下一位是否仍未数字类型，是则不进行，否则进行数字入栈
				char temp[10];
				strmncpy(postfix,i,count-i,temp);
				Push_SqStack(S,atof(temp));
				i=count-1;
			}
		}
		switch(postfix[i]) {
			case '+':
				b=Pop_SqStack(S);
				a=Pop_SqStack(S);
				Push_SqStack(S,a+b);
				//cout<<a+b<<endl;
				break;
			case '-':
				b=Pop_SqStack(S);
				a=Pop_SqStack(S);
				Push_SqStack(S,a-b);
				//cout<<a-b<<endl;
				break;
			case '*':
				b=Pop_SqStack(S);
				a=Pop_SqStack(S);
				Push_SqStack(S,a*b);
				//cout<<a*b<<endl;
				break;
			case '/':
				b=Pop_SqStack(S);
				a=Pop_SqStack(S);
				Push_SqStack(S,a/b);
				//cout<<a/b<<endl;
				break;
			default:
				break;
		}
	}
	a=Pop_SqStack(S);
	return a;
}

//链栈的函数实现
Status Init_LinkStack(LinkStack &S) {
	S.top=(LinkStackPtr)malloc(sizeof(Node));
	S.top=NULL;
	S.count=0;
	return OK;
}

bool IsEmpty_LinkStack(LinkStack &S) {
	if(S.count==0)	return true;
	else	return false;
}

int Length_LinkStack(LinkStack &S) {
	return S.count;
}

Status Push_LinkStack(LinkStack &S,ElemType data) {
	Node *temp=(Node*)malloc(sizeof(Node));
	temp->data=data;
	temp->next=S.top;
	S.top=temp;
	S.count++;
	return OK;
}

ElemType Pop_LinkStack(LinkStack &S) {
	if(IsEmpty_LinkStack(S))	return -1;
	else {
		Node *p=(Node*)malloc(sizeof(Node));
		p=S.top;
		S.top=S.top->next;
		ElemType e=p->data;
		free(p);
		S.count--;
		return e;
	}
}

ElemType GetHead_LinkStack(LinkStack &S) {
	if(IsEmpty_LinkStack(S))	return -1;
	return S.top->data;
}

Status Clear_LinkStack(LinkStack &S) {
	Node *p,*q;
	p=S.top;
	while(p) { //释放结点
		q=p;
		p=p->next;
		free(q);
	}
	S.count=0;
	return OK;
}

Status Traverse_LinkStack(LinkStack &S) {
	Node *p=S.top;
	while(p) {
		cout<<p->data<<endl;
		p=p->next;
	}
	return OK;
}

bool Infix2Postfix_LinkStack(LinkStack &S,char infix[],int num,char postfix[]) {
	int i=0;
	int len=num;
	cout<<"表达式长度："<<len<<endl;
	cout<<"对应的后缀表达式：";
	for(int j=0; j<len; ++j) {
		while((infix[j]>='0'&&infix[j]<='9')||infix[j]=='.') { //如果是操作数，直接输出 【并且如果是多位数，则一直判断】
			//cout<<"here1"<<endl;
			postfix[i++]=infix[j];
			cout<<infix[j];
			j++;
			if((infix[j]<'0'||infix[j]>'9')&&infix[j]!='.') {
				postfix[i++]=' ';
				cout<<' ';
			}
		}
		if(infix[j]=='('||IsEmpty_LinkStack(S)) { //如果是(或是栈空，先入栈
			//cout<<"here2"<<endl;
			Push_LinkStack(S,infix[j]);
		} else if(infix[j]==')') { //如果是)，进行出栈，直到栈顶是(，然后把(踢出去
			//cout<<"here3"<<endl;
			while(GetHead_LinkStack(S)!='(') {
				postfix[i]=Pop_LinkStack(S);
				cout<<postfix[i]<<' ';
				i++;
				postfix[i++]=' ';
			}
			Pop_LinkStack(S);
		} else if(GetHead_LinkStack(S)=='('||check(GetHead_LinkStack(S),infix[j])) { //如果是操作符，检测优先级，如果高于栈顶则存入
			//cout<<"here4"<<endl;
			Push_LinkStack(S,infix[j]);
		} else { //如果优先级低于栈顶操作符，则出栈，直到本操作符大于栈顶操作符的优先级
			while(!(check(GetHead_LinkStack(S),infix[j])||IsEmpty_LinkStack(S)||GetHead_LinkStack(S)=='(')) {
				//cout<<"here5"<<endl;
				postfix[i]=Pop_LinkStack(S);
				cout<<postfix[i]<<' ';
				i++;
				postfix[i++]=' ';
			}
			Push_LinkStack(S,infix[j]);
		}
	}
	while(!IsEmpty_LinkStack(S)) {
		//cout<<"here6"<<endl;
		postfix[i]=Pop_LinkStack(S);
		cout<<postfix[i]<<' ';
		i++;
		postfix[i++]=' ';
	}
	postfix[i]='\0';
}

ElemType Calculation_LinkStack(LinkStack &S,char postfix[]) {
	ElemType a=0,b=0;
	for(int i=0; postfix[i]!='\0'; ++i) {
		int count=i;
		while((postfix[count]>='0'&&postfix[count]<='9')||postfix[count]=='.') { //如果是数字或小数点，连续判断得出位数，将其转化入栈
			count++;
			if((postfix[count]<'0'||postfix[count]>'9')&&postfix[count]!='.') { //判断下一位是否仍未数字类型，是则不进行，否则进行数字入栈
				char temp[10];
				strmncpy(postfix,i,count-i,temp);
				Push_LinkStack(S,atof(temp));
				i=count-1;
			}
		}
		switch(postfix[i]) {
			case '+':
				b=Pop_LinkStack(S);
				a=Pop_LinkStack(S);
				Push_LinkStack(S,a+b);
				//cout<<a+b<<endl;
				break;
			case '-':
				b=Pop_LinkStack(S);
				a=Pop_LinkStack(S);
				Push_LinkStack(S,a-b);
				//cout<<a-b<<endl;
				break;
			case '*':
				b=Pop_LinkStack(S);
				a=Pop_LinkStack(S);
				Push_LinkStack(S,a*b);
				//cout<<a*b<<endl;
				break;
			case '/':
				b=Pop_LinkStack(S);
				a=Pop_LinkStack(S);
				Push_LinkStack(S,a/b);
				//cout<<a/b<<endl;
				break;
			default:
				break;
		}
	}
	a=Pop_LinkStack(S);
	return a;
}

//四则运算公用函数
void strmncpy(char *s, int m, int n, char *t) {
	int k=0;
	while(s[k]!=0) {
		k++;
	}
	if(k<=m) {
		*t='\0';
		return;
	}
	char *p=s+m;
	for(int i=0; i<n; i++) {
		*t=*p;
		if(*t=='\0') {
			return;
		}
		t++;
		p++;
	}
	*t='\0';
}

bool check(char ch1, char ch2) { // 只有ch1的优先级小于ch2的优先级时返回true
	if((ch1 == '+' || ch1 == '-') && (ch2 == '*' || ch2 == '/')) {
		return true;
	}
	return false;
}

void ShowMenu() {
	cout<<"===============欢迎来到我的计算器=============="<<endl;
	cout<<"================选择你想要的功能==============="<<endl;
	cout<<"==============================================="<<endl;
	cout<<"*******\t\t1-简单四则计算\t\t*******"<<endl;
	cout<<"*******\t\t2-大数计算\t\t*******"<<endl;
	cout<<"*******\t\t3-进制转换\t\t*******"<<endl;
	cout<<"*******\t\t0-退出\t\t\t*******"<<endl;
	cout<<"==============================================="<<endl;
	cout<<"==============================================="<<endl;
}

void operation() {
	while(true) {
		ShowMenu();
		int choice;
		int select;
		cout<<"输入对应数字：";
		cin>>choice;
		if(choice==1) {
			while(true) {
				cout<<"选择您想要实现的结构："<<endl;
				cout<<" 1-顺序栈 || 2-链栈 "<<endl;
				cin>>select;
				char infix[100]= {0};
				char postfix[100]= {0};//创建中缀表达式数组与后缀表达式数组
				if(select==2) {
					LinkStack S;
					Init_LinkStack(S);//创建出一个栈，以备后用
					cout<<"输入您想要的计算表达式：(计算结果自动保留三位小数)";
					getchar();
					gets(infix);//获取中缀表达式
					Infix2Postfix_LinkStack(S,infix,strlen(infix),postfix);//中后缀转换
					cout<<fixed<<setprecision(3)<<"\n结果："<<Calculation_LinkStack(S,postfix);//计算并输出结果，保留三位小数
					system("pause");
					system("cls");
					break;
				} else if(select==1) {
					LinkStack S;
					Init_LinkStack(S);//创建出一个栈，以备后用
					cout<<"输入您想要的计算表达式：(计算结果自动保留三位小数)"<<endl;
					getchar();
					gets(infix);//获取中缀表达式
					Infix2Postfix_LinkStack(S,infix,strlen(infix),postfix);//中后缀转换
					cout<<fixed<<setprecision(3)<<"\n结果："<<Calculation_LinkStack(S,postfix)<<endl;//计算并输出结果，保留三位小数
					system("pause");
					system("cls");
					break;
				} else {
					cout<<"输入有误！请重新输入！"<<endl;
				}
			}
		}
		else if(choice==2){
			system("pause");
			system("cls");
		}
		else if(choice==3){
			system("pause");
			system("cls");
		}
		else if(choice==0){
			cout<<"感谢使用！欢迎再来！"<<endl;
			return ;
		}
		else{
			cout<<"输入有误！请重新输入！"<<endl;
			system("pause");
			system("cls"); 
		}
	}
}

int main() {
	operation();//进行操作
	return 0 ;
}

//四则运算测试数据
// (4+5)/3-2+5*4+2	——23
// (8+4)*6+5/1/5*2-4/2+6+2-1	—— 79
// 100/5+3*(2+5/4)/2+0-5*1+14	—— 33.875
// 4.08/3*1.3/5.78+2*3.41-1.66+7/5	—— 6.866
