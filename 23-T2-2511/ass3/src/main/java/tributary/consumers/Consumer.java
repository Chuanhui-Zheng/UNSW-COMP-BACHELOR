package tributary.consumers;

import java.util.ArrayList;

public class Consumer {

	private String id;
	private final ArrayList<String> partitions = new ArrayList<>();

	public Consumer(String id){
		this.id = id;
	}

	public void consume(String partitionID){
		this.partitions.add(partitionID);
	}
	public void remove(String partitionID){
		this.partitions.remove(partitionID);
	}

	public String getID(){
		return this.id;
	}
	//show consumer
	public void show(){
		for(String partition:partitions){
			System.out.print(partition+" ");
		}
		System.out.println();
	}
}
