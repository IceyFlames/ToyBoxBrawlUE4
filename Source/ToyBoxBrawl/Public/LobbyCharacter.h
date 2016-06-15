// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "LobbyCharacter.generated.h"


USTRUCT(BlueprintType)
struct FClothes
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClothProperty")
	bool _ColorWheel;

	UPROPERTY(EditAnywhere, Category = "ClothProperty")
	int _MaterialSlot;

	UPROPERTY(EditAnywhere, Category = "ClothProperty")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "ClothProperty")
	FName _Socketname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClothProperty")
	bool _EntireBody;

};


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

	void DPAD_UpButton();
	void DPAD_DownButton();
	void DPAD_LeftButton();
	void DPAD_RightButton();

	void BottomButton();
	void RightButton();
	void LeftButton();
	void MoveForward(float axisValue);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Constructing a functionevent to update the widget
	UFUNCTION(BlueprintImplementableEvent, meta = (Name = "UpdateWidgetReferences"))
	void UpdateWidgets(int _CreationID);

	void CreatingCharacterProcess(int num);
	void TransitionBack(int num);
	void UpdateCharacterPreview();
	
	void AssignClothing();
	void UpdateClothingCounters(int _num);

#pragma region Lists
	UPROPERTY(EditAnywhere, Category = "RuthClothes")
	TArray<FClothes> RHats;

	UPROPERTY(EditAnywhere, Category = "RuthClothes")
	TArray<FClothes> RTorso;

	UPROPERTY(EditAnywhere, Category = "RuthClothes")
	TArray<FClothes> RPants;
	
	UPROPERTY(EditAnywhere, Category = "RuthClothes")
	TArray<FClothes> RShoes;

	FName ShoeSockets;

#pragma endregion

#pragma region Options Selected
	UPROPERTY(BlueprintReadWrite, Category = "ClothingSelection")
	int ClothingOptionHighlighted; //ID of the widget object being highlighted

	UPROPERTY(BlueprintReadWrite, Category = "ClothingSelection")
	int HatIDHighlighted; //ID of the widget object being highlighted

	UPROPERTY(BlueprintReadWrite, Category = "ClothingSelection")
	int TorsoIDHightlighted; //ID of the widget object being highlighted

	UPROPERTY(BlueprintReadWrite, Category = "ClothingSelection")
	int PantsIDHightlighted; //ID of the widget object being highlighted

	UPROPERTY(BlueprintReadWrite, Category = "ClothingSelection")
	int ShoesIDHighlighted; //ID of the widget object being highlighted

	UPROPERTY(BlueprintReadWrite, Category = "ClothingSelection")
	bool ClothingOptionSelected; //A clothing option has been selected
	
	UPROPERTY(BlueprintReadWrite, Category = "CreationProcess")
	int CharacterCreationID;
#pragma endregion

#pragma region IDReferences
	//Controller Input as well as Character ID References
	UPROPERTY(BlueprintReadWrite, Category = "CharacterID")
	int CharacterID; //What is the characters ID
	int ControllerID; //What is the controller ID
	

	//References to ID of the clothes the character is wearing
	int HatID; //ID of hat from the array
	int TorsoID; //ID of torso from the array
	int PantsID; //ID of the pants from the array
	int ShoesID; //ID of the shoes from the array
#pragma endregion

#pragma region Meshes
	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* CurrentMesh;

	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UAnimationAsset* CurrentAnimation;

	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* CurrentHat;


	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* CurrentTorso;

	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* CurrentHair;

	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* CurrentLeftShoe;
	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* CurrentRightShoe;


	//Shes a very special unique character aint she *sarcasm/annoyed*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMesh* RuthHairMesh;
#pragma endregion

	
	//Skeletal Meshes
#pragma region SkeletalMeshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMesh* RuthSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMesh* AEIOUSkeletalMesh;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	//USkeletalMesh* MarcelSkeletalMesh;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	//USkeletalMesh* BazzaSkeletalMesh;
#pragma endregion


	//Animations for Meshes
#pragma region IdleStates
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	UAnimationAsset* RuthIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	UAnimationAsset* AEIOUIdle;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	//UAnimationAsset* MarcelIdle;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	//UAnimationAsset* BazzaIdle;
#pragma endregion



	//Character Components
	USkeletalMeshComponent* CharacterMesh; //The characters main mesh body
	UStaticMeshComponent* HeadComponent; //What is on top of the characters head
	
	
};
