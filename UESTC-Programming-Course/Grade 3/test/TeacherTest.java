class TeacherTest {
	public static void main(String[] args) {
		GradeController gra = new GradeController();
		CourseController cou = new CourseController();
		TeacherController tch = new TeacherController();
		StudentController stu = new StudentController();
/*
		tch.addStudentTest(stu);
		tch.delStudentTest(stu);
		tch.modStudentTest(stu);

		tch.addCourseTest(stu);
		tch.delCourseTest(stu);
		tch.modCourseTest(stu);

		tch.queryScoreTest(cou, gra);*/
		tch.regScoreTest(cou, gra);
	}
}