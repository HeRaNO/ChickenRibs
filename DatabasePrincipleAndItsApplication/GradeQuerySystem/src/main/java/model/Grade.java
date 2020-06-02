package model;

public class Grade {
	private GradePK PK;
	private Integer Score;
	private String Note;
	private Student Student;
	private Course Course;

	public Course getCourse() {
		return Course;
	}

	public GradePK getPK() {
		return PK;
	}

	public Integer getScore() {
		return Score;
	}

	public String getNote() {
		return Note;
	}

	public Student getStudent() {
		return Student;
	}

	public void setCourse(Course course) {
		Course = course;
	}

	public void setNote(String note) {
		Note = note;
	}

	public void setPK(GradePK PK) {
		this.PK = PK;
	}

	public void setScore(Integer score) {
		Score = score;
	}

	public void setStudent(Student student) {
		Student = student;
	}
}
