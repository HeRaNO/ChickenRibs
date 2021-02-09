class StudentTest {
	public static void main(String[] args) {
		GradeController gra = new GradeController();
		CourseController cou = new CourseController();
		TeacherController tch = new TeacherController();
		StudentController stu = new StudentController();

		stu.getScore(gra, cou);
	}
}