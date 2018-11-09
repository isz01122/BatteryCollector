// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Pickup.h"
#include "Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//���������� ǥ���ϱ����� �ڽ�������Ʈ ����
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;


	//������ ���� �ּ� �ִ� �ʱⰪ �����ϱ�
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;


}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;//����
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;//�� ���� ����

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn)
{
	if (bShouldSpawn)
	{
		//���� �Ⱦ��� Ÿ�̸� ����
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);

	}
	else
	{
		//���� �Ⱦ��� Ÿ�̸� �ʱ�ȭ
		GetWorldTimerManager().ClearTimer(SpawnTimer);

	}
}

void ASpawnVolume::SpawnPickup()
{
	if (WhatToSpawn != NULL)
	{
		//check for a vaild world
		UWorld* const World = GetWorld();
		if (World)
		{
			//set the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//get a randon location to spawn at
			FVector SpawnLocation = GetRandomPointInVolume();

			//get a random rotation for the spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			//spawn the pickup
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);

		}
	}
}