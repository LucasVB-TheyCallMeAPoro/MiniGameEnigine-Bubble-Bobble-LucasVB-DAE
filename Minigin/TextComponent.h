#pragma once
#include "Transform.h"
#include <SDL.h>
namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		void Update(float elapsed) override;
		void Render() const override;
		void Initialize() override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent() override;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		Texture2D* m_Texture;
		SDL_Color m_Color;
	};
}
