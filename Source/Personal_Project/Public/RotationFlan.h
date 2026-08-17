// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotationFlan.generated.h"

UCLASS()
class PERSONAL_PROJECT_API Aflan : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	Aflan();

private:
	FVector InitialLocation;

protected:
	// Called when the game starts or when spawned
	USceneComponent* SceneRoot;
	UStaticMeshComponent* SceneMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveDistance;

	bool MoveForward;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
