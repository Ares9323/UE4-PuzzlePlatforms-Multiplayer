// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformTrigger.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API APlatformTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Platform Trigger Volume
	UPROPERTY(VisibleAnywhere, Category="TriggerVolume")
	class UBoxComponent* TriggerVolume;

	UPROPERTY(EditAnywhere, Category="TriggerVolume")
	TArray<class AMovingPlatform*> PlatformsToTrigger;

	// On Volume Begin Overlap
	UFUNCTION(Category="Overlap Events")
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// On Volume End Overlap
	UFUNCTION(Category="Overlap Events")
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
