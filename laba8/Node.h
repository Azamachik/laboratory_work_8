#ifndef __NODE_H__
#define __NODE_H__
#include <string>
#include <forward_list>
using namespace std;
struct Node {
	string fullName;
	int age;
	string maritalStatus;
	bool operator<(const Node& other) const;};
namespace constants {
	const string fullName{ "Иванов Иван Иванович" };
	const string status{ "Не женат" };
	const int age{ 20 };}
void addElement(forward_list<Node>&, const string&, int, const string&);
void printList(forward_list<Node>&);
void selectFieldForDeleting();
void saveListToFile(const forward_list<Node>&, const string&);
bool loadListFromFile(forward_list<Node>&, const string&);
void clearList(forward_list<Node>&);
void removeElement(forward_list<Node>&, const string&, int);
int getIntInput();
void printSortedList(forward_list<Node>&);
int countElementsWithContent(forward_list<Node>&, const string&, const string&);
void setDefaultValues(forward_list<Node>&, const string&, int, const string&);
void setList(forward_list<Node>&, const string&);
void printFunctionsList();
#endif