// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class CPPSTUDY_API AEnemyManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// �����ð��� �ּ� �ִ� : 1~5 ���̿��� �̰ڴ�
	UPROPERTY(EditAnywhere, Category = "SpawnSettings") float minTime = 1;
	UPROPERTY(EditAnywhere, Category = "SpawnSettings") float maxTime = 5;

	// ������ ��ġ ���� �迭
	// AActor* ���� ���� ���� arr
	// Tarray�� ���ø� Ŭ����, Ÿ���� ���� �ٸ� ������Ʈ���� ���� �� �ִ� Ŭ���� == �����̳� Ŭ����
	// https://jhtop0419.tistory.com/41
	// 2���� ������Ƽ�� ���� : ������Ʈ Ÿ��, ���ΰ�����
	// ������Ʈ Ÿ�� : add�Լ��� emplace �Լ� ����. add�� ������Ʈ Ÿ���� �ν��Ͻ��� �����̳ʿ� ����
	// emplace �Լ��� ������ �Ķ���͸� ����Ͽ� ������Ʈ Ÿ���� �ν��Ͻ��� ���� ����
	// add�� �ӽ� ������ Ÿ���� ���� �� ���빰�� �����̳� ���� ���ο� ������ Ÿ������ �̵� / emplace�� ���� ���� - �ӽú��� ���� x
	// append : �ٸ� TArray �Ǵ� �Ϲ� c�迭���� ������ �� �ش� �迭�� ũ�⿡ �ټ��� ������Ʈ�� �Ѳ����� ���� �� ����
	// -> ��ǿ� ����
	// TArray ���¶� ���� ������ ���� �� �ִµ�. + ������ �߰��ǰ�. �����Ϳ��� Ȯ�� ����  
	UPROPERTY(EditAnywhere, Category = "SpawnSettings") TArray<class AActor*> spawnPoints;

	// AEenmy Ÿ���� bp �Ҵ���� ����
	// TSubclassOf<T>
	// UClass Ÿ�� �������� �����ϴ� ���ø� Ŭ����
	// Ŭ���� �Ҵ��� �������� ���ѽ�ų �� �ִ�.
	// https://jhtop0419.tistory.com/51
	UPROPERTY(EditAnywhere, Category = "SpawnSettings") TSubclassOf<class AEnemy> enemyFactory;

	// ������ ���� �˶� Ÿ�̸�
	// �ڵ��� ������ �־�� ������ ���Ḧ �� �� ����
	// https://online-unreal.tistory.com/15
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/FTimerHandle/
	// ������ �븮���� �ִ� Ÿ�̸Ӹ� �����ϴµ� ����� �� �ִ� ���� �ڵ�...?

	// �𸮾󿡼� �˶� ���� �� ���� �ð��� �Ǹ� �˷� �ִ� Ÿ�̸� ����� ����. - ���� �ϳ��� �ִ� �۷ι� Ÿ�̸� �Ŵ����� �̿��� ����� �� �ִ�.
	// �۷ι� Ÿ�̸� �Ŵ������� �˶��ð踦 �Ѱ��ְ� ���ϴ� �ð��� �Ǹ� �˷��޶� ��û�ϴµ� -> �Ŵ������� �˸����� �Լ� Ȥ�� �������̵�
	// �������̵� : https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/
	// �������̵� : �Լ��� ���ε� �ϴ� ���·� ��Ͻ���, callback �Լ��� ���� Ȱ���� �� �ִ�.
	// �ݹ��Լ�? https://www.youtube.com/watch?v=-iZlNnTGotk
	// �Լ��� �Ķ���ͷ� ���� �Լ�, �뵵 : ���������� �����ϰ� ���� �� ����.  
	// � ��ư ������ �� Ư�� �ڵ� �����ϰ� �ʹ� : �Լ� �Ķ���� �ڸ��� �Լ� �ִ´�.
	// void first(�Ķ����) { �Ķ����() }, void second(){}
	// -> void first(second) �ϸ� { second() } ���� == ������ ����
	// �ݹ��Լ� ���������� �ڿ� ����� ������ ���ؼ� �� �� �ִ�.  
	FTimerHandle spawnTimerHandle;


	// �� ���� �Լ�
	void CreateEnemy();

	// ������ ��ġ ���� ã�� �Ҵ��ϱ� - �ű⼭ �ڼ��� ����
	// BP_EnemySpawnPoint�� ��ϵ� �̸��� ���͸� ��� ã�� �迭�� �߰� : spawnPoints
	void FindSpawnPoints();
};
