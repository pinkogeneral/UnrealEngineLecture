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
	//�𸮾��� null�����Ͱ� ��ü �����⸦ �ٿ��ų �� �ִ�. 


	// �̺�Ʈ �ݺ��� 

}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	// ������ -> BeginPlay�� �ű� �����ڰ� �Ϸ�Ǳ⵵ ���� Ŭ������ ��� �޼��带 �����ڿ��� �Լ� �����ͷ� �����ڴ� �� ������ ���� �ʴ´�.
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
	// ������ Tarray�� ������ �ִٸ�, �װ� ���� �������� Tarray�� ���� �ʴ´�.
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

