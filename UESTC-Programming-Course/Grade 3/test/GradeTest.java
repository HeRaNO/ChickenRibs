class GradeTest {
	public static void main(String[] args) {
		GradeController gra = new GradeController();
		CourseController cou = new CourseController();
		TeacherController tch = new TeacherController();
		StudentController stu = new StudentController();
/*
		gra.calculateAvg("1");
		gra.calculateAvg("2");
		gra.calculateAvg("3");
*/
		gra.printGradeInfo(cou, tch, "1");
		gra.printGradeInfo(cou, tch, "2");
		gra.printGradeInfo(cou, tch, "3");
	}
}