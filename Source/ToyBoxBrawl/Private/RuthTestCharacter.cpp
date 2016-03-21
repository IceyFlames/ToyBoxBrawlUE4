// Fill out your copyright notice in the Description page of Project Settings.

#include "ToyBoxBrawl.h"
#include "RuthTestCharacter.h"
#include "Equipment.h"

// Sets default values
ARuthTestCharacter::ARuthTestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARuthTestCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARuthTestCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ARuthTestCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ARuthTestCharacter::SetPlayerID(PlayerID _id)
{
	_PlayerId = _id;
}

void ARuthTestCharacter::LimbTakeDamage(AActor* OtherActor, UPrimitiveComponent* OtherComponent, FLimb _Limb)
{

	if (OtherActor != LeftHandWeapon && OtherActor != RightHandWeapon &&
		OtherActor != this && _Limb._LimbActive)
	{

		ARuthTestCharacter* Player = Cast<ARuthTestCharacter>(OtherActor);
		AEquipment* Equippable = Cast<AEquipment>(OtherActor);

		TArray<FName> Tags = OtherComponent->ComponentTags;

		for (signed int i = 0; i < Tags.Num(); i++)
		{
			FName Tag = Tags[i];

			#pragma region Case: RightArm
			if (Tag.IsEqual("RightArm"))
			{
				_Limb._LimbHP -= Player->RightHandLimb._WeaponDamage;
				break;
			}
			#pragma endregion

			#pragma region Case: LeftArm
			if (Tag.IsEqual("LeftArm"))
			{
				_Limb._LimbHP -= Player->RightHandLimb._WeaponDamage;
				break;
			}
			#pragma endregion

			#pragma region Case: RightLeg
			if (Tag.IsEqual("RightLeg"))
			{
				_Limb._LimbHP -= Player->RightHandLimb._WeaponDamage;
				break;
			}
			#pragma endregion

			#pragma region Case: LeftLeg
			if (Tag.IsEqual("LeftLeg"))
			{
				_Limb._LimbHP -= Player->RightHandLimb._WeaponDamage;
				break;
			}
			#pragma endregion

			#pragma region Case: Weapon
			if (Tag.IsEqual("Weapon"))
			{
				_Limb._LimbHP -= Equippable->_WeaponStrength;
			}
			#pragma endregion
		}
	}
	return;
}

void ARuthTestCharacter::RagDollBodyPart(FName bone)
{
	CharacterMesh->SetAllBodiesBelowSimulatePhysics(bone, true);
	CharacterMesh->SetAllBodiesBelowPhysicsBlendWeight(bone, 1, false);
}

void ARuthTestCharacter::BlendBackBone(FName bone, float dt)
{
	CharacterMesh->SetAllBodiesBelowPhysicsBlendWeight(bone,FMath::FInterpTo(1, 0, dt, 1),false);
}