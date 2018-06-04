var ws;
var mtr1;

function setConnected(connected) {
	$("#connect").prop("disabled", connected);
	$("#disconnect").prop("disabled", !connected);
}

function connect() {
	ws = new WebSocket('ws://127.0.0.1:8080/ws');
	ws.onmessage = function(data) {
		helloWorld(data.data);
	}
	setConnected(true);
}

function disconnect() {
	if (ws != null) {
		ws.close();
	}
	setConnected(false);
	console.log("Websocket is in disconnected state");
}

function sendData(data) {
	ws.send(data);
}

function helloWorld(message) {
//	$("#helloworldmessage").append("<tr><td> " + message + "</td></tr>");
}
//
//$(function() {
//	$("form").on('submit', function(e) {
//		e.preventDefault();
//	});
//	$("#connect").click(function() {
//		connect();
//	});
//	$("#disconnect").click(function() {
//		disconnect();
//	});
//	$("#mtr1").click(function() {
//			 sendData("1");
//	});
//
//	$("#mtr11").click(function() {
//			 sendData("2");
//	});
//
//	$("#mtr2").mousedown(function() {
//		
//		 mtr1= setInterval(function(){
//
//			 sendData();
//			 console.log("on2");
//		    }, 105);
//		
//	});
//
//	$("#mtr22").mousedown(function() {
//		
//		 mtr1= setInterval(function(){
//
//			 sendData();
//			 console.log("on22");
//		    }, 105);
//		
//	});
//
//	
//	$("#mtr3").mousedown(function() {
//		
//		 mtr1= setInterval(function(){
//
//			 sendData();
//			 console.log("on3");
//		    }, 105);
//		
//	});
//
//});
