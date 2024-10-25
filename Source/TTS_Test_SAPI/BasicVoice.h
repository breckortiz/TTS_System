#pragma once
#include <sapi.h>
#include<iostream>
#include <string>
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "BasicVoice.generated.h"

UCLASS(Blueprintable)
class TTS_TEST_SAPI_API UBasicVoice : public UObject
{
    GENERATED_BODY()

protected:
    ISpVoice* pVoice;
    HRESULT hr;
    FString input;

public:
    UBasicVoice();
    void initVoice();
    virtual void SetSpeech(const FString& Text);
    void SpeakInThread(const FString& Text);
    virtual void OutSpeech();
    virtual void ByeSpeech();
    virtual ~UBasicVoice();
};