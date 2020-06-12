#pragma once

namespace LVB
{
	template <typename ... Args>
	class Notifier;
	template <typename ... Args>
	class Listener
	{
	private:
		friend Notifier<Args...>;
		virtual void OnNotify(Args... args) = 0;
	};
}