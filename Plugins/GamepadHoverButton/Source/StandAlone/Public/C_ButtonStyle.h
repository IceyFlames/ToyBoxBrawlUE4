// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/**
*
*/
class SC_ButtonStyle : public SButton
{
public:
	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;

	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;

private:
	TOptional<EFocusCause> hadFocusLastFrame = TOptional<EFocusCause>();
};
