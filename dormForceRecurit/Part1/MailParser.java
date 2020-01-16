import java.io.*;
import java.util.*;

public class MailParser {
	public static void main(String[] args) throws Exception {
		if (args.length != 1) {
			System.err.println("Needs only one argument.");
			return ;
		}
		String name = args[0];
		File file = new File("a.html");
		BufferedWriter wr = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("newfile.html"), "UTF-8"));
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));
		String line = null;
		try {
			while ((line = br.readLine()) != null) {
				line = line.replaceAll("reg_Name", name);
				wr.append(line);
				wr.append(System.getProperty("line.separator"));
			}
		}
		catch (IOException e) {
			System.out.println("Exception thrown: " + e);
			return ;
		}
		br.close();
		wr.close();
		wr = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("mail.txt"), "UTF-8"));
		wr.append(name + "注册成功！");
		wr.append(System.getProperty("line.separator"));
		wr.close();
	}
}