
#include"Header.h"


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
List<T>::List() {
	Head = Tail = nullptr;
	size = 0;
	//cout << "LConstructor " << this << endl;
}
template <typename T>
List<T>::List(const std::initializer_list<T>& xz) :List()
{
	for (T i : xz) { push_back(i); }
}
template <typename T>List<T>::List(const List& other) : List()
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
	for (typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); ++it) {
		cat.push_back(*it);
		//*it *= 1000;
	}
	return cat;
}
