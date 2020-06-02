package dao;

import model.Grade;
import java.util.List;

public interface IGradeDAO {
	Grade findGradeByStudentIDAndCourseID(int SID, int CID);
	List<Grade> findGradeByCourseName(String name);
	List<Grade> findGradeByStudentName(String name);
	List<Grade> findGradeByStudentID(Integer SID);
}
