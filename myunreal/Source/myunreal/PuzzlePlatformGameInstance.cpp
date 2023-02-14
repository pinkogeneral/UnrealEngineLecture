// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"

void UPuzzlePlatformGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitalizer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UPuzzlePlatformGameInstance::Host()
{
	UEngine* Engin = GetEngine(); 
	if (!ensure(Engin != nullptr)) return; 

	Engin->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	UEngine* Engin = GetEngine();
	if (!ensure(Engin != nullptr)) return;

	Engin->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Jonining %s"), *Address));
}
