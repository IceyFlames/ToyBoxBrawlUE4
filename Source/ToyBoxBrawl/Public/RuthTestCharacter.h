// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "RuthTestCharacter.generated.h"


UENUM(BlueprintType)
enum class DamageCollisionType : uint8
{
	NODAMAGE UMETA(DisplayName = "NODAMAGE"),
	DAMAGED UMETA(DisplayName = "DAMAGED"),
	DISMEMBERED UMETA(DisplayName = "DISMEMBERED"),
};

USTRUCT(BlueprintType)
struct FLimb
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limb")
	float _BaseDamage;

	UPROPERTY(BlueprintReadWrite, Category = "Limb")
	float _WeaponDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limb")
	float _LimbHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limb")
	bool _LimbActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limb")
	FName _BoneName;

	void SubtractHealth(float val) { _LimbHP -= val; }
	
};

UCLASS()
class TOYBOXBRAWL_API ARuthTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARuthTestCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	

	UFUNCTION(BlueprintCallable, Category = Collision)
	DamageCollisionType LimbTakeDamage(AActor* OtherActor, UPrimitiveComponent* OtherComponent, UPARAM(ref)FLimb& _Limb, bool DistributedDamage, float &aforce_out);
	



	UFUNCTION(BlueprintCallable, Category = PhysicsBlend)
	void RagDollBodyPart(FName bone);

	UFUNCTION(BlueprintCallable, Category = PhysicsBlend)
	void BlendBackBone(FName bone, float dt);


	UFUNCTION(BlueprintCallable, Category = FighterMech)
	void ThrowWeapon(AActor* WeaponRef, UPARAM(ref)bool &_ArmEquipped);

	UFUNCTION(BlueprintCallable, Category = FighterMech) //True for Left Hand: False for Right Hand Equipped:
	void EquipWeapon(UPoseableMeshComponent* HandSocket,AActor* WeaponRef,bool _ArmEquipped);

	UFUNCTION(BlueprintCallable, Category = FighterMech) //Retrieves the closest weapon from PickupArray
	void RetrieveClosestWeapon(AEquipment* &_WeaponRef);

	UFUNCTION(BlueprintCallable, Category = FighterMech) //Retrieves the closest weapon from PickupArray
	void TargetClosestPlayer(float Time);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category= Mechanic)
	void StunEffect(float Duration);

	UPROPERTY(BlueprintReadWrite)
	AActor* LeftHandWeapon;

	UPROPERTY(BlueprintReadWrite)
	AActor* RightHandWeapon;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float SpecialAbilityCooldown;


	UPROPERTY(BlueprintReadWrite, Category = "ControllerID")
	int PlayerControllerID;


#pragma region Lists
	UPROPERTY(BlueprintReadWrite, Category = "PickUpArray")
	TArray<AEquipment*> PickUpArray;

	UPROPERTY(BlueprintReadWrite, Category = "TargetArray")
	TArray<ARuthTestCharacter*> PlayerReferenceArray;

#pragma endregion

#pragma region HitStrings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float _ArmKB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float _LegKB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetSystem")
	float _RotatePivot;

	UPROPERTY(BlueprintReadWrite, Category = "Character Collision Animation")
	TArray<AActor*> HitInvulnerability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Collision Animation")
	TArray<float> HitValues;


#pragma endregion

#pragma region StructLimbs(Not using atm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FLimb LeftHandLimb;							
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FLimb RightHandLimb;								
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FLimb LeftLegLimb;									
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FLimb RightLegLimb;
#pragma endregion

#pragma region Weapon_Equipping_Properties
	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	bool bLeftArmEquipped;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	bool bRightArmEquipped;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	bool bCanPickup;
#pragma endregion

#pragma region Animation_Properties
	UPROPERTY(BlueprintReadWrite, Category = "Animating")
	bool bLeftPunch;
	UPROPERTY(BlueprintReadWrite, Category = "Animating")
	bool bRightPunch;
	UPROPERTY(BlueprintReadWrite, Category = "Animating")
	bool bLeftKick;
	UPROPERTY(BlueprintReadWrite, Category = "Animating")
	bool bRightKick;

	UPROPERTY(BlueprintReadWrite, Category = "Animating")
	bool bSliding;

	UPROPERTY(BlueprintReadWrite, Category = "Animating")
	bool bRobotSpecial;

#pragma endregion


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limb")
	bool bIsDead;


};
