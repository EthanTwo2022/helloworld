// helloworld.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Student
{
	friend ostream& operator<<(ostream& os, const Student& stu);

public:
	std::string m_id;//学号
	std::string m_name;//姓名
	int m_age;//年龄
	std::string m_date;//生日
};

std::ostream& operator<<(std::ostream& os, const Student& stu)
{
	//向os输出Student对象的每一个成员变量，从而将Student输出到os
	os
		//如果这个函数不是friend，这里就只能写 stu.get_id()这样的代码来获取类的成员变量，比较麻烦
		<< stu.m_id << " "
		<< stu.m_name << " "
		<< stu.m_age << " "
		<< stu.m_date;
	return os;//这样os就可以连续输出多个对象。例如， cout<<stu1<<stu2;
}

