// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if(DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
	
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	//ENetRole LocalRole = InPawn->GetLocalRole();
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	APlayerState* PlayerState = InPawn->GetPlayerState();
	FString PlayerName = FString("");
	if(PlayerState)
	{
	PlayerName = PlayerState->GetPlayerName();
		
	}
	FString Role;
	/*
	switch(LocalRole)
	{
	case ENetRole::ROLE_Authority:
		Role = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Role = FString("Authonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		Role = FString("None");
		break;
	}

	FString LocalRoleString = FString::Printf(TEXT("Local role: %s"), *Role);
	SetDisplayText(LocalRoleString);
	*/
	switch(RemoteRole)
	{
	case ENetRole::ROLE_Authority:
		Role = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Role = FString("Authonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		Role = FString("None");
		break;
	}
	FString RemoteRoleString = FString::Printf(TEXT("Remote role: %s"), *PlayerName);
	SetDisplayText(RemoteRoleString);
	
}



void UOverheadWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
