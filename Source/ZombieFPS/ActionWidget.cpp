// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionWidget.h"

void UActionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UActionWidget::OnStart_Implementation(bool bIsFirstTime)
{
	IAction::OnStart_Implementation(bIsFirstTime);
}

void UActionWidget::OnUpdate_Implementation(float DeltaTime)
{
	IAction::OnUpdate_Implementation(DeltaTime);
}

void UActionWidget::OnEnd_Implementation()
{
	IAction::OnEnd_Implementation();
}

bool UActionWidget::IsDone_Implementation()
{
	return bIsDone;
}


