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

	// AAIController 할당하기
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
	// 애니 동기화 여기 써야함
	// 최초 랜덤한 위치 정하기
	GetRandomPositionInNavMesh(enemySelf->GetActorLocation(), 500, randomPosition);
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

	/*
	// 적 -> 플레이어 이동
	// FVector::GetSafeNormal : 벡터의 정규화된 복사본을 가져오고, 길이가 일정 이하라면 0 벡터 반환. <- 최소 벡터 길이를 매개변수로 받음
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FVector/GetSafeNormal/
	// AddMovementInput : 방향을 넣으면 그쪽으로 이동입력이 된다.
	// AddMovementInput(입력 적용할 월드 공간 방향, 적용 크기(0.5는 절반, -는 반대방향 : 멀어지기), bool : true인 경우 IsMoveInputIgnored() 결과 무시)
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/GameFramework/APawn/AddMovementInput/
	//enemySelf->AddMovementInput(targetDir.GetSafeNormal());
	// bp에서 똑같은거. 단, 똑똑하게 이동-
	ai->MoveToLocation(targetPositionVector);
	*/
	
	// 위의 것을 플레이어한테 이동은 할건데, 먼저 플레이어 위치를 찾았냐를 묻고,
	// 찾으면 이동, 아니면 패트롤 기능 넣기

	enemySelf->AddMovementInput(targetDir.GetSafeNormal());
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	// 목적지 길 찾기 경로 검색???
	// 둘 다 하위 기능들이 많은 구조체
	// UNavigationSystemV1의 FindPathSync() 함수를 통해 길 찾기 결과를 가져와야 하는데,
	// FPathFindingQuery 구조체 정보가 필요하다. 
	// query : 질의문
	FPathFindingQuery query;
	FAIMoveRequest req;

	// 목적지를 인지할 수 있는 범위
	// == 도착지의 범위
	req.SetAcceptanceRadius(3);
	// 여기까지, 도착지에서 3센티 근방에 도달하면 이동 가능하다는 것.  

	// 도착지 == 타겟의 위치 정보 넘겨주기
	req.SetGoalLocation(targetPositionVector);


	// 길 찾기를 위한 쿼리 생성
	// PathfindingQuery 즉, 길 찾기를 수행할 쿼리를 만드는 함수
	// 이 함수가 쿼리를 만들기 위한 조건으로 FAIMoveRequest <- req 정보가 필요함. 
	ai->BuildPathfindingQuery(req, query);
	// 길 찾기 결과 가져오기
	FPathFindingResult r = ns->FindPathSync(query);


	// 이제 길을 찾았으니 이동해야함  
	// 성공 -> 이동 / 실패 -> 랜덤위치 찾고, 이동하고 반복  
	if (r.Result == ENavigationQueryResult::Success)
	{
		ai->MoveToLocation(targetPositionVector);
	}
	//else
	//{
	//	// 목적지가 아닌, 랜덤 위치로 이동시키기
	//	auto result = ai->MoveToLocation(randomPosition);
	//	// 목적지 도달하면 다시 랜덤위치를 줘서, 이동
	//	// EPathFollowingRequestResult : 3가지 타입 : Failed, AlreadyAtGoal, RequestSuccessful  
	//	// 어떻게 써야하지????
	//	if (result == EPathFollowingRequestResult)
	//	{
	//		// 새로운 랜덤 위치 가져오기
	//		// 밑에 있음. 
	//		// 랜덤 위치 가져오는 함수 : bool 타입을 반환한다. : 제대로 검색 됐는지
	//		// 검색할 기준 위치, 검색 범위, 랜덤 위치 저장을 위한 참조 타입 변수
	//		GetRandomPositionInNavMesh(enemySelf->GetActorLocation(), 500, randomPosition);
	//	}


	//}



	//일정 이상 들어오면 공격상태
	if (targetDir.Size() < attackRange)
	{
		// 먼저 길 찾기를 정지해 주고 때려야함
		ai->StopMovement();

		enemyState = EEnemyState::Attack;
	}
}
// 공격
void UEnemyFSM::AtackState() 
{
	// 평타에 쿨타임 있게
	// 바로 공격
	currentTime += GetWorld()->DeltaTimeSeconds + attackDelayTime;
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

		GetRandomPositionInNavMesh(enemySelf->GetActorLocation(), 500, randomPosition);
	}
}
// 피격
void UEnemyFSM::DamageSate() 
{
	// 플레이어한테 공격당한 후 경직타임
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > damageDelayTime)
	{
		// 맞고 나서 돌아가기
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

	ai->StopMovement();
}

// 랜덤 위치 가져오는 함수 : bool 타입을 반환한다. : 제대로 검색 됐는지
// 검색할 기준 위치, 검색 범위, 랜덤 위치 저장을 위한 참조 타입 변수

bool UEnemyFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	// 네비 시스템 :	https://docs.unrealengine.com/4.26/en-US/BlueprintAPI/AI/Navigation/GetNavigationSystem/
	// 블루프린트 함수라고만 나와있음 ???
	// NavigationSystem에 객체 가져옴
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	// 들어가보니 struct 이고, location과 NavNodeRef가 있음, 그리고 FNavLocation() 있음
	// location : 경로의 베이스에 상대적인 위치
	// NavNodeRef : 네비게이션 데이터의 노드 참조
	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/AI/Navigation/FNavLocation?application_version=5.0
	// 탐색 데이터의 지점 설명 -> 변수로 FVector 와 NavNodeRef 받음
	FNavLocation loc;

	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/NavigationSystem/UNavigationSystemV1/GetRandomReachablePointInRadius?application_version=5.3
	// GetRandomReachablePointInRadius : 원점 주변의 반경으로 제한된 탐색 가능한 공간에서 임의의 도달 가능한 지점을 찾는다.
	// 위치가 발각되면 true, 아님 false
	// GetRandomReachablePointInRadius(원점으로 삼을 좌표, 반경, 위치정보를 담을 변수 loc)
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);

	// 랜덤한 위치정보를 dest에 할당한다.
	dest = loc.Location;

	return result;
}
