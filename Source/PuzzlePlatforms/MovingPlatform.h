// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Engine/StaticMeshActor.h>
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// MovementSpeed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actor Modifier")
	float Speed;

	// Target Location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actor Modifier", Meta=(MakeEditWidget = true))
	FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:
	FVector GlobalStartLocation;

	FVector GlobalTargetLocation;


	// Comment
	UPROPERTY(EditAnywhere)
	int ActiveTriggers;

};
