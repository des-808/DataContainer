#include<iostream>
using namespace std;
#define tab "\t"





class List {
	class Element {

		int Data;
		Element* pNext;//сдедующий элемент
		Element* pPrev;//предведущий элемет
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev) {
			cout << "EConstructor " << this << endl;
		}
		~Element() {
			cout << "EDestructor " << this << endl;
		}
		friend class List;
	};//*Head, * Tail;
	Element* Head;
	Element* Tail;
	size_t size;
	class ConstBaseIterator {
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp) {
			cout << "CBItConstructor:\t" << this << endl;
		}
		~ConstBaseIterator() {
			cout << "CBItDestructor:\t" << this << endl;
		}

		bool operator==(const ConstBaseIterator& other)const {
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const {
			return this->Temp != other.Temp;
		}
		const int& operator*()const {
			return Temp->Data;
		}
		
	};
public:
	class ConstIterator:public ConstBaseIterator{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator (Temp) {
			cout << "ItConstructor:\t" << this << endl;
		}
		~ConstIterator() {
			cout << "ItDestructor:\t" << this << endl;
		}

		ConstIterator& operator--(){
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator& operator--(int) {
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstIterator& operator++(){//постфиксный
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator& operator++(int) {//префиксный
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class ConstReversIterator:public ConstBaseIterator {
	public:
		ConstReversIterator(Element* Temp) :ConstBaseIterator(Temp) {
			cout << "REversIteratorConstructor " << this << endl;
		}
		~ConstReversIterator()  {
			cout << "REversIteratorDestructor " << this << endl;
		}
		ConstReversIterator& operator++() {
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReversIterator& operator++(int) {
			ConstReversIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReversIterator& operator--() {
			Temp = Temp->pNext;
			return *this;
		}
		ConstReversIterator& operator-(int) {
			ConstReversIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator {
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		int& operator*(){return Temp->Data;}
	};

	class ReversIterator :public ConstReversIterator {
	public:
		ReversIterator(Element* Temp) :ConstReversIterator(Temp){}
		~ReversIterator() {}
		int& operator*() {return Temp->Data;}
	};

	const ConstIterator cbegin()const{
		return this->Head;
	}

	const ConstIterator cend()const{
		return nullptr;
	}

	ConstReversIterator crbegin()const{
		return Tail;
		}
	ConstReversIterator crend()const{
		return nullptr;
		}
	Iterator begin() {
		return Head;
	}
	Iterator end() {
		return nullptr;
	}
	ReversIterator rbegin() {
		return Tail;
	}
	ReversIterator rend() {
		return nullptr;
	}
	List() {
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor " << this << endl;
	}

	List(const std::initializer_list<int>& xz) :List()
	{
		/*for (const int* temp = xz.begin(); temp != xz.end(); temp++){push_back(*temp);	}
		cout << "xzConstructor:\t" << this << endl;*/
		for (int i : xz){push_back(i);}
	}
	List(const List& other) :List()
	{
		//for (Element* temp = other.Head; temp; temp = temp->pNext){push_back(temp->Data);}
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}



	~List() {
		//while (Head)pop_front();
		//while (Head)pop_back();
		//cout << "LDestructor " << this << endl;
	}

	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		//while (Head)pop_front();
		//while (Head)pop_back();
		this->~List();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext){push_back(Temp->Data);}
		//cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	void push_front(int Data) {
		if (Head == nullptr && Tail == nullptr) {
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data);
		size++;
	}

	void push_back(int Data) {
		if (Head == nullptr && Tail == nullptr) {
			return push_front(Data);
		}
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr,Tail);
		size++;
	}

	void pop_front() {
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

	void pop_back() {
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void insert(int Data, int Index) {

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
		
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data,Temp,Temp->pPrev);
		size++;
	}



	void erase(int Index)
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

	void print()const {
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) {
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
	}

	void revers_print()const {
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) {
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
	}
};

List operator+(const List& left, const List& right) {
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); ++it) {
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


	//cout << "----------------------------------------------------" << endl;
	/*List list44 = { 3, 5, 8, 13, 21 };
	for (int i : list44) {
		cout << i << endl;
	}*/

	//for(int i:list)cout<<i<<tab; cout<<endl;
	//for (List::ReversIterator it = list.rbegin(); it != list.rend(); ++it)cout << *it << endl; 

	cout << "list43" << endl;
	List list43 = { 2,5,8,6,9 };
	cout << "list45" << endl;
	List list45 = { 7, 44, 77, 99, 11 };
	list45.print();
	cout << "list46 = list43+list43" << endl;
	List list46 = list43 + list45;
	list46.print();

	for (int i : list43)cout << i << tab; cout << endl;
	for (List::ReversIterator it = list45.rbegin(); it != list45.rend(); ++it)cout << *it << endl;
}