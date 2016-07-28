// Fill out your copyright notice in the Description page of Project Settings.

#include "GamepadHoverButtonPCH.h"
#include "C_ButtonWidget.h"
#include "Runtime/UMG/Public/UMGStyle.h"


#define LOCTEXT_NAMESPACE "Custom Button"

/////////////////////////////////////////////////////
// UButton

UC_ButtonWidget::UC_ButtonWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SButton::FArguments ButtonDefaults;
	WidgetStyle = *ButtonDefaults._ButtonStyle;

	ColorAndOpacity = FLinearColor::White;
	BackgroundColor = FLinearColor::White;

	ClickMethod = EButtonClickMethod::DownAndUp;
	TouchMethod = EButtonTouchMethod::DownAndUp;

	IsFocusable = true;
}

void UC_ButtonWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	CustomButton.Reset();
}

TSharedRef<SWidget> UC_ButtonWidget::RebuildWidget()
{
	CustomButton = SNew(SC_ButtonStyle)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
		.OnHovered_UObject(this, &ThisClass::SlateHandleHovered)
		.OnUnhovered_UObject(this, &ThisClass::SlateHandleUnhovered)
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.IsFocusable(IsFocusable)
		;

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(CustomButton.ToSharedRef());
	}

	return CustomButton.ToSharedRef();
}

void UC_ButtonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	CustomButton->SetColorAndOpacity(ColorAndOpacity);
	CustomButton->SetBorderBackgroundColor(BackgroundColor);
}

UClass* UC_ButtonWidget::GetSlotClass() const
{
	return UButtonSlot::StaticClass();
}

void UC_ButtonWidget::OnSlotAdded(UPanelSlot* Slot)
{
	// Add the child to the live slot if it already exists
	if (CustomButton.IsValid())
	{
		Cast<UButtonSlot>(Slot)->BuildSlot(CustomButton.ToSharedRef());
	}
}

void UC_ButtonWidget::OnSlotRemoved(UPanelSlot* Slot)
{
	// Remove the widget from the live slot if it exists.
	if (CustomButton.IsValid())
	{
		CustomButton->SetContent(SNullWidget::NullWidget);
	}
}

void UC_ButtonWidget::SetStyle(const FButtonStyle& InStyle)
{
	WidgetStyle = InStyle;
	if (CustomButton.IsValid())
	{
		CustomButton->SetButtonStyle(&WidgetStyle);
	}
}

void UC_ButtonWidget::SetColorAndOpacity(FLinearColor InColorAndOpacity)
{
	ColorAndOpacity = InColorAndOpacity;
	if (CustomButton.IsValid())
	{
		CustomButton->SetColorAndOpacity(InColorAndOpacity);
	}
}

void UC_ButtonWidget::SetBackgroundColor(FLinearColor InBackgroundColor)
{
	BackgroundColor = InBackgroundColor;
	if (CustomButton.IsValid())
	{
		CustomButton->SetBorderBackgroundColor(InBackgroundColor);
	}
}

bool UC_ButtonWidget::IsPressed() const
{
	if (CustomButton.IsValid())
	{
		return CustomButton->IsPressed();
	}

	return false;
}

void UC_ButtonWidget::PostLoad()
{
	Super::PostLoad();

	if (GetChildrenCount() > 0)
	{
		//TODO UMG Pre-Release Upgrade, now buttons have slots of their own.  Convert existing slot to new slot.
		if (UPanelSlot* PanelSlot = GetContentSlot())
		{
			UButtonSlot* ButtonSlot = Cast<UButtonSlot>(PanelSlot);
			if (ButtonSlot == NULL)
			{
				ButtonSlot = NewObject<UButtonSlot>(this);
				ButtonSlot->Content = GetContentSlot()->Content;
				ButtonSlot->Content->Slot = ButtonSlot;
				Slots[0] = ButtonSlot;
			}
		}
	}

	if (GetLinkerUE4Version() < VER_UE4_DEPRECATE_UMG_STYLE_ASSETS && Style_DEPRECATED != nullptr)
	{
		const FButtonStyle* StylePtr = Style_DEPRECATED->GetStyle<FButtonStyle>();
		if (StylePtr != nullptr)
		{
			WidgetStyle = *StylePtr;
		}

		Style_DEPRECATED = nullptr;
	}
}

FReply UC_ButtonWidget::SlateHandleClicked()
{
	OnClicked.Broadcast();

	return FReply::Handled();
}

void UC_ButtonWidget::SlateHandlePressed()
{
	OnPressed.Broadcast();
}

void UC_ButtonWidget::SlateHandleReleased()
{
	OnReleased.Broadcast();
}

void UC_ButtonWidget::SlateHandleHovered()
{
	SetUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	OnHovered.Broadcast();
}

void UC_ButtonWidget::SlateHandleUnhovered()
{
	//SetUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	OnUnhovered.Broadcast();
}

#if WITH_EDITOR

const FSlateBrush* UC_ButtonWidget::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.Button");
}

const FText UC_ButtonWidget::GetPaletteCategory()
{
	return LOCTEXT("Common", "Common");
}

#endif


#undef LOCTEXT_NAMESPACE