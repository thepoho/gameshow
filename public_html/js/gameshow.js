GameShow = {
  websocket: null,
  startup: function(){
     GameShow.websocket = new WebSocket("ws://"+location.host+"/ws");
     GameShow.websocket.onopen = GameShow.socketOnOpen;
     GameShow.websocket.onmessage = GameShow.socketOnMessage;
  },

  socketOnMessage: function(ev){
    // console.log("GOT WS DATA");
    console.log("WS response: "+ev.data);
    // console.log(ev);

    var data = $.parseJSON(ev.data);
    if(data.name == "get_buttons"){
      GameShow.handleGetButtonsResponses(data.data);
      
    }
    
  },

  socketOnOpen: function(ev){
    // console.log("WS Connected");
    GameShow.websocket.send("get_buttons");
    //ask server for switch/lamp/coil information
  },

  handleGetButtonsResponses: function(button_data){
    ret = "";
    $.each(button_data, function(idx, data){
      if(data.col == 0){
        ret += "<tr>";
      }
      ret += "<td>"+data.name+"</td>";
      if(data.col == 7){
        ret += "</tr>";
      }
    })
    $("table.buttons").html(ret);
  }
}