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
	HasTape,
	HasRope,
	HasKnife,
	None
};

UENUM(BlueprintType)
enum class ETopic : uint8
{
	PartyPlanner,
	Tape,
	Rope,
	Knife,
	None
};

UENUM(BlueprintType)
enum class EBackgroundColor : uint8
{
	Color1,
	Color2,
	Color3,
	Color4,
	Color5,
	Color6
};