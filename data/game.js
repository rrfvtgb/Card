({
	ready: 0,
	playing: [],
	playerReady: function(player){
		// Do some stuff
	},
	init: function(){
		// print("Hello script!")
		// print(game)
		// print(server)
		// print(card)
		// print(packet)
		// print("Cya!")
		print(packet[1])
	},
	newPlayer: function(p){
		p.becameReady.connect(this.playerReady)
	}
})