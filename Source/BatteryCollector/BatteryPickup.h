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

	//wascollected �Լ� �������̵� ���ø������̼� ��� ������ �������Ʈ ����Ƽ�� �̺�Ʈ �̱� ����
	void WasCollected_Implementation() override;

	//�ۺ������� ��𿡼��� ���͸��� �Ŀ����� ���� �� ����
	float GetPower();
	
protected:
	//���͸��� ĳ���Ϳ��� ������ �Ŀ�
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float BatteryPower;


};
