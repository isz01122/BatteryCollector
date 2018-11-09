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

	//���� �� ���� ���� ��ȯ���ش�
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	//�ڽ� ������Ʈ ���� ���� ������ ��ǥ�� ��ȯ�մϴ�.
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	//���� ������ �Ⱦ� ���� �۵��� �����ϴ� �Լ�
	UFUNCTION(Blueprintcallable, Category = "Spawning")
	void SetSpawningActive(bool bShouldSpawn);

//protected:
	//�Ⱦ� ����
	UPROPERTY(EditAnyWhere, Category = "Spawning")
	TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	//������ �ּ� ���� �ð�
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	//������ �ִ� ���� �ð�
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;


private:
	//������ ���� ��ġ�� ������ �ڽ� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;
	
	//�� ������ ����
	void SpawnPickup();
	
	//���� ������ ���� �����̰�
	float SpawnDelay;

};
