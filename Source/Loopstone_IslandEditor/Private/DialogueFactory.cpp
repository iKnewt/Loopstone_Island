#include "DialogueFactory.h"
#include "Dialogue/Dialogue.h"

#define LOCTEXT_NAMESPACE "DialogueFactory"

UDialogueFactory::UDialogueFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UDialogue::StaticClass();
}

UObject* UDialogueFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UObject>(InParent, InClass, InName, Flags | RF_Transactional);
}	

FText UDialogueFactory::GetDisplayName() const
{
	return LOCTEXT("FactoryName", "Dialogue");
}

FString UDialogueFactory::GetDefaultNewAssetName() const
{
	return "Dialogue";
}

#undef LOCTEXT_NAMESPACE