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
	None
};

UENUM(BlueprintType)
enum class EEventType : uint8
{
	HasRope,
	None
};

UENUM(BlueprintType)
enum class ETopic : uint8
{
	Tape,
	Rope,
	PartyPlanner,
	None
};


