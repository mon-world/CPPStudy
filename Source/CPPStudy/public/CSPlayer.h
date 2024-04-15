// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSPlayer.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

// 델리게이트 왜함? -> 델리게이트 실행해 주면, 연결된 함수 자동 실행
// 즉, 호출하는 애 입장에서 누가 함수를 등록해 놨는지 알 필요 없음
// 등록된 컴포넌트를 미리 알고 있지 않더라도 사용자의 입력을 전달가능하다.
// == 여기에 등록한 이벤트를 실행해줌으로써 입력 바인딩했던거 : bindaction 처리가 가능하다.
// 멀티캐스트 델리게이트. 즉, 델리게이트에 여러 개의 처리 함수를 등록하겠다는 뜻
// 매개변수를 1개만 받으므로 OneParam을 사용한다. -> 자료형 써줘야함
// 이름, 자료형 순서
DECLARE_MULTICAST_DELEGATE_OneParam(FinputBindingDelegate, class UInputComponent*);

UCLASS()
class CPPSTUDY_API ACSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSPlayer();

	// 입력 바인딩 델리게이트
	// 델리게이트 자료형 변수 선언
	FinputBindingDelegate onInputBindingDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UPROPERTY(EditAnywhere) : BP 에디터나 배치된 오브젝트 디테일 패널에서 볼수만 있음		// https://darkcatgame.tistory.com/62
	// 뒤 카테고리는 디테일 패널의 항목 이름을 명칭할 수 있음, | 를 써서 붙이면 하위 카테고리 명칭 가능하다.  
	UPROPERTY(VisibleAnywhere, Category = Camera)
	// class를 통한 전방 선언 이유 : 안그러면 위에 스프링암 컴포넌트.h를 #include 해야하는데, 컴파일 시간 늘어남
	// 포인터인 이유 : USpringArmComponent 메모리 크기 모름
	class USpringArmComponent* springArmComp;
	// BlueprintReadOnly : 블루프린트에서 변수 읽기 가능
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* csCamComp;

	// 이동속도 처리 -> Vector 이라는 곳에 묶어버리자
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vector|Speed")
	float walkSpeed = 600;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vector|Speed")
	float sprintSpeed = 900;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vector|Speed")
	//float dashDistance = 6000;


	// -------------------------

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// shift 누르면 스프린트 할 수 있는 액션 추가할 것
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	//UPROPERTY(EditAnywhere, Category = "Input")
	//UInputAction* DashAction;




	// Input | Jump : BP_Player의 details에 Input의 하위 카테고리로 Jump가 생긴다. 
	// 그런데 이렇게 해버리면 기존에 있는 Input이 아니라 새로 Input이 생겨서 하위로 들어가서 보기가 좀...
	//UPROPERTY(EditAnywhere, Category = "Input | Jump")
	//UInputAction* JumpAction;

	//UPROPERTY(EditAnywhere, Category = "Input | Look")
	//UInputAction* LookAction;

	//UPROPERTY(EditAnywhere, Category = "Input | Move")
	//UInputAction* MoveAction;

	// 달리기
	

protected:
	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);
	void SprintStart(const FInputActionInstance& Instance);
	void SprintEnd(const FInputActionInstance& Instance);
	//void Dash(const FInputActionInstance& Instance);

};
