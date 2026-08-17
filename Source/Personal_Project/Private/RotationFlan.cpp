 // Fill out your copyright notice in the Description page of Project Settings.


#include "RotationFlan.h"

// Sets default values
Aflan::Aflan()
{
	PrimaryActorTick.bCanEverTick = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SceneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SceneMeshComponent->SetupAttachment(SceneRoot);
	// /Game/ModularSciFiStation/Environment/Floor/SM_floor_100x100_02.SM_floor_100x100_02
	// /Game/ModularSciFiStation/Materials/Trims/MI_interior_trim_01.MI_interior_trim_01
	// /Game/ModularSciFiStation/Materials/Metal/MI_grid_floor.MI_grid_floor
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/ModularSciFiStation/Environment/Floor/SM_floor_100x100_02.SM_floor_100x100_02"));
	if (MeshAsset.Succeeded()) {
		SceneMeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterialAsset(TEXT("/Game/ModularSciFiStation/Materials/Trims/MI_interior_trim_01.MI_interior_trim_01"));
	if (MeshMaterialAsset.Succeeded()) {
		SceneMeshComponent->SetMaterial(0, MeshMaterialAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterialAsset2(TEXT("/Game/ModularSciFiStation/Materials/Metal/MI_grid_floor.MI_grid_floor"));
	if (MeshMaterialAsset2.Succeeded()) {
		SceneMeshComponent->SetMaterial(1, MeshMaterialAsset2.Object);
	}
	
	MoveForward = true;
	RotationSpeed = 30.0f;
	MoveSpeed = 10.0f;
}

// Called when the game starts or when spawned
void Aflan::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	//SetActorLocation(FVector(500.0f, 500.0f, 500.0f));
	//SetActorRotation(FRotator(0.0f, 10.0f, 0.0f));
	//SetActorScale3D(FVector(5.0f));//0.0f, 0.0f, 0.0f µµ °¡´É


}

// Called every frame
void Aflan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyZero(RotationSpeed)){
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

	float MoveDirection = MoveForward ? 1.0f : -1.0f;

	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + FVector(0.0f, 1.0f, 0.0f) * MoveSpeed * MoveDirection * DeltaTime;

	float NewDistance = (NewLocation - InitialLocation).Size();

	if (NewDistance >= MoveDistance) {
		FVector ClampedOffset = InitialLocation + FVector(0.0f, 1.0f, 0.0f) * MoveDistance * MoveDirection;
		SetActorLocation(ClampedOffset);
		MoveForward = !MoveForward;
	}

	else {
		SetActorLocation(NewLocation);
	}

}

