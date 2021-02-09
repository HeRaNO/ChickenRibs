import java.io.*;
import java.util.*;

class Grade {
	private int gradeID;
	private String courseID;
	private String teacherID;
	private int maxSize;
	private int studentCounter;
	private pair[] grade;

	Grade(int _gid, String _cid, String _tid, int _maxSize) {
		gradeID = _gid;
		teacherID = _tid;
		courseID = _cid;
		maxSize = _maxSize;
		grade = new pair [maxSize];
		studentCounter = 0;
	}

	int getGradeID() {
		return gradeID;
	}

	String getCourseID() {
		return courseID;
	}

	String getTeacherID() {
		return teacherID;
	}

	int getStuCounter() {
		return studentCounter;
	}

	pair getStuGra(int x) {
		return grade[x];
	}

	String getCourseName(CourseController cou) {
		return cou.getNameByID(courseID);
	}

	double calculateAvg() {
		if (studentCounter == 0)
			return -1;
		int sum = 0;
		for (int i = 0; i < studentCounter; i++)
			sum += grade[i].score;
		return (double)sum / studentCounter;
	}

	void sort() {
		for (int i = 0; i < studentCounter - 1; i++) {
			int mn = i;
			for (int j = i + 1; j < studentCounter; j++)
				if (grade[j].compareTo(grade[mn]) < 0)
					mn = j;
			if (mn != i)
				grade[mn].swap(grade[i]);
		}
		return ;
	}

	void getScore(String id, String name) {
		for (int i = 0; i < studentCounter; i++)
			if (grade[i].id.equals(id) && grade[i].name.equals(name)) {
				System.out.println("Student ID: " + id + "\tName: " + name + "\tScore: " + grade[i].score);
				return ;
			}
		System.out.println("Student ID: " + id + "\tName: " + name + "\tNot found");
		return ;
	}

	void regScore(String id, String name, int sc) {
		if (studentCounter == maxSize) {
			System.err.println("Score info overflow.");
			return ;
		}
		grade[studentCounter] = new pair(id, name, sc);
		studentCounter++;
		return ;
	}

	void regScore(String id, String name) {
		Scanner in = new Scanner(System.in);
		if (studentCounter == maxSize) {
			System.err.println("Score info overflow.");
			return ;
		}
		System.out.print("Pls input the score: ");
		int sc = in.nextInt();
		grade[studentCounter] = new pair(id, name, sc);
		studentCounter++;
		return ;
	}

	void exportInfo(CourseController cou, TeacherController tch) {
		if (studentCounter == 0) {
			System.err.println("No grade info.");
			return ;
		}
		sort();
		Course c = cou.getCourseDetail(courseID);
		if (!c.getCourseID().equals(courseID)) {
			System.err.println("Internal error at searching course info.");
			return ;
		}
		Teacher t = tch.getTeacherDetail(teacherID);
		if (!t.getID().equals(teacherID)) {
			System.err.println("Internal error at searching teacher info.");
			return ;
		}
		String fileName = courseID + "-" + getCourseName(cou) + "-GradeTable.txt";
		System.out.println("Export grade table to: " + fileName);
		try {
			FileOutputStream out = new FileOutputStream(new File(fileName));
			OutputStreamWriter osw = new OutputStreamWriter(out, "UTF-8");
			BufferedWriter bw = new BufferedWriter(osw);
			bw.write("Course ID: " + c.getCourseID() + "\tTeacher Name: " + t.getName() + "\n");
			bw.write("Course name: " + c.getCourseName() + "\tClass hour: " + c.getHour() + "\tCredit: " + c.getCredit() + "\n");
			bw.write("No.\tStu. ID\tScore\tNo.\tStu. ID\tScore\n");
			int x = studentCounter; x >>= 1;
			if (studentCounter % 2 == 1) ++x;
			for (int i = 0; i < x; i++) {
				bw.write(i + 1 + "\t" + grade[i].id + "\t" + grade[i].score);
				if (i + x == studentCounter) {
					bw.write("\n");
					break;
				}
				bw.write("\t");
				bw.write(i + x + 1 + "\t" + grade[i + x].id + "\t" + grade[i + x].score + "\n");
			}
			bw.write("Sum of student: " + studentCounter + "\tAverage Score: " + calculateAvg() + "\tTeacher sign:\tRegister date:\n");
			bw.close();
			osw.close();
			out.close();
		}
		catch (IOException e) {
			System.err.println("Meet a exception when export student info.");
			e.printStackTrace();
		}
		System.out.println("Export grade table finished successfully.");
		return ;
	}
}
