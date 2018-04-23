/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm

    This file is part of CoD4X18-Server source code.

    CoD4X18-Server source code is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CoD4X18-Server source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================
*/
#pragma once

#include "scr_vm.h"
#include "g_sv_shared.h"
#include "dobj.h"

#ifndef SCR_ENTREF_DEFINED
#define SCR_ENTREF_DEFINED
typedef int scr_entref_t;
#endif

void PlayerCmd_GetUid(scr_entref_t arg);
void PlayerCmd_SetUid(scr_entref_t arg);
void PlayerCmd_GetGuid(scr_entref_t arg);
void PlayerCmd_GetSteamID(scr_entref_t arg);
void PlayerCmd_GetPlayerID(scr_entref_t arg);
void PlayerCmd_GetSteamID64(scr_entref_t arg);
void PlayerCmd_GetPlayerID64(scr_entref_t arg);
void PlayerCmd_GetPower(scr_entref_t arg);
void PlayerCmd_SetPower(scr_entref_t arg);
void PlayerCmd_SetStat(scr_entref_t arg);
void PlayerCmd_GetStat(scr_entref_t arg);
void PlayerCmd_GetUserinfo(scr_entref_t arg);
void PlayerCmd_GetPing(scr_entref_t arg);
void PlayerCmd_SetGravity(scr_entref_t arg);
void PlayerCmd_SetGroundReferenceEnt(scr_entref_t arg);
void PlayerCmd_SetJumpHeight(scr_entref_t arg);
void PlayerCmd_SetMoveSpeed(scr_entref_t arg);
void PlayerCmd_GetGeoLocation(scr_entref_t arg);
void PlayerCmd_GetCountedFPS(scr_entref_t arg);
void PlayerCmd_GetCountedFPSSweetspot(scr_entref_t arg);
void PlayerCmd_GetSpectatorClient(scr_entref_t arg);
void PlayerCmd_SetVelocity(scr_entref_t arg);

void PlayerCmd_ForwardButtonPressed(scr_entref_t object);
void PlayerCmd_BackButtonPressed(scr_entref_t object);
void PlayerCmd_MoveLeftButtonPressed(scr_entref_t object);
void PlayerCmd_MoveRightButtonPressed(scr_entref_t object);
void PlayerCmd_SprintButtonPressed(scr_entref_t object);
void PlayerCmd_ReloadButtonPressed(scr_entref_t object);
void PlayerCmd_LeanLeftButtonPressed(scr_entref_t object);
void PlayerCmd_LeanRightButtonPressed(scr_entref_t object);
void PlayerCmd_IsProning(scr_entref_t object);
void PlayerCmd_IsCrouching(scr_entref_t object);
void PlayerCmd_IsStanding(scr_entref_t object);
void PlayerCmd_JumpButtonPressed(scr_entref_t object);
void PlayerCmd_IsInADS(scr_entref_t object);
void PlayerCmd_HoldBreathButtonPressed(scr_entref_t object);
void PlayerCmd_ADSButtonPressed(scr_entref_t object);

void GScr_StrTokByPixLen();
void GScr_StrTokByLen();
void GScr_StrPixLen();
void GScr_StrColorStrip();
void GScr_StrRepl();
void GScr_CopyString();
void GScr_GetRealTime();
void GScr_TimeToString();
void GScr_SHA256();
void GScr_CbufAddText();
void GScr_CbufAddTextEx();
void GScr_FS_FOpen();
void GScr_FS_FClose();
void GScr_FS_FCloseAll();
void GScr_FS_TestFile();
void GScr_FS_ReadLine();
void GScr_FS_WriteLine();
void GScr_FS_Remove();
void GScr_SpawnBot();
void GScr_RemoveAllBots();
void GScr_RemoveBot();
void GScr_KickClient();
void GScr_BanClient();
void PlayerCmd_spawn(scr_entref_t arg);
void GScr_NewHudElem();
void GScr_NewClientHudElem();
void HECmd_SetText(scr_entref_t entnum);
void GScr_Spawn();
void GScr_SpawnVehicle();
void GScr_SpawnHelicopter();
void GScr_VectorAdd();
void GScr_TypeTest();

void PlayerCmd_GetSteamGroupMembership(scr_entref_t arg);

void Scr_PrecacheString_f();
void Scr_Destroy_f(scr_entref_t hud_elem_num);

void GScr_IsCvarDefined();

void Scr_IsArray_f();
void GScr_ArrayTest();

qboolean GetTagInfoForEntity(gentity_t *ent, int partNameIdx, DObjPartCache_t *cache, int seekInSubModels);
void PrintModelBonesInfo(gentity_t *ent);

void GScr_Base64Encode();
void GScr_Base64Decode();
void GScr_IsEntity();
void GScr_IsVector();
void GScr_IsString();
void GScr_IsFloat();
void GScr_IsInt();
void GScr_Float();
void GScr_Pow();

void GScr_CloneBrushModelToScriptModel(scr_entref_t brushModelEnt);
void PlayerCmd_SetStance(scr_entref_t playerEntNum);
