// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//웨얼 투 스폰 값을 반환해준다
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	//박스 컴포넌트 볼륨 속의 랜덤한 좌표를 반환합니다.
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	//볼륨 스폰의 픽업 스폰 작동을 조정하는 함수
	UFUNCTION(Blueprintcallable, Category = "Spawning")
	void SetSpawningActive(bool bShouldSpawn);

//protected:
	//픽업 스폰
	UPROPERTY(EditAnyWhere, Category = "Spawning")
	TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	//생성시 최소 지연 시간
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	//생성시 최대 지연 시간
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;


private:
	//아이템 스폰 위치를 지정할 박스 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;
	
	//새 아이템 생성
	void SpawnPickup();
	
	//현재 아이템 생성 딜레이값
	float SpawnDelay;

};
