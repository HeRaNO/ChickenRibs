import java.util.*;

public class Calculate {
	public static void main(String[] args) {
		Triangle a = new Triangle(3.0, 4.0);
		System.out.println(a.getArea());
		Pillar b = new Pillar(a, 5.0);
		System.out.println(b.getVolumn());
		Rectangle c = new Rectangle(3.0, 4.0);
		System.out.println(c.getArea());
		Pillar d = new Pillar(c, 5.0);
		System.out.println(d.getVolumn());
	}
}

abstract class Shape {
	protected double dim1, dim2;
	Shape(double _dim1, double _dim2) {
		dim1 = _dim1;
		dim2 = _dim2;
	}
	abstract double getArea();
}

class Triangle extends Shape {
	Triangle(double _dim1, double _dim2) {
		super(_dim1, _dim2);
	}
	double getArea() {
		return dim1 * dim2 * 0.5;
	}
}

class Rectangle extends Shape {
	Rectangle(double _dim1, double _dim2) {
		super(_dim1, _dim2);
	}
	double getArea() {
		return dim1 * dim2;
	}
}

class Pillar {
	private Shape bottom;
	private double h;
	Pillar(Shape _bottom, double _h) {
		bottom = _bottom;
		h = _h;
	}
	double getVolumn() {
		return bottom.getArea() * h;
	}
}