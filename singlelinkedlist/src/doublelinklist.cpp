#include "doublelinklist.h"

template<typename T>
void DoublyLinkedList<T>::deleteNode(Node*& p)
{
	//p is not nullptr
	assert(p);
	Node* q = p->next;
	//1 inner node
	/*(1)*/ p->prev->next = p->next;
	/*(2)*/ p->next->prev = p->prev;
	delete p;
	p = q;//p指向被删除节点的下一个节点
}
template<typename T>
void DoublyLinkedList<T>::backwardsPrint(void) const
{
	Node* p = m_tail.prev;
	while (p != nullptr && p != &m_head)
	{
		cout << p->data << " ";
		//(1) your code
        p = p->prev;

	}
	cout << endl;
}
template<typename T>
void DoublyLinkedList<T>::searchDeleteLoop(T t)
{
	Node* p = m_head.next;
	while (p)
	{
		if (p->data == t)
		{
			//p=p->next is finished inner
			//(2) your code
            deleteNode(p);
            cout << "element " << t << " has been deleted..." << endl;

		}
		else
		{
			p = p->next;
		}
	}
}

template<typename T>
void DoublyLinkedList<T>::searchDelete(T t)
{
	searchDeleteLoop(t);
}
template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList()
{
	//(3) your code
	m_head.next = &m_tail;
	m_tail.prev = &m_head;
}
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	Node* p = m_head.next;
	while (p != &m_tail)
	{
		Node* q = p;
		p = p->next;
		delete q;
	}
	m_head.next = &m_tail;
	m_tail.prev = &m_head;
}
template<typename T>
void DoublyLinkedList<T>::insert(T t)
{
	
	Node* p = new Node(t);

	Node* right = m_head.next;

	while (right != &m_tail && right->data < p->data)
	{
		right = right->next;
	}
	//inner insert
	/*(1)*/ right->prev->next = p;
	/*(2)*/ p->prev = right->prev;
	/*(3)*/ p->next = right;
	//(4) your code
    right->prev = p;

}

template<typename T>
string DoublyLinkedList<T>::print(void) const
{
	ostringstream oss;
	Node* p = m_head.next;
	while (p != &m_tail)
	{
		oss << p->data << " ";
		p = p->next;
	}
	string result = oss.str();
	return result;
}


int main()
{
	DoublyLinkedList<int> dlist;
	dlist.insert(5);
	check(dlist.print() == "5 ");
	dlist.insert(2);
	check(dlist.print() == "2 5 ");
	dlist.insert(8);
	check(dlist.print() == "2 5 8 ");
	dlist.insert(7);
	check(dlist.print() == "2 5 7 8 ");
	dlist.insert(7);
	check(dlist.print() == "2 5 7 7 8 ");
	dlist.insert(8);
	check(dlist.print() == "2 5 7 7 8 8 ");
	dlist.insert(9);
	check(dlist.print() == "2 5 7 7 8 8 9 ");
	dlist.backwardsPrint();
	dlist.searchDelete(2);
	check(dlist.print() == "5 7 7 8 8 9 ");
	dlist.backwardsPrint();
	dlist.searchDelete(9);
	check(dlist.print() == "5 7 7 8 8 ");
	dlist.backwardsPrint();
	dlist.searchDelete(7);
	check(dlist.print() == "5 8 8 ");
	dlist.insert(7);
	check(dlist.print() == "5 7 8 8 ");
	dlist.searchDelete(7);
	check(dlist.print() == "5 8 8 ");
	dlist.searchDelete(5);
	check(dlist.print() == "8 8 ");
	dlist.searchDelete(8);
	check(dlist.print() == "");
	dlist.insert(7);
	check(dlist.print() == "7 ");
	dlist.backwardsPrint();
	return 0;
}