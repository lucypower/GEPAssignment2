﻿#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "Widget_Score.generated.h"

class UTextBlock;

UCLASS(Abstract, BlueprintType)
class GEPASSIGNMENT2_API UWidget_Score : public UUserWidget
{
	GENERATED_BODY()

public :

	virtual void NativeConstruct() override;

	void UpdateScore(int score);

private :

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
};
