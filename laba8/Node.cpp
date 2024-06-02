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
		cerr << "�訡�� ������ 䠩�� ��� �����" << endl;
		return;}
	for (const auto& person : list) {
		outFile << person.fullName << "; " << person.age <<
		"; " << person.maritalStatus << '\n';}}
bool loadListFromFile(forward_list<Node>& list, const string& filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "�訡�� ������ 䠩�� ��� �⥭��" << endl;
		return false;}
	string line;
	regex valid_fio("^[A-Za-z�-��-�]+? [A-Za-z�-��-�]+? [A-Za-z�-��-�]+?$");
	while (getline(inFile, line)) {
		istringstream ss(line);
		string fullName, maritalStatus;
		int age;
		char delimiter;
		getline(ss, fullName, ';');
		ss >> age >> delimiter;
		getline(ss, maritalStatus);
		if (!regex_match(fullName, valid_fio)) {
			cerr << "�訡�� �� �⥭�� ������.\n";
			cerr << "�����४⭮� ���. (�ਬ��: ���� �� ������)\n";
			cerr << "��������, ��ࠢ�� ᮤ�ন��� 䠩��.\n";
			return false;}
		if(!(fullName.length() && bool(age) && maritalStatus.length())) {
			cerr << "�訡�� �� �⥭�� ������.\n";
			cerr << "�ய�饭� ���� �� �����.\n";
			cerr << "��������, ��ࠢ�� ᮤ�ন��� 䠩��.\n";
			return false;}
		if (fullName.length() > 35) {
			cerr << "�訡�� �� �⥭�� ������.\n";
			cerr << "���� ��� ������ ᮤ�ঠ�� �� ����� 35 ᨬ����� ��� ���४⭮�� ࠡ��� �ணࠬ��.\n";
			cerr << "��������, ��ࠢ�� ᮤ�ন��� 䠩��.\n";
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
		cout << "�����४�� ����. ��������, ������ 楫�� �᫮: ";}
	return input;}
void removeElement(forward_list<Node>& lst, const string& value, int field) {
	if (lst.empty()){
		cerr << "���᮪ ����. �� ���� �믮����� ������ ������.\n";
		cerr << "��������, ��ࠢ�� ᮤ�ন��� 䠩��.\n";
		return ;}
    lst.remove_if([&value, field](const Node& person) {
        istringstream iss(person.fullName);
        vector<string> fio{istream_iterator<string>{iss}, istream_iterator<string>{}};
        switch (field) {
            case 1: // �� 䠬����
                return fio.size() > 0 && fio[0] == value;
            case 2: // �� �����
                return fio.size() > 1 && fio[1] == value;
            case 3: // �� ������
                return fio.size() > 2 && fio[2] == value;
            case 4: // �� �������
                return std::to_string(person.age) == value;
            case 5: // �� ᥬ������ ���������
                return person.maritalStatus == value;
            default:
                return false;}});}
void printFunctionsList() {
    cout << "���᮪ ����㯭�� ������:\n";
    cout << "1) ������� �� ������ � ������� ���祭���.\n";
    cout << "2) ����� ��� ����⮢ � �����஢����� ���� (�� ���).\n";
    cout << "3) ��᢮��� �ᥬ ����⠬ �।��⠭������� ���祭��.\n";
    cout << "4) ��������� ����묨.\n";
	cout << "5) ��室.\n";
	cout << "������ ����� �������: ";}
void selectFieldForDeleting() {
    cout << "���� �롮ન:\n";
    cout << "1) �� 䠬����.\n2) �� �����.\n";
    cout << "3) �� ������.\n4) �� �������.\n";
    cout << "5) �� ᥬ������ ���������.\n";
	cout << "������ ����� �������: ";}
bool Node::operator<(const Node& other) const {
	return fullName < other.fullName;}
void printSortedList(forward_list<Node>& list) {
    if (list.empty()){
		cerr << "���᮪ ����. �� ���� �믮����� ������ ������.\n";
		cerr << "��������, ��ࠢ�� ᮤ�ন��� 䠩��.\n";
		return ;}
	vector<Node> sorted_list(list.begin(), list.end());
	sort(sorted_list.begin(), sorted_list.end());
    cout << left << setw(40) << "���" << setw(10) << "������" << setw(20) << " �������� ���������" << endl;
    cout << "--------------------------------------------------------------------------------\n";
    for (const auto& person : sorted_list) {
    cout << left << setw(40) << person.fullName << setw(10) << person.age << setw(20) << person.maritalStatus << endl;
    }
	cout << endl;}
void setDefaultValues(forward_list<Node>& list, const string& fullName, int age, const string& maritalStatus) {
	if (list.empty()){
		cerr << "���᮪ ����. �� ���� �믮����� ������ ������.\n";
		cerr << "��������, ��ࠢ�� ᮤ�ন��� 䠩��.\n";
		return ;}
	for(auto& person : list) {
		person.fullName = fullName;
		person.age = age;
		person.maritalStatus = maritalStatus;}}
void setList(forward_list<Node>& list, const string& filename) {
	clearList(list);
	addElement(list, "������ ����᫠� ���ॢ��", 25, "�� �����");
	addElement(list, "��㫮� ��⬨� ��᫠�����", 18, "�� �����");
	addElement(list, "����襢 �������� ���ॢ��", 19, "�� �����");
	addElement(list, "�������� ������ ����⮢��", 19, "�� ���㦥�");
	addElement(list, "��㬮� ����� ��������", 31, "�����");
	addElement(list, "����஢ ����� ���������", 24, "�� �����");
	addElement(list, "��������� ������� ���ᮢ��", 24, "���㦥�");
	addElement(list, "��ਬ�� ������ ����஢��", 43, "�� �����");
	saveListToFile(list, filename);}