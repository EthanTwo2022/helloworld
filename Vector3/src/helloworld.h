//------下面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
#include <algorithm>
#include <cstdlib>
#include <iostream> 
#include <vector>
#include <utility>
using namespace std;
struct Record { Record(void* ptr1, size_t count1, const char* location1, int line1, bool is) :ptr(ptr1), count(count1), line(line1), is_array(is) { int i = 0; while ((location[i] = location1[i]) && i < 100) { ++i; } }void* ptr; size_t count; char location[100] = { 0 }; int line; bool is_array = false; bool not_use_right_delete = false; }; bool operator==(const Record& lhs, const Record& rhs) { return lhs.ptr == rhs.ptr; }std::vector<Record> myAllocStatistic; void* newFunctionImpl(std::size_t sz, char const* file, int line, bool is) { void* ptr = std::malloc(sz); myAllocStatistic.push_back({ ptr,sz, file, line , is }); return ptr; }void* operator new(std::size_t sz, char const* file, int line) { return newFunctionImpl(sz, file, line, false); }void* operator new [](std::size_t sz, char const* file, int line)
{ return newFunctionImpl(sz, file, line, true); }void operator delete(void* ptr) noexcept { Record item{ ptr, 0, "", 0, false }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }void operator delete[](void* ptr) noexcept {Record item{ ptr, 0, "", 0, true }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (!itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); }}
#define new new(__FILE__, __LINE__)
struct MyStruct { void ReportMemoryLeak() { std::cout << "Memory leak report: " << std::endl; bool leak = false; for (auto& i : myAllocStatistic) { if (i.count != 0) { leak = true; std::cout << "leak count " << i.count << " Byte" << ", file " << i.location << ", line " << i.line; if (i.not_use_right_delete) { cout << ", not use right delete. "; }	cout << std::endl; } }if (!leak) { cout << "No memory leak." << endl; } }~MyStruct() { ReportMemoryLeak(); } }; static MyStruct my; void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);
//------上面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------

#include <iostream>
#include <cassert>

class Vector
{
public:
    Vector(void);//1 默认构造函数
    Vector(int count, int value);//2 非默认构造函数
    Vector(const Vector& from);//4 复制构造函数
    Vector(int* start, int* end);// 3 非默认构造函数
    Vector& operator = (const Vector& from);
    ~Vector();
public:
    size_t size(void) const;
    bool empty(void) const;
    const int& operator[] (size_t n) const;
    int& operator[] (size_t n);
    void push_back(const int& val);
public:
    class iterator
    {
        friend class  Vector;
        friend bool operator == (const iterator& lhs, const iterator& rhs);//用于实现!=,因为==非常容易实现
        friend bool operator != (const iterator& lhs, const iterator& rhs);
    public:
        iterator & operator++(); //用于前置形式
        iterator operator++(int); //用于后置形式，这里有个int参数纯粹是为了区分前自增操作符而加的语法规定
        int& operator*();//解引用操作符重载
    private:
        int* m_hold=nullptr;
    };
    class const_iterator
    {
        friend class  Vector;
    public:
        bool operator == (const const_iterator& rhs) { return this->m_hold == rhs.m_hold; }//用于实现!=,因为==非常容易实现
        bool operator != (const const_iterator& rhs) { return !(*this == rhs); };
        const_iterator & operator++(); //用于前置形式 ++itr  先改变自己，指向下一个位置，再返回自己
        const_iterator operator++(int); //用于后置形式 itr++ 先创建一个改变前的副本用于返回，再在返回前改变自己，指向下一个位置
        const int& operator*() const;
    private:
        const int* m_hold=nullptr;
    };
    //noexcept 表示这个函数内不会抛出异常，这样有助于编译器优化代码生成
    const_iterator begin() const noexcept;
    iterator begin() noexcept;
    const_iterator end() const noexcept;
    iterator end() noexcept;
private:
    void clear(void);
private:
    size_t m_size;//当前元素数量
    size_t m_capacity;//容量
    int* m_data;//数据部分
};