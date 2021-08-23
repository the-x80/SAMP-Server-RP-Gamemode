#ifndef PLAYER_H
#define PLAYER_H

namespace SAMP_SDK {
	class Vehicle;

	class Player : public GameObject {
	private:
		static Array<Player*> a_PlayerPool;//This might be replaced with a PlayerPool class
	protected:
		int n_ID;


	public:
		Player();
		~Player();

		
		

		Vehicle* GetCurrentVehicle();


		static Player* Create(int n_ID);
		/// <summary>
		/// Removes Player ply from the player pool and frees the memory associated with it.
		/// </summary>
		static void Destroy(Player* ply);
	};
}

#endif
