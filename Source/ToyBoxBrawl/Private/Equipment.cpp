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
	//_WeaponStrength = _BaseDamage;
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
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, String);

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
		_WeaponStrength = 0;
		_WeaponThrown = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Thrown Object: Deweaponised");
		return;
	}

	if (StaticMeshObject != nullptr)
	{
		
		StaticMeshObject->ComponentTags.Remove(FName("Weapon"));
		StaticMeshObject->ComponentTags.Add(FName("Pickup"));
		_WeaponStrength = 0;
		_WeaponThrown = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Thrown Object: Deweaponised");
		return;
	}


	//if (BoxCollider != nullptr)
	//{
	//	BoxCollider->ComponentTags.Remove(FName("Weapon"));
	//	BoxCollider->ComponentTags.Add(FName("Pickup"));
	//	_WeaponStrength = 0;
	//	_WeaponThrown = false;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Thrown Object: Deweaponised");
	//	return;
	//}
	//
	//if (CapsuleCollider != nullptr)
	//{
	//	CapsuleCollider->ComponentTags.Remove(FName("Weapon"));
	//	CapsuleCollider->ComponentTags.Add(FName("Pickup"));
	//	_WeaponStrength = 0;
	//	_WeaponThrown = false;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Thrown Object: Deweaponised");
	//	return;
	//}
	//
	//if(SphereCollider != nullptr)
	//{
	//	SphereCollider->ComponentTags.Remove(FName("Weapon"));
	//	SphereCollider->ComponentTags.Add(FName("Pickup"));
	//	_WeaponStrength = 0;
	//	_WeaponThrown = false;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Thrown Object: Deweaponised");
	//	return;
	//}

	
}

void AEquipment::ObjectThrown()
{
	if (MeshObject != nullptr)
		MeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	if (StaticMeshObject != nullptr)
		StaticMeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	_WeaponThrown = true;
	_WeaponStrength = 0;

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
	
	

	//if (BoxCollider != nullptr)
	//{
	//	BoxCollider->ComponentTags.Remove(FName("Pickup"));
	//	BoxCollider->ComponentTags.Add(FName("Weapon"));
	//	return;
	//}
	//
	//if (CapsuleCollider != nullptr)
	//{
	//	CapsuleCollider->ComponentTags.Remove(FName("Pickup"));
	//	CapsuleCollider->ComponentTags.Add(FName("Weapon"));
	//	return;
	//}
	//
	//if (SphereCollider != nullptr)
	//{
	//	SphereCollider->ComponentTags.Remove(FName("Pickup"));
	//	SphereCollider->ComponentTags.Add(FName("Weapon"));
	//	return;
	//}

	return;
}