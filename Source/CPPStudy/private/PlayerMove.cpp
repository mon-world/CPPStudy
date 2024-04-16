// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMove.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "InputMappingContext.h"


// https://forums.unrealengine.com/t/ue-5-enhanced-input-c-problems/1412752/2
UPlayerMove::UPlayerMove()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Controller.IMC_Controller'"));
	if (InputContext.Object != nullptr)
	{
		DefaultMappingContext = InputContext.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputLook(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_LookP.IA_LookP'"));
	if (InputContext.Object != nullptr)
	{
		LookAction = InputLook.Object;
	}
}

void UPlayerMove::BeginPlay()
{
	// �� ��¥ �־�
	Super::BeginPlay();

	// �÷��̾� ��Ʈ�ѷ� ĳ����, subsystem�� context ����
	// ���� ���������� �м��ؾ��Ѵ�.... 
	if (APlayerController* PlayerController = Cast<APlayerController>(me->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

// ACSPlayer -> UPlayerMove. ���Ͱ� �ƴϴϱ�.
void UPlayerMove::Look(const FInputActionInstance& Instance)
{
	/*#include "EnhancedInputComponent.h"
	#include "EnhancedInputSubsystems.h"*/
	// ���� �� �߰��ߴ��� Instance�� ���� �����
	// �긦 ��� �ٲ���ϳ�...?

	// 1. �Է��� �÷��̾����� �޾ƾ� �Ѵ�.
	// 2. 
	FVector2D LookVector = Instance.GetValue().Get<FVector2D>();

	// me : 362��. PlayerBaseComponent.h�� .cpp���� ���� <- �θ� Ŭ����
	// me = Cast<ACSPlayer>(GetOwner());
	// ��, �÷��̾ ĳ��Ʈ �� ����
	// Yaw ������ �̵��Է�
	me->AddControllerYawInput(LookVector.X);
	// Pitch ������ �̵��Է�
	me->AddControllerPitchInput(LookVector.Y);

}

void UPlayerMove::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	// �̰� ���� �ѹ��� �ǹ��� ������
	// Super::SetupInputBinding(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// LookAction�� ������, Input�� ������...
	// �ƹ��� ���� LookAction�� ��� �ϴ��� ���߰ڴ�
	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &UPlayerMove::Look);
}


