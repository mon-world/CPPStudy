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

	// 월드에서 ACSPlayer 타깃 가져오기
	// api : https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Kismet/UGameplayStatics/
	// UGameplayStatics : 게임플레이 유틸리티 함수가 포함된 정적 클래스. api 들어가면 어마무시하게 많다
	// UGameplayStatics::GetActorOfClass : 지정된 클래스의 월드에서 첫번째 액터를 찾는다.
	// 변수 = UGameplayStatics::GetActorOfClass(월드에 존재하는 모든 오브젝트, 찾고자 하는 액터의 클래스);
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACSPlayer::StaticClass());
	// ASPlayer 타입으로 캐스팅 == 형변환
	// 변수 = Cast<T>(형변환 할 무언가)
	targetSelf = Cast<ACSPlayer>(actor);
	// 소유 객체 가져오기
	// GetOwner : 이 액터의 소유자를 가져옴.
	// 그럼 소유자는 뭐지??? 
	enemySelf = Cast<AEnemy>(GetOwner());

	ai = Cast<AAIController>(enemySelf->GetController());
	
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
void UEnemyFSM::IdleState() 
{
	// GetWorld() : 현재 실행중인 월드를 불러온다. 엑터 스폰 등 여러가지 작업 가능
	// DeltaTimeSeconds : 시간 확장에 따라 조정된 프레임 델타 시간을 초 단위로 반환 == 시스템 성능이 달라도 일정한 값 가져올 수 있음
	// 즉, 시스템 성능 같으면 굳이 deltatimeseconds 쓰지 말고 상수 넣어주면 된다
	currentTime += GetWorld()->DeltaTimeSeconds;

	// 경과 시간 > 대기시간 이면 움직임
	if (currentTime > idleDelayTime)
	{
		enemyState = EEnemyState::Move;
		// 누적된 시간 초기화
		currentTime = 0;
	}

}
// 이동
void UEnemyFSM::MoveState() 
{
	// 타겟의 위치를 벡터로 가져옴
	FVector targetPositionVector = targetSelf->GetActorLocation();
	// 적 위치(내 위치)를 벡터로 가져옴
	FVector enemyPositionVector = enemySelf->GetActorLocation();
	// 내쪽으로 오도록 하기 : -
	FVector targetDir = targetPositionVector - enemyPositionVector;
	// 적 -> 플레이어 이동
	// FVector::GetSafeNormal : 벡터의 정규화된 복사본을 가져오고, 길이가 일정 이하라면 0 벡터 반환. <- 최소 벡터 길이를 매개변수로 받음
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FVector/GetSafeNormal/
	// AddMovementInput : 방향을 넣으면 그쪽으로 이동입력이 된다.
	// AddMovementInput(입력 적용할 월드 공간 방향, 적용 크기(0.5는 절반, -는 반대방향 : 멀어지기), bool : true인 경우 IsMoveInputIgnored() 결과 무시)
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/GameFramework/APawn/AddMovementInput/
	enemySelf->AddMovementInput(targetDir.GetSafeNormal());
	
	//일정 이상 들어오면 공격상태
	if (targetDir.Size() < attackRange)
	{
		enemyState = EEnemyState::Attack;
	}
}
// 공격
void UEnemyFSM::AtackState() 
{
	// 평타에 쿨타임 있게
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 쿨이 돌았으면 공격하고, 다시 쿨다운 시작
	if (currentTime > attackDelayTime)
	{
		PRINT_LOG(TEXT("attack"));
		currentTime = 0;
	}

	// 범위를 벗어나면 다시 이동상태로
	// 차의 제곱의 합의 제곱근으로 구한다. 
	float distanceTargetEnemy = FVector::Distance(targetSelf->GetActorLocation(), enemySelf->GetActorLocation());

	if (distanceTargetEnemy > attackRange)
	{
		enemyState = EEnemyState::Move;
	}
}
// 피격
void UEnemyFSM::DamageSate() 
{
	// 플레이어한테 공격당한 후 경직타임
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > damageDelayTime)
	{
		enemyState = EEnemyState::Idle;
		currentTime = 0;
	}
}
// 죽으면 시체 처리하는 방법
void UEnemyFSM::DeadState() 
{
	// 등속도로 z축 감소시키기
	FVector P0 = enemySelf->GetActorLocation();
	FVector vt = FVector::DownVector * deadSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	enemySelf->SetActorLocation(P);

	// 2미터보다 내려갔으면 그냥 화면에서 사라지게
	// 단위가 cm 이므로 200
	if (P.Z < -200.0f)
	{
		enemySelf->Destroy();
	}
}

void UEnemyFSM::OnDamageProcess()
{
	// 나중에 공격력? STR 같은거 넣어줘서 hp -= STR * 계수 이렇게 해주면 될듯
	hp--;

	if (hp > 0)
	{
		// 피격상태
		enemyState = EEnemyState::Damage;
	}
	else
	{
		// hp 0이하니까 죽은 상태
		enemyState = EEnemyState::Dead;

		// 캡슐 컴포넌트 비활성화
		// 왜? -> 바닥과 충돌하여 뚫고 들어가야 하는데 이게 있어서 충돌해버리면 못뚫고 들어감
		enemySelf->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

