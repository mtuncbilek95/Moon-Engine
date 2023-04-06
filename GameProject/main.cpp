#include <Application/ApplicationModule.h>
#include <FileSystem/FileSystem.h>

#include <World/SceneManager.h>

#include <GameProject/Scene/BlankScene.h>

int main()
{
	Moon::FileSystem::GetInstance().SetProjectTarget("D:\\Projects\\Moon-Engine\\");

	Moon::SceneManager::GetInstance().AddNewScene(new BlankScene());

	Moon::ApplicationModule* App = new Moon::ApplicationModule({800,800});

	App->StartApplication();
	App->LoopApplication();

	return 0;
}