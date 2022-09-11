﻿#include<iostream>
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
	class ConstIterator:public ConstBaseIterator{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator--();
		ConstIterator& operator--(int);
		ConstIterator& operator++();
		ConstIterator& operator++(int);
	};
	class ConstReversIterator:public ConstBaseIterator {
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
		ReversIterator(Element* Temp) :ConstReversIterator(Temp){}
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////			Element         		////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :Data(Data), pNext(pNext), pPrev(pPrev) {
	//cout << "EConstructor " << this << endl;
}
template<typename T>List<T>::Element::~Element() {
	//cout << "EDestructor " << this << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////			Element  end       		////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////			const 	iterators		////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp) {
	//cout << "CBItConstructor:\t" << this << endl;
}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator() {
	//cout << "CBItDestructor:\t" << this << endl;
}
template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const {
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const {
	return this->Temp != other.Temp;
}
template<typename T>const T& List<T>::ConstBaseIterator::operator*()const {
	return Temp->Data;
}
//----------------------------------------------------------------------------------------------------------
template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp) {
	//cout << "ItConstructor:\t" << this << endl;
}
template<typename T>List<T>::ConstIterator::~ConstIterator() {
	//cout << "ItDestructor:\t" << this << endl;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--() {
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--(int) {
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++() {//постфиксный
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++(int) {//префиксный
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
//----------------------------------------------------------------------------------------------------------
template<typename T>List<T>::ConstReversIterator::ConstReversIterator(Element* Temp) :ConstBaseIterator(Temp) {
	//cout << "REversIteratorConstructor " << this << endl;
}
template<typename T>List<T>::ConstReversIterator::~ConstReversIterator() {
	//cout << "REversIteratorDestructor " << this << endl;
}
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator++() {
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator++(int) {
	ConstReversIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator--() {
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator-(int) {
	ConstReversIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////			const 	iterators	end	////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>T& List<T>::Iterator::operator*() { return ConstBaseIterator::Temp->Data; }
template<typename T>T& List<T>::ReversIterator::operator*() { return ConstBaseIterator::Temp->Data; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>const typename List<T>::ConstIterator List<T>::cbegin()const {
	return this->Head;
}
template <typename T>const typename List<T>::ConstIterator List<T>::cend()const {
	return nullptr;
}
template <typename T>typename List<T>::ConstReversIterator List<T>::crbegin()const {
	return Tail;
}
template <typename T>typename List<T>::ConstReversIterator List<T>::crend()const {
	return nullptr;
}
template <typename T>typename List<T>::Iterator List<T>::begin() {
	return Head;
}
template <typename T>typename List<T>::Iterator List<T>::end() {
	return nullptr;
}
template <typename T>typename List<T>::ReversIterator List<T>::rbegin() {
	return Tail;
}
template <typename T>typename List<T>::ReversIterator List<T>::rend() {
	return nullptr;
}
template <typename T>
List<T>:: List() {
	Head = Tail = nullptr;
	size = 0;
	//cout << "LConstructor " << this << endl;
}
template <typename T>
List<T>::List(const std::initializer_list<T>& xz) :List()
{
	for (T i : xz) { push_back(i); }
}
template <typename T>List<T>::List(const List& other) :List()
{
	*this = other;
	cout << "CopyConstructor:\t" << this << endl;
}
template <typename T>List<T>::~List() {}
template <typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	this->~List();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) { push_back(Temp->Data); }
	return *this;
}
template <typename T>void List <T>::push_front(T Data) {
	if (Head == nullptr && Tail == nullptr) {
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Head = Head->pPrev = new Element(Data);
	size++;
}
template <typename T>void List <T>::push_back(T Data) {
	if (Head == nullptr && Tail == nullptr) {
		return push_front(Data);
	}
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template <typename T>void List <T>::pop_front() {
	if (Head == nullptr && Tail == nullptr) { return; }
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template <typename T>void List <T>::pop_back() {
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template <typename T>void List <T>::insert(T Data, int Index) {
	if (Index > size)return;
	if (Index == size)return push_back(Data);
	if (Index == 0)return push_front(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++) {
			Temp = Temp->pPrev;
		}
	}
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}
template <typename T>void List <T>::erase(int Index)
{
	if (Index >= size)return;
	if (Index == size - 1)  return pop_back();
	if (Index == 0)return pop_front();

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}
template <typename T>void List <T>::print()const {
	for (Element* Temp = Head; Temp; Temp = Temp->pNext) {
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
}
template <typename T>void List <T>::revers_print()const {
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) {
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right) {
	List<T> cat = left;
	for ( typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); ++it) {
		cat.push_back(*it);
		//*it *= 1000;
	}
	return cat;
}


void main() {
	setlocale(LC_ALL, "");


	/*int n;
	cout << "введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++) {
		list.push_back(rand() % 100);
	}
	list.print();*/
	///*list.revers_print();
	//cout << endl;*/
	////list.pop_front();
	////list.print(); 
	//cout << "Insert:" << endl;
	//list.insert(444, 3);
	//list.print();
	//list.revers_print();
	//cout << "Erase:" << endl;
	//list.erase(3);
	//list.print();
	//list.revers_print();


	cout << "----------------------------------------------------" << endl;
	/*List list44 = { 3, 5, 8, 13, 21 };
	for (int i : list44) {
		cout << i << endl;
	}*/

	//for(int i:list)cout<<i<<tab; cout<<endl;
	//for (List::ReversIterator it = list.rbegin(); it != list.rend(); ++it)cout << *it << endl; 

	/*cout << "list43" << endl;
	List<int> list43 = { 2,5,8,6,9 };
	cout << "list45" << endl;
	List<int> list45 = { 7, 44, 77, 99, 11 };
	list45.print();
	cout << "list46 = list43+list43" << endl;
	List<int> list46 = list43 + list45;
	list46.print();

	for (int i : list43)cout << i << tab; cout << endl;
	for (List<int>::ReversIterator it = list45.rbegin(); it != list45.rend(); ++it)cout << *it << endl;*/


	List<int> i_list = { 3,5,8,13,21 };
	for (int i:i_list)cout << i << tab; cout << endl;
	List<double> d_list = { 3.1,5.1,8.1,13.1,21.1 };
	for (double i : d_list)cout << i << tab; cout << endl;

	for (List<double>::ConstReversIterator it = d_list.crbegin(); it != d_list.crend(); ++it) {
		cout << *it << tab;
	}cout << endl;
}
















/*
ШАБЛОНЫ КЛАССОВ
ШАБЛОННЫМ НАЗЫВАЕТСЯ КЛАСС ТИП ПОЛЕЙ КОТОРОГО ОПРЕДЕЛЯЕТСЯ ВО ВРЕМЯ СОЗДАНИЯ ОБЬЕКТА
если к обычному обращаемся 
class object;

Class<type> object;
где тайп показывает какого типа будут поля класса в создоваемом обьекте.
к шаблонному класу  можно обратиться только после указания типа
для того что бы сделать класс шаблонным перед ним достаточно сделать шаблон при помощи

template<typename T>
после созд шаблона любая переменная член класса могут быть шаблонного типа
Все методы в нутри шаблонного класса автоматически становятся шаблонными

*/