// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "BatteryCollector.h"
#include "Classes/Components/StaticMeshComponent.h"


ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);
	//배터리의 기본값을 설정
	BatteryPower = 150.0f;
}

void ABatteryPickup::WasCollected_Implementation()
{
	//베이스 픽업 스크립트 사용
	Super::WasCollected_Implementation();
	//배터리 아이템 파괴하기
	Destroy();


}

//배터리의 파워 값을 반환함
float ABatteryPickup::GetPower()
{
	return BatteryPower;
}

