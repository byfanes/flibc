#ifndef __ATOMICS_H__
#define __ATOMICS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdtypes.h"

/* TODO: Currently we are not doing any memory order so we might need them in future */

bool atomic_cas_u32(volatile u32* ptr, u32 expected, u32 new_val);
bool atomic_cas_u64(volatile u64* ptr, u64 expected, u64 new_val);
bool atomic_cas_usz(volatile usz* ptr, usz expected, usz new_val);
bool atomic_cas_i32(volatile i32* ptr, i32 expected, i32 new_val);
bool atomic_cas_i64(volatile i64* ptr, i64 expected, i64 new_val);
bool atomic_cas_ssz(volatile ssz* ptr, ssz expected, ssz new_val);

u32 atomic_load_u32(volatile u32* ptr);
u64 atomic_load_u64(volatile u64* ptr);
usz atomic_load_usz(volatile usz* ptr);
i32 atomic_load_i32(volatile i32* ptr);
i64 atomic_load_i64(volatile i64* ptr);
ssz atomic_load_ssz(volatile ssz* ptr);

u32 atomic_xchg_u32(volatile u32* ptr, u32 new_val);
u64 atomic_xchg_u64(volatile u64* ptr, u64 new_val);
usz atomic_xchg_usz(volatile usz* ptr, usz new_val);
i32 atomic_xchg_i32(volatile i32* ptr, i32 new_val);
i64 atomic_xchg_i64(volatile i64* ptr, i64 new_val);
ssz atomic_xchg_ssz(volatile ssz* ptr, ssz new_val);

u32 atomic_fetch_add_u32(volatile u32* ptr, u32 val);
u64 atomic_fetch_add_u64(volatile u64* ptr, u64 val);
usz atomic_fetch_add_usz(volatile usz* ptr, usz val);
i32 atomic_fetch_add_i32(volatile i32* ptr, i32 val);
i64 atomic_fetch_add_i64(volatile i64* ptr, i64 val);
ssz atomic_fetch_add_ssz(volatile ssz* ptr, ssz val);

u32 atomic_fetch_sub_u32(volatile u32* ptr, u32 val);
u64 atomic_fetch_sub_u64(volatile u64* ptr, u64 val);
usz atomic_fetch_sub_usz(volatile usz* ptr, usz val);
i32 atomic_fetch_sub_i32(volatile i32* ptr, i32 val);
i64 atomic_fetch_sub_i64(volatile i64* ptr, i64 val);
ssz atomic_fetch_sub_ssz(volatile ssz* ptr, ssz val);

void atomic_memory_barrier(void);

#ifdef __cplusplus
}
#endif

#endif /* __ATOMICS_H__ */
