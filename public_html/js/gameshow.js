GameShow = {
  websocket: null,
  lamp_states: ["lamp_off","lamp_on","lamp_flash_slow", "lamp_flash_fast"],
  startup: function(){
     GameShow.websocket = new WebSocket("ws://"+location.host+"/ws");
     GameShow.websocket.onopen = GameShow.socketOnOpen;
     GameShow.websocket.onmessage = GameShow.socketOnMessage;
     GameShow.websocket.onclose = function(ev) {console.log(ev);}
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
    if(data.name == "get_lamps"){
      GameShow.handleGetLampsResponses(data.data);
    }
    if(data.name == "lamp_state"){
      GameShow.handleLampState(data.data); 
    }
    if(data.name == "get_coils"){
      GameShow.handleGetCoils(data.data); 
    }
    if(data.name == "coil_state"){
      GameShow.handleCoilState(data.data); 
    }
    
  },

  socketOnOpen: function(ev){
    // console.log("WS Connected");
    var data = JSON.stringify({message: "get_buttons"});
    GameShow.websocket.send(data);

    data = JSON.stringify({message: "get_lamps"});
    GameShow.websocket.send(data);

    data = JSON.stringify({message: "get_coils"});
    GameShow.websocket.send(data);
    // GameShow.websocket.send("get_lamps");
    // GameShow.websocket.send("get_buttons");
    //ask server for switch/lamp/coil information
  },

  handleGetButtonsResponses: function(button_data){
    ret = "";
    $.each(button_data, function(idx, data){
      if(data.col == 0){
        ret += "<tr>";
      }
      state = "";
      if(data.state == 1){
        state = "buttonPressed";
      }
      ret += "<td class='button "+state+"' data-num='"+data.num+"'>"+data.name+"</td>";
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
  },

  handleLampState: function(lamp_data){
    var tmp = $("td.lamp[data-num="+lamp_data.num+"]");
    if(tmp.length != 0){
      $.each(GameShow.lamp_states, function(idx, e){
        tmp.removeClass(e);
      });
      tmp.addClass(GameShow.lamp_states[lamp_data.state]);
      tmp.find("option").removeAttr("selected");
      tmp.find("select").val(GameShow.lamp_states[lamp_data.state]);
      // tmp.find("option[value="+GameShow.lamp_states[lamp_data.state]+"]").attr("selected", "selected");

    }
  },


  handleGetLampsResponses: function(button_data){
    var ret = "";
    $.each(button_data, function(idx, data){
      if(data.col == 0){
        ret += "<tr>";
      }
      var tmpCombo = $("div.hidden_lamp_combo").clone();
      tmpCombo.find("option[value="+GameShow.lamp_states[data.state]+"]").attr("selected", "selected");
      ret += "<td class='lamp "+GameShow.lamp_states[data.state]+"' data-num='"+data.num+"' data-name='"+data.name+"'>";
      ret += data.name + "<br>" + tmpCombo.html();
      ret += "</td>";
      if(data.col == 7){
        ret += "</tr>";
      }
    })
    $("table.lamps").html(ret);
    $("select.lamp_state").change(function(event){
      var name = $(this).parent().attr("data-name");
      var data = {message: "set_lamp_state", 
        name: name,
        value: GameShow.lamp_states.indexOf($(this).val())
      }
      GameShow.websocket.send(JSON.stringify(data));
    });
  },

  handleGetCoils: function(coil_data){
    var tmp = "";
    $.each(coil_data, function(idx, data){
      var state = "";
      if(data.state == 1){
        state = "coil_on";
      }
      tmp += "<tr><td class='coil "+state+"' data-name='"+data.name+"' data-num='"+data.num+"'>"+data.name+"</td></tr>"
    });
    $("table.coils").html(tmp);
    $("td.coil").click(function(){
      var val = 1;
      if($(this).hasClass("coil_on")){
        val = 0;
      }
      var name = $(this).attr("data-name");
      var data = {message: "set_coil_state", 
        name: name,
        value: val}
      GameShow.websocket.send(JSON.stringify(data));
    })
  },

  handleCoilState: function(coil_data){
    var tmp = $("td.coil[data-num="+coil_data.num+"]");
    if(tmp.length != 0){
      if(coil_data.state == 0){
        tmp.removeClass("coil_on");
      }else{
        tmp.addClass("coil_on");
      }
    }
  }

}