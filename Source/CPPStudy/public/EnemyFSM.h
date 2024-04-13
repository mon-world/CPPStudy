// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

// https://chalk-homegrown-fe4.notion.site/UENUM-117c5d367b684e17908ecb43c5af7165?pvs=74
// �𸮾󿡼� ����ϴ� ������ �𸮾� ����ü - enum calss�� �����ϰ�, Ÿ���� �׻� uint8
// enum class ���������� ������� + Ŭ�������� E ���̱�
// enum class Ŭ������ : uint8 { ����, ..., };
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
	// ���º���
	// ��𼭳� �� �� ������, bp���� ���� �Ұ���, fsm���� ǥ��
	// ������ �ɹ� ����. :: �����ڸ� ���� �����Ѵ�. https://eteo.tistory.com/688
	EEnemyState enemyState = EEnemyState::Idle;

	// idle
	void IdleState();
	// �̵�
	void MoveState();
	// ����
	void AtackState();
	// �ǰ�
	void DamageSate();
	// ����
	void DeadState();

	//���, �̵� ����
	UPROPERTY(EditDefaultsOnly, Category = "FSM") float idleDelayTime = 2;
	// ��� �ð�
	float currentTime = 0;

	// Ÿ�� : 
	UPROPERTY(VisibleAnywhere, Category = "FSM") class ACSPlayer* targetSelf;

	// �� ��ġ == enemy�� ��ġ
	// ������ ���ϱ� ���ؼ� vector ������ �÷��̾� ��ġ - enemy ��ġ �ϸ� enemy�� ������ ������ �� �� �ִ�.
	// ���⼭ �����Ǹ� �������°� �ƴϴϱ� self�� ����
	UPROPERTY() class AEnemy* enemySelf;

	// ���� ����
	UPROPERTY(EditAnywhere, Category = "FSM") float attackRange = 150.0f;

	// ���� ���ð� == �⺻ ��Ÿ��
	UPROPERTY(EditAnywhere, Category = "FSM") float attackDelayTime = 2.0f;

	// �ǰ� �˸� �̺�Ʈ �Լ� == ���� �����̻� ������ �װ�.
	// ���� �� ȣ��Ǵ� �Լ�
	void OnDamageProcess();

	// ü��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FSM") int hp = 3;

	// �����ð�
	UPROPERTY(EditAnywhere, Category = "FSM") float damageDelayTime = 2.0f;

	// ��ü�� �ٴ����� ���� ������ == z�� ���ҽ�Ŵ
	UPROPERTY(EditAnywhere, Category = "FSM") float deadSpeed = 50.0f;


	// Enemy�� �����ϰ� �ִ� AIController
	// AEnemy�� ĳ���� Ŭ�����̰�, �̴� �� APawn Ŭ�����̴�. 
	// �̸� �����ϱ� ���� ���� Ŭ������ APlayerController �̰�,  
	// AI�� ���� �����ϱ� ���� ������ Ŭ������ AAIController �̴�.
	UPROPERTY() class AAIController* ai;

	// ���� ��ġ�� ������ ����
	FVector randomPosition;

	// ���� ��ġ �������� �Լ� : bool Ÿ���� ��ȯ�Ѵ�. : ����� �˻� �ƴ���
	// �˻��� ���� ��ġ, �˻� ����, ���� ��ġ ������ ���� ���� Ÿ�� ����
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

};
