#include "Node.h"
#include <iostream>
#include <fstream>
#include <forward_list>
#include <sstream>
#include <vector>
#include <regex>
#include <iomanip>
#include <limits>
#include <iterator>
#include <algorithm>
using namespace std;
void addElement(forward_list<Node>& list, const string& fullName, int age, const string& maritalStatus) {
	list.push_front({ fullName, age, maritalStatus});}
void saveListToFile(const forward_list<Node>& list, const string& filename) {
	ofstream outFile(filename);
	if (!outFile) {
		cerr << "Ошибка открытия файла для записи" << endl;
		return;}
	for (const auto& person : list) {
		outFile << person.fullName << "; " << person.age <<
		"; " << person.maritalStatus << '\n';}}
bool loadListFromFile(forward_list<Node>& list, const string& filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "Ошибка открытия файла для чтения" << endl;
		return false;}
	string line;
	regex valid_fio("^[A-Za-zА-Яа-я]+? [A-Za-zА-Яа-я]+? [A-Za-zА-Яа-я]+?$");
	while (getline(inFile, line)) {
		istringstream ss(line);
		string fullName, maritalStatus;
		int age;
		char delimiter;
		getline(ss, fullName, ';');
		ss >> age >> delimiter;
		getline(ss, maritalStatus);
		if (!regex_match(fullName, valid_fio)) {
			cerr << "Ошибка при чтении данных.\n";
			cerr << "Некорректное ФИО. (пример: Янов Ян Янович)\n";
			cerr << "Пожалуйста, исправьте содержимое файла.\n";
			return false;}
		if(!(fullName.length() && bool(age) && maritalStatus.length())) {
			cerr << "Ошибка при чтении данных.\n";
			cerr << "Пропущено одно из полей.\n";
			cerr << "Пожалуйста, исправьте содержимое файла.\n";
			return false;}
		if (fullName.length() > 35) {
			cerr << "Ошибка при чтении данных.\n";
			cerr << "Поле ФИО должно содержать не более 35 символов для корректности работы программы.\n";
			cerr << "Пожалуйста, исправьте содержимое файла.\n";
			return false;}
		if (maritalStatus.length() > 15) {
			cerr << "Ошибка при чтении данных.\n";
			cerr << "Поле семейное положение должно содержать не более 15 символов для корректности работы программы.\n";
			cerr << "Пожалуйста, исправьте содержимое файла.\n";
			return false;}
		addElement(list, fullName, age, maritalStatus);}
	inFile.close();
	return true;}
void clearList(forward_list<Node>& list) {
	if (list.empty()) return ;
	list.clear();}
int getIntInput() {
	int input;
	while (!(cin >> input)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Некорректный ввод. Пожалуйста, введите целое число: ";}
	return input;}
void removeElement(forward_list<Node>& lst, const string& value, int field) {
	if (lst.empty()){
		cerr << "Список пуст. Не могу выполнить данную операцию.\n";
		cerr << "Пожалуйста, исправьте содержимое файла.\n";
		return ;}
    lst.remove_if([&value, field](const Node& person) {
        istringstream iss(person.fullName);
        vector<string> fio{istream_iterator<string>{iss}, istream_iterator<string>{}};
        switch (field) {
            case 1: // По фамилии
                return fio.size() > 0 && fio[0] == value;
            case 2: // По имени
                return fio.size() > 1 && fio[1] == value;
            case 3: // По отчеству
                return fio.size() > 2 && fio[2] == value;
            case 4: // По возрасту
                return std::to_string(person.age) == value;
            case 5: // По семейному положению
                return person.maritalStatus == value;
            default:
                return false;}});}
void printFunctionsList() {
    cout << "Список доступных команд:\n";
    cout << "1) Удалить все элементы с заданным значением.\n";
    cout << "2) Печать всех элементов в отсортированном виде (по ФИО).\n";
    cout << "3) Присвоить всем элементам предустановленные значения.\n";
    cout << "4) Заполнить данными.\n";
	cout << "5) Выход.\n";
	cout << "Введите номер команды: ";}
void selectFieldForDeleting() {
    cout << "Поле выборки:\n";
    cout << "1) по фамилии.\n2) по имени.\n";
    cout << "3) по отчеству.\n4) по возрасту.\n";
    cout << "5) по семейному положению.\n";
	cout << "Введите номер команды: ";}
bool Node::operator<(const Node& other) const {
	return fullName < other.fullName;}
void printSortedList(forward_list<Node>& list) {
    if (list.empty()){
		cerr << "Список пуст. Не могу выполнить данную операцию.\n";
		cerr << "Пожалуйста, исправьте содержимое файла.\n";
		return ;}
	vector<Node> sorted_list(list.begin(), list.end());
	sort(sorted_list.begin(), sorted_list.end());
    cout << left << setw(40) << "ФИО" << setw(10) << "Возраст" << setw(20) << " Семейное положение" << endl;
    cout << "--------------------------------------------------------------------------------\n";
    for (const auto& person : sorted_list) {
    cout << left << setw(40) << person.fullName << setw(10) << person.age << setw(20) << person.maritalStatus << endl;
    }
	cout << endl;}
void setDefaultValues(forward_list<Node>& list, const string& fullName, int age, const string& maritalStatus) {
	if (list.empty()){
		cerr << "Список пуст. Не могу выполнить данную операцию.\n";
		cerr << "Пожалуйста, исправьте содержимое файла.\n";
		return ;}
	for(auto& person : list) {
		person.fullName = fullName;
		person.age = age;
		person.maritalStatus = maritalStatus;}}
void setList(forward_list<Node>& list, const string& filename) {
	clearList(list);
	addElement(list, "Иванов Святослав Игоревич", 25, "Не женат");
	addElement(list, "Ишгулов Ратмир Русланович", 18, "Не женат");
	addElement(list, "Малышев Владимир Игоревич", 19, "Не женат");
	addElement(list, "Замилова Азалия Ринатовна", 19, "Не замужем");
	addElement(list, "Наумов Денис Олегович", 31, "Женат");
	addElement(list, "Мухтаров Адель Рамилевич", 24, "Не женат");
	addElement(list, "Самойлова Анастасия Борисовна", 24, "Замужем");
	addElement(list, "Каримов Азамат Тимурович", 43, "Не женат");
	saveListToFile(list, filename);}
