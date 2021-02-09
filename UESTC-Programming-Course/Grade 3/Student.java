import java.util.*;

class Student {
	private String studentID;
	private String name;
	private int sex;
	private GregorianCalendar birthday;
	private String college;
	private String major;
	private final String[] _Sex = { "Male", "Female" };

	Student(String _sid, String _name, int _sex, GregorianCalendar _birthday, String _college, String _major) {
		studentID = _sid;
		name = _name;
		sex = _sex;
		birthday = _birthday;
		college = _college;
		major = _major;
	}

	String getID() {
		return studentID;
	}

	String getName() {
		return name;
	}

	GregorianCalendar getBirthday() {
		return birthday;
	}

	String getSex() {
		return _Sex[sex];
	}

	String getCollege() {
		return college;
	}

	String getMajor() {
		return major;
	}

	void setID(String _id) {
		studentID = _id;
	}

	void setName(String _name) {
		name = _name;
	}

	void setSex(String _s) {
		if (_s.equals("Male"))
			sex = 0;
		else
			sex = 1;
	}

	void setBirthday(int y, int m, int d) {
		birthday.set(y, m, d);
	}

	void setCollege(String _college) {
		college = _college;
	}

	void setMajor(String _major) {
		major = _major;
	}

	void showDetail() {
		System.out.println("-------------------------------------------------");
		System.out.println("Student ID: " + studentID);
		System.out.println("Name: " + name);
		System.out.println("Sex: " + _Sex[sex]);
		System.out.println("Birthday: " + birthday.get(Calendar.YEAR) + "-" + birthday.get(Calendar.MONTH) + "-" + birthday.get(Calendar.DATE));
		System.out.println("College: " + college);
		System.out.println("Major: " + major);
		System.out.println("-------------------------------------------------");
		return ;
	}

	void getScore(GradeController gra, CourseController cou, String cname) {
		int x = gra.getPosByName(cou, cname);
		if (x == -1) {
			System.err.println("Error: no such course. Name: " + cname);
			return ;
		}
		gra.queryScore(x, studentID, name);
		return ;
	}
}
