#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MaleVoice.h" // Include MaleVoice here
#include "VoiceCaller.generated.h"

UCLASS(Blueprintable)
class TTS_TEST_SAPI_API AVoiceCaller : public AActor
{
    GENERATED_BODY()

private:
    UPROPERTY()
    AMaleVoice* MaleVoiceInstance; // Instance of the male voice

public:
    // Sets default values for this actor's properties
    AVoiceCaller();

    // Function to speak the given text
    UFUNCTION(BlueprintCallable, Category = "TTS")
    void SpeakText(const FString& Text);

protected:
    virtual void BeginPlay() override; // Override BeginPlay
};
