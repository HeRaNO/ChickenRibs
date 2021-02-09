import java.io.*;
import java.util.*;

class StudentController {
	private final int _maxSize = 10;

	private int maxSize;
	private int counter;
	private Student[] stu;

	StudentController() {
		boolean fromFile = true;
		try {
			FileInputStream ins = new FileInputStream("studentDB");
			InputStreamReader isr = new InputStreamReader(ins, "UTF-8");
			BufferedReader br = new BufferedReader(isr);
			System.out.println("Initializing from studentDB...");
			String l = br.readLine();
			counter = Integer.parseInt(l);
			if (counter == 0)
				maxSize = _maxSize;
			else
				maxSize = counter << 1;
			stu = new Student[maxSize];
			for (int i = 0; i < counter; i++) {
				l = br.readLine();
				String[] arg = l.split(",");
				stu[i] = new Student(arg[0], arg[1], arg[2].equals("Male") ? 0 : 1, new GregorianCalendar(Integer.parseInt(arg[3]), Integer.parseInt(arg[4]), Integer.parseInt(arg[5])), arg[6], arg[7]);
			}
			for (int i = 0; i < counter; i++) {
				stu[i].showDetail();
			}
			br.close();
			isr.close();
			ins.close();
		}
		catch (IOException e) {
			System.out.println("studentDB not found...");
			fromFile = false;
		}
		catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("studentDB is broken.");
			fromFile = false;
		}
		catch (NullPointerException e) {
			System.out.println("studentDB is broken.");
			fromFile = false;
		}
		if (!fromFile) {
			System.out.println("Initializing by default way...");
			maxSize = _maxSize;
			counter = 0;
			stu = new Student[maxSize];
		}
		System.out.println("Initialize student finished.");
	}

	int getStuPosByID(String id) {
		for (int i = 0; i < counter; i++)
			if (stu[i].getID().equals(id))
				return i;
		return -1;
	}

	int getStuPosByName(String name) {
		for (int i = 0; i < counter; i++)
			if (stu[i].getName().equals(name))
				return i;
		return -1;
	}

	String getInfoItem(String it) {
		Scanner in = new Scanner(System.in);
		System.out.print("Input " + it + ": ");
		String ret = in.nextLine();
		return ret;
	}

	void flush() {
		try {
			FileOutputStream out = new FileOutputStream(new File("studentDB"));
			OutputStreamWriter osw = new OutputStreamWriter(out, "UTF-8");
			BufferedWriter bw = new BufferedWriter(osw);
			bw.write(counter + "\n");
			for (int i = 0; i < counter; i++) {
				bw.write(stu[i].getID() + ",");
				bw.write(stu[i].getName() + ",");
				bw.write(stu[i].getSex() + ",");
				GregorianCalendar c = stu[i].getBirthday();
				bw.write(c.get(Calendar.YEAR) + "," + c.get(Calendar.MONTH) + "," + c.get(Calendar.DATE) + ",");
				bw.write(stu[i].getCollege() + ",");
				bw.write(stu[i].getMajor() + "\n");
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

	void addInfo() {
		if (counter == maxSize) {
			maxSize <<= 1;
			Student[] nstu = new Student[maxSize];
			for (int i = 0; i < counter; i++)
				nstu[i] = stu[i];
			stu = nstu;
		}
		String id = getInfoItem("student ID");
		if (getStuPosByID(id) != -1) {
			System.err.println("ID already existed.");
			return ;
		}
		String name = getInfoItem("name");
		int s;
		while (true) {
			String sex = getInfoItem("sex (Male or Female)");
			if (!sex.equals("Male") && !sex.equals("Female"))
				System.err.println("Invalid sex.");
			else {
				if (sex.equals("Male"))
					s = 0;
				else
					s = 1;
				break;
			}
		}
		String ret = getInfoItem("birth year");
		int y = Integer.parseInt(ret);
		ret = getInfoItem("birth month");
		int m = Integer.parseInt(ret);
		ret = getInfoItem("birth date");
		int d = Integer.parseInt(ret);
		GregorianCalendar birth = new GregorianCalendar(y, m, d);
		String co = getInfoItem("college");
		String ma = getInfoItem("major");
		stu[counter] = new Student(id, name, s, birth, co, ma);
		System.out.println("Add info successfully.");
		stu[counter].showDetail();
		counter++;
		flush();
		return ;
	}

	void deleteInfo(int x) {
		stu[x].showDetail();
		System.out.println("This item is going to delete, pls confirm (Y/N)");
		String ret = getInfoItem("");
		if (!ret.equals("Y")) {
			System.out.println("Cancelled.");
			return ;
		}
		for (int i = x + 1; i < counter; i++)
			stu[i - 1] = stu[i];
		counter--;
		System.out.println("Delete info successfully.");
		flush();
		return ;
	}

	void modifyInfo(int x) {
		while (true) {
			System.out.println("Now info:");
			stu[x].showDetail();
			System.out.println("1. Student ID");
			System.out.println("2. Name");
			System.out.println("3. Sex");
			System.out.println("4. Birthday");
			System.out.println("5. College");
			System.out.println("6. Major");
			System.out.println("0. Exit");
			System.out.println("Select the info you want to modify");
			int opt = Integer.parseInt(getInfoItem("Your choice"));
			if (opt < 0 || opt > 6) {
				System.err.println("Invalid option.");
				continue;
			}
			if (opt == 0) {
				System.out.println("Modify info successfully.");
				flush();
				break;
			}
			if (opt == 1)
				stu[x].setID(getInfoItem("student ID"));
			else if (opt == 2)
				stu[x].setName(getInfoItem("name"));
			else if (opt == 3) {
				String nsex = getInfoItem("sex (Male or Female)");
				if (nsex.equals("Male") || nsex.equals("Female"))
					stu[x].setSex(nsex);
				else
					System.err.println("Invalid sex.");
				return ;
			}
			else if (opt == 4) {
				String ret = getInfoItem("birth year");
				int y = Integer.parseInt(ret);
				ret = getInfoItem("birth month");
				int m = Integer.parseInt(ret);
				ret = getInfoItem("birth date");
				int d = Integer.parseInt(ret);
				stu[x].setBirthday(y, m, d);
			}
			else if (opt == 5)
				stu[x].setCollege(getInfoItem("college"));
			else if (opt == 6)
				stu[x].setMajor(getInfoItem("major"));
		}
	}

	void getScore(GradeController gra, CourseController cou) {
		String name = getInfoItem("your name");
		int x = getStuPosByName(name);
		if (x == -1) {
			System.err.println("No such student. name: " + name);
			return ;
		}
		String id = getInfoItem("your student ID");
		if (!stu[x].getID().equals(id)) {
			System.err.println("No such student. name: " + name + " ID: " + id);
			return ;
		}
		String cname = getInfoItem("which course you want to query");
		stu[x].getScore(gra, cou, cname);
		return ;
	}
}