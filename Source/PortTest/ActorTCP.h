// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "GameFramework/Actor.h"
#include "ActorTCP.generated.h"

UCLASS()
class PORTTEST_API AActorTCP : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AActorTCP();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Socket")
	FString SocketName = "SocketListener";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Socket")
	FString IpAddress = "127.0.0.1";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Socket")
	int32 Port = 4445;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FSocket* ListenerSocket;
	FSocket* ConnectionSocket;
	FIPv4Endpoint RemoteAddressForConnection;

	FTimerHandle TCPSocketListenerTimerHandle;
	FTimerHandle TCPConnectionListenerTimerHandle;

	bool StartTCPReceiver(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort
	);

	FSocket* CreateTCPConnectionListener(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort,
		const int32 ReceiveBufferSize = 2 * 1024 * 1024
	);

	//Timer functions, could be threads
	void TCPConnectionListener(); 	//can thread this eventually
	FString StringFromBinaryArray(TArray<uint8> BinaryArray);
	void TCPSocketListener();		//can thread this eventually


	//Format String IP4 to number array
	bool FormatIP4ToNumber(const FString& TheIP, uint8(&Out)[4]);

	UFUNCTION(BlueprintCallable, Category = "TCPServer")
	bool LaunchTCP();

	UFUNCTION(BlueprintCallable, Category = "TCPServer")
	void TCPSend(FString message);

	UFUNCTION(BlueprintImplementableEvent, Category = "TCPServer")
	void recievedMessage(const FString &message);
};
