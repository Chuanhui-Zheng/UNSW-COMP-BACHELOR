package tributary;

import cli.CLI;
import org.junit.jupiter.api.Test;

import java.io.*;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TributaryTest {

	@Test
	void creationTest(){
		String userInput = "create topic t1 int\n" +
				"create partition t1 p1\n" +
				"create consumer group g1 t1 Range\n" +
				"create consumer g1 c1\n" +
				"create producer p1 int manual\n" +
				"q\n";
		String expectedOutput = "Enter your command(enter q to quit): Topic t1 created, type = int" + System.lineSeparator() +
				"Enter your command(enter q to quit): Partition p1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Group g1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Consumer c1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Producer p1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit):";
		assert commonTest(userInput, expectedOutput);
	}
	@Test
	void showTest(){
		String userInput = "create topic t1 int\n" +
				"create partition t1 p1\n" +
				"create consumer group g1 t1 Range\n" +
				"create consumer g1 c1\n" +
				"create producer p1 int manual\n" +
				"show topic t1\n" +
				"show consumer group g1\n" +
				"q\n";
		String expectedOutput = "Enter your command(enter q to quit): Topic t1 created, type = int" + System.lineSeparator() +
				"Enter your command(enter q to quit): Partition p1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Group g1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Consumer c1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Producer p1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): partition p1:" + System.lineSeparator() +
				"Enter your command(enter q to quit): consumer c1:" + System.lineSeparator() +
				"Enter your command(enter q to quit):";
		assert commonTest(userInput, expectedOutput);
	}
	@Test
	void integrationTest(){
		String userInput = "create topic t1 int\n" +
				"create partition t1 p1\n" +
				"create consumer group g1 t1 Range\n" +
				"create consumer g1 c1\n" +
				"create producer p1 int manual\n" +
				"produce event p1 t1 message1.json p1\n" +
				"show topic t1\n" +
				"consume event c1 p1\n" +
				"show consumer group g1\n" +
				"show topic t1\n" +
				"q\n";
		String expectedOutput = "Enter your command(enter q to quit): Topic t1 created, type = int" + System.lineSeparator() +
				"Enter your command(enter q to quit): Partition p1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Group g1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Consumer c1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Producer p1 created." + System.lineSeparator() +
				"Enter your command(enter q to quit): Event 001 created in partition p1" + System.lineSeparator() +
				"Enter your command(enter q to quit): partition p1:001 " + System.lineSeparator() +
				"Enter your command(enter q to quit): Event ID is 001, the content is 123456." + System.lineSeparator() +
				"Enter your command(enter q to quit): consumer c1:p1 " + System.lineSeparator() +
				"Enter your command(enter q to quit): partition p1:" + System.lineSeparator() +
				"Enter your command(enter q to quit):";
		assert commonTest(userInput, expectedOutput);
	}

	boolean commonTest(String userInput, String expectedOutput) {
		InputStream originalSystemIn = System.in;
		PrintStream originalSystemOut = System.out;
		ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
		System.setOut(new PrintStream(outputStream));
		InputStream inputStream = new ByteArrayInputStream(userInput.getBytes());
		System.setIn(inputStream);
		CLI cli = new CLI();
		cli.run();
		System.setIn(originalSystemIn);
		System.setOut(originalSystemOut);
		String projectOutput = outputStream.toString().trim();
		return projectOutput.equals(expectedOutput);
	}
}
