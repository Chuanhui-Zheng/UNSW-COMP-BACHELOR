package tributary.message;

public class Message<T> {
	private String createdTime;
	private String id;
	private String payloadType;
	private String key;
	private T content;

	public String getId() {
		return id;
	}
	public T getContent() {
		return content;
	}

	public Message(String createdTime, String id, String payloadType, String key, T content){
		this.createdTime = createdTime;
		this.id = id;
		this.payloadType = payloadType;
		this.key = key;
		this.content = content;
	}


}
