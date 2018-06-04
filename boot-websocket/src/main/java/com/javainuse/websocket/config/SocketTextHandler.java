package com.javainuse.websocket.config;

import java.io.IOException;

import org.json.JSONObject;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

@Component
public class SocketTextHandler extends TextWebSocketHandler {

	static WebSocketSession session;

	@Override
	public void handleTextMessage(WebSocketSession session, TextMessage message)
			throws InterruptedException, IOException {
		SocketTextHandler.session = session;	
		String payload = message.getPayload();
//		JSONObject jsonObject = new JSONObject(payload);
//		System.out.println(jsonObject.get("user").toString());
		sendMessages(payload);

	}

	public static void sendMessages(String payload) {
		System.out.println(payload);
		
		try {
			session.sendMessage(new TextMessage(payload));
//			if (payload.equals("1")) {
//				session.sendMessage(new TextMessage("1"));
//			} else if (payload.equals("2")) {
//				session.sendMessage(new TextMessage("2"));
//			} else if (payload.equals("3")) {
//				session.sendMessage(new TextMessage("3"));
//			} else if (payload.equals("4")) {
//				session.sendMessage(new TextMessage("4"));
//			}else if(payload.equals("5")) {
//				session.sendMessage(new TextMessage("5"));
//			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


}