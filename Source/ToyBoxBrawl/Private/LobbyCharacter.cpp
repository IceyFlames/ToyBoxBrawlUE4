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
	
}

// Called every frame
void ALobbyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALobbyCharacter::Select()
{

}

void ALobbyCharacter::Deselect()
{

}

void ALobbyCharacter::UpButton()
{

}

void ALobbyCharacter::DownButton()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Bottom Button Pressed"));
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
	InputComponent->BindAction("Bottom_Button", IE_Pressed, this, &ALobbyCharacter::DownButton);
	InputComponent->BindAction("Right_Button", IE_Pressed, this, &ALobbyCharacter::RightButton);
	InputComponent->BindAction("Dpad_up", IE_Pressed, this,  &ALobbyCharacter::UpButton);
	InputComponent->BindAction("Dpad_down", IE_Pressed, this, &ALobbyCharacter::DownButton);
	 
}

