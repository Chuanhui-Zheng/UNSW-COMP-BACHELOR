package tributary.producer;

import org.json.JSONObject;
import tributary.message.Message;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Producer {
	private String id;
	private String type;
	private String allocation;
	private final String currentWorkingDir = System.getProperty("user.dir");
	private final String dirPath = currentWorkingDir + File.separator + "src" + File.separator+ "main"+File.separator+"resources"+File.separator;

	public Producer(String id, String type, String allocation){
		this.id = id;
		this.type = type;
		this.allocation = allocation;
	}

	//create a message from json file
	public Message create(String filename){
		try {
			String jsonString = new String(Files.readAllBytes(Paths.get(dirPath+filename)));
			JSONObject jsonObject = new JSONObject(jsonString);
			String type = jsonObject.getString("payloadType");
			String time = jsonObject.getString("createdTime");
			String id = jsonObject.getString("id");
			String key = jsonObject.getString("key");
			switch (type){
				case "int":
				case "Integer":
					return new Message<>(time, id, type, key, jsonObject.getInt("content"));
				case "String":
					return new Message(time, id, type, key, jsonObject.getString("content"));
				default:
					System.out.println("Only 'int' and 'String' supported currently.");
			}
		}catch (Exception e){
			e.printStackTrace();
		}
		return null;
	}
}
