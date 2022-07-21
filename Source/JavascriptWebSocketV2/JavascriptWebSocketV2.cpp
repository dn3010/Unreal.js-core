#include "JavascriptWebSocketV2.h"
#include "IWebSocket.h"
#include "JavascriptContext.h"
#include "WebSocketsModule.h"

UJavascriptWebSocketV2 *
UJavascriptWebSocketV2::Create(const FString &endpoint) {
  auto instance = NewObject<UJavascriptWebSocketV2>(GetTransientPackage());
  if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
    FModuleManager::Get().LoadModule("WebSockets");
  }
  
  instance->WebSocket =
      FWebSocketsModule::Get().CreateWebSocket(endpoint, "wss");

  return instance;
}

void UJavascriptWebSocketV2::Connect() {
  // bind Native WS events to JS Events.
  UJavascriptWebSocketV2::WebSocket->OnConnected().AddLambda([this]() {
    UE_LOG(LogTemp, Log, TEXT("Connected to websocket server."));
    this->OnConnectedEvent.Broadcast();
  });

  UJavascriptWebSocketV2::WebSocket->OnConnectionError().AddLambda([this](const FString &Error) {
    UE_LOG(LogTemp, Log, TEXT("Connection error."));
    this->OnConnectionErrorEvent.Broadcast(Error);
  });

  UJavascriptWebSocketV2::WebSocket->OnClosed().AddLambda([this](int32 StatusCode, const FString &Reason, bool bWasClean) {
    UE_LOG(LogTemp, Log, TEXT("Connection closed."));
    // TODO: do we need to pass StatusCode, Reason to JS ?
    this->OnClosedEvent.Broadcast(); 
  });

  UJavascriptWebSocketV2::WebSocket->OnMessage().AddLambda([this](const FString &Message) {
  UE_LOG(LogTemp, Log, TEXT("Received message from websocket server:\"%s\"."), *Message);
    this->OnMessageEvent.Broadcast(Message); 
  });

  UJavascriptWebSocketV2::WebSocket->Connect();
}

bool UJavascriptWebSocketV2::IsConnected(){
  return WebSocket->IsConnected();
}

void UJavascriptWebSocketV2::Close(){
  WebSocket->Close();
}

void UJavascriptWebSocketV2::Send(const FString &data){
  WebSocket->Send(data);
}

