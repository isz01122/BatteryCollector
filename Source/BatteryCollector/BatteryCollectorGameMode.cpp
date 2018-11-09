// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h" //���� �÷��̽� ������ ����� �� �ִ� �Լ����� �ִ�
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "SpawnVolume.h"
#include "EngineUtils.h"
#include "GameFramework/PawnMovementComponent.h"
#include "BatteryCollector.h"


ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;

	//������ �⺻�� ����
	DecayRate = 0.01f;
}

void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//��� ���� ���� ���͸� ã�Ƴ�
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}
	
	SetCurrentState(EBatteryPlayState::EPlaying);

	//��ǥ ���� ����!
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower())*1.25f;
	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

}


void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//���͸��ݷ���ĳ���͸� ����ϰ��ִ°����� Ȯ��!
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		//�䱸ġ �̻��� �Ŀ��� ������ ���� ���¸� won���� ����
		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}

		//���� ĳ������ �Ŀ��� 0���� ũ��
		else if (MyCharacter->GetCurrentPower()>0)
		{
			//�����̷���Ʈ�� �̿��ؼ� �Ŀ��� ���ҽ�Ų��
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * (MyCharacter->GetInitialPower()));
		}
		else
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}



}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	//�������
	CurrentState = NewState;
	//���ο� ���·� �����
	HandleNewState(CurrentState);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		//���� �÷��� ���ΰ��
		case EBatteryPlayState::EPlaying:
		{
			//���� ���� Ȱ��ȭ
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(true);
			}

		}
		break;

		//���ӿ��� �¸��� ���
		case EBatteryPlayState::EWon:
		{
			//���� ���� ��Ȱ��ȭ
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(false);
			}

		}
		break;

		//���ӿ��� �й��� ���
		case EBatteryPlayState::EGameOver:
		{
			//���� ���� ��Ȱ��ȭ
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(false);
			}
			//�÷��̾� �Է��� ���´�
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
			{
				PlayerController->SetCinematicMode(true, false, false, true, true);
			}
			//ĳ���Ϳ� ���׵� ȿ���� �ش�
			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (MyCharacter)
			{
				MyCharacter->GetMesh()->SetSimulatePhysics(true);
				MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			}
		}
		break;

		//�˼�����/�⺻����
		default:
		case EBatteryPlayState::EUnKnown:
		{
			//�ƹ��� �ൿ���� �ʴ´�
			

		}
		break;
		
	}
}