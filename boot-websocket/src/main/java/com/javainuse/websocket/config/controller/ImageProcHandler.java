package com.javainuse.websocket.config.controller;

import javax.websocket.server.PathParam;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.javainuse.websocket.config.SocketTextHandler;

@RestController
public class ImageProcHandler {
	
	@GetMapping("move")
	public void getMessage(@RequestParam("eks") String val)
	{
		SocketTextHandler.sendMessages(val);
	}


}
