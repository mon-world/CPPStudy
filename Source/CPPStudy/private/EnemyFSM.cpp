// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "CSPlayer.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
#include "CPPStudy.h"
#include <Components/CapsuleComponent.h>
#include <NavigationSystem.h>
#include <AIController.h>

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

	// AAIController �Ҵ��ϱ�
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
	// �ִ� ����ȭ ���� �����
	// ���� ������ ��ġ ���ϱ�
	GetRandomPositionInNavMesh(enemySelf->GetActorLocation(), 500, randomPosition);
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

	/*
	// �� -> �÷��̾� �̵�
	// FVector::GetSafeNormal : ������ ����ȭ�� ���纻�� ��������, ���̰� ���� ���϶�� 0 ���� ��ȯ. <- �ּ� ���� ���̸� �Ű������� ����
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FVector/GetSafeNormal/
	// AddMovementInput : ������ ������ �������� �̵��Է��� �ȴ�.
	// AddMovementInput(�Է� ������ ���� ���� ����, ���� ũ��(0.5�� ����, -�� �ݴ���� : �־�����), bool : true�� ��� IsMoveInputIgnored() ��� ����)
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/GameFramework/APawn/AddMovementInput/
	//enemySelf->AddMovementInput(targetDir.GetSafeNormal());
	// bp���� �Ȱ�����. ��, �ȶ��ϰ� �̵�-
	ai->MoveToLocation(targetPositionVector);
	*/
	
	// ���� ���� �÷��̾����� �̵��� �Ұǵ�, ���� �÷��̾� ��ġ�� ã�ҳĸ� ����,
	// ã���� �̵�, �ƴϸ� ��Ʈ�� ��� �ֱ�

	enemySelf->AddMovementInput(targetDir.GetSafeNormal());
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	// ������ �� ã�� ��� �˻�???
	// �� �� ���� ��ɵ��� ���� ����ü
	// UNavigationSystemV1�� FindPathSync() �Լ��� ���� �� ã�� ����� �����;� �ϴµ�,
	// FPathFindingQuery ����ü ������ �ʿ��ϴ�. 
	// query : ���ǹ�
	FPathFindingQuery query;
	FAIMoveRequest req;

	// �������� ������ �� �ִ� ����
	// == �������� ����
	req.SetAcceptanceRadius(3);
	// �������, ���������� 3��Ƽ �ٹ濡 �����ϸ� �̵� �����ϴٴ� ��.  

	// ������ == Ÿ���� ��ġ ���� �Ѱ��ֱ�
	req.SetGoalLocation(targetPositionVector);


	// �� ã�⸦ ���� ���� ����
	// PathfindingQuery ��, �� ã�⸦ ������ ������ ����� �Լ�
	// �� �Լ��� ������ ����� ���� �������� FAIMoveRequest <- req ������ �ʿ���. 
	ai->BuildPathfindingQuery(req, query);
	// �� ã�� ��� ��������
	FPathFindingResult r = ns->FindPathSync(query);


	// ���� ���� ã������ �̵��ؾ���  
	// ���� -> �̵� / ���� -> ������ġ ã��, �̵��ϰ� �ݺ�  
	if (r.Result == ENavigationQueryResult::Success)
	{
		ai->MoveToLocation(targetPositionVector);
	}
	//else
	//{
	//	// �������� �ƴ�, ���� ��ġ�� �̵���Ű��
	//	auto result = ai->MoveToLocation(randomPosition);
	//	// ������ �����ϸ� �ٽ� ������ġ�� �༭, �̵�
	//	// EPathFollowingRequestResult : 3���� Ÿ�� : Failed, AlreadyAtGoal, RequestSuccessful  
	//	// ��� �������????
	//	if (result == EPathFollowingRequestResult)
	//	{
	//		// ���ο� ���� ��ġ ��������
	//		// �ؿ� ����. 
	//		// ���� ��ġ �������� �Լ� : bool Ÿ���� ��ȯ�Ѵ�. : ����� �˻� �ƴ���
	//		// �˻��� ���� ��ġ, �˻� ����, ���� ��ġ ������ ���� ���� Ÿ�� ����
	//		GetRandomPositionInNavMesh(enemySelf->GetActorLocation(), 500, randomPosition);
	//	}


	//}



	//���� �̻� ������ ���ݻ���
	if (targetDir.Size() < attackRange)
	{
		// ���� �� ã�⸦ ������ �ְ� ��������
		ai->StopMovement();

		enemyState = EEnemyState::Attack;
	}
}
// ����
void UEnemyFSM::AtackState() 
{
	// ��Ÿ�� ��Ÿ�� �ְ�
	// �ٷ� ����
	currentTime += GetWorld()->DeltaTimeSeconds + attackDelayTime;
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

		GetRandomPositionInNavMesh(enemySelf->GetActorLocation(), 500, randomPosition);
	}
}
// �ǰ�
void UEnemyFSM::DamageSate() 
{
	// �÷��̾����� ���ݴ��� �� ����Ÿ��
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > damageDelayTime)
	{
		// �°� ���� ���ư���
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

	ai->StopMovement();
}

// ���� ��ġ �������� �Լ� : bool Ÿ���� ��ȯ�Ѵ�. : ����� �˻� �ƴ���
// �˻��� ���� ��ġ, �˻� ����, ���� ��ġ ������ ���� ���� Ÿ�� ����

bool UEnemyFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	// �׺� �ý��� :	https://docs.unrealengine.com/4.26/en-US/BlueprintAPI/AI/Navigation/GetNavigationSystem/
	// �������Ʈ �Լ���� �������� ???
	// NavigationSystem�� ��ü ������
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	// ������ struct �̰�, location�� NavNodeRef�� ����, �׸��� FNavLocation() ����
	// location : ����� ���̽��� ������� ��ġ
	// NavNodeRef : �׺���̼� �������� ��� ����
	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/AI/Navigation/FNavLocation?application_version=5.0
	// Ž�� �������� ���� ���� -> ������ FVector �� NavNodeRef ����
	FNavLocation loc;

	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/NavigationSystem/UNavigationSystemV1/GetRandomReachablePointInRadius?application_version=5.3
	// GetRandomReachablePointInRadius : ���� �ֺ��� �ݰ����� ���ѵ� Ž�� ������ �������� ������ ���� ������ ������ ã�´�.
	// ��ġ�� �߰��Ǹ� true, �ƴ� false
	// GetRandomReachablePointInRadius(�������� ���� ��ǥ, �ݰ�, ��ġ������ ���� ���� loc)
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);

	// ������ ��ġ������ dest�� �Ҵ��Ѵ�.
	dest = loc.Location;

	return result;
}
