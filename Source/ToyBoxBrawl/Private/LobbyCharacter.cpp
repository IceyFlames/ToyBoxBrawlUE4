// Fill out your copyright notice in the Description page of Project Settings.

#include "ToyBoxBrawl.h"
#include "LobbyCharacter.h"


// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterCreationID = 0;
	ClothingOptionChosen = -1;
	
}

// Called every frame
void ALobbyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALobbyCharacter::CreatingCharacterProcess(int num)
{
	switch (num)
	{
	case 0: 
	{
		CurrentMesh->SetSkeletalMesh(RuthSkeletalMesh, true);
		CurrentHair->SetStaticMesh(RuthHairMesh);
		CurrentMesh->PlayAnimation(RuthIdle, true);
	}
	break;

	case 1: 
	{
		ClothingOptionChosen++;
		UpdateWidgets(ClothingOptionChosen);
		

	}
	break;

	case 2:
	{

	}
	break;

	default:
		break;
	}
}

void ALobbyCharacter::Select()
{

}

void ALobbyCharacter::Deselect()
{

}

void ALobbyCharacter::DPAD_UpButton()
{
	switch (CharacterCreationID)
	{
		case 0: break;
		case 1: 
		{
			CharacterID--;
			if (CharacterID < 0) { CharacterID = 1; }
			UpdateCharacterPreview();
		}
		break;

		case 2:
		{
			ClothingOptionChosen--;
			if (ClothingOptionChosen < 0) { ClothingOptionChosen = 4; }
				UpdateWidgets(ClothingOptionChosen);
		}
		break;
		case 3: break;
	}
}

void ALobbyCharacter::DPAD_DownButton()
{
	switch (CharacterCreationID)
	{
	case 0: break;
	case 1: 
	{
		CharacterID++;
		if (CharacterID > 1) { CharacterID = 0; }
		UpdateCharacterPreview();
	}
	break;

	case 2:
	{
		ClothingOptionChosen++;
		if (ClothingOptionChosen > 4) { ClothingOptionChosen = 0; }
		UpdateWidgets(ClothingOptionChosen);
	}
	break;
	case 3: break;
	}
}

void ALobbyCharacter::UpdateCharacterPreview()
{
	switch (CharacterID)
	{
		case 0:
		{
			CurrentMesh->SetSkeletalMesh(RuthSkeletalMesh, true);
			CurrentHair->SetStaticMesh(RuthHairMesh);
			CurrentMesh->PlayAnimation(RuthIdle, true);
		}
		break;

		case 1:
		{
			CurrentMesh->SetSkeletalMesh(AEIOUSkeletalMesh, true);
			CurrentHair->SetStaticMesh(nullptr);
			CurrentMesh->PlayAnimation(AEIOUIdle, true);
		}
	}
}


void ALobbyCharacter::BottomButton()
{
	CreatingCharacterProcess(CharacterCreationID);
	CharacterCreationID++;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Character Creation: x: %i"), CharacterCreationID));

}

void ALobbyCharacter::RightButton()
{

}

void ALobbyCharacter::LeftButton()
{

}

void ALobbyCharacter::MoveForward(float axisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("axisValue: x: %f"), axisValue));
}


// Called to bind functionality to input
void ALobbyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &ALobbyCharacter::MoveForward);
	InputComponent->BindAction("Bottom_Button", IE_Pressed, this, &ALobbyCharacter::BottomButton);
	InputComponent->BindAction("Right_Button", IE_Pressed, this, &ALobbyCharacter::RightButton);
	InputComponent->BindAction("Dpad_up", IE_Pressed, this,  &ALobbyCharacter::DPAD_UpButton);
	InputComponent->BindAction("Dpad_down", IE_Pressed, this, &ALobbyCharacter::DPAD_DownButton);
	 
}

