package cn.tju.tiei;

import static org.junit.Assert.*;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class CalculatorTest {
	
	private Calculator cal;
	
	@BeforeClass
	public static void testBeforeClass() {
//		System.out.println("Test BeforeClass");
	}
	
	@AfterClass
	public static void testAfterClass() {
//		System.out.println("Test AfterClass");
	}
	
	@Before
	public void setUp() {
		cal = new Calculator();
//		System.out.println("Test Before");
	}
	
	@Test
	public void testAdd() {
		assertEquals(2, cal.add(1,  1));
//		System.out.println("Test Add");
	}
	
	@Test
	public void testMinus() {
		assertEquals(2, cal.minus(5, 3));
//		System.out.println("Test Minus");
	}
	
	@Test(expected = ArithmeticException.class)
	public void testDivede() {
		int result;
		result = cal.divide(6, 0);
//		assertEquals(2, result);
	}
	
	/*@Test(timeout=500)
	public void testTime() {
		try {
			Thread.sleep(500);
			
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}*/
	
	@After
	public void testDown() {
//		System.out.println("Test After");
	}
}
