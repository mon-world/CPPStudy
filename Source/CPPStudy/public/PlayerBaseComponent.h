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
		// 틱 함수 호출 안되게 막음
		// .cpp 파일 개조 필요함. 말도 안됨
		PrimaryComponentTick.bCanEverTick = false;
	};

	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Components/UActorComponent/InitializeComponent?application_version=5.3
	virtual void InitializeComponent() override;

	// 비긴 플레이 => 가상함수 // 상속받을 클래스에서 재정의해라~
	virtual void BeginPlay() override;

	// 사용자 입력 맵핑 처리 함수
	// 사용자 입력을 매핑하려나봐... 올드 인풋이 예제이므로 일단 따라한 후 수정예정
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) {};

	// 컴포넌트 소유 액터
	UPROPERTY() ACSPlayer* me;
	UPROPERTY()	UCharacterMovementComponent* moveComp;

		
};
