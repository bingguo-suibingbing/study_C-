#define _CRT_SECURE_NO_WARNINGS
#include<iostream>//C++中标准输出输入库    采用流
#include<cstdio>//C++中stdio.h的包装版本
#include<conio.h>//包含getch() putch()
#include<Windows.h>
//#include<string.h>纯c风格
#include<queue>//队列数据结构
#include<algorithm>//算法数据结构
#include<memory.h>
#include<math.h>//数学库
#include<string>//C++中string标准库
#include<cstring>//C++中string.h的包装版本
#include<iomanip>//格式化控制工具
#define NOMINMAX
using namespace std;
void chapter(const char a[]) {
	printf("\n");
	for (int i = 0;i < 10;++i) {
		printf("--");
	}
	printf(a);
	printf("\n");
	
}
//<iostream>流
//istream
//ostream
//iostream
//ifstream
//ofstream
//fstream
//isringstream string输入流
//ostringstream string输出流
//stringstream string双向流

//对于windows系统不怎么在意行缓存  而Linux很强调一行结束才刷新缓存区



//链表
struct ListNode {
	int val;
	ListNode* next;

	ListNode(int x = 0) : val(x), next(nullptr) {}
};



//二叉树
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int x = 0) : val(x), left(nullptr), right(nullptr) {}
};




int add(int a,int b) {


	return a + b;
}
//满足以下规则
//1只能是字母的大小写和数字，下划线
//2第一个字母不能是数字




//所有的关键词有
//auto char default else for inline
//return static union while _Bool _Complex
//restrict enum goto int short struct
//unsigned break const do extern if
//long signed switch void case continue
//double float _Imaginary register sizeof typedef volatile


int main() {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	

	//string a = "okay";
	//char m[] = "okay";
	chapter("其他函数");


	//包含在memory.h中
	//memory(目标地址,数据来源地址,赋值大小)
	//可用于给数组赋值 注意检查 空
	{
		int a[2] = { 1,1 };
		int b[2] = { 2,2 };
		memcpy(a,b,sizeof(a));
		cout <<"->" << a[0];
	}

	




	//初始化操作
	int a[10] = {  };//数组a中都将填0
	int _a[10];//未初始化数组_a



	//赋值与初始化的差异
	int a_a[2] = { 1,2 };//列表只能用于初始化
	//a_a = { 3,4 };


	
	//用于编码处理
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	chapter("输入输出函数");

	//printf是控制台打印函数，第一个参数是字符串(c语言风格--char字符串+\0)
	
	{

		char a[] = "Hello World!\n";
		printf("%zu", strlen(a));
		printf(a);//发生隐性转换 从char*到const char*
		printf(static_cast<const char*>(&a[0]));//与上边的基本等价
		printf("Hello World!\n");
	}
	//采用占位符 依次打印
	printf("数字是%d\n", 110);
	
	//printf的转换规范
	// 【-+0#】【12】【.4】【l】【d】
	// 【标志字符】【最小字段宽度】【精度范围】【长度指示符】【转换操作】
	//                                          h、hh、l、ll、z
	//                              固定小数点后的位数或限制整数的最小位数
	//              在前面加空格或其他
	printf("%.3f\n",1.0023);
	printf("%e\n",12346.326);
	//%d 有符号十进制整数 decimal(十进制)  %i integer
	//%u 无符号十进制整数 unsigned
	//%o 无符号八进制整数 octal(八进制)
	//%x或者%X 无符号十六进制整数 hexadecimal 大小写用x区分
	//%f 十进制浮点数 float
	//%e或者%E 科学技术法浮点数 exponent 大小写用e区分
	//%g或者%G 自动选择更紧凑的形式 自动选择%E/%e或者%F/%f general
		//范围小
	//%a或者%A 十六进制浮点数 hexadecimal
	//%c 单个字符 character
	//%s 字符串 string
	//%p 指针地址 pointer
	//%% 输出字面量%
	 
	


	//%h short 配合d/i/o/u/x/X
	//%l long 配合d/i/o/u/x/X
	//%ll long long 配合d/i/o/u/x/X
	//%L long double 配合f/e/g/a
		//double要用%lf 输出有提升不用考虑，但是输入必须考虑！！！
	//%z size_t int别名 配合d/i/o/u/x/X
		//%zu是sizeof的返回值
	//%j intmax_t 配合d/i/o/u/x/X
	//%t ptrdiff_t 配合d/i/o/u/x/X
	
	
	//标志字符
	//%- 左对齐 通常需要配合宽度限制
	printf("\n[%5d]\n",42);
	//%+ 强制显示正负号 加在符号后数字前
	printf("%+07d\n", 1234);
	printf("[%+d]\n",42);
	//% (空格) 整数前留一个空格 加在符号之前
	printf("%+7d\n", 1234);
	printf("% d\n", 42);
	//%# 备用格式 读作hash
		//%#o  保证输出以0开头   标明八进制
		//%#X或者%#x  非零值时加0x或者0X标识十六进制
		//%#f/e/g保留小数点
		//%#g/G 保留结尾的0
	

    //转义字符
	// \a 报警
	// \b 退格---删除上一个字符
	// \f 换页---换行在上一个位置的正下方
	// \n 换行
	// \r 回车---
	// \t 水平制表
	// \v 垂直制表


	//宽度输出默认右对齐,小数点也算在内
	//%0 用0填充宽度  只在右对齐时生效   不能用%-   0会被忽略
	//%.3   保留三位精度
	printf("[%-10.3s]\n","hello");
	printf("[%+08.2f]\n",3.1415926);
	printf("[%-+8d]\n",42);
	printf("[%#08x]\n",255);

	printf("%*.*f\n",10,3,3.1415926538);
	printf("%-*d\n",8,42);
	printf("%-08d\n",42);//这里0被忽略

	//scnaf函数
	
	{
		char a[20];
		//有必要限制缓存区最大大小 留一个位置放\0
		//scanf函数也会自动删除换行 空格 制表符等并结束当前输入
		if (scanf("%19s", a) == 1) {//scanf函数在数组末尾会自动加上\0 可以正常结尾
			//返回值是成功赋值的变量数目
			printf("%s", a);
		}
	}


	chapter("数据类型");
	//数据类型
	//int 4 long 4
	//short 2 char 1
	//long long 8

	//不同类型的相互转换
	//编译器坚持能不丢失数据就不绝不丢失数据


	{
		//强制类型转化不会改变变量本身的类型
		//数字运算时的结果的数据类型：
				//比int低的或等于的都会变成int作为结果，比int高的保留运算中最大的类型
		//float 中间参与计算时是double计算结果
		//unsigned 不可用于float和double
		unsigned int m = 110;
		char a = '0';
		short b = 0;
		int c = 0;
		long d = 0;
		long long e = 0;
		auto x = m + d;//此处long比unsigned int小而usigned int作为结果可能失去符号所以使用unsigned long
		double n = -3.14;
		printf("%f\n", -n);

	}





	//字符常量在不同编译其中不一样
	//char 在c编译器中是4字节
	//char 在cpp编译器中是1字节
	//字符串常量会在末尾自动加上\0  char val[]="..."可以赋值
	//如果用{'h'...}初始化，不会主动添加\0

	//char本质是整形 可以参与数学运算
	//大写字母加32等于小写字母
	//阿斯克码编码
	char letter = 'A';
	letter += 32;
	printf("%c\n",letter);


	//n字节的模为2^n
	//不考虑负数 n字节可以表示0到(2^n)-1
	//考虑负数 把最高位当作符号位 0为正数 1为负数
	//n字节可以表示-2^（n-1）到(2^(n-1))-1
		//对于负数 用模减去这数的整数，把结果直接用二进制表示，结果就为负数补码



	//数组



	//数组声明的公式是  元素类型 数组名称 [元素个数]
	{
		int a[10][5];//int[5] a[10]经过调整得到
		//元素是int[5] 数组名是a 元素个数是10
		int b[10][6][5];//
	}
	//数组注意！！！
	{
		char a[2][3] = {
		{'h','e','l'},
		{'l','o','!' }
		};


		//指针增量的算法是:n*sizeof(*p) ->p+n
		printf("a=%p\n", a);
		printf("*a=%p\n", *a);
		printf("*a+1=%p\n", *a + 1);//1*sizeof(**a)
		printf("&a[0]=%p\n", &a[0]);
		printf("&a[0]+1=%p\n", &a[0] + 1);//1*sizeof(*&a[0])==1*sizeof(a[0])
		printf("a[0]=%p\n", a[0]);
		printf("a[1]=%p\n", a[1]);
	}


	chapter("运算符");

	//运算符
	//    +        -       *       /       %     =     <      >
	//    ++       --     ||      &&       |      &       ^       >>      <<  
	

	//赋值运算符表达式的结果为右边的值
	int m_1 = 0;//这个是初始化的等号，额外作用是给m_1赋值0
	if ((m_1 = 100)==100) {//这个是赋值的等号
		printf("11110000\n");
	}
	/*
	
	  “全部计算完成后求值”
		算术运算符(直接对二进制作用)
		逐位非 ~ 取反
		逐位或 | 并联
		逐位与 & 串联



		【短路求值】
		逻辑运算符(代用运算符)
		逻辑或 || (or )	只要判断出一个true 后边都不执行
		逻辑非	!(not)
		逻辑与 && (and)	只要判断出一个false 后边都不执行
	*/



	//自增和自减
		//前缀模式中，先进行加1运算，再带入表达式
		//后缀模式中，先进行表达式计算，在进行加1运算
	//额外作用是改变变量的值
	int m = 1;
	printf("{%d}", m);
	printf("%d",m++);
	//额外作用使得m=2
	printf("--%d--",++m);//先使m=m+1，此时m=3
	printf("{%d}\n", m);
	{
		char str[20];
		scanf("%s", str);
		int i = 0;
		while (str[i]!='\0') {
			putchar(str[i++]);
		}
	}

	chapter("语法");

	//break语句对于for和while都直接跳出循环
	//continue对于for语句则会更新变量
	//对于switch    break不会影响外边  continue会影响外边循环->while for ...





	return 0;
}