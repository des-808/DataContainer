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
	}*Head, * Tail;
	size_t size;

public:
	List() {
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor " << this << endl;
	}
	~List() {
		//while (Head)pop_front();
		//while (Head)pop_back();

		cout << "LDestructor " << this << endl;
	}
	void push_front(int Data) {
		if (Head == nullptr && Tail == nullptr) {
			Head = Tail = new Element(Data);
			size++;
			return;
		}

		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;
	}


	void push_back(int Data) {
		if (Head == nullptr && Tail == nullptr) {
			return push_front(Data);
		}
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
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
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
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


void main() {
	setlocale(LC_ALL, "");


	int n;
	cout << "введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++) {
		list.push_back(rand() % 100);
	}
	list.print();
	/*list.revers_print();
	cout << endl;*/
	//list.pop_front();
	//list.print(); 
	cout << "Insert:" << endl;
	list.insert(444, 3);
	list.print();
	list.revers_print();
	cout << "Erase:" << endl;
	list.erase(3);
	list.print();
	list.revers_print();

}