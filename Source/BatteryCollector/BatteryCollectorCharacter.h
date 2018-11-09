// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BatteryCollectorCharacter.generated.h"

UCLASS(config=Game)
class ABatteryCollectorCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** 아이템 탐지용 구체 콜리젼 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;


public:
	ABatteryCollectorCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//초기파워 값 얻어오는 함수
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetInitialPower();

	//현재파워 값 얻어오는 함수
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower();

	//캐릭터의 현재 파워값을 업데이트 함
	//파워체인지는 현재 파워에 더할 값으로, 값은 양수 또는 음수일 수 있음
	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdatePower(float PowerChange);


protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	//버튼을 누르면 동작함
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void CollectPickups();

	//캐릭터 파워 초기값
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintPRotected = "true"))
	float InitialPower;
	
	//캐릭터 속도에 곱해지는 값
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintPRotected = "true"))
	float SpeedFactor;
	
	//파워레벨이 0일때의 캐릭터 속도
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintPRotected = "true"))
	float BaseSpeed;

	UFUNCTION(BlueprintImplementableEvent, Category = "Power")
	void PowerChangeEffect();

private:
	//캐릭터 현재 파워값을 저장하는 변수
	UPROPERTY(VisibleAnyWhere, Category = "Power")
	float CharacterPower;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	//콜렉션 스피어 서브젝트를 반환해줌
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }

};

