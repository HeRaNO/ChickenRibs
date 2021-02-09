public class pair implements Comparable {
	public String id;
	public String name;
	public int score;
	pair(String a, String b, int c){
		id = a;
		name = b;
		score = c;
	}
	public int compareTo(Object o) {
		pair to = (pair)o;
		if (this.score > to.score) return -1;
		else if (this.score == to.score) return id.compareTo(to.id);
		else return 1;
	}
	void swap(pair o) {
		String t = o.id;
		o.id = id;
		id = t;
		t = o.name;
		o.name = name;
		name = t;
		int td = o.score;
		o.score = score;
		score = td;
		return ;
	}
}
