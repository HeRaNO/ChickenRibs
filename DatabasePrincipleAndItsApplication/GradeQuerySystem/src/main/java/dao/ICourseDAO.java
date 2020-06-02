package dao;

import model.Course;

public interface ICourseDAO {
	Course findCourseByID(Integer CID);
}
