#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "Widget_GoalText.generated.h"

class UTextBlock;

UCLASS(Abstract, BlueprintType)
class GEPASSIGNMENT2_API UWidget_GoalText : public UUserWidget
{
	GENERATED_BODY()

public :

	virtual void NativeConstruct() override;

private :

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GoalText;
};
