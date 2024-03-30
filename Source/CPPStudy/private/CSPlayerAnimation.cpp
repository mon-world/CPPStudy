// Fill out your copyright notice in the Description page of Project Settings.


#include "CSPlayerAnimation.h"
#include "CSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

// 헤더파일의 UCSPlayerAnimation에서 TickAnim( = tick)을 오버라이딩 하겠다.
// 
void UCSPlayerAnimation::NativeUpdateAnimation(float delta)
{
	// super : 부모 클래스의 맴버에 접근하도록 하는 키워드
	// 단, private는 접근 못한다.
	// 부모 클래스의 멤버와 이름이 같은 자식 클래스의 멤버가 있을 때, 이를 구별하기 위해 사용되기도 함
	
	Super::NativeUpdateAnimation(delta);

	// 플레이어의 속도를 가져와 speed에 할당 <- .h에서 만들었었음
	// TryGetPawnOwner : 현재 AnimInstnace를 소유중인 Pawn을 가져오는것을 시도함.
	// AnimInstance : UAnimInstance의 c++ 객체. ABP는 UAnimInstance에서 파생됨
	// 기본적으로 UAnimInstance에서 ABP를 생성하고 이를 BP로만 확장.
	// https://forums.unrealengine.com/t/what-is-an-animinstance-theory-question/462924/2
	// 
	// 흐름 보기
	// 1. ABP의 변수 및 스크립트 관리를 해야한다
	// 2. 이를 위해선 ABP가 상속할 수 있는 AnimInstance 타입의 c++ 클래스가 있어야한다.
	// 3. 따라서, 이 클래스를 만든 뒤, ABP_Player를 내가 만든 C++클래스를 상속받게 한다.
	// 
	// 부모 클래스를 바꾸지 않았었나...? <- 다시 빌드하면서 사라졌을 것. 확인하기
	// auto : 형식이 추론되는 변수를 선언하는 역할...? <- 정확히 무슨 뜻이지
	// -> 함수 반환 형식이 변경될 때를 포함해서, 식의 형식이 변경되면 작동
	// 자동 형변환인가 그럼? 형변환은 아니고 자동 자료형 지정???
	auto tempPawn = TryGetPawnOwner();

	// 이 폰을 플레이어로 캐스팅한다.
	// auto csplayer = Cast<내가 원하는 타입>(형변환 하고 싶은 녀석)
	auto csPlayerAnim = Cast<ACSPlayer>(tempPawn);
	
	if (csPlayerAnim)
	{
		// 이동속도에 따라 달리냐 / Idle 이냐 할 것이므로 이동속도 필요
		// x,y,z 축의 속도(cm/s)를 가져와라
		// 왜 -> 사용? ASPlayer *csPlayerAnim 이므로 
		FVector velocity = csPlayerAnim->GetVelocity();
		FVector forwardVector = csPlayerAnim->GetActorForwardVector();

		// 내가 가고있는 방향의 이동속도만 필요함
		speed = FVector::DotProduct(forwardVector, velocity);
		
		// 플레이어가 공중에 있냐 없냐
		// GetCharacterMovement
		auto movement = csPlayerAnim->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}




}
