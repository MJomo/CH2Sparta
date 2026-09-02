#include "PlayerPawn.h"
#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

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
	Capsule->SetSimulatePhysics(false);
	Capsule->SetEnableGravity(false);

	skeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL"));
	skeleton->SetupAttachment(Capsule);
	skeleton->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springarm->SetupAttachment(Capsule);
	springarm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(springarm);

	MoveCom = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MoveCom"));
	MoveCom->UpdatedComponent = RootComponent;
	MoveCom->MaxSpeed = 150.0f;

	bUseControllerRotationYaw = true;
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

	CheckGroundState();
	if (CurrentMoveInput.X != 0.0f || CurrentMoveInput.Y != 0.0f)
	{
	HandleMovement(DeltaTime);
	}
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
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Completed, this, &APlayerPawn::Move);
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
	CurrentMoveInput = value.Get<FVector2D>();
	


	
//	if (!Controller) return;
//
//	const FVector2D MoveInput = value.Get<FVector2D>();
//
//	if (!FMath::IsNearlyZero(MoveInput.X))
//	{
//		AddMovementInput(GetActorForwardVector(), MoveInput.X);
//	}
//	if (!FMath::IsNearlyZero(MoveInput.Y))
//	{
//		AddMovementInput(GetActorForwardVector(), MoveInput.Y);
//	}
}

void APlayerPawn::StartJump(const FInputActionValue& value)
{
	if (bIsGrounded)
	{
		VerticalVelocity = JumpVelocity;
		bIsGrounded = false;
	}
}

void APlayerPawn::StopJump(const FInputActionValue& value)
{
	if (VerticalVelocity > 0.0f)
	{
		VerticalVelocity *= JumpCutMultiplier;
	}
}

void APlayerPawn::Lock(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void APlayerPawn::StartSprint(const FInputActionValue& value)
{
	MoveCom->MaxSpeed = 310.0f;
	bIsSprinting = true;
}

void APlayerPawn::StopSprint(const FInputActionValue& value)
{
	MoveCom->MaxSpeed = 150.0f;
	bIsSprinting = false;
}


void APlayerPawn::CheckGroundState()
{
	if (!Capsule) return;

	const float CapsuleHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
	const FVector Start = GetActorLocation();
	const FVector End = Start - FVector(0.0f, 0.0f, CapsuleHalfHeight + GroundTraceExtraDistance);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult Hit;
	bIsGrounded = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams);

	if (bIsGrounded && VerticalVelocity <= 0.0f)
	{
		VerticalVelocity = 0.0f;
	}
}

void APlayerPawn::HandleMovement(float DeltaTime)
{
	if (!bIsGrounded)
	{
		VerticalVelocity -= GravityStrength * DeltaTime;
	}


	AddMovementInput(GetActorForwardVector(), CurrentMoveInput.X );
	AddMovementInput(GetActorRightVector(), CurrentMoveInput.Y );

}

