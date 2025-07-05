// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosWorldPlayerChatWidget.h"
#include "PlayerController/EosWorldPlayerController.h"
#include "Components/UI/EosPlayerUIComponent.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"


void UEosWorldPlayerChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_Chat)
	{
		EditableTextBox_Chat->OnTextCommitted.AddDynamic(this, &UEosWorldPlayerChatWidget::OnTextCommitted);
	}

	GetWorld()->GetTimerManager().SetTimer(GetUIComponentTimer, this, &UEosWorldPlayerChatWidget::Init, 5.0f, false);

}

void UEosWorldPlayerChatWidget::UpdateMessages(const FText& InMessage)
{
	UTextBlock* Message = NewObject<UTextBlock>(this);
	Message->SetText(InMessage);
	Message->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	Message->SetAutoWrapText(true);
	FSlateFontInfo FontInfo = Message->Font;
	FontInfo.Size = 13;
	Message->SetFont(FontInfo);

	ScrollBox_ChatBox->AddChild(Message);
	ScrollBox_ChatBox->ScrollToEnd();
}

void UEosWorldPlayerChatWidget::UpdateSystemMessages(const FText& InMessage)
{
	UTextBlock* Message = NewObject<UTextBlock>(this);
	Message->SetText(FText::Format(FText::FromString("[SYSTEM] : {0}"), InMessage));
	Message->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
	Message->SetAutoWrapText(true);
	FSlateFontInfo FontInfo = Message->Font;
	FontInfo.Size = 14;
	Message->SetFont(FontInfo);

	ScrollBox_ChatBox->AddChild(Message);
	ScrollBox_ChatBox->ScrollToEnd();
}

void UEosWorldPlayerChatWidget::FocusEditableTextBox()
{
	EditableTextBox_Chat->SetKeyboardFocus();
}

void UEosWorldPlayerChatWidget::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		AEosWorldPlayerController* PlayerController = Cast<AEosWorldPlayerController>(GetOwningPlayer());
		if (PlayerController)
		{
			FInputModeGameOnly GameOnly;
			PlayerController->SetInputMode(GameOnly);

			if (!Text.IsEmpty())
			{
				if (Text.ToString().StartsWith(TEXT("/")))
				{
					FString Trimmed = Text.ToString().RightChop(1);		// 슬래시 제거
					FString Command;
					FString Argument;
					FString PartyCommand = "party";

					if (Trimmed.Split(TEXT(" "), &Command, &Argument))
					{
						if (Command.Equals(PartyCommand, ESearchCase::IgnoreCase))
						{
							EditableTextBox_Chat->SetText(FText::GetEmpty());
							PlayerController->Server_AskParty(Argument);
							return;
						}
					}
				}

				FText Message = FText::Format(FText::FromString("{0} : {1}"), FText::FromString(PlayerController->GetPlayerInfo().NickName), Text);
				PlayerController->Server_SendMessage(Message);
				EditableTextBox_Chat->SetText(FText::GetEmpty());
			}
		}
	}
}

void UEosWorldPlayerChatWidget::Init()
{
	UEosPlayerUIComponent* UIComponent = BringPlayerUIComponent();
	if (UIComponent)
	{
		UIComponent->OnSendMessage.AddDynamic(this, &UEosWorldPlayerChatWidget::FocusEditableTextBox);
		UIComponent->OnUpdateMessage.AddDynamic(this, &UEosWorldPlayerChatWidget::UpdateMessages);
		UIComponent->OnSystemMessage.AddDynamic(this, &UEosWorldPlayerChatWidget::UpdateSystemMessages);
	}
}
