#include <iostream>
#include <algorithm>
#include "Vector.h"
#include <vector>

template<typename T>
void print(const Vector<T>& v, const std::string& msg)
{
	std::cout << "The contents of " << msg.c_str() << " are:";
	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << ' ' << v[i];
	}
	std::cout << '\n';
}
template<typename T>
void print_itr(Vector<T>& v, const std::string& msg)
{
	std::cout << "The contents of " << msg.c_str() << " are:";
	for (auto itr = v.begin(); itr != v.end(); ++itr)
	{
		std::cout << ' ' << *itr;
	}
	std::cout << '\n';
}
template<typename T>
void print_const_itr(const Vector<T>& v, const std::string& msg)
{
	std::cout << "The contents of " << msg.c_str() << " are:";
	for (auto itr = v.cbegin(); itr != v.cend(); ++itr)
	{
		std::cout << ' ' << *itr;
	}
	std::cout << '\n';
}

int main()
{
	Vector<int> a;

	Vector<int> first;                   // empty vector of ints
	check(first.empty() == true && first.size() == 0);
	Vector<int> second(4, 100);                       // four ints with value 100
	check(second.empty() == false);
	check(second.size() == 4);
	check(*second.begin() == 100);
	Vector<int> fourth(second);                       // a copy of third
	check(fourth.size() == second.size());

	int myints[] = { 16,2,77,29 };
	Vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
	check(fifth.empty() == false);
	check(fifth[0] == 16);
	check(fifth[3] == 29);
	check(fifth.size() == sizeof(myints) / sizeof(int));
	print(fifth, "fifth");//The contents of fifth are:16 2 77 29 
	fifth.push_back(30);
	check(fifth[4] == 30);
	check(fifth.size() == 5);
	print(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
	check(fifth.size() == sizeof(myints) / sizeof(int) + 1);
	first = fifth = fifth;
	print(first, "first");//The contents of first are:16 2 77 29 30 
	check(first.empty() == false && first.size() == fifth.size());
	print_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
	print_const_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
	std::sort(fifth.begin(), fifth.end());
	std::cout << "fifith after sort:" << std::endl;
	print_const_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
	Vector<int> a1(myints, myints + sizeof(myints) / sizeof(int));
	{
		Vector<int> b(a1);
		b.push_back(2);
		check(b[4] == 2);
		auto result = (b == Vector<int>{ 16, 2, 77, 29, 2});
		check(result);

		//iterator
		check(b.begin() + b.size() == b.end());
		auto begin = b.begin();
		auto itr = b.begin() + 1;
		check(*begin == 16);
		check(*itr == 2);
	}
	{
		Vector<int> b{ 1,3,5,7 };
		b.push_back(9);
	}
	{
		Vector<int> c;
		for (auto i : c)
		{
			std::cout << i << " ";
		}
		c = a1;
		for (auto i : c)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	check(a1.size() == sizeof(myints) / sizeof(int));
	{
		Vector<int> c;
		c = fifth;
		c[0] = 1;
		check(c[0] == 1);
	}
}