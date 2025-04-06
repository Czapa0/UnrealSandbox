// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DungeonCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"

ADungeonCharacter::ADungeonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = bUseControllerRotationRoll = bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->AttachmentName = TEXT("head");
	Hair->SetupAttachment(GetMesh());

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->AttachmentName = TEXT("head");
	Eyebrows->SetupAttachment(GetMesh());
}

void ADungeonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Subsystem is null"));
		}
	}
}

void ADungeonCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();

	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0, ControlRotation.Yaw, 0);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, DirectionValue.Y);
	AddMovementInput(Right, DirectionValue.X);
}

void ADungeonCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void ADungeonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ADungeonCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADungeonCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ADungeonCharacter::Jump);
	}
}

