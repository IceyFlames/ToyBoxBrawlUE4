// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "RuthTestCharacter.generated.h"

UENUM(BlueprintType)
enum class PlayerID : uint8
{
	PLAYER1 UMETA(DisplayName = "Player1"),
	PLAYER2 UMETA(DisplayName = "Player2"),
	PLAYER3 UMETA(DisplayName = "Player3"),
	PLAYER4 UMETA(DisplayName = "Player4")
};

USTRUCT(BlueprintType)
struct FLimb
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limb")
	int32 _WeaponDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limb")
	int32 _LimbHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limb")
	bool _LimbActive;
	UPROPERTY(BlueprintReadWrite, Category = "Limb")
	FName _BoneName;
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
	
	UFUNCTION(BlueprintCallable, Category = Playertag)
	void SetPlayerID(PlayerID _id);

	UFUNCTION(BlueprintCallable, Category = Collision)
	void LimbTakeDamage(AActor* OtherActor, UPrimitiveComponent* OtherComponent, FLimb _Limb);
	
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

#pragma region Miscallaneous
	//This is just a bidning for which id this player is and which collision filter to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	PlayerID _PlayerId;
#pragma endregion

#pragma region Damage_Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	int32 _LeftLegWS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	int32 _RightLegWS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	int32 _RightArmWS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	int32 _LeftArmWS;
#pragma endregion

#pragma region HealthProperties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 _LeftLegHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 _RightLegHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 _RightArmHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 _LeftArmHP;
#pragma endregion

#pragma region Limb_Active_Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LimbsActive")
	bool bLeftArmActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LimbsActive")
	bool bRightArmActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LimbsActive")
	bool bLeftLegActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LimbsActive")
	bool bRightLegActive;
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
