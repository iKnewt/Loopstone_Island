// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableObjectBase.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/AudioComponent.h"
#include "Systems/Loopstone_IslandGameState.h"

//Sets default values
AInteractableObjectBase::AInteractableObjectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ObjectMesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneRoot"));
	Mesh->AttachTo(RootComponent);
	Sound = CreateDefaultSubobject<UAudioComponent>(FName("Audio"));
	Sound->AttachTo(RootComponent);
}

void AInteractableObjectBase::VisualizeInteraction(bool bActivate)
{
	if (!IsValid(Material))
	{
		CreateDynamicMaterial();
	}
	Material->SetScalarParameterValue("Glow", int(bActivate));
	bVisualizingInteraction = bActivate;
}

void AInteractableObjectBase::CreateDynamicMaterial()
{
	Material = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
	for (int i = 0; i < Mesh->GetNumMaterials(); i++)
	{
		Mesh->SetMaterial(i, Material);
	}
}

void AInteractableObjectBase::Interact()
{
	// Sound->Play();
	Mesh->SetVisibility(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AInteractableObjectBase::BeginPlay()
{
	Super::BeginPlay();
	Sound->SetWorldLocation(GetActorLocation());
}
