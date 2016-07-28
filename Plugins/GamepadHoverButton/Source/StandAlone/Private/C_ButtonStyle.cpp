// Fill out your copyright notice in the Description page of Project Settings.

#include "GamepadHoverButtonPCH.h"
#include "C_ButtonStyle.h"
#include "Runtime/UMG/Public/UMGStyle.h"


FReply SC_ButtonStyle::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	bIsHovered = true;

	return SButton::OnFocusReceived(MyGeometry, InFocusEvent);
}

void SC_ButtonStyle::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	bIsHovered = false;

	SButton::OnFocusLost(InFocusEvent);
}