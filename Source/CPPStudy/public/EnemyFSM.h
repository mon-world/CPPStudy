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
	// �� ai ���� ������Ʈ Ŭ����
	// ������Ʈ�� ���������� ������ �� ����. ���Ϳ� ���ԵǾ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSMComp") class UEnemyFSM* fsm;

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

};
