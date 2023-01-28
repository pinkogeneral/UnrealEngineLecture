// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true; 
	SetMobility(EComponentMobility::Movable); //컴포넌트를 움직일 수 있게 만들거다.
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay(); //이걸 실행하지 않으면 BluePrint가 호출되지 않기 때문이다.

	if (HasAuthority())
	{

		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	//정적 메서드로 Super Tick이 없다.
	Super::Tick(DeltaTime);
	if (HasAuthority()) //Not on Server == client
	{
		//우리가 하고 싶은 것은 Actor 위치를 얻는 것이다. 
		//FVector유형이 될 변수에 저장한다.
		FVector Location = GetActorLocation();
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		// 언리얼에서는 cm가 기본 단위이다.
		// 언리얼에서 초속 5cm에 DeltaTime을 곱하면 이동할 거리가 나온다.
		// 이동거리는 단위 시간 동안 이동한 거리에 시간을 곱하면 된다.
		// 벡터 자체를 수정하는 것은 좋지 않다. 
		// GetSafeNormal, GetUnSafeNormal (부동소수점 오류, 숫자가 아주 작을 때에 대한 보호가 없음)
		// Normal은 법선을 의미하는데, 언리얼에서는 정규화된 벡터를 의미하므로 주의하자.
		FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
		Location += FVector(Speed* Direction* DeltaTime);
		SetActorLocation(Location);
	}
	//HasAuthority 메서드는 Actor에 있으며 자신이 서버인지 그 여부를 불린값으로 반환한다.
	//True라면 서버를 의미한다. False는 클라이언트를 의미한다. 
	//HasAuthority
}
