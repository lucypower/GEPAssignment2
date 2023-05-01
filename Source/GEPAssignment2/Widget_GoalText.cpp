#include "Widget_GoalText.h"
#include "Components/TextBlock.h"

void UWidget_GoalText::NativeConstruct()
{
	Super::NativeConstruct();

	if (GoalText)
	{
		GoalText->SetText(FText::FromString("Find and Destroy all the fruit baskets!"));
	}
}
