// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadBobCameraShake.h"

UHeadBobCameraShake::UHeadBobCameraShake()
{
	bSingleInstance = true;

	OscillationDuration = 0.2;
	OscillationBlendInTime = 0.1;
	OscillationBlendOutTime = 0.2;

	RotOscillation.Pitch.Amplitude = 0.5;
	RotOscillation.Pitch.Frequency = 17;

	RotOscillation.Yaw.Amplitude = 0.5;
	RotOscillation.Yaw.Frequency = 8.5;

	RotOscillation.Roll.Amplitude = 0.5;
	RotOscillation.Roll.Frequency = 4.75;
	
	LocOscillation.Z.Amplitude = 2.0;
	LocOscillation.Z.Frequency = 17;

}
