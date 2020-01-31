#include "Loopstone_IslandEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
// #include "Loopstone_IslandEditor/Public/Loopstone_IslandEditor.h"

IMPLEMENT_GAME_MODULE(FLoopstone_IslandEditorModule, Loopstone_IslandEditor);

DEFINE_LOG_CATEGORY(Loopstone_IslandEditor)

#define LOCTEXT_NAMESPACE "Loopstone_IslandEditor"

void FLoopstone_IslandEditorModule::StartupModule()
{
	UE_LOG(Loopstone_IslandEditor, Warning, TEXT("Loopstone_IslandEditor: Log Started"));
}

void FLoopstone_IslandEditorModule::ShutdownModule()
{
	UE_LOG(Loopstone_IslandEditor, Warning, TEXT("Loopstone_IslandEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE