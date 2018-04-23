/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm
    Copyright (C) 1999-2005 Id Software, Inc.

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


#ifndef __CM_PUBLIC_H__
#define __CM_PUBLIC_H__


int CM_BoxLeafnums( const vec3_t mins, const vec3_t maxs, uint16_t *list, int listsize, int *lastLeaf );
byte *CM_ClusterPVS( int cluster );
int CM_PointLeafnum( const vec3_t p );
int CM_LeafCluster( int leafnum );
char *CM_EntityString( void );
void CM_ModelBounds( clipHandle_t model, vec3_t mins, vec3_t maxs );
clipHandle_t CM_InlineModel( int index );
int CM_NumInlineModels( void );
int CM_PointContents(const float *p, unsigned int model);
void SetPlaneSignbits( cplane_t *out );
int CM_TransformedPointContents( const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles );
void CM_DebugInit();



/* 760 */
typedef enum
{
  TRACE_HITTYPE_NONE = 0x0,
  TRACE_HITTYPE_ENTITY = 0x1,
  TRACE_HITTYPE_DYNENT_MODEL = 0x2,
  TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
  TRACE_HITTYPE_GLASS = 0x4
}TraceHitType;


typedef struct trace_s
{
  float fraction;
  vec3_t normal;
  int surfaceFlags;
  int contents;
  const char *material;
  TraceHitType hitType;
  uint16_t hitId;
  uint16_t modelIndex;
  uint16_t partName;
  uint16_t partGroup;
  byte allsolid;
  byte startsolid;
  byte walkable;
  byte padding;
}trace_t;

typedef struct
{
  int baseEntity;
  int parentEntity;
  byte ignoreSelf;
  byte ignoreParent;
  byte ignoreSiblings;
  byte ignoreChildren;
}IgnoreEntParams;

typedef struct 
{
	vec3_t start;
	vec3_t end;
	vec3_t invDelta;
}TraceExtents;

// trace->entityNum can also be 0 to (MAX_GENTITIES-1)
// or ENTITYNUM_NONE, ENTITYNUM_WORLD
#ifndef CLIPHANDLE_DEFINED
#define CLIPHANDLE_DEFINED
typedef unsigned int clipHandle_t;
#endif

qboolean CM_TraceBox(TraceExtents *extents, const float *mins, const float *maxs, float fraction);

clipHandle_t __cdecl CM_TempBoxModel(const float* mins, const float* maxs, int capsule);
void __cdecl CM_TransformedBoxTrace(trace_t* trace, const float* start, const float* end, const float* mins, const float* maxs,
			clipHandle_t cliphandle, int contentmask, const float* origin, const float* angle);
void CM_BoxTrace( trace_t *results, const vec3_t start, const vec3_t end,
				  const vec3_t mins, const vec3_t maxs,
				  clipHandle_t model, int brushmask );
#endif