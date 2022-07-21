#pragma once

#include "IWebSocket.h"
#include "JavascriptContext.h"
#include "JavascriptWebSocketV2.generated.h"


UCLASS()
class UJavascriptWebSocketV2 : public UObject {
  GENERATED_BODY()

public:
  DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebSocketDelegateV2NoParam);
  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketDelegateV2OneParam, const FString& , stringData);

	UPROPERTY(BlueprintAssignable, Category = "Scripting | Javascript")
  FOnWebSocketDelegateV2NoParam OnConnectedEvent;

  UPROPERTY(BlueprintAssignable, Category = "Scripting | Javascript")
  FOnWebSocketDelegateV2OneParam OnConnectionErrorEvent;

  UPROPERTY(BlueprintAssignable, Category = "Scripting | Javascript")
  FOnWebSocketDelegateV2NoParam OnClosedEvent;

  UPROPERTY(BlueprintAssignable, Category = "Scripting | Javascript")
  FOnWebSocketDelegateV2OneParam OnMessageEvent;

  UFUNCTION(BlueprintCallable, Category = "Scripting | Javascript")
  static UJavascriptWebSocketV2 *Create(const FString &endpoint);

  UFUNCTION(BlueprintCallable, Category = "Scripting | Javascript")
  void Connect();

  UFUNCTION(BlueprintCallable, Category = "Scripting | Javascript")
  bool IsConnected();

  UFUNCTION(BlueprintCallable, Category = "Scripting | Javascript")
  void Close();

  UFUNCTION(BlueprintCallable, Category = "Scripting | Javascript")
  void Send(const FString &stringData /* utf-8 */);

private:
  TSharedPtr<IWebSocket> WebSocket;
};