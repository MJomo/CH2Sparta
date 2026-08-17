#include "PlayerPawn.h"
#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	SetRootComponent(Capsule);

	Capsule->SetSimulatePhysics(true);
	Capsule->SetEnableGravity(true);

	skeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL"));
	skeleton->SetupAttachment(Capsule);

	springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springarm->SetupAttachment(skeleton);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(springarm);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &APlayerPawn::StartJump);
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &APlayerPawn::StopJump);
			}

			if (PlayerController->LockAction)
			{
				EnhancedInput->BindAction(PlayerController->LockAction, ETriggerEvent::Triggered, this, &APlayerPawn::Lock);
			}
			
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &APlayerPawn::StartSprint);
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &APlayerPawn::StopSprint);
			}

		}
    }
}

void APlayerPawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void APlayerPawn::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		
	}
}

void APlayerPawn::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
	}
}

void APlayerPawn::Lock(const FInputActionValue& value)
{

}

void APlayerPawn::StartSprint(const FInputActionValue& value)
{
}

void APlayerPawn::StopSprint(const FInputActionValue& value)
{

}
