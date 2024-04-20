// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;
/**
 * 
 */
UCLASS()
class CPPSTUDY_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:
	// https://forums.unrealengine.com/t/ue-5-enhanced-input-c-problems/1412752/2
	// 여기 너무 억지인데... 이정도면 comp로 뽑는 의미가 없을듯?

	UPlayerMove()
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

	// 비긴 플레이 사용해야하므로 순수가상함수로 선언 - 무조건 바꿔써라
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, Category = Input) UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* LookAction;

public:
	// PlayerBaseComponent, CSPlayer로 include 하기 때문에 알아먹는건가...? 왜 에러 아니지
	// h 파일을 많이 include 하는 파일을 또 include 하면 어떻게 되지 -> .h와 .cpp 관계 생각하면 될지도
	void Look(const FInputActionInstance& Instance);

	// Called to bind functionality to input
	// SetupPlayerInputComponent 이거 왜 안씀? or 안됨?
	// SetupInputBinding 얘는 그냥 정의가 없다고 하네
	// p370 상으론 서로 같다고 한다...? 저 comp 함수 역할을 하는게 아래것.
	// 저 comp 함수는 ASCPlayer 클래스의 함수... character 클래스를 상속받은 것만이 가질 수 있나?
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;
	
};
