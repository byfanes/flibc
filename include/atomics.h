#ifndef __FLIBC_ATOMICS_H__
#define __FLIBC_ATOMICS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

/* TODO: Currently we are not doing any memory order so we might need them in future */

bool atomic_cas_u32(volatile u32* ptr, u32 expected, u32 new_val);
bool atomic_cas_u64(volatile u64* ptr, u64 expected, u64 new_val);
bool atomic_cas_usz(volatile usz* ptr, usz expected, usz new_val);
bool atomic_cas_s32(volatile s32* ptr, s32 expected, s32 new_val);
bool atomic_cas_s64(volatile s64* ptr, s64 expected, s64 new_val);
bool atomic_cas_ssz(volatile ssz* ptr, ssz expected, ssz new_val);

u32 atomic_load_u32(volatile u32* ptr);
u64 atomic_load_u64(volatile u64* ptr);
usz atomic_load_usz(volatile usz* ptr);
s32 atomic_load_s32(volatile s32* ptr);
s64 atomic_load_s64(volatile s64* ptr);
ssz atomic_load_ssz(volatile ssz* ptr);

u32 atomic_xchg_u32(volatile u32* ptr, u32 new_val);
u64 atomic_xchg_u64(volatile u64* ptr, u64 new_val);
usz atomic_xchg_usz(volatile usz* ptr, usz new_val);
s32 atomic_xchg_s32(volatile s32* ptr, s32 new_val);
s64 atomic_xchg_s64(volatile s64* ptr, s64 new_val);
ssz atomic_xchg_ssz(volatile ssz* ptr, ssz new_val);

u32 atomic_fetch_add_u32(volatile u32* ptr, u32 val);
u64 atomic_fetch_add_u64(volatile u64* ptr, u64 val);
usz atomic_fetch_add_usz(volatile usz* ptr, usz val);
s32 atomic_fetch_add_s32(volatile s32* ptr, s32 val);
s64 atomic_fetch_add_s64(volatile s64* ptr, s64 val);
ssz atomic_fetch_add_ssz(volatile ssz* ptr, ssz val);

u32 atomic_fetch_sub_u32(volatile u32* ptr, u32 val);
u64 atomic_fetch_sub_u64(volatile u64* ptr, u64 val);
usz atomic_fetch_sub_usz(volatile usz* ptr, usz val);
s32 atomic_fetch_sub_s32(volatile s32* ptr, s32 val);
s64 atomic_fetch_sub_s64(volatile s64* ptr, s64 val);
ssz atomic_fetch_sub_ssz(volatile ssz* ptr, ssz val);

void atomic_memory_barrier(void);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_ATOMICS_H__ */
