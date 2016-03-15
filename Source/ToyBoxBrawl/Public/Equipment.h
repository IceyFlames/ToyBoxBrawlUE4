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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* MeshObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshObject;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* SphereCollider;
	


#pragma region Weapon_Properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 _BaseDamage;

	UPROPERTY(BlueprintReadWrite, Category = "Properties")
	int32 _WeaponStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	EquipmentType _EquipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ToolTip = "If Type is Armour treat_NumofUses as hp" ))
	int32 _NumOfUses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	bool _UnlimitedUses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ToolTip = "Has Weapon been picked up"))
	bool _WeaponActive;

#pragma endregion
};
