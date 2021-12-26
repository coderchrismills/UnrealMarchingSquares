// Fill out your copyright notice in the Description page of Project Settings.


#include "MarchingPlayerController.h"
#include "MarchingCameraManager.h"

AMarchingPlayerController::AMarchingPlayerController()
{
	PlayerCameraManagerClass = AMarchingCameraManager::StaticClass();
}