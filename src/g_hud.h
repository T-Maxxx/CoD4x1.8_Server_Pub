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


#ifndef __G_HUD_H__
#define __G_HUD_H__

#include "q_shared.h"
#include "entity.h"

#define HUDELEM_ADDR 0x8335620
#define MAX_HUDELEMS 1024

typedef enum{
    HUDFONT_DEFAULT,
    HUDFONT_BIGFIXED,
    HUDFONT_SMALLFIXED,
    HUDFONT_OBJECTIVE
}fonttype_t;

typedef enum{
    HUDALIGN_TOP = 0,
    HUDALIGN_LEFT = 0,
    HUDALIGN_MIDDLE = 1,
    HUDALIGN_BOTTOM = 2,
    HUDALIGN_CENTER = 4,
    HUDALIGN_RIGHT = 8
}hudalign_t;

typedef enum{
    HUDSCRNALIGN_TOP = 0,
    HUDSCRNALIGN_MIDDLE = 1,
    HUDSCRNALIGN_BOTTOM = 2,
    HUDSCRNALIGN_LEFT = 9,
    HUDSCRNALIGN_CENTER = 17,
    HUDSCRNALIGN_RIGHT = 25
}hudscrnalign_t;

typedef enum{
    HUDDISPLAY_FOREGROUND = 1,
    HUDDISPLAY_HIDEINMENU = 4
}huddisplayoptions_t;

typedef struct
{
    int type;
    float x;
    float y;
    int var_03;
    int targetEnt;
    float fontScale;
    fonttype_t fontType;
    hudalign_t align;
    hudscrnalign_t screenAlign;
    ucolor_t color;
    ucolor_t fadeColor;
    int fadeStartTime;
    int fadeTime;
    int var_13;
    int shaderWidth;
    int shaderHeight;
    int materialIndex;
    int waypointMaterialIndex;
    int shaderOldWidth;
    int shaderOldHeight;
    int scaleStartTime;
    int scaleTime;
    float moveX;
    float moveY;
    int moveAlign;
    int moveScreenAlign;
    int moveStartTime;
    int movingTime;
    int timeValue;
    int duration;
    float value;
    int hudTextConfigStringIndex;
    float sort;
    ucolor_t glowColor;
    int pulseStartTime;
    int pulseSpeed;
    int pulseDecayStart;
    int pulseDecayDuration;
    int var_38;
    huddisplayoptions_t displayOption;
    int entityNum;
    int teamNum;
    int archived;
}game_hudelem_t; //Size: 0xac

extern game_hudelem_t* g_hudelems;

qboolean OnSameTeam( gentity_t *ent1, gentity_t *ent2 );
qboolean Cmd_FollowClient_f(gentity_t *ent, int clientnum);
game_hudelem_t* G_GetNewHudElem(unsigned int clnum);
void G_HudSetText(game_hudelem_t*, const char*);
void G_HudSetPosition(game_hudelem_t*, float x, float y, hudscrnalign_t, hudscrnalign_t, hudalign_t alignx, hudalign_t aligny);
void G_HudSetColor(game_hudelem_t*, ucolor_t, ucolor_t);
void G_HudSetMovingOverTime(game_hudelem_t*, int, float newx, float newy);
void G_HudSetFont(game_hudelem_t*, float fontscale, fonttype_t ft);
void G_HudSetFadingOverTime(game_hudelem_t* element ,int time, ucolor_t newcolor);
void G_HudDestroy(game_hudelem_t* element);


#endif


