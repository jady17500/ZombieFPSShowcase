// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionStackComponent.h"
#include "Action.h"


// Sets default values for this component's properties
UActionStackComponent::UActionStackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionStackComponent::BeginPlay()
{
	Super::BeginPlay();
	

	// ...
	
}


// Called every frame
void UActionStackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	UpdateActions(DeltaTime);
}

void UActionStackComponent::PushAction(UObject* Action)
{
	if (ValidateAction(Action))
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, "Added");
		ActionStack.Insert(Action, 0);
		
		CurrentAction = ActionStack[0];
		bool FirstTime = !FirstTimeActions.Contains(CurrentAction);
		
		if (FirstTime)
			FirstTimeActions.Add(CurrentAction);
		OnActionAdded.Broadcast(Action);
		IAction::Execute_OnStart(Action, FirstTime);
	}
}

void UActionStackComponent::PopAction()
{
	IAction::Execute_OnEnd(CurrentAction);
	ActionStack.RemoveAt(0);
	FirstTimeActions.RemoveAt(0);
	if (ActionStack.Num() > 0)
		OnActionRemoved.Broadcast(ActionStack[0]);
	CurrentAction = nullptr;
}

bool UActionStackComponent::ValidateAction(UObject* Action)
{
	if (!IsValid(Action)) return false;
	return Action->Implements<UAction>();
}

void UActionStackComponent::UpdateActions(float DeltaTime)
{
	if (ActionStack.IsEmpty()) return;
	
	if (IsValid(CurrentAction))
	{
		IAction::Execute_OnUpdate(CurrentAction, DeltaTime);
		if (ActionStack.Num() > 0 && CurrentAction == ActionStack[0])
		{
			if (IAction::Execute_IsDone(CurrentAction))
			{
				IAction::Execute_OnEnd(CurrentAction);
				PopAction();
				CurrentAction = nullptr;				
			}
		}
	}
	else if (ActionStack.Num()>0 && ValidateAction(ActionStack[0]))
	{
		CurrentAction = ActionStack[0];
		bool FirstTime = !FirstTimeActions.Contains(CurrentAction);
		if (FirstTime)
			FirstTimeActions.Add(CurrentAction);
		IAction::Execute_OnStart(CurrentAction, FirstTime);
	}
}

