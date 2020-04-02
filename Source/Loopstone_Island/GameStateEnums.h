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
	Detective,
	PartyPlanner,
	AssistantChef,
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
UENUM(BlueprintType)
enum class EAnimations : uint8
{
	Idle,
	HandsBehindBack,
	HandsTogether,
	Happy,
	HeadTilt,
	Lazy,
	Ready,
	Sad,
	Shocked,
	Thinking,
	Angry,
	CustomIdle1,
	CustomIdle2,
	Walk,
	CustomAnimation1,
	CustomAnimation2,
	CustomAnimation3,
	CustomAnimation4,
	CustomAnimation5,
	CustomAnimation6,
	CustomAnimation7,
	CustomAnimation8,
	CustomAnimation9,
	CustomAnimation10

};