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


DamageCollisionType ARuthTestCharacter::LimbTakeDamage(AActor* OtherActor, UPrimitiveComponent* OtherComponent, UPARAM(ref)FLimb& _Limb, bool DistributedDamage, float &aforce_out)
{
	
	float LimbsCurrentHp = _Limb._LimbHP;

	if (OtherActor != LeftHandWeapon && OtherActor != RightHandWeapon &&
		OtherActor != this && _Limb._LimbActive)
	{
		float damageAmount = 0;

		if (LeftHandLimb._LimbActive) { damageAmount += 1; }
		if (RightHandLimb._LimbActive) { damageAmount += 1; }
		if (LeftLegLimb._LimbActive) { damageAmount += 1; }
		if (RightLegLimb._LimbActive) { damageAmount += 1; }

		


		ARuthTestCharacter* Player = Cast<ARuthTestCharacter>(OtherActor);
		AEquipment* Equippable = Cast<AEquipment>(OtherActor);

		TArray<FName> Tags = OtherComponent->ComponentTags;

		for (int i = 0; i < Tags.Num(); i++)
		{
			FName Tag = Tags[i];

			if (Tag.IsEqual("RightArm"))
			{
				aforce_out = Player->_ArmKB;
				if (DistributedDamage) { _Limb._LimbHP -= Player->RightHandLimb._WeaponDamage / damageAmount; break; }
				_Limb._LimbHP -= Player->RightHandLimb._WeaponDamage;
				break;
			}


			#pragma region Case: LeftArm
			else if (Tag.IsEqual("LeftArm"))
			{
				aforce_out = Player->_ArmKB;
				if (DistributedDamage) { _Limb._LimbHP -= Player->LeftHandLimb._WeaponDamage / damageAmount; break; }
				_Limb._LimbHP -= Player->LeftHandLimb._WeaponDamage;
				break;
			}
			#pragma endregion

			#pragma region RightLeg
			else if (Tag.IsEqual("RightLeg"))
			{
				aforce_out = Player->_LegKB;
				if (DistributedDamage) { _Limb._LimbHP -= Player->RightLegLimb._WeaponDamage /damageAmount; break; }
				_Limb._LimbHP -= Player->RightLegLimb._WeaponDamage;	
				break;
			}
			#pragma endregion

			#pragma region Case: LeftLeg
			else if (Tag.IsEqual("LeftLeg"))
			{
				aforce_out = Player->_LegKB;
				if (DistributedDamage) { _Limb._LimbHP -= Player->LeftLegLimb._WeaponDamage / damageAmount; break; }
				_Limb._LimbHP -= Player->LeftLegLimb._WeaponDamage;
				break;
			}
			#pragma endregion

			#pragma region Case: Weapon
			else if (Tag.IsEqual("Weapon"))
			{
				aforce_out = Equippable->_KnockbackForce;
				if (DistributedDamage) { _Limb._LimbHP -= Equippable->_WeaponStrength / damageAmount; break; }
				_Limb._LimbHP -= Equippable->_WeaponStrength;
				break;
				
			}
			#pragma endregion
		}


		if (_Limb._LimbHP < 0)
		{
			_Limb._LimbActive = false;
			return DamageCollisionType::DISMEMBERED;
		}


		if (LimbsCurrentHp == _Limb._LimbHP)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("No Damage")));
			return DamageCollisionType::NODAMAGE;
		}

		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current HP: %i"), _Limb._LimbHP, _Limb._BoneName));
			return DamageCollisionType::DAMAGED;
		}
		
	}
	return DamageCollisionType::NODAMAGE;
}

void ARuthTestCharacter::RetrieveClosestWeapon(AEquipment* &_WeaponRef)
{
	float LengthProduct = 9999999.0;
	int Index = 0;

	for (int i = 0; i < PickUpArray.Num(); i++) 
	{
		if (GetDistanceTo(PickUpArray[i]) < LengthProduct)
		{
			LengthProduct = GetDistanceTo(PickUpArray[i]);
			Index = i;
		}
	}

	_WeaponRef = PickUpArray[Index];

}

void ARuthTestCharacter::ThrowWeapon(AActor* WeaponRef, UPARAM(ref)bool &_ArmEquipped)
{
	
	AEquipment* Equipment = Cast<AEquipment>(WeaponRef);
	if (Equipment != nullptr)
	{
		if (Equipment->StaticMeshObject->IsValidLowLevel())
		{
			Equipment->StaticMeshObject->SetSimulatePhysics(true);
			Equipment->DetachRootComponentFromParent(true);
			Equipment->ObjectThrown();
			_ArmEquipped = false;

		}

		if (Equipment->MeshObject->IsValidLowLevel())
		{
			Equipment->MeshObject->SetSimulatePhysics(true);
			Equipment->DetachRootComponentFromParent(true);
			Equipment->ObjectThrown();
			_ArmEquipped = false;
		}
	}
}

void ARuthTestCharacter::EquipWeapon(UPoseableMeshComponent* HandSocket, AActor* WeaponRef, bool _ArmEquipped)
{
	if (_ArmEquipped)
	{
		if (!bLeftArmEquipped)
		{
			WeaponRef->K2_AttachRootComponentTo(HandSocket, NAME_None, EAttachLocation::SnapToTarget, true);
			bLeftArmEquipped = true;
			LeftHandWeapon = WeaponRef;
		}
	}

	if (!_ArmEquipped)
	{
		if (!bRightArmEquipped)
		{
			WeaponRef->K2_AttachRootComponentTo(HandSocket, NAME_None, EAttachLocation::SnapToTarget, true);
			bRightArmEquipped = true;
			RightHandWeapon = WeaponRef;
		}
	}
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

void  ARuthTestCharacter::TargetClosestPlayer(float Time)
{
	
}