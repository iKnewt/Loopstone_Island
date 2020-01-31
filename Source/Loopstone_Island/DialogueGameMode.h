// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseIslanderCharacter.h"
#include "PlayerCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DialogueGameMode.generated.h"

UENUM(BlueprintType)
enum class EStory : uint8
{
	Party_Planner,
	Assistant_Chef,
	Child_Caretaker,
};

UENUM(BlueprintType)
enum class EDayTime : uint8
{
	Morning,
	Afternoon,
	Evening,
	Night
};

USTRUCT(BlueprintType)
struct FDialogueEdge
{
	GENERATED_USTRUCT_BODY()

	// Text to display
	UPROPERTY(VisibleAnywhere)
	FString Text;

	// All conditions must be true for this option to show
	UPROPERTY(VisibleAnywhere)
	TArray<bool> Conditions;

	FDialogueEdge()
	{
	}
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_USTRUCT_BODY()

	// What Islander is talking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueSystem")
	EIslanderType IslanderType;

	// Text to display
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueSystem")
	FText Text;

	// All conditions must be true for this dialogue to show
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueSystem")
	TArray<bool> Conditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueSystem")
	EEyeExpression EyeExpression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueSystem")
	EMouthExpression MouthExpression;
	//
	// UPROPERTY(EditAnywhere, Category = "DialogueSystem")
	// 	FDialogueNode NextDialogueNode;
	//
	// 	

	FDialogueNode()
	{
	}
};

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API ADialogueGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "DialogueSystem")
	APlayerCharacter* PlayerCharacter = nullptr;

	UPROPERTY(EditAnywhere, Category = "DialogueSystem")
	TArray<FDialogueNode> DialogueNodes;

	// UPROPERTY(EditAnywhere, Category = "DialogueSystem")
	TArray<FDialogueNode*> DialogueNodePtrs;

	UPROPERTY(EditAnywhere, Category = "DialogueSystem")
	TArray<bool> DialogueNodeTest;

	// UPROPERTY(VisibleAnywhere, Category = "DialogueSystem")
	// FDialogueNode* DialogueNode = nullptr;

public:

	/** What is the Player's current musical skill level? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerMusicSkill)
	int32 MusicSkillLevel;

	UFUNCTION(BlueprintCallable)
	void AddNodeToThing(FDialogueNode DigNodIn)
	{
	}

	UFUNCTION(BlueprintCallable)
	void Dialogue(FDialogueNode DigNodIn)
	{
	}


	// UFUNCTION(BlueprintCallable)
	// FDialogueNode* AddNubbers(FDialogueNode duggityindo)
	// {
	// DialogueNodes.Add(duggityindo);
	//
	// DialogueNodePtrs.Add(new FDialogueNode(duggityindo));
	// return DialogueNodePtrs.Last();
	//
	// // return DialogueNodes.Last()*;
	// return nullptr;
	// }

	// UFUNCTION(BlueprintCallable)
	// 	bool AddNubbers(FDialogueNode duggityindo)
	// {
	// DialogueNodes.Add(duggityindo);
	//
	// DialogueNodePtrs.Add(new FDialogueNode(duggityindo));
	// return DialogueNodePtrs.Last();
	//
	// // return DialogueNodes.Last()*;
	// 	return true;
	// }

	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DialogueSystem")
	// TArray<FDialogueNode> DialogueNodes2;
};
