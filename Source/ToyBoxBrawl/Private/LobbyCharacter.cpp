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
	ClothingOptionHighlighted = -1;
	
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
		ClothingOptionHighlighted++;
		UpdateWidgets(ClothingOptionHighlighted);
		

	}
	break;

	case 2:
	{
		ClothingOptionSelected = true;
		UpdateWidgets(ClothingOptionHighlighted);
	}
	break;

	default:
		break;
	}
}

void ALobbyCharacter::TransitionBack(int num)
{
	switch (num)
	{
	case 0:
	{
		//CurrentMesh->SetSkeletalMesh(nullptr, true);
		//CurrentHair->SetStaticMesh(nullptr);
		//CurrentMesh->PlayAnimation(nullptr , true);
	}
	break;

	case 1:
	{
		CurrentMesh->SetSkeletalMesh(nullptr, true);
		CurrentHair->SetStaticMesh(nullptr);
		CurrentMesh->PlayAnimation(nullptr, true);
		CharacterCreationID = 0;

		//ClothingOptionHighlighted--;
		UpdateWidgets(ClothingOptionHighlighted);


	}
	break;

	case 2:
	{
		
		ClothingOptionHighlighted = -1;
		UpdateWidgets(ClothingOptionHighlighted);
		//ClothingOptionHighlighted = 0;
	}
	break;

	case 3:
	{
		ClothingOptionSelected = false;
		UpdateWidgets(ClothingOptionHighlighted);
	}

	default:
		break;
	}
}



void ALobbyCharacter::UpdateClothingCounters(int _num)
{
	switch (CharacterID)
	{
		//What is the characters ID
		case 0: 
		{
			//Which clothing Option is selected
			switch (ClothingOptionHighlighted)
			{

			case 0:
			{
				HatIDHighlighted += _num;
				if (HatIDHighlighted > RHats.Num() - 1)
					HatIDHighlighted = 0;

				if (HatIDHighlighted < 0)
					HatIDHighlighted = RHats.Num() - 1;

				CurrentHat->SetStaticMesh(RHats[HatIDHighlighted].StaticMesh);
				CurrentHat->AttachSocketName = RHats[HatIDHighlighted]._Socketname;
				UpdateWidgets(ClothingOptionHighlighted);
				
			}
			break;

			case 1:
			{
				if (RTorso.Num() > 0)
				{
					TorsoIDHightlighted += _num;
					if (TorsoIDHightlighted > RTorso.Num() - 1)
						TorsoIDHightlighted = 0;

					if (TorsoIDHightlighted < 0)
						TorsoIDHightlighted = RTorso.Num() - 1;


					CurrentTorso->SetStaticMesh(RTorso[TorsoIDHightlighted].StaticMesh);
					CurrentTorso->AttachSocketName = RTorso[TorsoIDHightlighted]._Socketname;
					UpdateWidgets(ClothingOptionHighlighted);
				}
			}
			break;
			
			case 2:
			{
				if (RPants.Num() > 0)
				{
					PantsIDHightlighted += _num;
					if (PantsIDHightlighted > RPants.Num() - 1)
						PantsIDHightlighted = 0;

					if (PantsIDHightlighted < 0)
						PantsIDHightlighted = RPants.Num() - 1;

					UpdateWidgets(ClothingOptionHighlighted);
				}
			}
			break;
			case 3:
			{
				if (RShoes.Num() > 0)
				{
					ShoesIDHighlighted += _num;
					if (ShoesIDHighlighted > RShoes.Num() - 1)
						ShoesIDHighlighted = 0;

					if (ShoesIDHighlighted < 0)
						ShoesIDHighlighted = RShoes.Num() - 1;

					UpdateWidgets(ClothingOptionHighlighted);
				}
			}
			break;
			
		

			default:
				break;
			}
		}
		break;

		case 1:
		{
			
		}
		break;
	}

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
			ClothingOptionHighlighted--;
			if (ClothingOptionHighlighted < 0) { ClothingOptionHighlighted = 4; }
				UpdateWidgets(ClothingOptionHighlighted);
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
		ClothingOptionHighlighted++;
		if (ClothingOptionHighlighted > 4) { ClothingOptionHighlighted = 0; }
		UpdateWidgets(ClothingOptionHighlighted);
	}
	break;
	case 3: break;
	}
}


void ALobbyCharacter::DPAD_LeftButton()
{
	if (ClothingOptionSelected)
	{
		UpdateClothingCounters(-1);
	}
}

void ALobbyCharacter::DPAD_RightButton()
{
	if (ClothingOptionSelected)
	{
		UpdateClothingCounters(1);
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
	if (CharacterCreationID > 3) CharacterCreationID = 3;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Character Creation: x: %i"), CharacterCreationID));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Clothing Option: x: %i"), ClothingOptionHighlighted));
}

void ALobbyCharacter::RightButton()
{
	TransitionBack(CharacterCreationID);
	CharacterCreationID--;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Character Creation: x: %i"), CharacterCreationID));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Clothing Option: x: %i"), ClothingOptionHighlighted));

	if (CharacterCreationID < 0) { CharacterCreationID = 0; }
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
	InputComponent->BindAction("Dpad_left", IE_Pressed, this, &ALobbyCharacter::DPAD_LeftButton);
	InputComponent->BindAction("Dpad_right", IE_Pressed, this, &ALobbyCharacter::DPAD_RightButton);
	 
}

