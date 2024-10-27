#include "ConversationManager.h" 
#include "Sound/SoundWaveProcedural.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundNodeWavePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

USoundCue* UConversationManager::GetSoundCueFromFileName(const FString& FileName, UObject* WorldContextObject)
{
    FString FolderPath = FPaths::ProjectSavedDir() + TEXT("GeneratedAudio/");
    FString FilePath = FolderPath + FileName + TEXT(".wav");

    if (!FPaths::FileExists(FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("File %s not found in %s"), *FileName, *FolderPath);
        return nullptr;
    }

    // Load the .wav file into a byte array and remove the 44-byte header
    TArray<uint8> RawFileData;
    if (!FFileHelper::LoadFileToArray(RawFileData, *FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load file data from %s"), *FilePath);
        return nullptr;
    }

    constexpr int32 WavHeaderSize = 44; // shave off squeak sound
    for (int i = 0; i < 2560; i++) {
        RawFileData.Pop();
    }
    if (RawFileData.Num() <= WavHeaderSize)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid .wav file format, data too short in %s"), *FilePath);
        return nullptr;
    }
    TArray<uint8> AudioData(RawFileData.GetData() + WavHeaderSize, RawFileData.Num() - WavHeaderSize);

    // Create a procedural SoundWave
    USoundWaveProcedural* SoundWaveProcedural = NewObject<USoundWaveProcedural>();
    if (!SoundWaveProcedural)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create SoundWaveProcedural object"));
        return nullptr;
    }

    SoundWaveProcedural->SetSampleRate(GetSampleRate(FilePath));
    SoundWaveProcedural->NumChannels = 1; // Mono; set to 2 for stereo if required
    SoundWaveProcedural->Duration = 0;

    SoundWaveProcedural->QueueAudio(AudioData.GetData(), AudioData.Num());

    // Create a SoundCue and link it to the SoundWave
    USoundCue* SoundCue = NewObject<USoundCue>();
    USoundNodeWavePlayer* WavePlayer = NewObject<USoundNodeWavePlayer>(SoundCue);
    WavePlayer->SetSoundWave(SoundWaveProcedural);
    SoundCue->FirstNode = WavePlayer;

    // Create an AudioComponent to manage playback

    return SoundCue;
}

int32 UConversationManager::GetSampleRate(const FString& FilePath)
{
    TArray<uint8> RawFileData;
    if (!FFileHelper::LoadFileToArray(RawFileData, *FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load file data from %s"), *FilePath);
        return -1;
    }

    // Extract sample rate from bytes 24-27
    int32 SampleRate = *(int32*)(RawFileData.GetData() + 24);
    return SampleRate;
}
