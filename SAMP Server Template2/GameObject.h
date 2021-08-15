#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"

namespace SAMP_SDK {
	//Game object should be a generic base type in wich all of the objects inherrit from
	//It should have the bare minimum of controlls and should not be acessed directly
	class GameObject {
	private:
	protected:
		Array<Component*> a_c_OwnedComponents;

#pragma region Callback pointers
		Array<Delegate*> a_del_OnStart;
		Array<Delegate*> a_del_OnEnable;
		Array<Delegate*> a_del_OnDisable;
		Array<Delegate*> a_del_OnTick;
#pragma endregion

	public:
		GameObject();




		template <class T> T* AddComponent();
	};

}




template<class T>
inline T* SAMP_SDK::GameObject::AddComponent()
{
	T* gen_Component = new T();
	this->a_c_OwnedComponents.Add(T);
	T->go_OwnedBy = this;
	T->RegisterCallbacks();
	return NULL;
}
#endif