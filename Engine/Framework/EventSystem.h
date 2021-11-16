#pragma once
#include "Framework/System.h"
#include <string>
#include <functional>
#include <map>
#include <list>
#include <variant>
namespace smile
{
	class Object;

	struct Event
	{
		std::string name;
		Object* reciever{ nullptr };
		std::variant<int, bool, float, std::string, void*> data;
	};

	class EventSystem : public System
	{
	public:
		using function_t = std::function<void(const Event&)>;
	
		

		// Inherited via System
		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;

		void Subscribe(const std::string& name, function_t function, Object* reciever = nullptr);
		void Unsubscribe(const std::string& name, Object* reciever);
		void Notify(const Event& event);

		private:
		
			struct Observer
			{
				function_t function;
				Object* reciever;
			};

		private:
			std::map <std::string, std::list<Observer>> observers;


	};
}