import java.io.*;
import java.util.*;

class GradeController {
	private final int _maxSize = 10;

	private int maxSize;
	private int counter;
	private int idCounter;
	private Grade[] g;

	GradeController() {
		boolean fromFile = true;
		try {
			FileInputStream ins = new FileInputStream("gradeDB");
			InputStreamReader isr = new InputStreamReader(ins, "UTF-8");
			BufferedReader br = new BufferedReader(isr);
			System.out.println("Initializing from gradeDB...");
			String l = br.readLine();
			String[] arg = l.split(",");
			counter = Integer.parseInt(arg[0]);
			idCounter = Integer.parseInt(arg[1]);
			if (counter == 0)
				maxSize = _maxSize;
			else
				maxSize = counter << 1;
			g = new Grade[maxSize];
			for (int i = 0; i < counter; i++) {
				l = br.readLine();
				arg = l.split(",");
				g[i] = new Grade(Integer.parseInt(arg[0]), arg[1], arg[2], Integer.parseInt(arg[3]) << 1);
				int stuC = Integer.parseInt(arg[3]);
				for (int j = 0; j < stuC; j++) {
					l = br.readLine();
					arg = l.split(",");
					g[i].regScore(arg[0], arg[1], Integer.parseInt(arg[2]));
				}
			}
			br.close();
			isr.close();
			ins.close();
		}
		catch (IOException e) {
			System.out.println("gradeDB not found...");
			fromFile = false;
		}
		catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("gradeDB is broken.");
			fromFile = false;
		}
		catch (NumberFormatException e) {
			System.out.println("gradeDB is broken.");
			fromFile = false;
		}
		catch (NullPointerException e) {
			System.out.println("gradeDB is broken.");
			fromFile = false;
		}
		if (!fromFile) {
			System.out.println("Initializing by default way...");
			maxSize = _maxSize;
			counter = 0;
			idCounter = 1;
			g = new Grade[maxSize];
		}
		System.out.println("Initialize grade finished.");
	}

	int getPosByName(CourseController cou, String c) {
		if (c.equals("$")) {
			System.out.println("Invalid name.");
			return -1;
		}
		for (int i = 0; i < counter; i++)
			if (g[i].getCourseName(cou).equals(c))
				return i;
		return -1;
	}

	int getPosByID(String c) {
		for (int i = 0; i < counter; i++)
			if (g[i].getCourseID().equals(c))
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
			FileOutputStream out = new FileOutputStream(new File("gradeDB"));
			OutputStreamWriter osw = new OutputStreamWriter(out, "UTF-8");
			BufferedWriter bw = new BufferedWriter(osw);
			bw.write(counter + "," + idCounter + "\n");
			for (int i = 0; i < counter; i++) {
				bw.write(g[i].getGradeID() + ",");
				bw.write(g[i].getCourseID() + ",");
				bw.write(g[i].getTeacherID() + ",");
				bw.write(g[i].getStuCounter() + "\n");
				int x = g[i].getStuCounter();
				for (int j = 0; j < x; j++) {
					pair t = g[i].getStuGra(j);
					bw.write(t.id + ",");
					bw.write(t.name + ",");
					bw.write(t.score + "\n");
				}
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

	int addGradeTable() {
		if (counter == maxSize) {
			maxSize <<= 1;
			Grade[] ng = new Grade[maxSize];
			for (int i = 0; i < counter; i++)
				ng[i] = g[i];
			g = ng;
		}
		String id = getInfoItem("course ID");
		if (getPosByID(id) != -1) {
			System.err.println("Already has this course.");
			return -1;
		}
		String tid = getInfoItem("teacher id");
		String st = getInfoItem("student number");
		g[counter] = new Grade(idCounter, id, tid, Integer.parseInt(st));
		counter++;
		idCounter++;
		System.out.println("Add grade info successfully.");
		flush();
		return counter - 1;
	}

	void calculateAvg(String gid) {
		int x = getPosByID(gid);
		if (x == -1) {
			System.err.println("Course ID: " + gid + " Not found");
			return ;
		}
		double ret = g[x].calculateAvg();
		if (ret == -1)
			System.err.println("Course ID: " + gid + " No grade info");
		else
			System.out.println("Course ID: " + gid + " avg = " + ret);
		return ;
	}

	void sort(String gid) {
		int x = getPosByID(gid);
		if (x == -1) {
			System.err.println("Course ID: " + gid + " Not found");
			return ;
		}
		g[x].sort();
		return ;
	}

	void queryScore(int x, String id, String name) {
		g[x].getScore(id, name);
		return ;
	}

	void addScore(int x, String id, String name) {
		g[x].regScore(id, name);
		flush();
		return ;
	}

	void printGradeInfo(CourseController cou, TeacherController tch, String gid) {
		int x = getPosByID(gid);
		if (x == -1) {
			System.err.println("Course ID: " + gid + " Not found");
			return ;
		}
		g[x].exportInfo(cou, tch);
		return ;
	}
}