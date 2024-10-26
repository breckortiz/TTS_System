#include "ConversationManager.h"
#include "Sound/SoundWaveProcedural.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundNodeWavePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

USoundCue* UConversationManager::GetSoundCueFromFileName(const FString& FileName)
{
    FString FolderPath = FPaths::ProjectSavedDir() + TEXT("GeneratedAudio/");
    FString FilePath = FolderPath + FileName + TEXT(".wav");

    if (!FPaths::FileExists(FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("File %s not found in %s"), *FileName, *FolderPath);
        return nullptr;
    }

    // Load the .wav file into a byte array
    TArray<uint8> RawFileData;
    if (!FFileHelper::LoadFileToArray(RawFileData, *FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load file data from %s"), *FilePath);
        return nullptr;
    }

    // Create a procedural SoundWave
    USoundWaveProcedural* SoundWaveProcedural = NewObject<USoundWaveProcedural>();
    if (!SoundWaveProcedural)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create SoundWaveProcedural object"));
        return nullptr;
    }

    // Set up properties for SoundWaveProcedural
    SoundWaveProcedural->SetSampleRate(24100); // Placeholder; adjust as needed for your audio
    SoundWaveProcedural->NumChannels = 2; // Mono; set to 2 for stereo if required
    SoundWaveProcedural->Duration = 3; // Infinite duration for streaming audio

    // Push audio data to SoundWaveProcedural
    SoundWaveProcedural->QueueAudio(RawFileData.GetData(), RawFileData.Num());

    // Create a SoundCue and link it to the SoundWave
    USoundCue* SoundCue = NewObject<USoundCue>();
    USoundNodeWavePlayer* WavePlayer = NewObject<USoundNodeWavePlayer>(SoundCue);
    WavePlayer->SetSoundWave(SoundWaveProcedural);
    SoundCue->FirstNode = WavePlayer;

    return SoundCue;
}
