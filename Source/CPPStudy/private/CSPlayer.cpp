// Fill out your copyright notice in the Description page of Project Settings.


#include "CSPlayer.h"
#include "PlayerMove.h"						// Ŭ���� ����� ���� ��
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
//�̸��� �����Ƿ� ������ �Լ��̰�, ������ �Լ��̹Ƿ�, ��ü�� �ν��Ͻ�ȭ �� �� �ڵ����� ȣ��ȴ�.
ACSPlayer::ACSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/GameFramework/AActor/PrimaryActorTick/
	// PrimaryActorTick : �⺻ ���� ƽ �Լ��� TickActor()�� ȣ���Ѵ�. 
	// TickActor() : �� �����Ӹ��� Tick()�� ȣ���Ѵ�.
	// Tick() : ���ͳ� ������Ʈ�� �� �����Ӹ��� �ڵ� or BP ��ũ��Ʈ�� �����Ű�� ��. // https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Actors/Ticking/
	// bCanEverTick�� �⺻���� 1, false�� �� ƽ�� �߻����� �ʴ´�.
	// �ؼ� : �� �����Ӹ��� ƽ�� �߻����Ѷ�.
	PrimaryActorTick.bCanEverTick = true;

	// 1. ���̷�Ż�޽� �����͸� �ҷ����� �ʹ�.
	// ConstructorHelpers::FObjectFinder�� StaticLoadObject�� ����ؼ� ������ UObject���� �����ڸ� ã�´�. // https://dev.epicgames.com/documentation/ko-kr/unreal-engine/gameplay-classes-in-unreal-engine?application_version=5.3
	// StaticLoadObject : ���� �̸����� ��ü�� ã�ų� �ε��Ѵ�.	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/CoreUObject/UObject/StaticLoadObject/
	// FObjectFinder�� ���ø��̰�, ���� TempMesh�� USkeletalMesh�� �ڷ����� ���´�.
	// TEXT�� ���� ��θ� �����Ͷ�.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (TempMesh.Succeeded())
	{
		// GetMesh : �޽� ������Ʈ�� �����´�.
		// SetSkeletalMesh : BP������ ���̷��� �޽� ����
		// TempMesh.Object : ����ü FObjectFinder�� ��������ν�, USkeletalMesh �ڷ��� Ÿ���� �ε�� �����Ͱ� ������.
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		// 2. Mesh ������Ʈ�� ��ġ�� ȸ�� ���� �����ϰ� �ʹ�.
		// SetRelativeLocationAndRotation : �ڿ� ��ġ���� ȸ������ �ް�, �����Ų��
		// ���� : FRotator�� ������ pitch, yaw, roll �̰�, �ΰ����� pitch, roll, yaw ����
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

		// 3. ī�޶� ���̰� �ʹ�.
		// 3-1. SpringArm ������Ʈ ���̱�
		// CreateDefaultSubobject : Ŭ������ �ν��Ͻ�ȭ ��Ű�� �޼ҵ�
		springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
		// SetupAttachment : �ڽ����� ����ϴ� �Լ�.
		springArmComp->SetupAttachment(RootComponent);
		// SetRelativeLocation : �����ǥ
		springArmComp->SetRelativeLocation(FVector(0, 70, 90));
		// ������ ���� ����
		springArmComp->TargetArmLength = 400;
		// bUsePawnControlRotation : BP�� use pawn control rotation
		springArmComp->bUsePawnControlRotation = true;
		// 3-2. Camera ������Ʈ ���̱�
		csCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CSCamComp"));
		csCamComp->SetupAttachment(springArmComp);
		csCamComp->bUsePawnControlRotation = false;
	}

	// CreateDefaultSubobject : Ŭ������ �ν��Ͻ�ȭ ��Ű�� �޼ҵ�
	// ���� �̰ɷ� ������ �ϵ� �����, ī�޶� �����... <> �ȿ� ���� comp�� ������.
	// UPlayerMove�� ���� ��. playermove ������Ʈ�� CSPlayer�� �߰��ƴ�.  
	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
}

// Called when the game starts or when spawned
void ACSPlayer::BeginPlay()
{
	Super::BeginPlay();

	// �̰����� ��Ե� PlayerMove.h�� .cpp�� �ű�� ���� �ʿ�
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// �ʱ� �ӵ� ���� : 600
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;


}

// Called every frame
void ACSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// �Է� ���ε��� ������Ʈ���� ó���ϵ��� �Ѵ�.
	// ��¥ �� �ű��
	// �ᱹ �� �Լ��� ������� �Է� ���� ���� ó���� �Լ��� ���ε����ִ� ����� ����Ѵ�.
	// comp���� �Է� ó���� �� �� �ֵ��� ����� �л��ϰ� ��
	playerMove->SetupInputBinding(PlayerInputComponent);

	// PlayerMove.cpp�� �̻簡��~
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACSPlayer::Jump);
	// Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACSPlayer::Look);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACSPlayer::Move);
	// ���⼭ Input �״�� ����� �� ����?
	// UEnhancedInputComponent ��ü�� enhanced ���� ����ϱ� ���� �����̹Ƿ�...
	// �ƴѵ� �� �� �����Ű�����... �س´� <- �ƴ�. ���� �ʿ�
	Input->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACSPlayer::SprintStart);
	Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACSPlayer::SprintEnd);
	//// Triggered�� �ݴ밡 Completed : Triggered -> None
	//Input->BindAction(DashAction, ETriggerEvent::Triggered, this, &ACSPlayer::Dash);


}

void ACSPlayer::Move(const FInputActionInstance& Instance)
{
	// FVector2D : using FVector2D 	= UE::Math::TVector2<double>;		// UE_DECLARE_LWC_TYPE(Vector2,, FVector2D);
	// get<FVector2D> : return Axis2D(Value.X, Value.Y);
	// ��, ���⼭ GetValue().Get<FVector2D>�� ������ ũ�⸦ �����´�. 
	FVector2D MovementVector = Instance.GetValue().Get<FVector2D>();

	// ���� const�� �� ���̴°���???
	// �����̼� = ��Ʈ�ѷ����� ȸ�� ��ǥ�� �����´�.
	// Frotator�� ȸ���� ���� �����̳ʸ� �����ϰ�, ��� ȸ������ ������ ����	// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FRotator/
	const FRotator Rotation = Controller->GetControlRotation();
	// ������ ������ �� ��, Yaw �κи� �����ͼ� YawRotation�� �ʱ�ȭ�Ѵ�.
	// ��, pitch, yaw, roll ���ΰ� ���� ����
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// FRotationMatrix : ĳ���� �߽��� 0,0,0�̶� ���, �� �࿡�� �󸶳� ȸ�����ִ����� ����.
	// ���� ������ ���� = ��鿡�� ���� yaw �������� �󸶳� ���ȴ��� ��(�ڽ��� ã�� ���� ���� ������ ���� ������ : X ����)
	// https://pppgod.tistory.com/26
	const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// ����������, Y(�� ĳ���� ������)�� �� ������ ���Ⱚ ������
	// ��°�� RightDirection���� ����ߴ°� : Ű �����ؼ��� �׷���, �𸮾󿡼� �������� ������ ������ �� ���� + �̱� ����
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// AddMovementInput : �־��� ���⺤�͸� ���� �̵��Է� �߰�
	// ��°�� FowardDirection ���� X���� �����Ծ����鼭, ũ��� Y�� �������°�???
	// X,Y �ʹ� �ñ��ؼ� �ٲ㺽 : W�� D�� Ű�Է��� ���� �ǰ� ���� -> MovementVector�� .Y���� ������� ũ���ε�
	// �־��� ���͵�� �̵��϶�(����, �̵��Ÿ�)
	AddMovementInput(FowardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);

}

// PlayerMove�� �̻�~
//void ACSPlayer::Look(const FInputActionInstance& Instance)
//{
//	FVector2D LookVector = Instance.GetValue().Get<FVector2D>();
//
//
//	// Yaw ������ �̵��Է�
//	AddControllerYawInput(LookVector.X);
//	// Pitch ������ �̵��Է�
//	AddControllerPitchInput(LookVector.Y);
//
//}

// ���� ��Ե� ��ġ��

void ACSPlayer::SprintStart(const FInputActionInstance& Instance)
{
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}


void ACSPlayer::SprintEnd(const FInputActionInstance& Instance)
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

//void ACSPlayer::Dash(const FInputActionInstance& Instance)
//{
//
//
//}

/* �ñ���
1. ���콺 ���� ���� ������ ����? - �׳� ������ �ع�����?
2. 

*/

/*DECLARE_MULTICAST_DELEGATE_OneParam(FinputBindingDelegate, UInputComponent*)
{
}*/
