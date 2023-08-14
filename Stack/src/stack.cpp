#include "stack.h"

template<typename T>
Stack<T>::CStackitem::CStackitem(void)
//(1) your code 对1个成员变量初始化
{
    data = 0;
}

template<typename T>
Stack<T>::CStackitem::CStackitem(const T& _data, CStackitem* _next)
    :data(_data), next(_next)
{
}
template<typename T>
Stack<T>::Stack(void)
//(3) your code 对1个成员变量初始化
{
    m_size = 0;
}

template<typename T>
Stack<T>::Stack(const Stack& _stack)
{
    //(4) your code  使用 copy 即可
    if(this == &_stack)
    {
        return;
    }
    copy(_stack);

}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& _stack)
{
    //(5) your code 记得判断同一个对象赋值给自己
    if (this == _stack)
    {
        return *this;
    }
    copy(_stack);

    return *this;
}

template<typename T>
Stack<T>::~Stack(void)
{
    clear();
}
template<typename T>
bool Stack<T>::empty(void) const
{
    return m_size == 0;
}
template<typename T>
void Stack<T>::pop(void)
{
    //(9) your code 注意对象获取成员用"."操作符，指针获取成员用"->"操作符




}
template<typename T>
void Stack<T>::clear(void)
{
    //(6) your code 可以利用 pop 来实现
    while(!empty())
    {
        pop();
    }
}
template<typename T>
void Stack<T>::copy(const Stack& from)
{
    //(7) your code 请先使用 clear ，再遍历链表来实现
    clear();
    if(from.empty())
    {
        return;
    }

    m_head = new CStackitem;
    m_head->data = from.m_head->data;
    m_head->next = nullptr;

    CStackitem* CurOther = from.m_head;
    CStackitem* CurHead = m_head;

    while(CurOther->next)
    {
        CurHead->next = new CStackitem;
        CurHead->next->data = CurOther->next->data;
        CurHead->next->next - nullptr;

        CurOther = CurOther->next;
        CurHead = CurHead->next;
        
    }

}
template<typename T>
size_t Stack<T>::size(void) const
{
    return m_size;
}
template<typename T>·
void Stack<T>::push(const T& item)
{
    //(8) your code， 注意 这样写新创建的节点 CStackitem* p = new CStackitem(item, first);
    CStackitem* tempNode = new CStackitem;
    tempNode->data = data;

}
template<typename T>
const T& Stack<T>::top(void) const
{
    return m_head.next->data;
}

int main(int argc, char** argv)
{
    Stack<int> stack1;
    check(stack1.size() == 0);
    stack1.push(1);
    check(stack1.size() == 1);
    auto stack2 = stack1;
    auto top = stack2.top();
    check(top == 1);
    check(stack2.size() == 1);
    stack1 = stack2;// 1 and 1
    stack1.push(2);// 2 1
    top = stack2.top();
    check(top == 1);
    check(stack1.size() == 2);
    check(stack1.top() == 2);
    stack1.clear();
    check(stack1.size() == 0 && stack1.empty());
    for (size_t i = 0; i < 10; i++)
    {
        stack1.push(i);
    }
    while (!stack1.empty())
    {
        std::cout << stack1.top() << " ";
        stack1.pop();
    }
    cout << endl;
    check(stack1.size() == 0 && stack1.empty());
    //copy constructor
    {
        Stack<int> from;
        from.push(1);
        from.push(2);
        Stack<int> to(from);

        check(to.size() == 2);
        check(to.top() == 2);
        to.pop();
        check(to.top() == 1);
        to.pop();
        check(to.empty());
    }
}