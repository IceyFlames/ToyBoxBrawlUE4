// Fill out your copyright notice in the Description page of Project Settings.

#include "ToyBoxBrawl.h"
#include "Equipment.h"


// Sets default values
AEquipment::AEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AEquipment::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEquipment::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	countdown -= DeltaTime;


	if (_WeaponThrown && countdown < 0)
	{
		
		float forceStrength = GetVelocity().Size();
		FString String = FString::SanitizeFloat(forceStrength);

		if (forceStrength < 125)
			Deweaponise();

		else
			_WeaponStrength = _BaseDamage;
	}

}

void AEquipment::Deweaponise()
{


	if (MeshObject != nullptr)
	{
		
		MeshObject->ComponentTags.Remove(FName("Weapon"));
		MeshObject->ComponentTags.Add(FName("Pickup"));
		_WeaponStrength = 0.0f;
		_WeaponThrown = false;
		return;
	}

	if (StaticMeshObject != nullptr)
	{
		
		StaticMeshObject->ComponentTags.Remove(FName("Weapon"));
		StaticMeshObject->ComponentTags.Add(FName("Pickup"));
		_WeaponStrength = 0.0f;
		_WeaponThrown = false;
		return;
	}

	if (DamageMesh != nullptr)
	{

		MeshObject->ComponentTags.Remove(FName("Weapon"));
		MeshObject->ComponentTags.Add(FName("Pickup"));
		_WeaponStrength = 0.0f;
		_WeaponThrown = false;
		return;
	}


	
}

void AEquipment::ObjectThrown()
{
	if (MeshObject != nullptr)
		MeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	if (StaticMeshObject != nullptr)
		StaticMeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);


	if (DamageMesh != nullptr)
		StaticMeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	_WeaponThrown = true;
	_WeaponStrength = 0.0f;

	countdown = timer;
}

void AEquipment::EquipmentPickedUp()
{
	if (MeshObject != nullptr)
	{
		MeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		MeshObject->ComponentTags.Remove(FName("Pickup"));
		MeshObject->ComponentTags.Add(FName("Weapon"));
	}

	if (StaticMeshObject != nullptr)
	{
		StaticMeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		StaticMeshObject->ComponentTags.Remove(FName("Pickup"));
		StaticMeshObject->ComponentTags.Add(FName("Weapon"));
	}

	if (DamageMesh != nullptr)
	{
		DamageMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		DamageMesh->ComponentTags.Remove(FName("Pickup"));
		DamageMesh->ComponentTags.Add(FName("Weapon"));
	}
	return;
}


void AEquipment::AssignMaterial(UMaterialInterface* MaterialReference)
{

	if (MeshObject != nullptr)
	{
		MeshObject->SetMaterial(0, MaterialReference);
	}

	if (StaticMeshObject != nullptr)
	{
		StaticMeshObject->SetMaterial(0, MaterialReference);
	}

	return;
}

void AEquipment::DestroyWeapon()
{
	if (_NumOfUses < 0)
	{
		Destroy();
	}
}