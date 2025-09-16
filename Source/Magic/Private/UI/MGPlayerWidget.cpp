// Copyright Bear Child


#include "UI/MGPlayerWidget.h"

#include "Attributes/MGAttributeComponent.h"
#include "Character/MGCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMGPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMGCharacter* Character = CastChecked<AMGCharacter>(GetOwningPlayerPawn()))
	{
		if (UMGAttributeComponent* AttributeComp = Character->GetAttributeComponent())
		{
			AttributeComp->RegisterCall_OnHealthChanged(FOnHealthChangedSignature::FDelegate::CreateLambda([this](const FHealthChangedInfo& Info)
			{
				HealthRatioProgressBar->SetPercent(Info.Ratio);
				HealthText->SetText(FText::Format(
					FText::FromString("Health: {0} / {1}"),
					FText::AsNumber(Info.Health),
					FText::AsNumber(Info.MaxHealth)));
			}));
		}
	}
}
