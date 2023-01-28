// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true; 
	SetMobility(EComponentMobility::Movable); //컴포넌트를 움직일 수 있게 만들거다.
}

void AMovingPlatform::Tick(float DeltaTime)
{
	//정적 메서드로 Super Tick이 없다.
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		//우리가 하고 싶은 것은 Actor 위치를 얻는 것이다. 
		//FVector유형이 될 변수에 저장한다.
		FVector Location = GetActorLocation();
		// 언리얼에서는 cm가 기본 단위이다.
		// 언리얼에서 초속 5cm에 DeltaTime을 곱하면 이동할 거리가 나온다.
		// 이동거리는 단위 시간 동안 이동한 거리에 시간을 곱하면 된다.
		Location += FVector(Speed * DeltaTime, 0, 0);
		SetActorLocation(Location);
	}
	//HasAuthority 메서드는 Actor에 있으며 자신이 서버인지 그 여부를 불린값으로 반환한다.
	//True라면 서버를 의미한다. False는 클라이언트를 의미한다. 
	//HasAuthority
}
