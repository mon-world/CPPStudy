// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include <EngineUtils.h>

// Sets default values
AEnemyManager::AEnemyManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 이미 셋 타임으로 tick의 경과시간 계산하는 방법은 안쓰므로, false로 바꿔줘서 생성자에서 호출 안되도록 한다.  
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// 랜덤 생성 시간
	float createTime = FMath::RandRange(minTime, maxTime);
	// timer manager한테 알람 등록
	// GetTimerManager().SetTimer(타이머의 핸들, 타이머 함수를 호출하는 오브젝트, 타이머가 발동할 때마다 호출될 함수, 타이머가 호출될 시간)
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);

	// 스폰 위치 동적 할당  
	FindSpawnPoints();

}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::CreateEnemy()
{
	// 랜덤 위치 : 0~스폰 포인트의 사이즈 == 0~배열 N-1개 까지 총 N개
	int idx = FMath::RandRange(0, spawnPoints.Num() - 1);
	// 적 생성 및 배치
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[idx]->GetActorLocation(), FRotator(0));

	// 다시 랜덤 시간에 create enemy 함수 호출되도록 타이머 설정하기
	float createTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

void AEnemyManager::FindSpawnPoints()
{
	// TActorIterator : 찾은 결과를 하나씩 꺼내서 사용
	// 후방에서 ++하면 빨간줄... 왜지
	// 이상하다, for문의 가운데는 조건일텐데, It이면 끝남...?  
	// 변수에 () 의미는? c++에서 = 과 같은건가  

	// 비교용 : for (int i = 0; i < n; ++i)
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		// It은 포인터 변수. 왜? GetWorld 니까. 
		// 그럼 It의 자료형만큼 ++ 하면 메모리 칸이 움직인다.  
		// It의 주소에 있는 값을, AActor* 타입의 spawn에 담는다.
		// 
		AActor* spawn = *It;
		// 찾을 액터의 이름에 해당 문자열을 포함한다면,
		if (spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
		{
			// 스폰 목록에 추가
			spawnPoints.Add(spawn);
		}

	}
}
