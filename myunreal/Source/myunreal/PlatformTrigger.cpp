// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return; 
	RootComponent = TriggerVolume; //#include "Components/BoxComponent.h" 
	//언리얼의 null포인터가 전체 편집기를 다운시킬 수 있다. 


	// 이벤트 콜벡을 

}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	// 생성자 -> BeginPlay로 옮김 생성자가 완료되기도 전에 클래스의 멤버 메서드를 생성자에서 함수 포인터로 때려박는 건 순서에 맞지 않는다.
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin); //AddDynamic(UserObject)
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Activated"));
	// 정수의 Tarray를 가지고 있다면, 그게 정수 포인터의 Tarray가 되진 않는다.
	for (AMovingPlatform* platform : PlatformToTrigger)
	{
		platform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("UnActivated"));
	for (AMovingPlatform* platform : PlatformToTrigger)
	{
		platform->RemoveActiveTrigger();
	}
}

