// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"


//���� �����÷��� ���¸� �����ϴ� enum
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnKnown
};


UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	//���� �¸��� �ʿ��� �Ŀ��� �˷���
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	virtual void BeginPlay() override;

	//���� �÷��� ���·� ���ư�
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	//�� �÷��� ���� ����
	void SetCurrentState(EBatteryPlayState newState);

protected:
	//ĳ���� �Ŀ��� �پ��� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;


	//�¸��ϱ����� ��ƾ� �ϴ� ���͸��� ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin;


	//HUD ȭ�鿡 ����� ���� Ŭ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	//HUD�ν��Ͻ�
	UPROPERTY()
	class UUserWidget* CurrentWidget;


private:
	//���� �÷��� ���¸� ������
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	//���� �÷��� ���¿� ������ �ִ� ��� �Լ��� ȣ���� ���
	void HandleNewState(EBatteryPlayState NewState);
};