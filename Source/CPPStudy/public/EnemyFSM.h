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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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

	//대기, 이동 구현
	UPROPERTY(EditDefaultsOnly, Category = "FSM") float idleDelayTime = 2;
	// 경과 시간
	float currentTime = 0;

	// 타깃 : 
	UPROPERTY(VisibleAnywhere, Category = "FSM") class ACSPlayer* targetSelf;

	// 내 위치 == enemy의 위치
	// 방향을 구하기 위해서 vector 값으로 플레이어 위치 - enemy 위치 하면 enemy가 가야할 방향을 알 수 있다.
	// 여기서 포지션만 가져오는게 아니니까 self로 변경
	UPROPERTY() class AEnemy* enemySelf;

	// 공격 범위
	UPROPERTY(EditAnywhere, Category = "FSM") float attackRange = 150.0f;

	// 공격 대기시간 == 기본 쿨타임
	UPROPERTY(EditAnywhere, Category = "FSM") float attackDelayTime = 2.0f;

	// 피격 알림 이벤트 함수 == 내가 일정이상 때리면 죽게.
	// 맞을 때 호출되는 함수
	void OnDamageProcess();

	// 체력
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FSM") int hp = 3;

	// 경직시간
	UPROPERTY(EditAnywhere, Category = "FSM") float damageDelayTime = 2.0f;

	// 시체가 바닥으로 점점 내려감 == z축 감소시킴
	UPROPERTY(EditAnywhere, Category = "FSM") float deadSpeed = 50.0f;


	// Enemy를 소유하고 있는 AIController
	// AEnemy는 캐릭터 클래스이고, 이는 곧 APawn 클래스이다. 
	// 이를 제어하기 위한 목적 클래스가 APlayerController 이고,  
	// AI가 폰을 제어하기 위한 목적의 클래스가 AAIController 이다.
	UPROPERTY() class AAIController* ai;

	// 랜덤 위치를 저장할 변수
	FVector randomPosition;

	// 랜덤 위치 가져오는 함수 : bool 타입을 반환한다. : 제대로 검색 됐는지
	// 검색할 기준 위치, 검색 범위, 랜덤 위치 저장을 위한 참조 타입 변수
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

};
