#include "DskMemory.h"

#include "Core/Logger.h"
#include "Platform/Platform.h"

// TODO: Custom string library... death
#include <string.h>
#include <stdio.h>

struct memory_stats
{
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

// TODO: Temporary debug string. Test string will be removed later on
static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = 
{
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      ",
};

static struct memory_stats stats;

void DskInitMemory()
{
    PlatformZeroMemory(&stats, sizeof(stats));
}

// TODO: Add proper shutdown procedures for memory subsystem
void DskShutdownMemory()
{}

void* DskAllocate(u64 size, memory_tag tag)
{
    if(tag == MEMORY_TAG_UNKNOWN)
    {
        DSK_WARN("Memory being allocated with MEMORY_TAG_UNKOWN. Re-classify this allocation.");
    }

    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    // TODO: what is memory alignment lol
    void* block = PlatformAllocate(size, FALSE);
    PlatformZeroMemory(block, size);
    return block;
}

void DskFree(void* block, u64 size, memory_tag tag)
{
    if(tag == MEMORY_TAG_UNKNOWN)
    {
        DSK_WARN("Memory being freed with MEMORY_TAG_UNKOWN. Re-classify this allocation.");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;

    PlatformFree(block, FALSE);
}

DSK_API void* DskZeroMemory(void* block, u64 size)
{
    return PlatformZeroMemory(block, size);
}
DSK_API void* DskCopyMemory(void* dest, const void* src, u64 size)
{
    return PlatformCopyMemory(dest, src, size);
}
DSK_API void* DskSetMemory(void* dest, i32 value, u64 size)
{
    return PlatformSetMemory(dest, value, size);
}

char* GetDskMemoryUsageStr()
{
    const u64 kib = 1024;
    const u64 mib = kib * kib;
    const u64 gib = kib * kib * kib;

    char buffer[8000] = "System memory used (tagged):\n";
    u64 offset = strlen(buffer);
    for(u32 i = 0; i < MEMORY_TAG_MAX_TAGS; ++i)
    {
        char unit[4] = "XiB";
        float amount = 1.0f;
        if(stats.tagged_allocations[i] >= gib)
        {
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (float)gib;
        }
        else if(stats.tagged_allocations[i] >= mib)
        {
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (float)mib;
        }
        else if(stats.tagged_allocations[i] >= kib)
        {
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (float)kib;
        }
        else
        {
            unit[0] = 'B';
            unit[1] = 0;
            amount = stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, 8000, " %s: %.2f%s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }
    char* out_string = _strdup(buffer);
    return out_string;
}