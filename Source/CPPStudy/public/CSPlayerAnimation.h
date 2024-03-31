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
	// 여기에 플레이어 이동속도를 왜 추가하지?
	// abp 창에서 변수로 사용하기 위함
	// 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CSPlayerAnimation") 
	float speed = 0;

	// 블랜드 스페이스의 방향을 위함
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CSPlayerAnimation")
	float direction = 0;


	// 매 프레임 갱신되는 함수...를 내가 만들어야함
	// NativeUpdateAnimation == Event Blueprint Update Animation == Tick() : 틱마다
	// override : 오버리이드 == 재정의 가능하다!를 선언
	// 가상함수 반환없음 함수명(float 변수명) 재정의가능, 반드시 재정의 해야 한다는 뜻  
	// NativeUpdateAnimation : g
	virtual void NativeUpdateAnimation(float Delta) override;

	// 점프를 스페이스바가 아닌 공중에 뜬 상태로 판단하기 위해 공중이냐 아니냐로 판별
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CSPlayerAnimation")
	bool isInAir = false;

};
