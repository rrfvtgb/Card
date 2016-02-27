({
	ready: 0,
	playing: [],
	playerReady: function(player){
		// Do some stuff
		if(this.playing.indexOf(player) != -1){
			server.log(player.name + " is ready")
		}else if(player){
			server.log(player.name + " ready but not playing");
			
			for(var i=0; i<this.playing.length; i++){
				server.log(player.name+" "+this.playing[i].name+" "+(player==this.playing[i]));
			}
		}
	},
	init: function(){
		server.log("Init script!")
	},
	handleEvent:function(target){ // Handle event, may add some extra arguments
		var game = this;
		var extra = [];
		
		for(var i=1; i<arguments.length; i++){
			extra[i-1] = arguments[i];
		}
		
		if(!(target instanceof Function)){
			target = game[target];
		}
		
		return (function(){
			var x = extra;
			
			for(var i=0; i<arguments.length; i++){
				x[i+extra.length] = arguments[i];
			}
			
			target.apply(game, x);
		});
	},
	newPlayer: function(p){
		var players = server.players;
		var size = players.size;
		
		p.becameReady.connect(this.handleEvent("playerReady", p))
		
		if(size == 2){
			server.log("2 player detected!")
			
			for(var i in players){
				if(!isNaN(i)){
					this.playing.push(players[i]);
					server.log("- "+players[i].name)
				}
			}
			
			p.ready = false;
		}else if(size < 2){
			server.log("Waiting for "+(2-size)+" player(s)")
		}
	}
})