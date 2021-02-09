import java.io.*;
import java.util.*;

class CourseController {
	private final int _maxSize = 10;

	private int maxSize;
	private int counter;
	private Course[] cou;

	CourseController() {
		boolean fromFile = true;
		try {
			FileInputStream ins = new FileInputStream("courseDB");
			InputStreamReader isr = new InputStreamReader(ins, "UTF-8");
			BufferedReader br = new BufferedReader(isr);
			System.out.println("Initializing from courseDB...");
			String l = br.readLine();
			counter = Integer.parseInt(l);
			if (counter == 0)
				maxSize = _maxSize;
			else
				maxSize = counter << 1;
			cou = new Course[maxSize];
			for (int i = 0; i < counter; i++) {
				l = br.readLine();
				String[] arg = l.split(",");
				cou[i] = new Course(arg[0], arg[1], Double.parseDouble(arg[2]), Integer.parseInt(arg[3]));
			}
			for (int i = 0; i < counter; i++) {
				cou[i].showDetail();
			}
			br.close();
			isr.close();
			ins.close();
		}
		catch (IOException e) {
			System.out.println("courseDB not found...");
			fromFile = false;
		}
		catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("courseDB is broken.");
			fromFile = false;
		}
		catch (NumberFormatException e) {
			System.out.println("courseDB is broken.");
			fromFile = false;
		}
		catch (NullPointerException e) {
			System.out.println("courseDB is broken.");
			fromFile = false;
		}
		if (!fromFile) {
			System.out.println("Initializing by default way...");
			maxSize = _maxSize;
			counter = 0;
			cou = new Course[maxSize];
		}
		System.out.println("Initialize course finished.");
	}

	String getNameByID(String id) {
		for (int i = 0; i < counter; i++)
			if (cou[i].getCourseID().equals(id))
				return cou[i].getCourseName();
		return "$";
	}

	int getPosByID(String id) {
		for (int i = 0; i < counter; i++)
			if (cou[i].getCourseID().equals(id))
				return i;
		return -1;
	}

	int getPosByName(String name) {
		if (name.equals("$")) {
			System.err.println("Invalid name.");
			return -1;
		}
		for (int i = 0; i < counter; i++)
			if (cou[i].getCourseName().equals(name))
				return i;
		return -1;
	}

	Course getCourseDetail(String id) {
		for (int i = 0; i < counter; i++)
			if (cou[i].getCourseID().equals(id))
				return cou[i];
		return new Course("", "", 0, 0);
	}

	String getInfoItem(String it) {
		Scanner in = new Scanner(System.in);
		System.out.print("Input " + it + ": ");
		String ret = in.nextLine();
		return ret;
	}

	void flush() {
		try {
			FileOutputStream out = new FileOutputStream(new File("courseDB"));
			OutputStreamWriter osw = new OutputStreamWriter(out, "UTF-8");
			BufferedWriter bw = new BufferedWriter(osw);
			bw.write(counter + "\n");
			for (int i = 0; i < counter; i++) {
				bw.write(cou[i].getCourseID() + ",");
				bw.write(cou[i].getCourseName() + ",");
				bw.write(cou[i].getCredit() + ",");
				bw.write(cou[i].getHour() + "\n");
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
			Course[] ncou = new Course[maxSize];
			for (int i = 0; i < counter; i++)
				ncou[i] = cou[i];
			cou = ncou;
		}
		String id = getInfoItem("course ID");
		if (getPosByID(id) != -1) {
			System.err.println("ID already existed.");
			return ;
		}
		String name = getInfoItem("name");
		String cr = getInfoItem("credits");
		String h = getInfoItem("class hour");
		cou[counter] = new Course(id, name, Double.parseDouble(cr), Integer.parseInt(h));
		System.out.println("Add info successfully.");
		cou[counter].showDetail();
		counter++;
		flush();
		return ;
	}

	void deleteInfo(int x) {
		cou[x].showDetail();
		System.out.println("This item is going to delete, pls confirm (Y/N)");
		String ret = getInfoItem("");
		if (!ret.equals("Y")) {
			System.out.println("Cancelled.");
			return ;
		}
		for (int i = x + 1; i < counter; i++)
			cou[i - 1] = cou[i];
		counter--;
		System.out.println("Delete info successfully.");
		flush();
		return ;
	}

	void modifyInfo(int x) {
		while (true) {
			System.out.println("Now info:");
			cou[x].showDetail();
			System.out.println("1. Course ID");
			System.out.println("2. Name");
			System.out.println("3. Credits");
			System.out.println("4. Class hours");
			System.out.println("0. Exit");
			System.out.println("Select the info you want to modify");
			int opt = Integer.parseInt(getInfoItem("Your choice"));
			if (opt < 0 || opt > 4) {
				System.err.println("Invalid option.");
				continue;
			}
			if (opt == 0) {
				System.out.println("Modify info successfully.");
				flush();
				break;
			}
			if (opt == 1)
				cou[x].setCourseID(getInfoItem("course ID"));
			else if (opt == 2)
				cou[x].setName(getInfoItem("name"));
			else if (opt == 3)
				cou[x].setCredit(Double.parseDouble(getInfoItem("credits")));
			else if (opt == 4)
				cou[x].setHours(Integer.parseInt(getInfoItem("class hours")));
		}
	}
}
