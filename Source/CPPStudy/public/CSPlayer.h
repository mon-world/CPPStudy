// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSPlayer.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

// ��������Ʈ ����? -> ��������Ʈ ������ �ָ�, ����� �Լ� �ڵ� ����
// ��, ȣ���ϴ� �� ���忡�� ���� �Լ��� ����� ������ �� �ʿ� ����
// ��ϵ� ������Ʈ�� �̸� �˰� ���� �ʴ��� ������� �Է��� ���ް����ϴ�.
// == ���⿡ ����� �̺�Ʈ�� �����������ν� �Է� ���ε��ߴ��� : bindaction ó���� �����ϴ�.
// ��Ƽĳ��Ʈ ��������Ʈ. ��, ��������Ʈ�� ���� ���� ó�� �Լ��� ����ϰڴٴ� ��
// �Ű������� 1���� �����Ƿ� OneParam�� ����Ѵ�. -> �ڷ��� �������
// �̸�, �ڷ��� ����
DECLARE_MULTICAST_DELEGATE_OneParam(FinputBindingDelegate, class UInputComponent*);

UCLASS()
class CPPSTUDY_API ACSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSPlayer();

	// �Է� ���ε� ��������Ʈ
	// ��������Ʈ �ڷ��� ���� ����
	FinputBindingDelegate onInputBindingDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UPROPERTY(EditAnywhere) : BP �����ͳ� ��ġ�� ������Ʈ ������ �гο��� ������ ����		// https://darkcatgame.tistory.com/62
	// �� ī�װ��� ������ �г��� �׸� �̸��� ��Ī�� �� ����, | �� �Ἥ ���̸� ���� ī�װ� ��Ī �����ϴ�.  
	UPROPERTY(VisibleAnywhere, Category = Camera)
	// class�� ���� ���� ���� ���� : �ȱ׷��� ���� �������� ������Ʈ.h�� #include �ؾ��ϴµ�, ������ �ð� �þ
	// �������� ���� : USpringArmComponent �޸� ũ�� ��
	class USpringArmComponent* springArmComp;
	// BlueprintReadOnly : �������Ʈ���� ���� �б� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* csCamComp;

	// �̵��ӵ� ó�� -> Vector �̶�� ���� ���������
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

	// shift ������ ������Ʈ �� �� �ִ� �׼� �߰��� ��
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	//UPROPERTY(EditAnywhere, Category = "Input")
	//UInputAction* DashAction;




	// Input | Jump : BP_Player�� details�� Input�� ���� ī�װ��� Jump�� �����. 
	// �׷��� �̷��� �ع����� ������ �ִ� Input�� �ƴ϶� ���� Input�� ���ܼ� ������ ���� ���Ⱑ ��...
	//UPROPERTY(EditAnywhere, Category = "Input | Jump")
	//UInputAction* JumpAction;

	//UPROPERTY(EditAnywhere, Category = "Input | Look")
	//UInputAction* LookAction;

	//UPROPERTY(EditAnywhere, Category = "Input | Move")
	//UInputAction* MoveAction;

	// �޸���
	

protected:
	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);
	void SprintStart(const FInputActionInstance& Instance);
	void SprintEnd(const FInputActionInstance& Instance);
	//void Dash(const FInputActionInstance& Instance);

};
