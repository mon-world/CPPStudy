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
		PrimaryComponentTick.bCanEverTick = false;
	};

	// ��� �÷��� => �����Լ� // ��ӹ��� Ŭ�������� �������ض�~
	virtual void BeginPlay() override;

	// ����� �Է� ���� ó�� �Լ�
	// ����� �Է��� �����Ϸ�����... �õ� ��ǲ�� �����̹Ƿ� �ϴ� ������ �� ��������
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) {};

	// ������Ʈ ���� ����
	UPROPERTY() ACSPlayer* me;
	UPROPERTY()	UCharacterMovementComponent* moveComp;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
