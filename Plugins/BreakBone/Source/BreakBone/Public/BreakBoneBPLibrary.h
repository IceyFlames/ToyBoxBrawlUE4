// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "BreakBoneBPLibrary.generated.h"


UCLASS()
class BREAKBONE_API UBreakBoneBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Bone Break", Keywords = "Break Bone Constraints Gore Gibs"), Category = "BreakBone")
	static void BoneBreak(USkeletalMeshComponent *Mesh, FName BoneName, FVector ImpactLocation, FVector Force, bool bShouldSetRagdollPhysics = false);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Bone Location", Keywords = "Bone Location Mesh"), Category = "BreakBone")
	static FVector GetBoneLocation(USkeletalMeshComponent *Mesh, FName BoneName);
	
};
