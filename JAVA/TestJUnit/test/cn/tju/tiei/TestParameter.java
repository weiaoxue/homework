package cn.tju.tiei;

import static org.junit.Assert.*;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

@RunWith(Parameterized.class)
public class TestParameter {

	private int input1;
	private int input2;
	private int result;
	private Calculator cal;
	
	@Before
	public void setUp() {
		cal = new Calculator();
	}
	
	public TestParameter(int input1, int input2, int result) {
		this.input1 = input1;
		this.input2 = input2;
		this.result = result;
	}
	
	@Parameters
	public static Collection<Object[]> getData() {
		return Arrays.asList(new Object[][] {
			{1, 1, 2},
			{2, 1, 3},
			{3, 5, 8}
		});
	}
	
	@Test
	public void testAdd() {
		assertEquals(this.result, cal.add(this.input1, this.input2));
	}

}
