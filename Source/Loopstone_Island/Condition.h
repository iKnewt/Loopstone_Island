// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameStateEnums.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Condition.generated.h"

UENUM(BlueprintType)
enum class EConditionListType : uint8
{
	Event,
	Topic,
	None
};

UENUM(BlueprintType)
enum class EEventType : uint8
{
	HasTape,
	HasRope,
	HasKnife,
	HasBoathouseKey,
	HasLighthouseKey,
	HasMachine,
	TutorialCompleted,
	DoctorWalkingAway,
	PartyPlannerCompleted,
	None
};

UENUM(BlueprintType)
enum class ETopic : uint8
{
	PartyPlanner,
	Tape,
	Rope,
	Knife,
	FarmerTalkedAboutInnkeeper,
	TalkedToFarmerAboutNoise,
	TalkedToDoctorAboutNoise,
	TalkedToMotherAboutNoise,
	TalkedToChildAboutNoise,
	TalkedToSBAboutNoise,
	HeardFarmersOpinionOnDoctor,
	TalkedToSBAboutRope,
	AskedChildAboutKey,
	TalkedToChildAboutSBDeath,
	TalkedToMotherAboutSBDeath,
	TalkedToFarmerAboutSBDeath,
	TalkedToInnkeeperAboutSBDeath,
	TalkedToDoctorABoutSBDeath,
	PartyReady,
	TalkedToDoctorAboutFeast,
	TalkedToFarmerAboutFeast,
	CollectedItemForFarmer,
	HelpedFarmerWithFeast,
	TalkedToMotherAboutFeast,
	CollectedItemForMother,
	HelpedMotherWithFeast,
	None
};

USTRUCT()
struct FConditions
{
	GENERATED_BODY()

		// UPROPERTY()
		// TArray<UCondition*> AndConditions;

	UPROPERTY(EditAnywhere)
		EConditionListType ConditionList = EConditionListType::None;

	UPROPERTY(EditAnywhere)
		bool bConditionShouldBeTrueOrFalse = true;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "ConditionList ==  EConditionListType::Event"))
		EEventType Event = EEventType::None;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "ConditionList ==  EConditionListType::Topic"))
		ETopic Topic = ETopic::None;
	
};

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API UCondition : public UObject
{
	GENERATED_BODY()

		// UPROPERTY()
		// TArray<FConditions> AndConditions;
	
	UPROPERTY(EditAnywhere)
		EConditionListType ConditionList = EConditionListType::None;
	
	UPROPERTY(EditAnywhere)
		bool bConditionShouldBeTrueOrFalse = true;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ConditionList ==  EConditionListType::Event"))
		EEventType Event = EEventType::None;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ConditionList ==  EConditionListType::Topic"))
		ETopic Topic = ETopic::None;
	
};

// USTRUCT()
// struct FConditions
// {
// 	GENERATED_BODY()

		// UPROPERTY()
		// TArray<UCondition*> AndConditions;
// };
