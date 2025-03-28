package edu.zut.newmath.tests;

import edu.zut.newmath.Circle;
import org.junit.Test;

import static org.junit.Assert.*;

public class CircleTests {

	@Test
	public void testCircum() {
		assertEquals(12.56, Circle.circumference(2), 0.01);
	}

}
