import java.util.*;

class Teacher {
	private String teacherID;
	private String name;
	private String college;

	Teacher(String _tid, String _name, String _college) {
		teacherID = _tid;
		name = _name;
		college = _college;
	}

	String getID() {
		return teacherID;
	}

	String getName() {
		return name;
	}

	String getCollege() {
		return college;
	}

	String getInfoItem(String it) {
		Scanner in = new Scanner(System.in);
		System.out.print("Input " + it + ": ");
		String ret = in.nextLine();
		return ret;
	}

	int searchStudent(StudentController stu) {
		System.out.println("1. Student ID");
		System.out.println("2. Name");
		System.out.println("Search student by");
		int opt = Integer.parseInt(getInfoItem("Your choice"));
		String tip;
		if (opt == 1)
			tip = getInfoItem("student ID");
		else
			tip = getInfoItem("name");
		if (opt == 1)
			return stu.getStuPosByID(tip);
		return stu.getStuPosByName(tip);
	}

	int searchCourse(CourseController cou) {
		System.out.println("1. Course ID");
		System.out.println("2. Name");
		System.out.println("Search course by");
		int opt = Integer.parseInt(getInfoItem("your choice"));
		String tip;
		if (opt == 1)
			tip = getInfoItem("course ID");
		else
			tip = getInfoItem("name");
		if (opt == 1)
			return cou.getPosByID(tip);
		return cou.getPosByName(tip);
	}

	int searchGrade(CourseController cou, GradeController gra) {
		System.out.println("1. Course ID");
		System.out.println("2. Name");
		System.out.println("Search course by");
		int opt = Integer.parseInt(getInfoItem("your choice"));
		String tip;
		if (opt == 1)
			tip = getInfoItem("course ID");
		else
			tip = getInfoItem("name");
		if (opt == 1)
			return gra.getPosByID(tip);
		return gra.getPosByName(cou, tip);
	}

	void addStudent(StudentController stu) {
		stu.addInfo();
		return ;
	}

	void deleteStudent(StudentController stu) {
		int x = searchStudent(stu);
		if (x == -1) {
			System.err.println("Student not found.");
			return ;
		}
		stu.deleteInfo(x);
		return ;
	}

	void modifyStudent(StudentController stu) {
		int x = searchStudent(stu);
		if (x == -1) {
			System.err.println("Student not found.");
			return ;
		}
		stu.modifyInfo(x);
		return ;
	}

	void addCourse(CourseController cou) {
		cou.addInfo();
		return ;
	}

	void deleteCourse(CourseController cou) {
		int x = searchCourse(cou);
		if (x == -1) {
			System.err.println("Course not found.");
			return ;
		}
		cou.deleteInfo(x);
		return ;
	}

	void modifyCourse(CourseController cou) {
		int x = searchCourse(cou);
		if (x == -1) {
			System.err.println("Course not found.");
			return ;
		}
		cou.modifyInfo(x);
		return ;
	}

	void queryScore(CourseController cou, GradeController gra) {
		int x = searchGrade(cou, gra);
		if (x == -1) {
			System.err.println("Grade table not found.");
			return ;
		}
		String id = getInfoItem("student ID");
		String name = getInfoItem("name");
		gra.queryScore(x, id, name);
		return ;
	}

	void regScore(CourseController cou, GradeController gra) {
		int x = searchGrade(cou, gra);
		if (x == -1) {
			System.out.println("Haven't had this course yet. Now new this grade table.");
			x = gra.addGradeTable();
		}
		if (x == -1)
			return ;
		String id = getInfoItem("student ID");
		String name = getInfoItem("name");
		gra.addScore(x, id, name);
	}

	void showDetail() {
		System.out.println("-------------------------------------------------");
		System.out.println("Teacher ID: " + teacherID);
		System.out.println("Name: " + name);
		System.out.println("College: " + college);
		System.out.println("-------------------------------------------------");
		return ;
	}
}
