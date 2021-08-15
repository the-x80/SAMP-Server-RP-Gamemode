#ifndef COMPONENT_H
#define COMPONENT_H



namespace SAMP_SDK {
	class GameObject;

	//This is the base class of all components.
	//It is used to extend the functionality of the GameObject class and its derrivatives
	class Component {
	private:
		char* cstr_Name;

		/// <summary>
		/// Specifies weather the Component is enabled and weather the GameObject calls the registered 
		/// messages.
		/// </summary>
		bool b_Enabled;

		/// <summary>
		/// References the owner of this component.
		/// </summary>
		GameObject* go_OwnedBy;
	public:



		char* GetName();
		void SetName(char* name);

		virtual void RegisterCallbacks();
	};
}

#endif
