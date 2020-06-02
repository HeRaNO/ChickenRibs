import dao.IGradeDAO;
import dao.IStudentDAO;
import model.Grade;
import model.Student;
import org.apache.ibatis.session.SqlSession;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(urlPatterns = {"/query"}, name = "query")
public class GradeQueryServlet extends HttpServlet {
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
		String idString = request.getParameter("student_id");
		int id = Integer.parseInt(idString);

		SqlSession session = SQL.NewSession();
		System.err.println("Connect ok");
		IStudentDAO studentDAO = session.getMapper(IStudentDAO.class);
		Student student = studentDAO.findByID(id);

		IGradeDAO gradeDAO = session.getMapper(IGradeDAO.class);

		response.setContentType("text/plain");

		PrintWriter writer = response.getWriter();
		writer.println(String.format("Name: %s, ID: %d, Age: %d, Sex: %s",
				student.getSName(), student.getSID(), student.getAge(), student.getSex()));
		for (Grade each : gradeDAO.findGradeByStudentID(student.getSID())) {
			writer.println(String.format("CourseName: %s, Teacher: %s, Grade: %d, Note: %s",
						each.getCourse().getCName(), each.getCourse().getTeacher(), each.getScore(), each.getNote()));
		}
	}
}
