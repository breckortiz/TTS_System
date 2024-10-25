#pragma once

#include "CoreMinimal.h"
#include "BasicVoice.h"  // Ensure this is included first if BasicVoice is a parent class
#include "MaleVoice.generated.h"

UCLASS(Blueprintable)
class TTS_TEST_SAPI_API AMaleVoice : public AActor
{
    GENERATED_BODY()

private:
    UBasicVoice* BasicVoiceComponent; // Use composition to include BasicVoice

public:
    AMaleVoice(); // Constructor to initialize BasicVoiceComponent

    UFUNCTION(BlueprintCallable, Category = "TTS")
    void SetSpeech(const FString& Text); // Update the signature

    UFUNCTION(BlueprintCallable, Category = "TTS")
    void OutSpeech();

    UFUNCTION(BlueprintCallable, Category = "TTS")
    void ByeSpeech();
};
