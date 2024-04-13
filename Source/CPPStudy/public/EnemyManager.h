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
	// 랜덤시간의 최소 최댓값 : 1~5 사이에서 뽑겠다
	UPROPERTY(EditAnywhere, Category = "SpawnSettings") float minTime = 1;
	UPROPERTY(EditAnywhere, Category = "SpawnSettings") float maxTime = 5;

	// 스폰할 위치 정보 배열
	// AActor* 형의 값이 들어가는 arr
	// Tarray는 템플릿 클래스, 타입이 같은 다른 오브젝트들을 넣을 수 있는 클래스 == 컨테이너 클래스
	// https://jhtop0419.tistory.com/41
	// 2가지 프로퍼티로 정의 : 엘리먼트 타입, 엘로게이터
	// 엘리먼트 타입 : add함수와 emplace 함수 존재. add는 엘리먼트 타입의 인스턴스를 컨테이너에 복사
	// emplace 함수는 지정한 파라미터를 사용하여 엘리먼트 타입의 인스턴스를 새로 생성
	// add는 임시 데이터 타입을 생성 후 내용물을 컨테이너 안의 새로운 데이터 타입으로 이동 / emplace는 직접 만듦 - 임시변수 생성 x
	// append : 다른 TArray 또는 일반 c배열로의 포인터 및 해당 배열의 크기에 다수의 엘리먼트를 한꺼번에 넣을 수 있음
	// -> 노션에 정리
	// TArray 형태라 하위 여러개 받을 수 있는듯. + 누르면 추가되게. 에디터에서 확인 ㄱㄱ  
	UPROPERTY(EditAnywhere, Category = "SpawnSettings") TArray<class AActor*> spawnPoints;

	// AEenmy 타입의 bp 할당받을 변수
	// TSubclassOf<T>
	// UClass 타입 안정성을 보장하는 템플릿 클래스
	// 클래스 할당의 선택지를 제한시킬 수 있다.
	// https://jhtop0419.tistory.com/51
	UPROPERTY(EditAnywhere, Category = "SpawnSettings") TSubclassOf<class AEnemy> enemyFactory;

	// 스폰을 위한 알람 타이머
	// 핸들을 가지고 있어야 다음에 종료를 할 수 있음
	// https://online-unreal.tistory.com/15
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/FTimerHandle/
	// 동일한 대리인이 있는 타이머를 구별하는데 사용할 수 있는 고유 핸들...?

	// 언리얼에서 알람 설정 해 놓고 시간이 되면 알려 주는 타이머 기능을 제공. - 월드 하나에 있는 글로벌 타이머 매니저를 이용해 사용할 수 있다.
	// 글로벌 타이머 매니저한테 알람시계를 넘겨주고 원하는 시간이 되면 알려달라 요청하는듯 -> 매니저에게 알림받을 함수 혹은 델리케이드
	// 델리케이드 : https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/
	// 델리케이드 : 함수를 바인딩 하는 형태로 등록시켜, callback 함수와 같이 활용할 수 있다.
	// 콜백함수? https://www.youtube.com/watch?v=-iZlNnTGotk
	// 함수에 파라미터로 들어가는 함수, 용도 : 순차적으로 실행하고 싶을 때 쓴다.  
	// 어떤 버튼 눌렀을 떄 특정 코드 실행하고 싶다 : 함수 파라미터 자리에 함수 넣는다.
	// void first(파라미터) { 파라미터() }, void second(){}
	// -> void first(second) 하면 { second() } 실행 == 순차적 실행
	// 콜백함수 만들어놓으면 뒤에 맘대로 순서를 정해서 쓸 수 있다.  
	FTimerHandle spawnTimerHandle;


	// 적 생성 함수
	void CreateEnemy();

	// 스폰할 위치 동적 찾아 할당하기 - 거기서 자세한 설명
	// BP_EnemySpawnPoint로 등록된 이름의 액터를 모두 찾아 배열에 추가 : spawnPoints
	void FindSpawnPoints();
};
