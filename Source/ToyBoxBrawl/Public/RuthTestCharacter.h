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
	DamageCollisionType LimbTakeDamage(AActor* OtherActor, UPrimitiveComponent* OtherComponent, UPARAM(ref)FLimb& _Limb);
	
	UFUNCTION(BlueprintCallable, Category = Collision)
	void DamageTorso(AActor* OtherActor, UPrimitiveComponent* OtherComponent, float _DamageAmount);


	UFUNCTION(BlueprintCallable, Category = PhysicsBlend)
	void RagDollBodyPart(FName bone);

	UFUNCTION(BlueprintCallable, Category = PhysicsBlend)
	void BlendBackBone(FName bone, float dt);

	UPROPERTY(BlueprintReadWrite)
	AActor* LeftHandWeapon;

	UPROPERTY(BlueprintReadWrite)
	AActor* RightHandWeapon;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* CharacterMesh;


#pragma region HitStrings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Collision Animation")
	TArray<FString> HitStrings;
#pragma endregion

#pragma region StructLimbs(Not using atm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Struct)
	FLimb LeftHandLimb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Struct)
	FLimb RightHandLimb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Struct)
	FLimb LeftLegLimb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Struct)
	FLimb RightLegLimb;
#pragma endregion


#pragma region Weapon_Equipping_Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	bool bLeftArmEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	bool bRightArmEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	bool bCanPickup;
#pragma endregion

#pragma region Animation_Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animating")
	bool bLeftPunch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animating")
	bool bRightPunch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animating")
	bool bLeftKick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animating")
	bool bRightKick;
#pragma endregion

};
