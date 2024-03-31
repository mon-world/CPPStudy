// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CSPlayerAnimation.generated.h"

/**
 * 
 */
UCLASS()
class CPPSTUDY_API UCSPlayerAnimation : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// ���⿡ �÷��̾� �̵��ӵ��� �� �߰�����?
	// abp â���� ������ ����ϱ� ����
	// 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CSPlayerAnimation") 
	float speed = 0;

	// ���� �����̽��� ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CSPlayerAnimation")
	float direction = 0;


	// �� ������ ���ŵǴ� �Լ�...�� ���� ��������
	// NativeUpdateAnimation == Event Blueprint Update Animation == Tick() : ƽ����
	// override : �������̵� == ������ �����ϴ�!�� ����
	// �����Լ� ��ȯ���� �Լ���(float ������) �����ǰ���, �ݵ�� ������ �ؾ� �Ѵٴ� ��  
	// NativeUpdateAnimation : g
	virtual void NativeUpdateAnimation(float Delta) override;

	// ������ �����̽��ٰ� �ƴ� ���߿� �� ���·� �Ǵ��ϱ� ���� �����̳� �ƴϳķ� �Ǻ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CSPlayerAnimation")
	bool isInAir = false;

};
