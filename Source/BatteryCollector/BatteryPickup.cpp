// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "BatteryCollector.h"
#include "Classes/Components/StaticMeshComponent.h"


ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);
	//���͸��� �⺻���� ����
	BatteryPower = 150.0f;
}

void ABatteryPickup::WasCollected_Implementation()
{
	//���̽� �Ⱦ� ��ũ��Ʈ ���
	Super::WasCollected_Implementation();
	//���͸� ������ �ı��ϱ�
	Destroy();


}

//���͸��� �Ŀ� ���� ��ȯ��
float ABatteryPickup::GetPower()
{
	return BatteryPower;
}

