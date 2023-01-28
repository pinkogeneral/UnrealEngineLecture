// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true; 
	SetMobility(EComponentMobility::Movable); //������Ʈ�� ������ �� �ְ� ����Ŵ�.
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay(); //�̰� �������� ������ BluePrint�� ȣ����� �ʱ� �����̴�.

	if (HasAuthority())
	{

		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	//���� �޼���� Super Tick�� ����.
	Super::Tick(DeltaTime);
	if (HasAuthority()) //Not on Server == client
	{
		//�츮�� �ϰ� ���� ���� Actor ��ġ�� ��� ���̴�. 
		//FVector������ �� ������ �����Ѵ�.
		FVector Location = GetActorLocation();
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		// �𸮾󿡼��� cm�� �⺻ �����̴�.
		// �𸮾󿡼� �ʼ� 5cm�� DeltaTime�� ���ϸ� �̵��� �Ÿ��� ���´�.
		// �̵��Ÿ��� ���� �ð� ���� �̵��� �Ÿ��� �ð��� ���ϸ� �ȴ�.
		// ���� ��ü�� �����ϴ� ���� ���� �ʴ�. 
		// GetSafeNormal, GetUnSafeNormal (�ε��Ҽ��� ����, ���ڰ� ���� ���� ���� ���� ��ȣ�� ����)
		// Normal�� ������ �ǹ��ϴµ�, �𸮾󿡼��� ����ȭ�� ���͸� �ǹ��ϹǷ� ��������.
		FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
		Location += FVector(Speed* Direction* DeltaTime);
		SetActorLocation(Location);
	}
	//HasAuthority �޼���� Actor�� ������ �ڽ��� �������� �� ���θ� �Ҹ������� ��ȯ�Ѵ�.
	//True��� ������ �ǹ��Ѵ�. False�� Ŭ���̾�Ʈ�� �ǹ��Ѵ�. 
	//HasAuthority
}
