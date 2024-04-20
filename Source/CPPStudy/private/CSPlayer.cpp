// Fill out your copyright notice in the Description page of Project Settings.


#include "CSPlayer.h"
#include "PlayerMove.h"						// 클래스 사용을 위해 씀
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
//이름이 같으므로 생성자 함수이고, 생성자 함수이므로, 객체가 인스턴스화 될 때 자동으로 호출된다.
ACSPlayer::ACSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/GameFramework/AActor/PrimaryActorTick/
	// PrimaryActorTick : 기본 액터 틱 함수는 TickActor()를 호출한다. 
	// TickActor() : 매 프레임마다 Tick()을 호출한다.
	// Tick() : 액터나 컴포넌트에 한 프레임마다 코드 or BP 스크립트를 실행시키는 것. // https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Actors/Ticking/
	// bCanEverTick의 기본값은 1, false일 시 틱이 발생하지 않는다.
	// 해석 : 매 프레임마다 틱을 발생시켜라.
	PrimaryActorTick.bCanEverTick = true;

	// 1. 스켈레탈메시 데이터를 불러오고 싶다.
	// ConstructorHelpers::FObjectFinder는 StaticLoadObject를 사용해서 지정된 UObject로의 참조자를 찾는다. // https://dev.epicgames.com/documentation/ko-kr/unreal-engine/gameplay-classes-in-unreal-engine?application_version=5.3
	// StaticLoadObject : 파일 이름으로 객체를 찾거나 로드한다.	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/CoreUObject/UObject/StaticLoadObject/
	// FObjectFinder가 템플릿이고, 따라서 TempMesh는 USkeletalMesh의 자료형을 갖는다.
	// TEXT에 넣은 경로를 가져와라.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (TempMesh.Succeeded())
	{
		// GetMesh : 메쉬 컴포넌트를 가져온다.
		// SetSkeletalMesh : BP에서의 스켈레톤 메쉬 에셋
		// TempMesh.Object : 구조체 FObjectFinder의 멤버변수로써, USkeletalMesh 자료형 타입의 로드된 데이터가 들어가있음.
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		// 2. Mesh 컴포넌트의 위치와 회전 값을 설정하고 싶다.
		// SetRelativeLocationAndRotation : 뒤에 위치값과 회전값을 받고, 적용시킨다
		// 주의 : FRotator는 들어가보면 pitch, yaw, roll 이고, 인게임은 pitch, roll, yaw 순임
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

		// 3. 카메라를 붙이고 싶다.
		// 3-1. SpringArm 컴포넌트 붙이기
		// CreateDefaultSubobject : 클래스를 인스턴스화 시키는 메소드
		springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
		// SetupAttachment : 자식으로 등록하는 함수.
		springArmComp->SetupAttachment(RootComponent);
		// SetRelativeLocation : 상대좌표
		springArmComp->SetRelativeLocation(FVector(0, 70, 90));
		// 스프링 암의 길이
		springArmComp->TargetArmLength = 400;
		// bUsePawnControlRotation : BP의 use pawn control rotation
		springArmComp->bUsePawnControlRotation = true;
		// 3-2. Camera 컴포넌트 붙이기
		csCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CSCamComp"));
		csCamComp->SetupAttachment(springArmComp);
		csCamComp->bUsePawnControlRotation = false;
	}

	// CreateDefaultSubobject : 클래스를 인스턴스화 시키는 메소드
	// 위에 이걸로 스프링 암도 만들고, 카메라도 만들고... <> 안에 들어가는 comp를 만들어낸다.
	// UPlayerMove를 만들어낸 것. playermove 컴포넌트가 CSPlayer에 추가됐다.  
	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
}

// Called when the game starts or when spawned
void ACSPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 이곳에서 어떻게든 PlayerMove.h나 .cpp로 옮기는 연구 필요
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// 초기 속도 설정 : 600
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

	// 입력 바인딩을 컴포넌트에서 처리하도록 한다.
	// 진짜 집 옮기네
	// 결국 이 함수도 사용자의 입력 맵핑 값과 처리할 함수를 바인딩해주는 기능을 담당한다.
	// comp에서 입력 처리를 할 수 있도록 기능을 분산하게 됨
	playerMove->SetupInputBinding(PlayerInputComponent);

	// PlayerMove.cpp로 이사가요~
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACSPlayer::Jump);
	// Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACSPlayer::Look);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACSPlayer::Move);
	// 여기서 Input 그대로 사용할 수 없나?
	// UEnhancedInputComponent 자체가 enhanced 에서 사용하기 위해 쓴것이므로...
	// 아닌데 쓸 수 있을거같은데... 해냈다 <- 아님. 수정 필요
	Input->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACSPlayer::SprintStart);
	Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACSPlayer::SprintEnd);
	//// Triggered의 반대가 Completed : Triggered -> None
	//Input->BindAction(DashAction, ETriggerEvent::Triggered, this, &ACSPlayer::Dash);


}

void ACSPlayer::Move(const FInputActionInstance& Instance)
{
	// FVector2D : using FVector2D 	= UE::Math::TVector2<double>;		// UE_DECLARE_LWC_TYPE(Vector2,, FVector2D);
	// get<FVector2D> : return Axis2D(Value.X, Value.Y);
	// 즉, 여기서 GetValue().Get<FVector2D>은 각각의 크기를 가져온다. 
	FVector2D MovementVector = Instance.GetValue().Get<FVector2D>();

	// 여기 const를 왜 붙이는거지???
	// 로테이션 = 컨트롤러에서 회전 좌표를 가져온다.
	// Frotator은 회전에 대한 컨테이너를 구현하고, 모든 회전값은 각도로 저장	// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FRotator/
	const FRotator Rotation = Controller->GetControlRotation();
	// 각도를 저장한 것 중, Yaw 부분만 가져와서 YawRotation을 초기화한다.
	// 단, pitch, yaw, roll 순인것 잊지 말기
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// FRotationMatrix : 캐릭터 중심을 0,0,0이라 잡고, 각 축에서 얼마나 회전해있는지를 본다.
	// 내가 가려는 방향 = 평면에서 내가 yaw 방향으로 얼마나 돌렸는지 봄(자신이 찾고 싶은 축이 가지는 방향 가져옴 : X 방향)
	// https://pppgod.tistory.com/26
	const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// 마찬가지로, Y(내 캐릭터 오른쪽)축 이 가지는 방향값 가져옴
	// 어째서 RightDirection으로 명명했는가 : 키 설정해서도 그렇고, 언리얼에선 전방방향과 오른쪽 방향이 각 축의 + 이기 때문
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// AddMovementInput : 주어진 방향벡터를 따라 이동입력 추가
	// 어째서 FowardDirection 에선 X축을 가져왔었으면서, 크기는 Y를 가져오는가???
	// X,Y 너무 궁금해서 바꿔봄 : W와 D의 키입력이 서로 되고 있음 -> MovementVector의 .Y값이 전방방향 크기인듯
	// 주어진 벡터들로 이동하라(방향, 이동거리)
	AddMovementInput(FowardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);

}

// PlayerMove로 이사~
//void ACSPlayer::Look(const FInputActionInstance& Instance)
//{
//	FVector2D LookVector = Instance.GetValue().Get<FVector2D>();
//
//
//	// Yaw 방향의 이동입력
//	AddControllerYawInput(LookVector.X);
//	// Pitch 방향의 이동입력
//	AddControllerPitchInput(LookVector.Y);
//
//}

// 여길 어떻게든 고치기

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

/* 궁금증
1. 마우스 감도 조절 변수는 없나? - 그냥 곱으로 해버리기?
2. 

*/

/*DECLARE_MULTICAST_DELEGATE_OneParam(FinputBindingDelegate, UInputComponent*)
{
}*/
