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
	// 얘 진짜 왜씀
	Super::BeginPlay();

	// 플레이어 컨트롤러 캐스팅, subsystem과 context 연결
	// 여기 무슨뜻인지 분석해야한다.... 
	if (APlayerController* PlayerController = Cast<APlayerController>(me->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

// ACSPlayer -> UPlayerMove. 액터가 아니니까.
void UPlayerMove::Look(const FInputActionInstance& Instance)
{
	/*#include "EnhancedInputComponent.h"
	#include "EnhancedInputSubsystems.h"*/
	// 위의 것 추가했더니 Instance에 밑줄 사라짐
	// 얘를 어떻게 바꿔야하나...?

	// 1. 입력은 플레이어한테 받아야 한다.
	// 2. 
	FVector2D LookVector = Instance.GetValue().Get<FVector2D>();

	// me : 362쪽. PlayerBaseComponent.h와 .cpp에서 나옴 <- 부모 클래스
	// me = Cast<ACSPlayer>(GetOwner());
	// 즉, 플레이어를 캐스트 한 것임
	// Yaw 방향의 이동입력
	me->AddControllerYawInput(LookVector.X);
	// Pitch 방향의 이동입력
	me->AddControllerPitchInput(LookVector.Y);

}

void UPlayerMove::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	// 이게 뭔지 한번도 의문이 없었네
	// Super::SetupInputBinding(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// LookAction이 문제냐, Input이 문제냐...
	// 아무리 봐도 LookAction을 어떻게 하는지 봐야겠다
	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &UPlayerMove::Look);
}


