import java.io.*;
import java.util.*;

public class ReadAndSave {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		File f = new File("output.txt");
		FileOutputStream out;
		try {
			out = new FileOutputStream(f);
		}
		catch(IOException e) {
			System.out.println("Cannot create file!");
			return ;
		}
		OutputStreamWriter writer;
		try {
			writer = new OutputStreamWriter(out, "UTF-8");
		}
		catch(IOException e) {
			System.out.println("Cannot create output stream!");
			return ;
		}
		try {
			while (in.hasNext()) {
				String x = in.nextLine();
				writer.append(x);
				writer.append("\n");
			}
			writer.close();
		}
		catch(IOException e) {
			System.out.println("Exception");
		}
	}
}