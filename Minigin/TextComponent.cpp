#include "MiniginPCH.h"

#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
LVB::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font) 
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr) , m_Color{ 255,255,255 }
{ }

LVB::TextComponent::~TextComponent()
{
	if (m_Texture != nullptr)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}
}

void LVB::TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		delete m_Texture;
		m_Texture = new Texture2D{ texture};
		SDL_FreeSurface(surf);
		m_NeedsUpdate = false;
	}
}

void LVB::TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = GetGameObject()->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void LVB::TextComponent::Initialize()
{
}

// This implementation uses the "dirty flag" pattern
void LVB::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void LVB::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}


