// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Equipment.generated.h"


UENUM(BlueprintType)
enum class EquipmentType : uint8
{
	ARMOUR UMETA(DisplayName = "ARMOUR"),
	REGULARWEAPON UMETA(DisplayName = "REGULARWEAPON"),
	SPECIALWEAPON UMETA(DisplayName = "SPECIALWEAPON"),
};


UCLASS()
class TOYBOXBRAWL_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipment();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = IteamEquipped)
	void EquipmentPickedUp();

	UFUNCTION(BlueprintCallable, Category = IteamEquipped)
	void ObjectThrown();


	UFUNCTION(BlueprintCallable, Category = IteamEquipped)
	void Deweaponise();

	UFUNCTION(BlueprintCallable, Category = IteamEquipped)
	void DestroyWeapon();

	UFUNCTION(BlueprintCallable, Category = IteamMisc)
	void AssignMaterial(UMaterialInterface* MaterialReference, int MaterialSlot);

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* MeshObject;
	
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshObject;

	UPROPERTY(BlueprintReadWrite)
	UDestructibleComponent* DamageMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Rotation")
	FVector Ruth_PickupRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Projectile Weapon")
	bool _WeaponThrown;

	float timer = .2f;
	float countdown = 0;

#pragma region Weapon_Properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float _BaseDamage;

	UPROPERTY(BlueprintReadWrite, Category = "Properties")
	float _WeaponStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	EquipmentType _EquipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float _KnockbackForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ToolTip = "If Type is Armour treat_NumofUses as hp" ))
	float _NumOfUses;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	bool _UnlimitedUses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ToolTip = "Has Weapon been picked up"))
	bool _WeaponActive;

#pragma endregion
};
