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


DamageCollisionType ARuthTestCharacter::LimbTakeDamage(AActor* OtherActor, UPrimitiveComponent* OtherComponent, UPARAM(ref)FLimb& _Limb)
{
	
	float LimbsCurrentHp = _Limb._LimbHP;

	if (OtherActor != LeftHandWeapon && OtherActor != RightHandWeapon &&
		OtherActor != this && _Limb._LimbActive)
	{
		

		ARuthTestCharacter* Player = Cast<ARuthTestCharacter>(OtherActor);
		AEquipment* Equippable = Cast<AEquipment>(OtherActor);

		TArray<FName> Tags = OtherComponent->ComponentTags;

		for (int i = 0; i < Tags.Num(); i++)
		{
			FName Tag = Tags[i];

			if (Tag.IsEqual("RightArm"))
			{
				_Limb._LimbHP -= Player->RightHandLimb._WeaponDamage;
				break;
			}


			#pragma region Case: LeftArm
			else if (Tag.IsEqual("LeftArm"))
			{
				
				_Limb._LimbHP -= Player->LeftHandLimb._WeaponDamage;
				break;
			}
			#pragma endregion

			#pragma region RightLeg
			else if (Tag.IsEqual("RightLeg"))
			{
				_Limb._LimbHP -= Player->RightLegLimb._WeaponDamage;	
				break;
			}
			#pragma endregion

			#pragma region Case: LeftLeg
			else if (Tag.IsEqual("LeftLeg"))
			{
				_Limb._LimbHP -= Player->LeftLegLimb._WeaponDamage;
				break;
			}
			#pragma endregion

			#pragma region Case: Weapon
			else if (Tag.IsEqual("Weapon"))
			{
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

//void TorsoTakeDamage(AActor* OtherActor, UPrimitiveComponent* OtherComponent, float _DamageAmount);
//{
//
//	if (OtherActor != LeftHandWeapon && OtherActor != RightHandWeapon &&
//		OtherActor != this && _Limb._LimbActive)
//	{
//		int AmountOfActiveLimbs = 0;
//
//		ARuthTestCharacter* Player = Cast<ARuthTestCharacter>(OtherActor);
//		AEquipment* Equippable = Cast<AEquipment>(OtherActor);
//
//		TArray<FName> Tags = OtherComponent->ComponentTags;
//
//		int DistributedDamage = 0;
//
//#pragma region AmountOfLimbsActive
//		if (LeftHandLimb._LimbActive) { AmountOfActiveLimbs += 1; }
//		if (RightHandLimb._LimbActive) { AmountOfActiveLimbs += 1; }
//		if (LeftLegLimb._LimbActive) { AmountOfActiveLimbs += 1; }
//		if (RightLegLimb._LimbActive) { AmountOfActiveLimbs += 1; }
//#pragma endregion
//
//		for (int i = 0; i < Tags.Num(); i++)
//		{
//			FName Tag = Tags[i];
//
//			if (Tag.IsEqual("RightArm"))
//			{
//				DistributedDamage = Player->RightHandLimb._WeaponDamage / AmountOfActiveLimbs;
//				break;
//			}
//
//
//#pragma region Case: LeftArm
//			else if (Tag.IsEqual("LeftArm"))
//			{
//
//				DistributedDamage = Player->LeftHandLimb._WeaponDamage / AmountOfActiveLimbs;
//				break;
//			}
//#pragma endregion
//
//#pragma region RightLeg
//			else if (Tag.IsEqual("RightLeg"))
//			{
//				DistributedDamage = Player->RightLegLimb._WeaponDamage / AmountOfActiveLimbs;
//				break;
//			}
//#pragma endregion
//
//#pragma region Case: LeftLeg
//			else if (Tag.IsEqual("LeftLeg"))
//			{
//				DistributedDamage = Player->LeftLegLimb._WeaponDamage / AmountOfActiveLimbs;
//				break;
//			}
//#pragma endregion
//
//#pragma region Case: Weapon
//			else if (Tag.IsEqual("Weapon"))
//			{
//				DistributedDamage = Equippable->_WeaponStrength / AmountOfActiveLimbs;
//				break;
//
//			}
//#pragma endregion
//		}
//
//
//
//	}
//}

void ARuthTestCharacter::RagDollBodyPart(FName bone)
{
	CharacterMesh->SetAllBodiesBelowSimulatePhysics(bone, true);
	CharacterMesh->SetAllBodiesBelowPhysicsBlendWeight(bone, 1, false);
}

void ARuthTestCharacter::BlendBackBone(FName bone, float dt)
{
	CharacterMesh->SetAllBodiesBelowPhysicsBlendWeight(bone,FMath::FInterpTo(1, 0, dt, 1),false);
}

