// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public :
	// Sets default values for this actor's properties
	ABatteryPickup();

	//wascollected 함수 오버라이딩 임플리멘테이션 사용 이유는 블루프린트 네이티브 이벤트 이기 때문
	void WasCollected_Implementation() override;

	//퍼블릭형으로 어디에서든 배터리의 파워값을 얻을 수 있음
	float GetPower();
	
protected:
	//배터리가 캐릭터에게 보내는 파워
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float BatteryPower;


};
