// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

// https://chalk-homegrown-fe4.notion.site/UENUM-117c5d367b684e17908ecb43c5af7165?pvs=74
// 언리얼에서 사용하는 열거형 언리얼 구조체 - enum calss로 선언하고, 타입은 항상 uint8
// enum class 열거형으로 만들어줌 + 클래스명은 E 붙이기
// enum class 클래스명 : uint8 { 열거, ..., };
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Dead,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPSTUDY_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 적 ai 관리 컴포넌트 클래스
	// 컴포넌트는 독립적으로 존재할 수 없다. 액터에 포함되어야함
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSMComp") class UEnemyFSM* fsm;

public:
	// 상태변수
	// 어디서나 볼 수 있지만, bp에서 수정 불가능, fsm으로 표시
	// 열거형 맴버 접근. :: 연산자를 통해 접근한다. https://eteo.tistory.com/688
	EEnemyState enemyState = EEnemyState::Idle;

	// idle
	void IdleState();
	// 이동
	void MoveState();
	// 공격
	void AtackState();
	// 피격
	void DamageSate();
	// 죽음
	void DeadState();

};
