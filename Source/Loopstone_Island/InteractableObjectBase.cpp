// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableObjectBase.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
// AInteractableObjectBase::AInteractableObjectBase()
// {
//  	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// 	PrimaryActorTick.bCanEverTick = true;
// 	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ObjectMesh"));
// 	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneRoot"));
// 	ObjectMesh->AttachTo(RootComponent);
// }
//
// void AInteractableObjectBase::VisualizeInteraction(bool bActivate)
// {
// 	if (!IsValid(Material))
// 	{
// 		CreateDynamicMaterial();
// 	}
// 	Material->SetScalarParameterValue("Glow", int(bActivate));
// 	bVisualizingInteraction = bActivate;
// }
//
// void AInteractableObjectBase::CreateDynamicMaterial()
// {
// 	Material = UMaterialInstanceDynamic::Create(ObjectMesh->GetMaterial(0), this);
// 	ObjectMesh->SetMaterial(0, Material);
// }

void AInteractableObjectBase::Interact()
{
}

// Called when the game starts or when spawned
void AInteractableObjectBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

