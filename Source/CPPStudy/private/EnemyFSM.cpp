// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// enum class 과 스위치문 사용법 : 클래스명 선언한 것의 상태를 switch-case 문으로 작성한다. 대신, 원 소속 :: 표시해줘야함
	// enumClass형의 변수 = enumClass::열거형;
	// switch-case 구문도 마찬가지
	// switch(uenum형으로 선언된 변수 a) { case uenum이름::맴버: 실행문;}
	switch (enemyState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AtackState();
		break;
	case EEnemyState::Damage:
		DamageSate();
		break;
	case EEnemyState::Dead:
		DeadState();
		break;
	}
}

// idle
void UEnemyFSM::IdleState() {}
// 이동
void UEnemyFSM::MoveState() {}
// 공격
void UEnemyFSM::AtackState() {}
// 피격
void UEnemyFSM::DamageSate() {}
// 죽음
void UEnemyFSM::DeadState() {}

