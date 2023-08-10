// helloworld.cpp: 定义应用程序的入口点。
//

#include "helloworld.h"

using namespace std;

int main(int argc, char** argv)
{
	//定义一个学生对象
	Student stu{ "001", "zhangsan", 18, "1995-09-08" };
	//将学生信息再次输出到控制台
	//这里可以直接输出stu对象
	std::cout << "学生信息：" << stu << std::endl;

	return 0;
}
