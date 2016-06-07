// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "LobbyCharacter.generated.h"

UCLASS()
class TOYBOXBRAWL_API ALobbyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALobbyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Select();
	void Deselect();
	void UpButton();
	void DownButton();
	void RightButton();
	void LeftButton();
	void MoveForward(float axisValue);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Boolean references for Transitions
	bool ConnectedToGame; //Is player connected to game
	bool CharacterChosoen; // Has player choosen a character
	bool ClothingOptionChosen; //Has a Option been Selected
	bool ReadyUp; //Is player ready to commence the game

	//Controller Input as well as Character ID References
	int CharacterID; //What is the characters ID
	int ControllerID; //What is the controller ID
	

	//References to ID of the clothes the character is wearing
	int HatID; //ID of hat from the array
	int TorsoID; //ID of torso from the array
	int PantsID; //ID of the pants from the array
	int ShoesID; //ID of the shoes from the array


	//Skeletal Meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuthMesh")
	USkeletalMeshComponent* RuthSkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuthMesh")
	UAnimationAsset* RuthIdle;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AEIOUMesh")
	USkeletalMeshComponent* AEIOUSkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AEIOUMesh")
	UAnimationAsset* AEIOUIdle;

	USkeletalMeshComponent* BazzaSkeletalMesh;
	USkeletalMeshComponent* MarcelSkeletalMesh;



	//Character Components
	USkeletalMeshComponent* CharacterMesh; //The characters main mesh body
	UStaticMeshComponent* HeadComponent; //What is on top of the characters head
	
	
};
