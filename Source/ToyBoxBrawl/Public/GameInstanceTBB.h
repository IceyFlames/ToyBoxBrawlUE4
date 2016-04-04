// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "GameInstanceTBB.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerCharacter
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	int32 _ControllerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	FString _CharacterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	int32 _TorsoColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	int32 _Haircolour;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	//int32 _TorsoID;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	//int32 _PantsID;

};



UCLASS()
class TOYBOXBRAWL_API UGameInstanceTBB : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerGameInstance")
	TArray<FPlayerCharacter> _Players;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	int32 _PlayerNum = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	int32 _PlayersDead;

private:

};
