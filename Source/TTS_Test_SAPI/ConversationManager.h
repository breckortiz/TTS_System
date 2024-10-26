#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "ConversationManager.generated.h"

UCLASS(Blueprintable)
class TTS_TEST_SAPI_API UConversationManager : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Searches for a .wav file in the GeneratedAudio folder by name and returns a Sound Cue made from that .wav file */
    UFUNCTION(BlueprintCallable, Category = "Sound")
    static USoundCue* GetSoundCueFromFileName(const FString& FileName);
};
