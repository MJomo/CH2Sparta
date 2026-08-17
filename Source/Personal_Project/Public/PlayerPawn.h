#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* skeleton;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* springarm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* Capsule;




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



	bool bIsGrounded;
};
