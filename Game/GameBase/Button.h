#pragma once
#include <functional>
#include "GameObject.h"
class Button : public LVB::GameObject
{
public:
	Button(int width, int height, std::function<void()>&& callback);


	void SetWidthAndHeight(int w, int h);
	void HandleClick(int mouseX, int mouseY);
protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:
	int m_Width;
	int m_Height;

	std::function<void()> m_Callback;
};