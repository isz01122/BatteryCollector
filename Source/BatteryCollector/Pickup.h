// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//return the mesh for pickup
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

	//return whrther or net the pickup is active
	UFUNCTION(BlueprintPure, Category = "Pickup")
		bool IsActive();

	//allows other classed to safely change whether or not pickup is active
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void SetActive(bool NewPickupState);
	
	//이벤트 발생시 코드에서 설정한 부분 실행
	//아이템을 먹었을 때 호출할 함수
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();//가상함수 사용이유 : 자손클래스에서 오버라이딩 하기위해



protected:
	//true when the pickup can be used, and false when pickup is deactived
	bool bIsActive;


private:
	//    Static mesh to represent the Pickup in the level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))

		class UStaticMeshComponent* PickupMesh;

	
};
