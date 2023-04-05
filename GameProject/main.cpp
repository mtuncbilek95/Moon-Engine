#include <Application/ApplicationModule.h>
#include <FileSystem/FileSystem.h>

int main()
{
	Moon::FileSystem::GetInstance().SetProjectTarget("D:\\Moon-Engine\\");

	Moon::ApplicationModule* App = new Moon::ApplicationModule({800,800});

	App->StartApplication();
	App->LoopApplication();

	return 0;
}