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
    if(data.name == "button_state"){
      GameShow.handleButtonState(data.data); 
    }
    
  },

  socketOnOpen: function(ev){
    // console.log("WS Connected");
    GameShow.websocket.send("get_buttons");
    GameShow.websocket.send("get_lamps");
    //ask server for switch/lamp/coil information
  },

  handleGetButtonsResponses: function(button_data){
    ret = "";
    $.each(button_data, function(idx, data){
      if(data.col == 0){
        ret += "<tr>";
      }
      ret += "<td class='button' data-num='"+data.num+"'>"+data.name+"</td>";
      if(data.col == 7){
        ret += "</tr>";
      }
    })
    $("table.buttons").html(ret);
  },

  handleButtonState: function(button_data){
    var tmp = $("td.button[data-num="+button_data.num+"]");
    if(tmp.length != 0){
      if(button_data.state == 0){
        tmp.removeClass("buttonPressed");
      }else{
        tmp.addClass("buttonPressed");
      }
    }
  }
}