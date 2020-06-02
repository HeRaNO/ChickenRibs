package model;

import java.util.List;

public class Course {
	private int CID;
	private String CName;
	private String Teacher;
	private List<Grade> Grades;

	public int getID() {
		return CID;
	}

	public void setID(int C) {
		CID = C;
	}

	public String getCName() {
		return CName;
	}

	public void setName(String name) {
		CName = name;
	}

	public String getTeacher() {
		return Teacher;
	}

	public void setTeacher(String t) {
		Teacher = t;
	}

	public List<Grade> getGrades() {
		return Grades;
	}

	public void setGrades(List<Grade> grades) {
		Grades = grades;
	}
}
