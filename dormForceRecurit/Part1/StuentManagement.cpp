// Simple version...
#include <map>
#include <cstring>
#include <iostream>
#include <algorithm>

class Student {
	std::string id;
	std::string name;
	// Something else...

public:
	Student(){}
	Student(std::string _id, std::string _name):
		id(_id), name(_name){}
	std::string getID() {
		return id;
	}
	std::string getName() {
		return name;
	}
};

std::map<std::string, Student> S;

std::string readID() {
	std::cout << "Pls input the student's id: ";
	std::string id;
	std::cin >> id;
	return id;
}

std::string readName() {
	std::cout << "Pls input the student's name: ";
	std::string name;
	std::cin >> name;
	return name;
}

void add() {
	std::string id = readID();
	std::string name = readName();
	S.insert(std::make_pair(id, Student(id, name)));
	std::cout << "Success" << std::endl;
	return ;
}

void del() {
	std::map <std::string, Student> :: iterator it;
	std::string id = readID();
	it = S.find(id);
	if (it == S.end()) {
		std::cout << "No such student." << std::endl;
		return ;
	}
	std::cout << "Delete this item:\n";
	std::cout << "ID: " << it -> first << '\n';
	std::cout << "Name: " << (it -> second).getName() << '\n';
	std::cout << "Pls confrim (y/n) :";
	std::string t;
	std::cin >> t;
	if (t == "y" || t == "Y") {
		S.erase(it);
		std::cout << "Success" << std::endl;
	} else {
		std::cout << "Canceled" << std::endl;
	}
	return ;
}

void search() {
	std::map <std::string, Student> :: iterator it;
	std::string id = readID();
	it = S.find(id);
	if (it == S.end()) {
		std::cout << "No such student." << std::endl;
		return ;
	}
	Student info = it -> second;
	std::cout << "ID: " << info.getID() << '\n';
	std::cout << "Name: " << info.getName() << std::endl;
	return ;
}

void modify() {
	std::map <std::string, Student> :: iterator it;
	std::string id = readID();
	it = S.find(id);
	if (it == S.end()) {
		std::cout << "No such student." << std::endl;
		return ;
	}
	std::cout << "If you don't want to modify some item, just press enter." << std::endl;
	std::string nid = readID();
	std::string nname = readName();
	if (nid == "") nid = id;
	if (nname == "") nname = (it -> second).getName();
	S.erase(it);
	S.insert(std::make_pair(nid, Student(nid, nname)));
	std::cout << "Success" << std::endl;
	return ;
}

void menu() {
	std::cout << "1. Add a student" << '\n';
	std::cout << "2. Delete a student" << '\n';
	std::cout << "3. Search for a student" << '\n';
	std::cout << "4. Modify info" << '\n';
	std::cout << "0. Exit" << std::endl;
	return ;
}

int main(int argc, char const *argv[]) {
	do {
		menu();
		int opt;
		if (std::cin >> opt) {
			if (!opt) break;
			if (opt == 1) add();
			else if (opt == 2) del();
			else if (opt == 3) search();
			else if (opt == 4) modify();
			else {
				std::cout << "Invalid option." << std::endl;
			}
		}
		else break;
	} while (true);
	return 0;
}