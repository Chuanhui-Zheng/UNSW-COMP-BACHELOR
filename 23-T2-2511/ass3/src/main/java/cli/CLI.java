package cli;


import tributary.Tributary;

import java.util.Scanner;

public class CLI {

	public static void main(String[] args) {
		new CLI().run();
	}
	public void run() {
		Scanner scanner = new Scanner(System.in);
		Tributary tributary = new Tributary();
		//keep reading the cmd line instruction until meet 'q'
		while (true) {
			System.out.print("Enter your command(enter q to quit): ");
			String input = scanner.nextLine();
			if(input.equals("q")) break;
			String[] inputs = input.split(" ");
			tributary.handleInput(inputs);
		}
	}

}
