#include "helloworld.h"

Vector::Vector(void)
    :m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
{
    std::cout << "Vector()" << std::endl;
}

Vector::Vector(const Vector& from)
{
    if (from.empty())
    {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
        return;
    }

    m_capacity = m_size = from.m_size;
    m_data = new int[m_size];
    for (auto i = 0; i < m_size; ++i)
    {
        m_data[i] = from.m_data[i];
    }
    std::cout << "Vector(const Vector & from)" << std::endl;
}

Vector::Vector(int count, int value)
    : m_data(nullptr)
{
    if (count <= 0)
    {
        throw std::runtime_error("size of vector to init must bigger than zero!");
    }
    m_data = new int[count];
    for (size_t i = 0; i < count; i++)
    {
        m_data[i] = value;
    }
    m_capacity = m_size = count;
    std::cout << "Vector(const, value)" << std::endl;
}

Vector::Vector(int* start, int* end)
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
{
    assert(start != nullptr && end != nullptr);
    m_capacity = m_size = ((size_t)end - (size_t)start) / sizeof(int);//这里如果用int来存放可能会盛不下，size_t可以保证盛放的下
    assert(m_size > 0);
    m_data = new int[m_size];
    for (size_t i = 0; i < m_size; i++)
    {
        m_data[i] = *start++;
    }
    std::cout << "Vector(start, end)" << std::endl;
}

Vector& Vector::operator=(const Vector& from)
{
    if (this == &from)
    {
        return *this;
    }
    //先释放自己的数据
    clear();
    m_size = from.m_size;
    m_capacity = from.m_capacity;
    m_data = new int[m_size];
    for (size_t i = 0; i < m_size; i++)
    {
        m_data[i] = from.m_data[i];
    }
    return *this;
    std::cout << "Vector & Vector::operator=(const Vector & from)" << std::endl;
}

Vector::~Vector()
{
    if (m_data)
    {
        delete[] m_data;
    }
    std::cout << "~Vector()" << std::endl;
}

size_t Vector::size(void) const
{
    return m_size;
}

bool Vector::empty(void) const
{
    return m_size == 0;
}

const int& Vector::operator[](size_t n) const
{
    return m_data[n];
}

int& Vector::operator[](size_t n)
{
    return  m_data[n];
}

void Vector::push_back(const int& val)
{
    if (m_capacity > m_size)//直接追加到最后一个
    {
        m_data[m_size++] = val;
    }
    else//只有满了的那一瞬间，才翻倍开辟新空间
    {
        auto pNewArray = new int[m_capacity = m_capacity + m_capacity];
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
//下面的代码 函数名是 Vector::begin
//           返回值类型是 Vector::const_iterator
//返回值类型之所以要加类作用域是因为，返回值类型在函数作用域之外。这是由C语言继承而来的
Vector::const_iterator Vector::begin() const noexcept
{
    if (empty())
    {
        return end();
    }
    const_iterator itr;
    //(1) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    itr.m_hold = m_data;

    return itr;
}

Vector::iterator Vector::begin() noexcept
{
    if (empty())
    {
        return end();
    }
    iterator itr;
    //(1) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    itr.m_hold = m_data;

    return itr;
}

Vector::const_iterator Vector::end() const noexcept
{
    const_iterator itr;
    //(2) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    // 如果容器为空，不能返回下标返回的元素位置
    itr.m_hold = m_data + m_size;

    return itr;
}

Vector::iterator Vector::end() noexcept
{
    iterator itr;
    //(2) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    // 如果容器为空，不能返回下标返回的元素位置
    itr.m_hold = m_data + m_size;

    return itr;
}

void Vector::clear(void)
{
    //(3) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    delete[] m_data;

    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

bool operator==(const Vector::iterator& lhs, const Vector::iterator& rhs)
{
    //(4) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    return lhs.m_hold == rhs.m_hold;
}

bool operator!=(const Vector::iterator& lhs, const Vector::iterator& rhs)
{
    //(5) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    return !(lhs == rhs);
}

Vector::iterator& Vector::iterator::operator++()
{
    //(6) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    ++m_hold;
    return *this;
}
Vector::const_iterator& Vector::const_iterator::operator++()
{
    //(7) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    ++m_hold;
    return *this;
}

Vector::iterator Vector::iterator::operator++(int)
{
    //(8) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    iterator old = *this;
    ++m_hold;

    return old;
}
Vector::const_iterator Vector::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ++m_hold;

    return old;
}
int& Vector::iterator::operator*()
{
    //(9) your code 
    return *m_hold;
}
const int& Vector::const_iterator::operator*() const
{
    //(9) your code 
    return *m_hold;
}
void print(const Vector& v, const std::string& msg)
{
    std::cout << "print The contents of " << msg.c_str() << " are:";
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << ' ' << v[i];
    }
    std::cout << '\n';
}
void print_itr(Vector& v, const std::string& msg)
{
    std::cout << "print_itr The contents of " << msg.c_str() << " are:";
    for (auto itr = v.begin(); itr != v.end(); itr++)
    {
        std::cout << ' ' << *itr;
    }
    std::cout << '\n';
}
void print_const_itr(const Vector& v, const std::string& msg)
{
    std::cout << "print_const_itr The contents of " << msg.c_str() << " are:";
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        //*itr = 4;
        std::cout << ' ' << *itr;
    }
    std::cout << '\n';
}


int main()
{
    Vector a;

    Vector first;                   // empty vector of ints
    assert(first.empty() == true && first.size() == 0);
    Vector second(4, 100);                       // four ints with value 100
    assert(second.empty() == false);
    assert(second.size() == 4);
    assert(*second.begin() == 100);
    Vector fourth(second);                       // a copy of third
    assert(fourth.size() == second.size());

    int myints[] = { 16,2,77,29 };
    Vector fifth(myints, myints + sizeof(myints) / sizeof(int));
    assert(fifth.empty() == false);
    assert(fifth[0] == 16);
    assert(fifth[3] == 29);
    assert(fifth.size() == sizeof(myints) / sizeof(int));
    print(fifth, "fifth");//The contents of fifth are:16 2 77 29 
    fifth.push_back(30);
    assert(fifth[4] == 30);
    assert(fifth.size() == 5);
    print(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
    assert(fifth.size() == sizeof(myints) / sizeof(int) + 1);
    first = fifth = fifth;
    print(first, "first");//The contents of first are:16 2 77 29 30 
    assert(first.empty() == false && first.size() == fifth.size());
    print_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
    print_const_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
    Vector a1(myints, myints + sizeof(myints) / sizeof(int));
    {
        Vector b(a1);
        b.push_back(2);
        assert(b[4] == 2);
    }
    {
        Vector c;
        for (auto i : c)
        {
            std::cout << i << " ";
        }
        c = a1;
        a1 = c;
        c = a1;

        for (auto i : c)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    assert(a1.size() == sizeof(myints) / sizeof(int));
    {
        Vector c;
        c = fifth;
        c[0] = 1;
        assert(c[0] == 1);
    }
}