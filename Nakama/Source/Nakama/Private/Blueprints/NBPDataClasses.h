/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "NakamaSDK/NError.h"
#include "NakamaSDK/NFriend.h"
#include "NakamaSDK/NSelf.h"
#include "NakamaSDK/NUser.h"
#include "NakamaSDK/NUserPresence.h"
#include "NakamaSDK/NGroup.h"
#include "NakamaSDK/NGroupSelf.h"
#include "NakamaSDK/NCursor.h"
#include "NakamaSDK/NGroupUser.h"
#include "NakamaSDK/NResultSet.h"
#include "NakamaSDK/NStorageKey.h"
#include "NakamaSDK/NStorageData.h"
#include "NakamaSDK/NMatch.h"
#include "NakamaSDK/NMatchData.h"
#include "NakamaSDK/NMatchPresence.h"
#include "NakamaSDK/NTopicId.h"
#include "NakamaSDK/NTopic.h"
#include "NakamaSDK/NTopicMessage.h"
#include "NakamaSDK/NTopicMessageAck.h"
#include "NakamaSDK/NTopicPresence.h"
#include "NakamaSDK/NLeaderboard.h"
#include "NakamaSDK/NLeaderboardRecord.h"
#include "NakamaSDK/NLeaderboard.h"
#include "NakamaSDK/NMatchToken.h"
#include "NakamaSDK/NMatchmakeTicket.h"
#include "NakamaSDK/NMatchmakeMatched.h"
#include "NakamaSDK/NNotification.h"
#include "NakamaSDK/NPurchaseRecord.h"
#include "NakamaSDK/NRuntimeRpc.h"
#include "NakamaSDK/NStorageUpdateMessage.h"
#include "NBPDataClasses.generated.h"

#define FROM_NAKAMA_DATE(__DATE__) FDateTime::FromUnixTimestamp(__DATE__/1000)
#define CONVERT_TO_BP_STATIC(__NTYPE__, __BPTYPE__) static __BPTYPE__* From(__NTYPE__ data) { auto bpItem = NewObject<__BPTYPE__>(); bpItem->Wrapped = data; return bpItem; }
#define CONVERT_RS_TO_BP_STATIC(__NTYPE__, __BPTYPE__) static TArray<__BPTYPE__*> FromResultSet(NResultSet<__NTYPE__>* resultSet) { TArray<__BPTYPE__*> rVal; auto results = resultSet->GetResults(); for (int i = 0, maxI = results.size(); i < maxI; i++) { rVal.Add(__BPTYPE__::From(results[i])); } return rVal; }

class UPlayFabJsonObject;

using namespace Nakama;

// ------------------------- NError -------------------------

UCLASS(BlueprintType)
class UNBPError : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NError, UNBPError)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Error")
		FString GetErrorMessage() { return UTF8_TO_TCHAR(Wrapped.GetErrorMessage().c_str()); }

private:
	NError Wrapped;
};

// ------------------------- NCursor -------------------------

UCLASS(BlueprintType)
class UNBPCursor : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NCursor, UNBPCursor)
	NCursor GetNCursor() { return Wrapped; }

private:
	NCursor Wrapped;
};

// ------------------------- NFriend -------------------------

UENUM(BlueprintType)
enum class EFriendType : uint8
{
	Friend = 0, Invite, Invited, Blocked
};

UCLASS(BlueprintType)
class UNBPFriend : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NFriend, UNBPFriend)
	CONVERT_RS_TO_BP_STATIC(NFriend, UNBPFriend)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetFullname() { return UTF8_TO_TCHAR(Wrapped.GetFullname().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FDateTime GetLastOnlineAt() { return FROM_NAKAMA_DATE(Wrapped.GetLastOnlineAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetLocation().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetTimezone().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		EFriendType GetState() { return (EFriendType)Wrapped.GetState(); }

private:
	NFriend Wrapped;
};

// ------------------------- NSelf -------------------------

UCLASS(BlueprintType)
class UNBPSelf : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NSelf, UNBPSelf)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetFullname() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FDateTime GetLastOnlineAt() { return FROM_NAKAMA_DATE(Wrapped.GetLastOnlineAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetCustomId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		TArray<FString> GetDeviceIds();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetEmail() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetFacebookId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetGameCenterId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetSteamId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		bool IsVerified() { return Wrapped.IsVerified(); }

private:
	NSelf Wrapped;
};

// ------------------------- NGroup -------------------------

UCLASS(BlueprintType)
class UNBPGroup : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NGroup, UNBPGroup)
	CONVERT_RS_TO_BP_STATIC(NGroup, UNBPGroup)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		bool IsPrivate() { return Wrapped.IsPrivate(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetCreatorId() { return UTF8_TO_TCHAR(Wrapped.GetCreatorId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetName() { return UTF8_TO_TCHAR(Wrapped.GetName().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetDescription() { return UTF8_TO_TCHAR(Wrapped.GetDescription().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FDateTime GetCount() { return FROM_NAKAMA_DATE(Wrapped.GetCount()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

private:
	NGroup Wrapped;
};

// ------------------------- NGroupSelf -------------------------

UENUM(BlueprintType)
enum class EGroupState : uint8
{
	Admin = 0, Member, Join
};

UCLASS(BlueprintType)
class UNBPGroupSelf : public UNBPGroup
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NGroupSelf, UNBPGroupSelf)
	CONVERT_RS_TO_BP_STATIC(NGroupSelf, UNBPGroupSelf)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		EGroupState GetState() { return (EGroupState)Wrapped.GetState(); }
private:
	NGroupSelf Wrapped;
};

// ------------------------- NGroupUser -------------------------

UENUM(BlueprintType)
enum class EGroupUserState : uint8
{
	Admin = 0, Member, Join
};

UCLASS(BlueprintType)
class UNBPGroupUser : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NGroupUser, UNBPGroupUser)
	CONVERT_RS_TO_BP_STATIC(NGroupUser, UNBPGroupUser)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetFullname() { return UTF8_TO_TCHAR(Wrapped.GetFullname().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FDateTime GetLastOnlineAt() { return FROM_NAKAMA_DATE(Wrapped.GetLastOnlineAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetLocation().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetTimezone().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		EGroupUserState GetState() { return (EGroupUserState)Wrapped.GetState(); }

private:
	NGroupUser Wrapped;
};


// ------------------------- NUser -------------------------

UCLASS(BlueprintType)
class UNBPUser : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NUser, UNBPUser)
	CONVERT_RS_TO_BP_STATIC(NUser, UNBPUser)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetFullname() { return UTF8_TO_TCHAR(Wrapped.GetFullname().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FDateTime GetLastOnlineAt() { return FROM_NAKAMA_DATE(Wrapped.GetLastOnlineAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetLocation().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetTimezone().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

private:
	NUser Wrapped;
};


// ------------------------- NStorageKey -------------------------

UCLASS(BlueprintType)
class UNBPStorageKey : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NStorageKey, UNBPStorageKey)
	CONVERT_RS_TO_BP_STATIC(NStorageKey, UNBPStorageKey)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Key")
		FString GetBucket() { return UTF8_TO_TCHAR(Wrapped.GetBucket().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Key")
		FString GetCollection() { return UTF8_TO_TCHAR(Wrapped.GetCollection().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Key")
		FString GetRecord() { return UTF8_TO_TCHAR(Wrapped.GetRecord().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Key")
		FString GetVersion() { return UTF8_TO_TCHAR(Wrapped.GetVersion().c_str()); }

private:
	NStorageKey Wrapped;
};


// ------------------------- NStorageData -------------------------

UENUM(BlueprintType)
enum class EStoragePermissionRead : uint8
{
	NoRead = 0, OwnerRead, PublicRead
};

UENUM(BlueprintType)
enum class EStoragePermissionWrite : uint8
{
	NoWrite = 0, OwnerWrite
};

UCLASS(BlueprintType)
class UNBPStorageData : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NStorageData, UNBPStorageData)
	CONVERT_RS_TO_BP_STATIC(NStorageData, UNBPStorageData)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetBucket() { return UTF8_TO_TCHAR(Wrapped.GetBucket().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetCollection() { return UTF8_TO_TCHAR(Wrapped.GetCollection().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetRecord() { return UTF8_TO_TCHAR(Wrapped.GetRecord().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetUserId() { return UTF8_TO_TCHAR(Wrapped.GetUserId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetValue() { return UTF8_TO_TCHAR(Wrapped.GetValue().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetVersion() { return UTF8_TO_TCHAR(Wrapped.GetVersion().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		EStoragePermissionRead GetPermissionRead() { return (EStoragePermissionRead)Wrapped.GetPermissionRead(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		EStoragePermissionWrite GetPermissionWrite() { return (EStoragePermissionWrite)Wrapped.GetPermissionWrite(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FDateTime GetExpiresAt() { return FROM_NAKAMA_DATE(Wrapped.GetExpiresAt()); }

private:
	NStorageData Wrapped;
};


// ------------------------- NUserPresence -------------------------

UCLASS(BlueprintType)
class UNBPUserPresence : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NUserPresence, UNBPUserPresence)

	static TArray<UNBPUserPresence*> FromArray(std::vector<NUserPresence> pArray);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|User Presence")
		FString GetUserId() { return UTF8_TO_TCHAR(Wrapped.GetUserId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|User Presence")
		FString GetSessionId() { return UTF8_TO_TCHAR(Wrapped.GetSessionId().c_str()); }

private:
	NUserPresence Wrapped;
};


// ------------------------- NMatch -------------------------

UCLASS(BlueprintType)
class UNBPMatch : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NMatch, UNBPMatch)
	CONVERT_RS_TO_BP_STATIC(NMatch, UNBPMatch)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match")
		TArray<UNBPUserPresence*> GetPresence() { return UNBPUserPresence::FromArray(Wrapped.GetPresence()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match")
		UNBPUserPresence* GetSelf() { return UNBPUserPresence::From(Wrapped.GetSelf()); }

private:
	NMatch Wrapped;
};


// ------------------------- NMatchData -------------------------

UCLASS(BlueprintType)
class UNBPMatchData : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NMatchData, UNBPMatchData)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Data")
		FString GetData() { return UTF8_TO_TCHAR(Wrapped.GetData().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Data")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Data")
		int32 GeOpCode() { return Wrapped.GeOpCode(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Data")
		UNBPUserPresence* GetPresence() { return UNBPUserPresence::From(Wrapped.GetPresence()); }

private:
	NMatchData Wrapped;
};

// ------------------------- NMatchPresence -------------------------

UCLASS(BlueprintType)
class UNBPMatchPresence : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NMatchPresence, UNBPMatchPresence)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Presence")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Presence")
		TArray<UNBPUserPresence*> GetJoin() { return  UNBPUserPresence::FromArray(Wrapped.GetJoin()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Presence")
		TArray<UNBPUserPresence*> GetLeave() { return  UNBPUserPresence::FromArray(Wrapped.GetLeave()); }

private:
	NMatchPresence Wrapped;
};

// ------------------------- NTopicId -------------------------

UENUM(BlueprintType)
enum class ETopicType : uint8
{
	DirectMessage = 0, Room, Group
};

UCLASS(BlueprintType)
class UNBPTopicId : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NTopicId, UNBPTopicId)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Id")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Id")
		ETopicType GetType() { return (ETopicType)Wrapped.GetType(); }

	NTopicId GetNTopicId() { return Wrapped; }

private:
	NTopicId Wrapped;
};

// ------------------------- NTopic -------------------------

UCLASS(BlueprintType)
class UNBPTopic : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NTopic, UNBPTopic)
	CONVERT_RS_TO_BP_STATIC(NTopic, UNBPTopic)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic")
		UNBPTopicId* GetTopic() { return UNBPTopicId::From(Wrapped.GetTopic()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic")
		TArray<UNBPUserPresence*> GetPresence() { return  UNBPUserPresence::FromArray(Wrapped.GetPresence()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic")
		UNBPUserPresence* GetSelf() { return  UNBPUserPresence::From(Wrapped.GetSelf()); }

private:
	NTopic Wrapped;
};

// ------------------------- NTopicMessage -------------------------

UENUM(BlueprintType)
enum class ETopicMessageType : uint8
{
	Chat = 0, GroupJoin, GroupAdd, GroupLeave, GroupKick, GroupPromoted
};

UCLASS(BlueprintType)
class UNBPTopicMessage : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NTopicMessage, UNBPTopicMessage)
	CONVERT_RS_TO_BP_STATIC(NTopicMessage, UNBPTopicMessage)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		UNBPTopicId* GetTopic() { return UNBPTopicId::From(Wrapped.GetTopic()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FString GetUserId() { return UTF8_TO_TCHAR(Wrapped.GetUserId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FString GetMessageId() { return UTF8_TO_TCHAR(Wrapped.GetMessageId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FDateTime GetExpiresAt() { return FROM_NAKAMA_DATE(Wrapped.GetExpiresAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		ETopicMessageType GetType() { return (ETopicMessageType)Wrapped.GetType(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FString GetData() { return UTF8_TO_TCHAR(Wrapped.GetData().c_str()); }

private:
	NTopicMessage Wrapped;
};

// ------------------------- NTopicMessageAck -------------------------

UCLASS(BlueprintType)
class UNBPTopicMessageAck : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NTopicMessageAck, UNBPTopicMessageAck)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message Ack")
		FString GetMessageId() { return UTF8_TO_TCHAR(Wrapped.GetMessageId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message Ack")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message Ack")
		FDateTime GetExpiresAt() { return FROM_NAKAMA_DATE(Wrapped.GetExpiresAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message Ack")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

private:
	NTopicMessageAck Wrapped;
};

// ------------------------- NTopicPresence -------------------------

UCLASS(BlueprintType)
class UNBPTopicPresence : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NTopicPresence, UNBPTopicPresence)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Presence")
		UNBPTopicId* GetTopic() { return UNBPTopicId::From(Wrapped.GetTopic()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Presence")
		TArray<UNBPUserPresence*> GetJoin() { return  UNBPUserPresence::FromArray(Wrapped.GetJoin()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Presence")
		TArray<UNBPUserPresence*> GetLeave() { return  UNBPUserPresence::FromArray(Wrapped.GetLeave()); }

private:
	NTopicPresence Wrapped;
};

// ------------------------- NLeaderboard -------------------------

UCLASS(BlueprintType)
class UNBPLeaderboard : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NLeaderboard, UNBPLeaderboard)
	CONVERT_RS_TO_BP_STATIC(NLeaderboard, UNBPLeaderboard)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard")
		bool IsAuthoritative() { return Wrapped.IsAuthoritative(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard")
		int32 GetSort() { return Wrapped.GetSort(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard")
		int32 GetCount() { return Wrapped.GetCount(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard")
		FString GetResetSchedule() { return UTF8_TO_TCHAR(Wrapped.GetResetSchedule().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

private:
	NLeaderboard Wrapped;
};

// ------------------------- NLeaderboardRecord -------------------------

UCLASS(BlueprintType)
class UNBPLeaderboardRecord : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NLeaderboardRecord, UNBPLeaderboardRecord)
	CONVERT_RS_TO_BP_STATIC(NLeaderboardRecord, UNBPLeaderboardRecord)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FString GetLeaderboardId() { return UTF8_TO_TCHAR(Wrapped.GetLeaderboardId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FString GetOwnerId() { return UTF8_TO_TCHAR(Wrapped.GetOwnerId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetLocation().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetTimezone().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		int32 GetRank() { return Wrapped.GetRank(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		int32 GetScore() { return Wrapped.GetScore(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		int32 GetNumScore() { return Wrapped.GetNumScore(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FDateTime GetRankedAt() { return FROM_NAKAMA_DATE(Wrapped.GetRankedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Leaderboard Record")
		FDateTime GetExpiresAt() { return FROM_NAKAMA_DATE(Wrapped.GetExpiresAt()); }

private:
	NLeaderboardRecord Wrapped;
};

// ------------------------- NMatchToken -------------------------

UCLASS(BlueprintType)
class UNBPMatchToken : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NMatchToken, UNBPMatchToken)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Token")
		FString GetToken() { return UTF8_TO_TCHAR(Wrapped.GetToken().c_str()); }

private:
	NMatchToken Wrapped;
};

// ------------------------- NMatchmakeTicket -------------------------

UCLASS(BlueprintType)
class UNBPMatchmakeTicket : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NMatchmakeTicket, UNBPMatchmakeTicket)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Matchmake Ticket")
		FString GetTicket() { return UTF8_TO_TCHAR(Wrapped.GetTicket().c_str()); }

	NMatchmakeTicket GetNMatchmakeTicket() { return Wrapped; }

private:
	NMatchmakeTicket Wrapped;
};

// ------------------------- NMatchmakeMatched -------------------------

UCLASS(BlueprintType)
class UNBPMatchmakeMatched : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NMatchmakeMatched, UNBPMatchmakeMatched)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Matchmake Matched")
		UNBPMatchmakeTicket* GetTicket() { return UNBPMatchmakeTicket::From(Wrapped.GetTicket()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Matchmake Matched")
		UNBPMatchToken* GetToken() { return UNBPMatchToken::From(Wrapped.GetToken()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Matchmake Matched")
		TArray<UNBPUserPresence*> GetPresence() { return  UNBPUserPresence::FromArray(Wrapped.GetPresence()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Matchmake Matched")
		UNBPUserPresence* GetSelf() { return UNBPUserPresence::From(Wrapped.GetSelf()); }

private:
	NMatchmakeMatched Wrapped;
};

// ------------------------- NNotification -------------------------

UCLASS(BlueprintType)
class UNBPNotification : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NNotification, UNBPNotification)
	CONVERT_RS_TO_BP_STATIC(NNotification, UNBPNotification)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Notification")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Notification")
		FString GetSubject() { return UTF8_TO_TCHAR(Wrapped.GetSubject().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Notification")
		FString GetContent() { return UTF8_TO_TCHAR(Wrapped.GetContent().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Notification")
		int32 GetCode() { return Wrapped.GetCode(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Notification")
		FString GetSenderId() { return UTF8_TO_TCHAR(Wrapped.GetSenderId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Notification")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Notification")
		FDateTime GetExpiresAt() { return FROM_NAKAMA_DATE(Wrapped.GetExpiresAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Notification")
		bool IsPersistent() { return Wrapped.IsPersistent(); }

private:
	NNotification Wrapped;
};

// ------------------------- NPurchaseRecord -------------------------

UCLASS(BlueprintType)
class UNBPPurchaseRecord : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NPurchaseRecord, UNBPPurchaseRecord)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Purchase Record")
		bool IsSuccess() { return Wrapped.IsSuccess(); }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Purchase Record")
		bool IsSeenBefore() { return Wrapped.IsSeenBefore(); }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Purchase Record")
		bool IsPurchaseProviderReachable() { return Wrapped.IsPurchaseProviderReachable(); }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Purchase Record")
		FString GetMessage() { return UTF8_TO_TCHAR(Wrapped.GetMessage().c_str()); }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Purchase Record")
		FString GetData() { return UTF8_TO_TCHAR(Wrapped.GetData().c_str()); }

private:
	NPurchaseRecord Wrapped;
};

// ------------------------- NStorageUpdateMessage::StorageUpdateBuilder -------------------------

// This is a collection of TStorageUpdate_StorageUpdate_UpdateOp items
UCLASS(BlueprintType)
class UNBPStorateUpdateOps : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Add(FString path, FString value)					{ Wrapped.Add(TCHAR_TO_UTF8(*path), TCHAR_TO_UTF8(*value)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Append(FString path, FString value)				{ Wrapped.Append(TCHAR_TO_UTF8(*path), TCHAR_TO_UTF8(*value)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Copy(FString from, FString path)					{ Wrapped.Copy(TCHAR_TO_UTF8(*from), TCHAR_TO_UTF8(*path)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Incr(FString path, int32 value)					{ Wrapped.Incr(TCHAR_TO_UTF8(*path), value); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Init(FString path, FString value)					{ Wrapped.Init(TCHAR_TO_UTF8(*path), TCHAR_TO_UTF8(*value)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Merge(FString path, FString value)					{ Wrapped.Merge(TCHAR_TO_UTF8(*path), TCHAR_TO_UTF8(*value)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Move(FString path, FString value)					{ Wrapped.Move(TCHAR_TO_UTF8(*path), TCHAR_TO_UTF8(*value)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Remove(FString path)								{ Wrapped.Remove(TCHAR_TO_UTF8(*path)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Replace(FString path, FString value)				{ Wrapped.Replace(TCHAR_TO_UTF8(*path), TCHAR_TO_UTF8(*value)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Test(FString path, FString value)					{ Wrapped.Test(TCHAR_TO_UTF8(*path), TCHAR_TO_UTF8(*value)); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage Update Operation")
		void Compare(FString path, FString value, int32 assert) { Wrapped.Compare(TCHAR_TO_UTF8(*path), TCHAR_TO_UTF8(*value), assert); }

	std::vector<TStorageUpdate_StorageUpdate_UpdateOp> FetchOperations() { return Wrapped.Build(); }

private:
	NStorageUpdateMessage::StorageUpdateBuilder Wrapped;
};

// ------------------------- NRuntimeRpc -------------------------

UCLASS(BlueprintType)
class UNBPRuntimeRpc : public UObject
{
	GENERATED_BODY()

public:
	CONVERT_TO_BP_STATIC(NRuntimeRpc, UNBPRuntimeRpc)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Runtime RPC")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Runtime RPC")
		FString GetPayload() { return UTF8_TO_TCHAR(Wrapped.GetPayload().c_str()); }

private:
	NRuntimeRpc Wrapped;
};

// ------------------------- NMatchmakeFilters -------------------------

USTRUCT()
struct FTermsData
{
	GENERATED_BODY()

	UPROPERTY()
		TArray<FString> Entries;
};

UCLASS(BlueprintType)
class UNBPMatchmakeFilters : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmake Filters")
		void AddTermFilter(FString name, TArray<FString> terms, bool matchAllTerms) {
		TermMatchAll.Add(name, matchAllTerms);
		FTermsData data;
		data.Entries.Append(terms);
		Terms.Add(name, data);
	}

	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmake Filters")
		void AddRangeFilter(FString name, int32 lowerBound, int32 upperBound) {
		RangesLB.Add(name, lowerBound);
		RangesUB.Add(name, upperBound);
	}

	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmake Filters")
		void AddCheckFilter(FString name, bool value) { Checks.Add(name, value); }

	TMap<FString, FTermsData> GetTerms() { return Terms; }
	TMap<FString, bool> GetTermMatchAll() { return TermMatchAll; }
	TMap<FString, int32> GetRangesLB() { return RangesLB; }
	TMap<FString, int32> GetRangesUB() { return RangesUB; }
	TMap<FString, bool> GetChecks() { return Checks; }

private:
	UPROPERTY() TMap<FString, FTermsData> Terms;
	UPROPERTY() TMap<FString, bool> TermMatchAll;
	UPROPERTY() TMap<FString, int32> RangesLB;
	UPROPERTY() TMap<FString, int32> RangesUB;
	UPROPERTY() TMap<FString, bool> Checks;

};

// ------------------------- NMatchmakeProps -------------------------

UCLASS(BlueprintType)
class UNBPMatchmakeProps : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmake Properties")
		void SetStringTermsProperty(FString key, TArray<FString> terms) { 
		FTermsData data;
		data.Entries.Append(terms);
		TermProperties.Add(key, data);
	}

	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmake Properties")
		void SetIntProperty(FString key, int32 value) { IntProperties.Add(key, value); }

	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmake Properties")
		void SetBoolProperty(FString key, bool value) { BoolProperties.Add(key, value); }

	TMap<FString, FTermsData> GetTermProperties() { return TermProperties; }
	TMap<FString, int32> GetIntProperties() { return IntProperties; }
	TMap<FString, bool> GetBoolProperties() { return BoolProperties; }

private:
	UPROPERTY() TMap<FString, FTermsData> TermProperties;
	UPROPERTY() TMap<FString, int32> IntProperties;
	UPROPERTY() TMap<FString, bool> BoolProperties;
};
