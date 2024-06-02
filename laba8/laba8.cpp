#include <iostream>
#include "Node.h"
#include <forward_list>
#include <string>
#include <Windows.h>
#include <regex>
using namespace std;
int main() {
	forward_list<Node> people;
	if (!loadListFromFile(people, "list.txt")) {
		return 1;}
	else cout << "Данные загружены" << endl;
	string input;
	regex valid_input("[1-5]"), valid_field("[1-5]");
	do {
		do {
			printFunctionsList();
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		//cout << endl;
		if (input == "1") {
			string search_field, search_content;
			do {
				selectFieldForDeleting();
				getline(cin, search_field);
			} while (!regex_match(search_field, valid_field));
			cout << "Введите содержимое поле: ";
			getline(cin, search_content);
			int field = atoi(search_field.c_str());
			removeElement(people, search_content, field);
		    saveListToFile(people, "list.txt");}
		else if (input == "2") printSortedList(people);
		else if (input == "3") {
			setDefaultValues(people, constants::fullName, constants::age, constants::status);
			saveListToFile(people, "list.txt");}
		else if (input == "4") setList(people, "list.txt");
	} while (input != "5");
	clearList(people);
	cout << "До свидания!" << endl;
	return 0;}