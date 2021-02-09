class Course {
	private String courseID;
	private String name;
	private double credit;
	private int hours;

	Course(String _cid, String _name, double _credit, int _hours) {
		courseID = _cid;
		name = _name;
		credit = _credit;
		hours = _hours;
	}

	String getCourseID() {
		return courseID;
	}

	String getCourseName() {
		return name;
	}

	int getHour() {
		return hours;
	}

	double getCredit() {
		return credit;
	}

	void setCourseID(String _id) {
		courseID = _id;
	}

	void setName(String _name) {
		name = _name;
	}

	void setCredit(double a) {
		credit = a;
	}

	void setHours(int h) {
		hours = h;
	}

	void showDetail() {
		System.out.println("-------------------------------------------------");
		System.out.println("Course ID: " + courseID);
		System.out.println("Name: " + name);
		System.out.println("Credits: " + credit);
		System.out.println("Class hours: " + hours);
		System.out.println("-------------------------------------------------");
		return ;
	}
}
