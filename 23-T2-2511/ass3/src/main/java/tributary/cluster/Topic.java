package tributary.cluster;

import tributary.message.Message;

import java.util.HashMap;
import java.util.Map;

public class Topic {
	private String id;
	private String type;
	private Map<String, Partition> partitions = new HashMap<>();

	public Topic(String id, String type){
		this.id = id;
		this.type = type;
	}
	public void addPartition(String id, Partition partition){
		if(partitions.containsKey(id)) System.out.println("Partition already exists.");
		else partitions.put(id, partition);
	}
	public void addMessage(String partitionID, Message message){
		Partition partition = this.partitions.get(partitionID);
		partition.addMessage(message);
	}
	public Message consume(String partitionID){
		Partition partition = this.partitions.get(partitionID);
		return partition.consumeMessage();
	}
	public void show(){
		for(Partition partition:partitions.values()){
			System.out.print("partition "+partition.getId()+":");
			partition.show();
		}
	}
}
