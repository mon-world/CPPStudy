// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseComponent.h"

void UPlayerBaseComponent::InitializeComponent()
{
	// UActorComponent::InitializeComponent
	// 레벨 시작 or 액터 스폰시 발생. begin play 이전에 발생
	// 레벨의 모든 컴ㅍ모넌트는 액터나 컴포넌트가 begin play를 받기 전에 로드 시 초기화된다.
	// 조건 == 컴포넌트 등록 && bWantsInitializeComponent가 true

	Super::InitializeComponent();

	me = Cast<ACSPlayer>(GetOwner());
	// 캐릭터 움직임에 관한 아주아주 많은 것들이 들어있음
	moveComp = me->GetCharacterMovement();

	// 델리게이트에 처리 함수 등록
	me->onInputBindingDelegate.AddUObject(this, &UPlayerBaseComponent::SetupInputBinding);
}

void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}
