// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "StrategyTeamInterface.h"
#include "StrategyPlayerController.generated.h"

class AStrategySpectatorPawn;
class UStrategyCameraComponent;
class AStrategyBuilding_Brewery;

UCLASS()
class AStrategyPlayerController : public APlayerController, public IStrategyTeamInterface
{
	GENERATED_UCLASS_BODY()

public:
	// Begin PlayerController interface
	/** fixed rotation */
	virtual void UpdateRotation(float DeltaTime) override;

protected:
	/** update input detection */
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface
	virtual void BeginPlay();

public:

	/** Allied Brewery */
	UPROPERTY(EditDefaultsOnly, Category = Brewery)
	AStrategyBuilding_Brewery* AlliedBrewery;

	// Begin StrategyTeamInterface interface
	virtual uint8 GetTeamNum() const override;
	// End StrategyTeamInterface interface
	
	/** set desired camera position. */
	void SetCameraTarget(const FVector& CameraTarget);

	/** helper function to toggle input detection. */
	void SetIgnoreInput(bool bIgnore);

	/** Input handlers. */
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime);
	void OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);
	void OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	/** Toggles the ingame menu display. */
	void OnToggleInGameMenu();

	/** Readies up player */
	void OnReadyUp();

	/** Handler for mouse leaving the minimap. */
	void MouseLeftMinimap();

	/** Handler for mouse pressed over minimap. */
	void MousePressedOverMinimap();
	
	/** Handler for mouse release over minimap. */
	void MouseReleasedOverMinimap();

	/** Event for when gameplay state changes. */
	void OnGameplayStateChange(EGameplayState::Type NewState);

	/** Event for when the possessed minion is destoryed. */
	void OnPossessedMinionDestroyed();

	/** Event for when the wave ends. */
	void OnWaveEnd();

protected:
	/** if set, input and camera updates will be ignored */
	uint8 bIgnoreInput : 1;

	/** currently selected actor */
	TWeakObjectPtr<AActor> SelectedActor;

	/** Swipe anchor. */
	FVector SwipeAnchor3D;

	FVector2D PrevSwipeScreenPosition;

	/** Previous swipe mid point. */
	FVector2D PrevSwipeMidPoint;

	/** Custom input handler. */
	UPROPERTY()
	class UStrategyInput* InputHandler;

	/** Currently Possesed Minion */
	TWeakObjectPtr<AStrategyChar> PossessedMinion = nullptr;

	/** Last Possessed pawn. */
	TWeakObjectPtr<APawn> LastPossessed = nullptr;

	/** 
	 * Change current selection (on toggle on the same). 
	 *
	 * @param	NewFocus	Actor to focus on.
	 * @param	NewPosition	
	 */
	void SetSelectedActor(AActor* NewFocus, const FVector& NewPosition);

	/** 
	 * Get friendly target under screen space coordinates.
	 *
	 * @param	ScreenPoint	Screen coordinates to check
	 * @param	WorldPoint	Point in the world the screen coordinates projected onto.
	 */
	AActor* GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const;

	/** 
	 * Get audio listener position and orientation.
	 * 
	 * @param	
	 * @param	
	 * @param	
	 */
	void GetAudioListenerPosition(FVector& Location, FVector& FrontDir, FVector& RightDir);

private:
	/** Helper to return cast version of Spectator pawn. */		
	AStrategySpectatorPawn* GetStrategySpectatorPawn() const;
	
	/** Helper to return camera component via spectator pawn. */
	UStrategyCameraComponent* GetCameraComponent() const;

	void MoveForward(float Val);

	void MoveRight(float Val);

	void LookRight(float Val);

	void Attack();
};
