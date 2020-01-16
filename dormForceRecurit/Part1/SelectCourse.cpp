// Just a framework, can't work
#include <set>

class Course {
	int id;
	// Something else
	void showCourse() {
		// Do something
	}
}

class Student {
	std::set <Course> cou;
	// Something else
}

void selectCourse(Student &a, Course &c) {
	a.cou.insert(c);
}

void deleteCourse(Student &a, Course &c) {
	std::set <Course> :: iterator it;
	it = a.cou.find(c);
	if (it != a.cou.end())
		a.cou.erase(it);
	return ;
}

void showCourseSelected(Student &a) {
	std::set <Course> :: iterator it = a.cou.begin();
	for (; it != a.cou.end(); it++)
		showCourse(it);
	return ;
}

void modifyCourse(Student &a, Course &del, Course &nadd) {
	deleteCourse(a, del);
	selectCourse(a, nadd);
	return ;
}
