// Fill out your copyright notice in the Description page of Project Settings.


#include "CSPlayerAnimation.h"
#include "CSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

// ��������� UCSPlayerAnimation���� TickAnim( = tick)�� �������̵� �ϰڴ�.
// 
void UCSPlayerAnimation::NativeUpdateAnimation(float delta)
{
	// super : �θ� Ŭ������ �ɹ��� �����ϵ��� �ϴ� Ű����
	// ��, private�� ���� ���Ѵ�.
	// �θ� Ŭ������ ����� �̸��� ���� �ڽ� Ŭ������ ����� ���� ��, �̸� �����ϱ� ���� ���Ǳ⵵ ��
	
	Super::NativeUpdateAnimation(delta);

	// �÷��̾��� �ӵ��� ������ speed�� �Ҵ� <- .h���� ���������
	// TryGetPawnOwner : ���� AnimInstnace�� �������� Pawn�� �������°��� �õ���.
	// AnimInstance : UAnimInstance�� c++ ��ü. ABP�� UAnimInstance���� �Ļ���
	// �⺻������ UAnimInstance���� ABP�� �����ϰ� �̸� BP�θ� Ȯ��.
	// https://forums.unrealengine.com/t/what-is-an-animinstance-theory-question/462924/2
	// 
	// �帧 ����
	// 1. ABP�� ���� �� ��ũ��Ʈ ������ �ؾ��Ѵ�
	// 2. �̸� ���ؼ� ABP�� ����� �� �ִ� AnimInstance Ÿ���� c++ Ŭ������ �־���Ѵ�.
	// 3. ����, �� Ŭ������ ���� ��, ABP_Player�� ���� ���� C++Ŭ������ ��ӹް� �Ѵ�.
	// 
	// �θ� Ŭ������ �ٲ��� �ʾҾ���...? <- �ٽ� �����ϸ鼭 ������� ��. Ȯ���ϱ�
	// auto : ������ �߷еǴ� ������ �����ϴ� ����...? <- ��Ȯ�� ���� ������
	// -> �Լ� ��ȯ ������ ����� ���� �����ؼ�, ���� ������ ����Ǹ� �۵�
	// �ڵ� ����ȯ�ΰ� �׷�? ����ȯ�� �ƴϰ� �ڵ� �ڷ��� ����???
	auto tempPawn = TryGetPawnOwner();

	// �� ���� �÷��̾�� ĳ�����Ѵ�.
	// auto csplayer = Cast<���� ���ϴ� Ÿ��>(����ȯ �ϰ� ���� �༮)
	auto csPlayerAnim = Cast<ACSPlayer>(tempPawn);
	
	if (csPlayerAnim)
	{
		// �̵��ӵ��� ���� �޸��� / Idle �̳� �� ���̹Ƿ� �̵��ӵ� �ʿ�
		// x,y,z ���� �ӵ�(cm/s)�� �����Ͷ�
		// �� -> ���? ASPlayer *csPlayerAnim �̹Ƿ� 
		FVector velocity = csPlayerAnim->GetVelocity();
		FVector forwardVector = csPlayerAnim->GetActorForwardVector();

		// ���� �����ִ� ������ �̵��ӵ��� �ʿ���
		speed = FVector::DotProduct(forwardVector, velocity);
		
		// �÷��̾ ���߿� �ֳ� ����
		// GetCharacterMovement
		auto movement = csPlayerAnim->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}




}
