package dao;

import model.Student;

public interface IStudentDAO {
	Student findByID(int SID);
}
