#ifndef GAMEMODE_H
#define GAMEMODE_H


namespace SAMP_SDK {
	//This is the contained of everything in the current session
	//In here you spawn vehicles, players and other objects
	//Also here is where you handle the weather.
	//All of the interaction should be taken place from this object.
	class GameMode {
	private:
		Array<GameObject*> a_go_ActiveObjects;
		Array<Player*> a_ply_ActivePlayers;

	protected:
	public:

	};
}
#endif