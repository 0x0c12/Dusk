#pragma once

#include "Defines.h"

typedef enum memory_tag
{
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,

    MEMORY_TAG_MAX_TAGS
} memory_tag;

DSK_API void DskInitMemory();
DSK_API void DskShutdownMemory();

DSK_API void* DskAllocate(u64 size, memory_tag tag);
DSK_API void DskFree(void* block, u64 size, memory_tag tag);
DSK_API void* DskZeroMemory(void* block, u64 size);
DSK_API void* DskCopyMemory(void* dest, const void* src, u64 size);
DSK_API void* DskSetMemory(void* dest, i32 value, u64 size);

DSK_API char* GetDskMemoryUsageStr();