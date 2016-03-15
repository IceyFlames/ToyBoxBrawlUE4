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

}

void AEquipment::EquipmentPickedUp()
{
	if(MeshObject != nullptr)
		MeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	if(StaticMeshObject != nullptr)
		StaticMeshObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	if (BoxCollider != nullptr)
	{
		BoxCollider->ComponentTags.Remove(FName("PickUp"));
		BoxCollider->ComponentTags.Add(FName("Weapon"));
		return;
	}

	if (CapsuleCollider != nullptr)
	{
		CapsuleCollider->ComponentTags.Remove(FName("PickUp"));
		CapsuleCollider->ComponentTags.Add(FName("Weapon"));
		return;
	}

	if (SphereCollider != nullptr)
	{
		SphereCollider->ComponentTags.Remove(FName("PickUp"));
		SphereCollider->ComponentTags.Add(FName("Weapon"));
		return;
	}

	return;
}