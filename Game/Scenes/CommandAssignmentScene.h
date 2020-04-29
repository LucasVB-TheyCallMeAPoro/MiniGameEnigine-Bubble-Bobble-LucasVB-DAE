#pragma once
#include <GameScene.h>
namespace LVB
{
	class CommandAssignmentScene : public GameScene
	{
	public:
		CommandAssignmentScene();
	
		CommandAssignmentScene(const CommandAssignmentScene& other) = delete;
		CommandAssignmentScene(CommandAssignmentScene&& other) noexcept = delete;
		CommandAssignmentScene& operator=(const CommandAssignmentScene& other) = delete;
		CommandAssignmentScene& operator=(CommandAssignmentScene&& other) noexcept = delete;

	protected:
		void Initialize() override;
		void Update(float) override;
		void Render() override;
	};
}

