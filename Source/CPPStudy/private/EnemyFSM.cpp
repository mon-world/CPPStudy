// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "CSPlayer.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
#include "CPPStudy.h"
#include <Components/CapsuleComponent.h>
#include <AIController.h>
#include <NavigationSystem.h>

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

	// ���忡�� ACSPlayer Ÿ�� ��������
	// api : https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Kismet/UGameplayStatics/
	// UGameplayStatics : �����÷��� ��ƿ��Ƽ �Լ��� ���Ե� ���� Ŭ����. api ���� ������ϰ� ����
	// UGameplayStatics::GetActorOfClass : ������ Ŭ������ ���忡�� ù��° ���͸� ã�´�.
	// ���� = UGameplayStatics::GetActorOfClass(���忡 �����ϴ� ��� ������Ʈ, ã���� �ϴ� ������ Ŭ����);
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACSPlayer::StaticClass());
	// ASPlayer Ÿ������ ĳ���� == ����ȯ
	// ���� = Cast<T>(����ȯ �� ����)
	targetSelf = Cast<ACSPlayer>(actor);
	// ���� ��ü ��������
	// GetOwner : �� ������ �����ڸ� ������.
	// �׷� �����ڴ� ����??? 
	enemySelf = Cast<AEnemy>(GetOwner());

	ai = Cast<AAIController>(enemySelf->GetController());
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// enum class �� ����ġ�� ���� : Ŭ������ ������ ���� ���¸� switch-case ������ �ۼ��Ѵ�. ���, �� �Ҽ� :: ǥ���������
	// enumClass���� ���� = enumClass::������;
	// switch-case ������ ��������
	// switch(uenum������ ����� ���� a) { case uenum�̸�::�ɹ�: ���๮;}
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
void UEnemyFSM::IdleState() 
{
	// GetWorld() : ���� �������� ���带 �ҷ��´�. ���� ���� �� �������� �۾� ����
	// DeltaTimeSeconds : �ð� Ȯ�忡 ���� ������ ������ ��Ÿ �ð��� �� ������ ��ȯ == �ý��� ������ �޶� ������ �� ������ �� ����
	// ��, �ý��� ���� ������ ���� deltatimeseconds ���� ���� ��� �־��ָ� �ȴ�
	currentTime += GetWorld()->DeltaTimeSeconds;

	// ��� �ð� > ���ð� �̸� ������
	if (currentTime > idleDelayTime)
	{
		enemyState = EEnemyState::Move;
		// ������ �ð� �ʱ�ȭ
		currentTime = 0;
	}

}
// �̵�
void UEnemyFSM::MoveState() 
{
	// Ÿ���� ��ġ�� ���ͷ� ������
	FVector targetPositionVector = targetSelf->GetActorLocation();
	// �� ��ġ(�� ��ġ)�� ���ͷ� ������
	FVector enemyPositionVector = enemySelf->GetActorLocation();
	// �������� ������ �ϱ� : -
	FVector targetDir = targetPositionVector - enemyPositionVector;
	// �� -> �÷��̾� �̵�
	// FVector::GetSafeNormal : ������ ����ȭ�� ���纻�� ��������, ���̰� ���� ���϶�� 0 ���� ��ȯ. <- �ּ� ���� ���̸� �Ű������� ����
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FVector/GetSafeNormal/
	// AddMovementInput : ������ ������ �������� �̵��Է��� �ȴ�.
	// AddMovementInput(�Է� ������ ���� ���� ����, ���� ũ��(0.5�� ����, -�� �ݴ���� : �־�����), bool : true�� ��� IsMoveInputIgnored() ��� ����)
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/GameFramework/APawn/AddMovementInput/
	enemySelf->AddMovementInput(targetDir.GetSafeNormal());
	
	//���� �̻� ������ ���ݻ���
	if (targetDir.Size() < attackRange)
	{
		enemyState = EEnemyState::Attack;
	}
}
// ����
void UEnemyFSM::AtackState() 
{
	// ��Ÿ�� ��Ÿ�� �ְ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	// ���� �������� �����ϰ�, �ٽ� ��ٿ� ����
	if (currentTime > attackDelayTime)
	{
		PRINT_LOG(TEXT("attack"));
		currentTime = 0;
	}

	// ������ ����� �ٽ� �̵����·�
	// ���� ������ ���� ���������� ���Ѵ�. 
	float distanceTargetEnemy = FVector::Distance(targetSelf->GetActorLocation(), enemySelf->GetActorLocation());

	if (distanceTargetEnemy > attackRange)
	{
		enemyState = EEnemyState::Move;
	}
}
// �ǰ�
void UEnemyFSM::DamageSate() 
{
	// �÷��̾����� ���ݴ��� �� ����Ÿ��
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > damageDelayTime)
	{
		enemyState = EEnemyState::Idle;
		currentTime = 0;
	}
}
// ������ ��ü ó���ϴ� ���
void UEnemyFSM::DeadState() 
{
	// ��ӵ��� z�� ���ҽ�Ű��
	FVector P0 = enemySelf->GetActorLocation();
	FVector vt = FVector::DownVector * deadSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	enemySelf->SetActorLocation(P);

	// 2���ͺ��� ���������� �׳� ȭ�鿡�� �������
	// ������ cm �̹Ƿ� 200
	if (P.Z < -200.0f)
	{
		enemySelf->Destroy();
	}
}

void UEnemyFSM::OnDamageProcess()
{
	// ���߿� ���ݷ�? STR ������ �־��༭ hp -= STR * ��� �̷��� ���ָ� �ɵ�
	hp--;

	if (hp > 0)
	{
		// �ǰݻ���
		enemyState = EEnemyState::Damage;
	}
	else
	{
		// hp 0���ϴϱ� ���� ����
		enemyState = EEnemyState::Dead;

		// ĸ�� ������Ʈ ��Ȱ��ȭ
		// ��? -> �ٴڰ� �浹�Ͽ� �հ� ���� �ϴµ� �̰� �־ �浹�ع����� ���հ� ��
		enemySelf->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

