// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSPlayer.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;


UCLASS()
class CPPSTUDY_API ACSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSPlayer();

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

public:
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// Input | Jump : BP_Player의 details에 Input의 하위 카테고리로 Jump가 생긴다. 
	// 그런데 이렇게 해버리면 기존에 있는 Input이 아니라 새로 Input이 생겨서 하위로 들어가서 보기가 좀...
	//UPROPERTY(EditAnywhere, Category = "Input | Jump")
	//UInputAction* JumpAction;

	//UPROPERTY(EditAnywhere, Category = "Input | Look")
	//UInputAction* LookAction;

	//UPROPERTY(EditAnywhere, Category = "Input | Move")
	//UInputAction* MoveAction;

protected:
	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);


};
