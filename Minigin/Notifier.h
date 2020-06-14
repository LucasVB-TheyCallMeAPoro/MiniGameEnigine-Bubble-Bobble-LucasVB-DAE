#pragma once
#include <vector>
#include "Listener.h"
namespace LVB
{

	template <typename ... Args>
	class Notifier
	{
	public:
		void AddListener(Listener<Args...>* listener);
		void RemoveListener(Listener<Args...>* listener);

		//Unpack operator ==> args is de verzameling van alle parameters
		void Notify(Args ... args) const;
	private:
		std::vector<Listener<Args...>*> m_Listeners;
	};

	template<typename ...Args>
	inline void Notifier<Args...>::AddListener(Listener<Args...>* listener)
	{
		m_Listeners.push_back(listener);
	}
	template<typename ...Args>
	inline void Notifier<Args...>::RemoveListener(Listener<Args...>* listener)
	{
		auto it = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
		*it = m_Listeners.back();
		m_Listeners.pop_back();
	}
	template<typename ...Args>
	inline void Notifier<Args...>::Notify(Args ...args) const
	{
		for (std::size_t i{ 0 }; i < m_Listeners.size(); ++i)
		{
			m_Listeners[i]->OnNotify(args...);
		}
	}
}
