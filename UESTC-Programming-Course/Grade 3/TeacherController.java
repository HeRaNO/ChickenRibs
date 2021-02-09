import java.io.*;
import java.util.*;

class TeacherController {
	private final int _maxSize = 10;

	private int maxSize;
	private int counter;
	private Teacher[] tch;

	TeacherController() {
		boolean fromFile = true;
		try {
			FileInputStream ins = new FileInputStream("teacherDB");
			InputStreamReader isr = new InputStreamReader(ins, "UTF-8");
			BufferedReader br = new BufferedReader(isr);
			System.out.println("Initializing from teacherDB...");
			String l = br.readLine();
			counter = Integer.parseInt(l);
			if (counter == 0)
				maxSize = _maxSize;
			else
				maxSize = counter << 1;
			tch = new Teacher[maxSize];
			for (int i = 0; i < counter; i++) {
				l = br.readLine();
				String[] arg = l.split(",");
				tch[i] = new Teacher(arg[0], arg[1], arg[2]);
			}
			for (int i = 0; i < counter; i++) {
				tch[i].showDetail();
			}
			br.close();
			isr.close();
			ins.close();
		}
		catch (IOException e) {
			System.out.println("teacherDB not found...");
			fromFile = false;
		}
		catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("teacherDB is broken.");
			fromFile = false;
		}
		catch (NullPointerException e) {
			System.out.println("teacherDB is broken.");
			fromFile = false;
		}
		if (!fromFile) {
			System.out.println("Initializing by default way...");
			maxSize = _maxSize;
			tch = new Teacher[maxSize];
			counter = 0;
		}
		System.out.println("Initialize teacher finished.");
	}

	Teacher getTeacherDetail(String id) {
		for (int i = 0; i < counter; i++)
			if (tch[i].getID().equals(id))
				return tch[i];
		return new Teacher("", "", "");
	}

	void addStudentTest(StudentController stu) {
		tch[0].addStudent(stu);
		return ;
	}

	void addCourseTest(CourseController cou) {
		tch[0].addCourse(cou);
		return ;
	}

	void delStudentTest(StudentController stu) {
		tch[0].deleteStudent(stu);
		return ;
	}

	void delCourseTest(CourseController cou) {
		tch[0].deleteCourse(cou);
		return ;
	}

	void modStudentTest(StudentController stu) {
		tch[0].modifyStudent(stu);
		return ;
	}

	void modCourseTest(CourseController cou) {
		tch[0].modifyCourse(cou);
		return ;
	}

	void queryScoreTest(CourseController cou, GradeController gra) {
		tch[0].queryScore(cou, gra);
		return ;
	}

	void regScoreTest(CourseController cou, GradeController gra) {
		tch[0].regScore(cou, gra);
		return ;
	}

	void flush() {
		try {
			FileOutputStream out = new FileOutputStream(new File("teacherDB"));
			OutputStreamWriter osw = new OutputStreamWriter(out, "UTF-8");
			BufferedWriter bw = new BufferedWriter(osw);
			bw.write(counter + "\n");
			for (int i = 0; i < counter; i++) {
				bw.write(tch[i].getID() + ",");
				bw.write(tch[i].getName() + ",");
				bw.write(tch[i].getCollege() + "\n");
			}
			bw.close();
			osw.close();
			out.close();
		}
		catch (IOException e) {
			System.err.println("Meet a exception when export student info.");
			e.printStackTrace();
		}
		System.out.println("flush finished successfully.");
		return ;
	}
}