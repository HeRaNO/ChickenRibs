import java.util.*;

public class StringTrim {
	public static void main(String[] args) {
		String str;
		Scanner in = new Scanner(System.in);
		str = in.nextLine();
		int st = 0;
		int ed = str.length() - 1;
		for (; ed >= 0; ed--)
			if (str.charAt(ed) != ' ')
				break;
		for (; st < str.length(); st++)
			if (str.charAt(st) != ' ')
				break;
		String strAfterTrim = str.substring(st, ed + 1);
		System.out.println(strAfterTrim);
	}
}