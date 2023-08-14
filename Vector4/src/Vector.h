#ifndef VEC_H
#define VEC_H
#include <iostream>
#include <cassert>
#include <initializer_list>
//------下面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
#include <algorithm>
#include <cstdlib>
#include <iostream> 
#include <vector>
#include <utility>
using namespace std;
struct Record { Record(void* ptr1, size_t count1, const char* location1, int line1, bool is) :ptr(ptr1), count(count1), line(line1), is_array(is) { int i = 0; while ((location[i] = location1[i]) && i < 100) { ++i; } }void* ptr; size_t count; char location[100] = { 0 }; int line; bool is_array = false; bool not_use_right_delete = false; }; bool operator==(const Record& lhs, const Record& rhs) { return lhs.ptr == rhs.ptr; }std::vector<Record> myAllocStatistic; void* newFunctionImpl(std::size_t sz, char const* file, int line, bool is) { void* ptr = std::malloc(sz); myAllocStatistic.push_back({ ptr,sz, file, line , is }); return ptr; }void* operator new(std::size_t sz, char const* file, int line) { return newFunctionImpl(sz, file, line, false); }void* operator new [](std::size_t sz, char const* file, int line)
{
	return newFunctionImpl(sz, file, line, true);
}void operator delete(void* ptr) noexcept { Record item{ ptr, 0, "", 0, false }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }void operator delete[](void* ptr) noexcept { Record item{ ptr, 0, "", 0, true }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (!itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }
#define new new(__FILE__, __LINE__)
struct MyStruct { void ReportMemoryLeak() { std::cout << "Memory leak report: " << std::endl; bool leak = false; for (auto& i : myAllocStatistic) { if (i.count != 0) { leak = true; std::cout << "leak count " << i.count << " Byte" << ", file " << i.location << ", line " << i.line; if (i.not_use_right_delete) { cout << ", not use right delete. "; }	cout << std::endl; } }if (!leak) { cout << "No memory leak." << endl; } }~MyStruct() { ReportMemoryLeak(); } }; static MyStruct my; void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);
//------上面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------

template<typename T>
class Vector
{
public:
	/* 提供默认构造函数， 否则只能使用有参版本，这会带来不便
	 例如，Vector<int> arr; 这样会报错，因为需要默认构造函数
	*/
	Vector(void);//如果类提供了非默认构造函数，编译器不会自动提供默认构造函数
	Vector(const Vector& from);// 复制构造函数
	Vector(T* start, T* end);//  非默认构造函数
	Vector(int count, int value);//2 非默认构造函数
	Vector(std::initializer_list<T> value_array)
	{
		for (auto& item : value_array)
		{
			push_back(item);
		}
	}
	Vector& operator = (const Vector& from);
	bool operator==(const Vector& other) const
	{
		//(1) your code
        if(m_size == other.m_size)
        {
            for(size_t i=0; i<m_size; i++)
            {
                if(m_data[i] != other.m_data[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
		
	}
	//赋值操作符
	~Vector();//析构函数
public:
	size_t size(void) const;
	bool empty(void) const;
	T& operator[] (size_t n) const;
	T& operator[] (size_t n);
	void push_back(const T& val);
	void clear(void);
private:
	void deep_copy_from(const Vector<T>& from);

public:
	struct iterator : std::iterator<std::random_access_iterator_tag, T>
	{
		friend class  Vector;
		friend bool operator == (const iterator& lhs, const iterator& rhs) { return lhs.m_hold == rhs.m_hold; }
		friend bool operator != (const iterator& lhs, const iterator& rhs) { return !(lhs == rhs); }
		friend size_t operator - (const iterator& lhs, const iterator& rhs) { return lhs.m_hold - rhs.m_hold; }
		friend bool operator < (const iterator& lhs, const iterator& rhs) { return lhs.m_hold < rhs.m_hold; }
		friend bool operator > (const iterator& lhs, const iterator& rhs) { return lhs.m_hold > rhs.m_hold; }
		friend bool operator <= (const iterator& lhs, const iterator& rhs) { return !(lhs > rhs); }
		friend bool operator >= (const iterator& lhs, const iterator& rhs) { return !(lhs < rhs); }
		friend iterator operator + (const iterator& lhs, size_t n) { iterator itr; itr.m_hold = lhs.m_hold + n; return itr; }//随机访问迭代器牛逼的地方
		friend iterator operator - (const iterator& lhs, size_t n) { iterator itr; itr.m_hold = lhs.m_hold - n; return itr; }//随机访问迭代器牛逼的地方
	public:
		//用于前置形式
		iterator& operator++() { m_hold = m_hold + 1; return *this; };
		iterator& operator--() { m_hold = m_hold - 1; return *this; };
		//用于后置形式
		iterator operator++(int) { iterator itr = *this; m_hold += 1; return itr; }
		iterator operator--(int) { iterator itr = *this; m_hold -= 1; return itr; }
		T& operator*() const//这里必须是const in C++14
		{
			return *m_hold;
		}
	private:
		T* m_hold;
	};
	struct const_iterator : std::iterator<std::random_access_iterator_tag, T>
	{
		friend class  Vector;
		friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) { return lhs.m_hold == rhs.m_hold; }
		friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) { return !(lhs == rhs); }
		friend size_t operator - (const const_iterator& lhs, const const_iterator& rhs) { return lhs.m_hold - rhs.m_hold; }
		friend bool operator < (const const_iterator& lhs, const const_iterator& rhs) { return lhs.m_hold < rhs.m_hold; }
		friend bool operator > (const const_iterator& lhs, const const_iterator& rhs) { return lhs.m_hold > rhs.m_hold; }
		friend bool operator <= (const const_iterator& lhs, const const_iterator& rhs) { return !(lhs > rhs); }
		friend bool operator >= (const const_iterator& lhs, const const_iterator& rhs) { return !(lhs < rhs); }
		friend const_iterator operator + (const const_iterator& lhs, size_t n) { const_iterator itr; itr.m_hold = lhs.m_hold + n; return itr; }//随机访问迭代器牛逼的地方
		friend const_iterator operator - (const const_iterator& lhs, size_t n) { const_iterator itr; itr.m_hold = lhs.m_hold - n; return itr; }//随机访问迭代器牛逼的地方
	public:
		//用于前置形式
		const_iterator& operator++() { m_hold = m_hold + 1; return *this; };
		const_iterator& operator--() { m_hold = m_hold - 1; return *this; };
		//用于后置形式
		const_iterator operator++(int) { const_iterator itr = *this; m_hold += 1; return itr; }
		const_iterator operator--(int) { const_iterator itr = *this; m_hold -= 1; return itr; }
		const T& operator*() const
		{
			return *m_hold;
		}
	private:
		T* m_hold;
	};

	iterator begin() noexcept
	{
		iterator itr;
		itr.m_hold = empty() ? nullptr : &m_data[0];
		return itr;
	}
	const_iterator cbegin() const noexcept;
	iterator end() noexcept
	{
		iterator itr;
		itr.m_hold = empty() ? nullptr : &m_data[m_size];
		return itr;
	}
	const_iterator cend() const noexcept;
private:
	size_t m_size = 0;//当前元素数量
	size_t m_capacity = 0;//容量
	T* m_data = nullptr;//数据部分
};

template<typename T>
Vector<T>::Vector(void)
{
}

template<typename T>
Vector<T>::Vector(T * start, T * end)
{
	std::cout << "Vector(T* start, T* end)" << std::endl;
	assert(start != nullptr && end != nullptr);
	m_capacity = m_size = ((size_t)end - (size_t)start)/sizeof(T);//这里如果用int来存放可能会盛不下，size_t可以保证盛放的下
	assert(m_size > 0);
	m_data = new T[m_size];
	for (size_t i = 0; i < m_size; i++)
	{
		m_data[i] = *start++;
	}
}
template<typename T>
Vector<T>::Vector(int count, int value)
{
	std::cout << "Vector(count, value)" << std::endl;
	if (count <= 0)
	{
		throw std::runtime_error("size of vector to init must bigger than zero!");
	}
	m_data = new T[count];
	for (size_t i = 0; i < count; i++)
	{
		m_data[i] = value;
	}
	m_capacity = m_size = count;
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& from)
{
	std::cout << "Vector::operator=" << std::endl;
	if (this == &from)
	{
		return *this;
	}
	//先释放自己的数据
	clear();
	deep_copy_from(from);
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	//(2) your code
    if(m_data)
    {
        delete[] m_data;
    }

}
template<typename T>
size_t Vector<T>::size(void) const
{
	return m_size;
}
template<typename T>
bool Vector<T>::empty(void) const
{
	//(3) your code
    return m_size == 0;
}
template<typename T>
T& Vector<T>::operator[](size_t n) const
{
	//(4) your code
	return m_data[n];
}
template<typename T>
T& Vector<T>::operator[](size_t n)
{
	//(4) your code
	return m_data[n];
}
template<typename T>
void Vector<T>::push_back(const T & val)
{
	//(5) your code
    if(m_capacity == 0)
    {
        m_capacity = 10;
        m_size = 0;
        m_data = new T[m_capacity];
        m_data[m_size++] = val;
    }
    else if (m_capacity > m_size)//直接追加到最后一个
    {
        m_data[m_size++] = val;
    }
    else//只有满了的那一瞬间，才翻倍开辟新空间
    {
        auto pNewArray = new T[m_capacity = m_capacity + m_capacity];
        //拷贝老数据
        for (size_t i = 0; i < m_size; i++)
        {
            pNewArray[i] = m_data[i];
        }
        //追加最新的末尾元素
        pNewArray[m_size++] = val;
        delete[] m_data;
        m_data = pNewArray;
    }   
}

template<typename T>
void Vector<T>::clear(void)
{
	//(6) your code
    delete[] m_data;

    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template<typename T>
void Vector<T>::deep_copy_from(const Vector<T>& from)
{
	//(7) your code
    clear();
    if(from.empty())
    {
        return;
    }

    m_capacity = from.m_capacity;
    m_size = from.m_size;
    m_data = new T[m_capacity];
    for(size_t i = 0; i < m_size; i++)
    {
        m_data[i] = from.m_data[i];
    }

}

template<typename T>
Vector<T>::Vector(const Vector& from)
{
	//(8) your code
    if(from.empty())
    {
        m_data = nullptr;
        m_capacity = 0;
        m_size = 0;
        return;
    }

    m_capacity = from.m_capacity;
    m_size = from.m_size;
    m_data = new T[m_capacity];
    for(size_t i=0; i<m_size; i++)
    {
        m_data[i] = from.m_data[i];
    }

}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept
{
	Vector<T>::const_iterator itr;
	//(9) your code
    itr.m_hold = m_data + m_size;

	return itr;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept
{
    if(empty())
    {
        return cend();
    }

	const_iterator itr;
	//(10) your code
    itr.m_hold = m_data;

	return itr;
}

#endif