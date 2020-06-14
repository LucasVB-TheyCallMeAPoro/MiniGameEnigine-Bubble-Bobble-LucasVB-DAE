#include "Button.h"
#include	"Transform.h"
Button::Button(int width, int height, std::function<void()>&& callback)
	:m_Width{width}
	,m_Height{height}
	,m_Callback{std::move(callback)}
{
}


void Button::SetWidthAndHeight(int w, int h)
{
	m_Width = w;
	m_Height = h;
}

void Button::HandleClick(int mouseX, int mouseY)
{
	if (mouseX >= this->GetTransform()->GetPosition().x && mouseX <= this->GetTransform()->GetPosition().x + m_Width && mouseY >= this->GetTransform()->GetPosition().y && mouseY <= this->GetTransform()->GetPosition().y +m_Height)
	{
		m_Callback();
	}
}

void Button::Render() const
{
}

void Button::Update(float elapsedSec)
{
}
