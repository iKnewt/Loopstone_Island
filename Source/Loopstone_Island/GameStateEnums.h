#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"


UENUM(BlueprintType)
enum class ETimeOfDay : uint8
{
	Morning,
	Afternoon,
	Evening,
	Night,
	None
};

UENUM(BlueprintType)
enum class EStory : uint8
{
	PartyPlanner,
	AssistantChef,
	Detective,
	None
};

// UENUM(BlueprintType)
// enum class EEventType : uint8
// {
// 	HasTape,
// 	HasRope,
// 	HasKnife,
// 	HasLighthouseKey,
// 	HasMachine,
// 	TutorialCompleted,
// 	None
// };
//
// UENUM(BlueprintType)
// enum class ETopic : uint8
// {
// 	PartyPlanner,
// 	Tape,
// 	Rope,
// 	Knife,
// 	FarmerTalkedAboutInnkeeper,
// 	TalkedToFarmerAboutNoise,
// 	TalkedToDoctorAboutNoise,
// 	TalkedToMotherAboutNoise,
// 	TalkedToChildAboutNoise,
// 	TalkedToSBAboutNoise,
// 	HeardFarmersOpinionOnDoctor,
// 	None
// };

UENUM(BlueprintType)
enum class EIslanderType : uint8
{
	SB,
	Child,
	Mother,
	Farmer,
	Innkeeper,
	Doctor,
	None
};