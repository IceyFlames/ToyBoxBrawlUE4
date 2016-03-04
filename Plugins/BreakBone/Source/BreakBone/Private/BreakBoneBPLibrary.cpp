// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BreakBonePrivatePCH.h"
#include "BreakBoneBPLibrary.h"


void UBreakBoneBPLibrary::BoneBreak(USkeletalMeshComponent *Mesh, FName BoneName, FVector ImpactLocation, FVector Force, bool bShouldSetRagdollPhysics)
{
	Mesh->BreakConstraint(Force, ImpactLocation, BoneName);
	Mesh->UpdateMeshForBrokenConstraints();
	Mesh->SetAllBodiesBelowSimulatePhysics(BoneName, true);
	Mesh->WakeAllRigidBodies();
	
	if (bShouldSetRagdollPhysics)
	{
		static FName CollisionProfileName(TEXT("Ragdoll"));
		Mesh->SetCollisionProfileName(CollisionProfileName);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	}
}

FVector UBreakBoneBPLibrary::GetBoneLocation(USkeletalMeshComponent *Mesh, FName BoneName)
{
	return Mesh->GetBoneLocation(BoneName);
}
