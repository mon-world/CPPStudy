// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Components/ActorComponent.h"
#include "PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPSTUDY_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerBaseComponent() 
	{
		// ƽ �Լ� ȣ�� �ȵǰ� ����
		// .cpp ���� ���� �ʿ���. ���� �ȵ�
		PrimaryComponentTick.bCanEverTick = false;
	};

	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Components/UActorComponent/InitializeComponent?application_version=5.3
	virtual void InitializeComponent() override;

	// ��� �÷��� => �����Լ� // ��ӹ��� Ŭ�������� �������ض�~
	virtual void BeginPlay() override;

	// ����� �Է� ���� ó�� �Լ�
	// ����� �Է��� �����Ϸ�����... �õ� ��ǲ�� �����̹Ƿ� �ϴ� ������ �� ��������
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) {};

	// ������Ʈ ���� ����
	UPROPERTY() ACSPlayer* me;
	UPROPERTY()	UCharacterMovementComponent* moveComp;

		
};
