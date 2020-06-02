import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.Reader;

public class SQL {
	private static final SqlSessionFactory Factory;
	static {
		SqlSessionFactory factory = null;
		try {
			String res = "MyBatis-Config.xml";
			Reader reader = Resources.getResourceAsReader(res);
			factory = new SqlSessionFactoryBuilder().build(reader);
		} catch (Exception e) {
			System.err.println(e);
		}
		Factory = factory;
	}
	public static SqlSession NewSession() {
		return Factory.openSession();
	}
}
