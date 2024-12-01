package tributary;

import tributary.cluster.Partition;
import tributary.cluster.Topic;
import tributary.consumers.Consumer;
import tributary.consumers.Group;
import tributary.message.Message;
import tributary.producer.Producer;

import java.util.HashMap;
import java.util.Map;

public class Tributary {
	private final Map<String, Topic> topics = new HashMap<>();
	private final Map<String, Group> groups = new HashMap<>();
	private final Map<String, Producer> producers = new HashMap<>();
	//analyze the command
	public void handleInput(String[] inputs){
		switch (inputs[0]){
			case "create":
				switch (inputs[1]){
					case "topic":
						createTopic(inputs[2], inputs[3]);
						break;
					case "partition":
						createPartition(inputs[2], inputs[3]);
						break;
					case "consumer":
						if(inputs[2].equals("group")){
							createGroup(inputs[3], inputs[4], inputs[5]);
						}else {
							createConsumer(inputs[2], inputs[3]);
						}
						break;
					case "producer":
						createProducer(inputs[2], inputs[3], inputs[4]);
						break;
					default:
						System.out.println("incorrect input");
						break;
				}
				break;
			case "delete":
				if(inputs[1].equals("consumer")){
					deleteConsumer(inputs[2]);
				}
				else System.out.println("incorrect input");
				break;
			case "produce":
				produceEvent(inputs[2], inputs[3], inputs[4], inputs[5]);
				break;
			case "consume":
				switch (inputs[1]){
					case "event":
						consumeEvent(inputs[2], inputs[3]);
						break;
					case "events":
						consumeEvents(inputs[2], inputs[3], Integer.parseInt(inputs[4]));
						break;
				}
				break;
			case "show":
				switch (inputs[1]){
					case "topic":
						showTopic(inputs[2]);
						break;
					case "consumer":
						showGroup(inputs[3]);
						break;
				}
				break;
			default:
				System.out.println("incorrect input");
				break;
		}
	}
	//add a topic to topics
	private void addTopic(String id, Topic topic){
		if(this.topics.containsKey(id)) System.out.println("Topic already exists.");
		else this.topics.put(id, topic);
	}
	//add a group to groups
	private void addGroup(String id, Group group){
		if(this.groups.containsKey(id)) System.out.println("Group already exists.");
		else this.groups.put(id, group);
	}
	//add a producer to producers
	private void addProducer(String id, Producer producer){
		if(this.producers.containsKey(id)) System.out.println("Producer already exists.");
		else this.producers.put(id, producer);
	}
	//create a topic
	private void createTopic(String id, String type){
		Topic topic = new Topic(id, type);
		this.addTopic(id, topic);
		System.out.println("Topic " + id + " created, type = " + type);
	}
	//create a partition
	private void createPartition(String topic, String id){
		Partition partition = new Partition(id);
		Topic curTopic = this.topics.get(topic);
		curTopic.addPartition(id, partition);
		System.out.println("Partition "+id+" created.");
	}
	//create a group
	private void createGroup(String id, String topic, String rebalancing){
		Group group = new Group(id, topic, rebalancing);
		this.addGroup(id, group);
		System.out.println("Group "+id+" created.");
	}
	//create a consumer
	private void createConsumer(String group, String id){
		Group curGroup = this.groups.get(group);
		Consumer consumer = new Consumer(id);
		curGroup.addConsumer(id, consumer);
		System.out.println("Consumer "+id+" created.");
	}
	//delete a consumer
	private void deleteConsumer(String consumer){
		for(Group group:this.groups.values()){
			if(group.hasMem(consumer)){
				group.removeConsumer(consumer);
				return;
			}
		}
		System.out.println("Consumer not existed.");
	}
	//create a producer
	private void createProducer(String id, String type, String allocation){
		Producer producer = new Producer(id, type, allocation);
		this.addProducer(id, producer);
		System.out.println("Producer "+id+" created.");
	}
	//produce an event
	private void produceEvent(String producerID, String topic, String event, String partition){
		Producer producer = this.producers.get(producerID);
		Message message = producer.create(event);
		Topic topic1 = this.topics.get(topic);
		topic1.addMessage(partition, message);
		System.out.println("Event "+message.getId()+" created in partition "+partition);
	}
	//consume an event
	private void consumeEvent(String consumer, String partition){
		for(Group group:groups.values()){
			if(group.hasMem(consumer)){
				group.getConsumer(consumer).consume(partition);
				String topicID = group.getTopic();
				Topic topic = this.topics.get(topicID);
				Message message = topic.consume(partition);
				System.out.println("Event ID is "+message.getId()+", the content is "+message.getContent()+".");
			}
		}
	}
	//consume an event
	private void consumeEvents(String consumer, String partition, int num){
		for(int i=0;i<num;i++) this.consumeEvent(consumer, partition);
	}
	//show topics
	private void showTopic(String topic){
		this.topics.get(topic).show();
	}
	//show groups
	private void showGroup(String group){
		this.groups.get(group).show();
	}
}
