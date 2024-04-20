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
	// ���� �ʹ� �����ε�... �������� comp�� �̴� �ǹ̰� ������?

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

	// ��� �÷��� ����ؾ��ϹǷ� ���������Լ��� ���� - ������ �ٲ���
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, Category = Input) UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* LookAction;

public:
	// PlayerBaseComponent, CSPlayer�� include �ϱ� ������ �˾ƸԴ°ǰ�...? �� ���� �ƴ���
	// h ������ ���� include �ϴ� ������ �� include �ϸ� ��� ���� -> .h�� .cpp ���� �����ϸ� ������
	void Look(const FInputActionInstance& Instance);

	// Called to bind functionality to input
	// SetupPlayerInputComponent �̰� �� �Ⱦ�? or �ȵ�?
	// SetupInputBinding ��� �׳� ���ǰ� ���ٰ� �ϳ�
	// p370 ������ ���� ���ٰ� �Ѵ�...? �� comp �Լ� ������ �ϴ°� �Ʒ���.
	// �� comp �Լ��� ASCPlayer Ŭ������ �Լ�... character Ŭ������ ��ӹ��� �͸��� ���� �� �ֳ�?
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;
	
};
