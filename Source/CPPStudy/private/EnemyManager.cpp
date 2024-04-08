// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// �̹� �� Ÿ������ tick�� ����ð� ����ϴ� ����� �Ⱦ��Ƿ�, false�� �ٲ��༭ �����ڿ��� ȣ�� �ȵǵ��� �Ѵ�.  
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// ���� ���� �ð�
	float createTime = FMath::RandRange(minTime, maxTime);
	// timer manager���� �˶� ���
	// GetTimerManager().SetTimer(Ÿ�̸��� �ڵ�, Ÿ�̸� �Լ��� ȣ���ϴ� ������Ʈ, Ÿ�̸Ӱ� �ߵ��� ������ ȣ��� �Լ�, Ÿ�̸Ӱ� ȣ��� �ð�)
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::CreateEnemy()
{
	// ���� ��ġ : 0~���� ����Ʈ�� ������ == 0~�迭 N-1�� ���� �� N��
	int idx = FMath::RandRange(0, spawnPoints.Num() - 1);
	// �� ���� �� ��ġ
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[idx]->GetActorLocation(), FRotator(0));

	// �ٽ� ���� �ð��� create enemy �Լ� ȣ��ǵ��� Ÿ�̸� �����ϱ�
	float createTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

