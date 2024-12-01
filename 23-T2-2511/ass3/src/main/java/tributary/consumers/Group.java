package tributary.consumers;

import java.util.HashMap;
import java.util.Map;

public class Group {
	private String id;
	private String topic;
	private String rebalancing;
	private Map<String, Consumer> consumers = new HashMap<>();

	public Group(String id, String topic, String rebalancing){
		this.id = id;
		this.topic = topic;
		this.rebalancing = rebalancing;
	}
	public void addConsumer(String id, Consumer consumer){
		if(consumers.containsKey(id)){
			System.out.println("Consumer already exists.");
		}else {
			consumers.put(id, consumer);
		}
	}
	public void removeConsumer(String id){
		this.consumers.remove(id);
		System.out.println("Consumer "+id+" deleted.");
	}
	public boolean hasMem(String id){
		return this.consumers.containsKey(id);
	}
	//show group
	public void show(){
		for(Consumer consumer:consumers.values()){
			System.out.print("consumer "+consumer.getID()+":");
			consumer.show();
		}
	}
	public String getTopic(){
		return this.topic;
	}
	public Consumer getConsumer(String id){
		return this.consumers.get(id);
	}
}
