

#include "List.cpp"



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