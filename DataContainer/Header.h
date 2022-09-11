#pragma once

#include<iostream>
using namespace std;
#define tab "\t"
template<typename T>
class List {
	class Element {
		T Data;
		Element* pNext;//сдедующий элемент
		Element* pPrev;//предведущий элемет
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	};//*Head, * Tail;
	Element* Head;
	Element* Tail;
	size_t size;
	class ConstBaseIterator {
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator {
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator--();
		ConstIterator& operator--(int);
		ConstIterator& operator++();
		ConstIterator& operator++(int);
	};
	class ConstReversIterator :public ConstBaseIterator {
	public:
		ConstReversIterator(Element* Temp);
		~ConstReversIterator();
		ConstReversIterator& operator++();
		ConstReversIterator& operator++(int);
		ConstReversIterator& operator--();
		ConstReversIterator& operator-(int);
	};
	class Iterator :public ConstIterator {
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReversIterator :public ConstReversIterator {
	public:
		ReversIterator(Element* Temp) :ConstReversIterator(Temp) {}
		~ReversIterator() {}
		T& operator*();
	};
	const ConstIterator cbegin()const;
	const ConstIterator cend()const;
	ConstReversIterator crbegin()const;
	ConstReversIterator crend()const;
	Iterator begin();
	Iterator end();
	ReversIterator rbegin();
	ReversIterator rend();
	List();
	List(const std::initializer_list<T>& xz);
	List(const List& other);
	~List();
	List& operator=(const List& other);
	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, int Index);
	void erase(int Index);
	void print()const;
	void revers_print()const;
};