package model;

import java.util.List;

public class Student {
	private int SID;
	private String SName;
	private int Age;
	private String Sex;
	private List<Grade> Grades;

	public int getAge() {
		return Age;
	}

	public String getSex() {
		return Sex;
	}

	public int getSID() {
		return SID;
	}

	public String getSName() {
		return SName;
	}

	public void setAge(int age) {
		Age = age;
	}

	public List<Grade> getGrades() {
		return Grades;
	}

	public void setSex(String sex) {
		Sex = sex;
	}

	public void setSID(int SID) {
		this.SID = SID;
	}

	public void setSName(String SName) {
		this.SName = SName;
	}

	public void setGrades(List<Grade> grades) {
		Grades = grades;
	}
}
