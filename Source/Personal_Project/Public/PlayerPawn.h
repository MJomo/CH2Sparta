#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <GameFramework/FloatingPawnMovement.h>
#include "PlayerPawn.generated.h"

struct FInputActionValue;

UCLASS()
class PERSONAL_PROJECT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	
	APlayerPawn();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Anim")
	class USkeletalMeshComponent* skeleton;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* springarm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Anim")
	TSubclassOf<UAnimInstance> AnimInstance;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
	void Move(const FInputActionValue& value);

	UFUNCTION()
	void StartJump(const FInputActionValue& value);

	UFUNCTION()
	void StopJump(const FInputActionValue& value);

	UFUNCTION()
	void Lock(const FInputActionValue& value);

	UFUNCTION()
	void StartSprint(const FInputActionValue& value);

	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsGrounded = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsSprinting = false;

	void CheckGroundState();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector2D CurrentMoveInput = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed = 700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float RotationInterpSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpVelocity = 700.0f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float GravityStrength = 980.0f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpCutMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Ground")
	float GroundTraceExtraDistance = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NowMoveSpeed = 0.0f;

	UFloatingPawnMovement* MoveCom;

	float VerticalVelocity = 0.0f;

	void HandleMovement(float DeltaTime);
};
