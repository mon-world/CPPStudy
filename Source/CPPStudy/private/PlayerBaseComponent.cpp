// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseComponent.h"

void UPlayerBaseComponent::InitializeComponent()
{
	// UActorComponent::InitializeComponent
	// ���� ���� or ���� ������ �߻�. begin play ������ �߻�
	// ������ ��� �Ĥ����Ʈ�� ���ͳ� ������Ʈ�� begin play�� �ޱ� ���� �ε� �� �ʱ�ȭ�ȴ�.
	// ���� == ������Ʈ ��� && bWantsInitializeComponent�� true

	Super::InitializeComponent();

	me = Cast<ACSPlayer>(GetOwner());
	// ĳ���� �����ӿ� ���� ���־��� ���� �͵��� �������
	moveComp = me->GetCharacterMovement();

	// ��������Ʈ�� ó�� �Լ� ���
	me->onInputBindingDelegate.AddUObject(this, &UPlayerBaseComponent::SetupInputBinding);
}

void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}
