package tributary.cluster;

import tributary.message.Message;

import java.util.LinkedList;
import java.util.Queue;

public class Partition {
	private String id;
	private Queue<Message> messages = new LinkedList<>();

	public Partition(String id){
		this.id = id;
	}
	public void addMessage(Message message){
		this.messages.offer(message);
	}
	public Message consumeMessage(){
		return this.messages.poll();
	}
	public void show(){
		for(Message message:messages){
			System.out.print(message.getId()+" ");
		}
		System.out.println();
	}
	public String getId(){
		return this.id;
	}
}
