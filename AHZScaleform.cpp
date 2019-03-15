﻿#include <wchar.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <list>
#include <algorithm>
#include "skse64/GameReferences.h"
#include "skse64/GameObjects.h"
#include "skse64/GameRTTI.h"
#include "skse64/GameSettings.h"
#include "skse64/GameExtraData.h"
#include "skse64/ScaleformCallbacks.h"
#include "skse64/ScaleformMovie.h"
#include "skse64/GameMenus.h"
#include "skse64/skse64_common/Utilities.h"
#include "AHZArmorInfo.h"
#include "AHZWeaponInfo.h"
#include "AHZScaleform.h"
#include "AHZScaleformHook.h"
#include "AHZFormLookup.h"
#include "AHZUtilities.h"

//Unpacked
//HxD Raw FF C0 83 F8 07 77 0A F3 0F 10 8A 70 01 00 00 EB 54 4C 8D 0D 80 B3 A7 01 C7 44 24 20 00 00 00 00
RelocAddr<GET_ACTOR_WARMTH_RATING> GetActorWarmthRating_Native(0x003BD5F0);

//text:00007FF7F661D850; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//   .text:00007FF7F661D850
//   .text : 00007FF7F661D850
//   .text : 00007FF7F661D850                         sub_7FF7F661D850 proc near; CODE XREF : sub_7FF7F6537280 + 2E↑p
//   .text : 00007FF7F661D850; sub_7FF7F6B0F2F0 + 129↓p ...
//   .text:00007FF7F661D850
//   .text : 00007FF7F661D850                         var_38 = qword ptr - 38h
//   .text : 00007FF7F661D850                         var_30 = qword ptr - 30h
//   .text : 00007FF7F661D850                         var_28 = dword ptr - 28h
//   .text : 00007FF7F661D850                         var_18 = xmmword ptr - 18h
//   .text : 00007FF7F661D850
//   .text : 00007FF7F661D850; FUNCTION CHUNK AT.text:00007FF7F661DCD0 SIZE 0000000B BYTES
//   .text : 00007FF7F661D850; FUNCTION CHUNK AT.text:00007FF7F7605A05 SIZE 0000000C BYTES
//   .text : 00007FF7F661D850
//   .text : 00007FF7F661D850; __unwind{ // __CxxFrameHandler3
//   .text:00007FF7F661D850 40 53                                   push    rbx
//   .text : 00007FF7F661D852 48 83 EC 50                             sub     rsp, 50h
//   .text : 00007FF7F661D856 48 C7 44 24 20 FE FF FF + mov[rsp + 58h + var_38], 0FFFFFFFFFFFFFFFEh
//   .text : 00007FF7F661D85F 0F 29 74 24 40                          movaps[rsp + 58h + var_18], xmm6
//   .text : 00007FF7F661D864 48 8B D9                                mov     rbx, rcx
//   .text : 00007FF7F661D867 0F 57 F6                                xorps   xmm6, xmm6
//   .text : 00007FF7F661D86A E8 91 B7 E1 FF                          call    sub_7FF7F6439000
//   .text : 00007FF7F661D86F 48 85 C0                                test    rax, rax
//   .text : 00007FF7F661D872 74 27                                   jz      short loc_7FF7F661D89B
//   .text : 00007FF7F661D874 48 8D 0D E5 44 21 01                    lea     rcx, ? ? _7WarmthCalcFunc@?A0x527f96c7@@6B@; const `anonymous namespace'::WarmthCalcFunc::`vftable'
//   .text:00007FF7F661D87B 48 89 4C 24 28                          mov[rsp + 58h + var_30], rcx
//   .text : 00007FF7F661D880 C7 44 24 30 00 00 00 00                 mov[rsp + 58h + var_28], 0
//   .text : 00007FF7F661D888
//   .text : 00007FF7F661D888                         loc_7FF7F661D888 : ; DATA XREF : .rdata : 00007FF7F7CBDB9C↓o
//   .text : 00007FF7F661D888;   try {
//   .text:00007FF7F661D888 48 8D 54 24 28                          lea     rdx,[rsp + 58h + var_30]
//      .text : 00007FF7F661D88D 48 8B C8                                mov     rcx, rax
//      .text : 00007FF7F661D890 E8 1B 7B E2 FF                          call    sub_7FF7F64453B0
//      .text : 00007FF7F661D895 F3 0F 10 74 24 30                       movss   xmm6,[rsp + 58h + var_28]
//      .text : 00007FF7F661D895;
//} // starts at 7FF7F661D888
//     .text:00007FF7F661D89B
//        .text : 00007FF7F661D89B                         loc_7FF7F661D89B : ; CODE XREF : sub_7FF7F661D850 + 22↑j
//        .text : 00007FF7F661D89B; DATA XREF : .rdata : 00007FF7F7CBDBA4↓o
//        .text : 00007FF7F661D89B 48 8D 8B B0 00 00 00                    lea     rcx,[rbx + 0B0h]
//        .text : 00007FF7F661D8A2 48 8B 01                                mov     rax,[rcx]
//        .text : 00007FF7F661D8A5 BA 4C 00 00 00                          mov     edx, 4Ch
//        .text : 00007FF7F661D8AA FF 50 08                                call    qword ptr[rax + 8]
//        .text:00007FF7F661D8AD F3 0F 58 C6                             addss   xmm0, xmm6
//        .text : 00007FF7F661D8B1 0F 28 74 24 40                          movaps  xmm6,[rsp + 58h + var_18]
//        .text : 00007FF7F661D8B6 48 83 C4 50                             add     rsp, 50h
//        .text : 00007FF7F661D8BA 5B                                      pop     rbx
//        .text : 00007FF7F661D8BB C3                                      retn
//        .text : 00007FF7F661D8BB; } // starts at 7FF7F661D850
//   .text:00007FF7F661D8BB                         sub_7FF7F661D850 endp
//        .text : 00007FF7F661D8BB
//        .text : 00007FF7F661D8BB; -------------------------------------------------------------------------- -
//        .text:00007FF7F661D8BC                         algn_7FF7F661D8BC : ; DATA XREF : .pdata : 00007FF7F97668D0↓o
//        .text : 00007FF7F661D8BC CC CC CC CC                             align 20h

//Unpacked 
//Hxd Raw F0 44 0F 28 44 24 30 0F 28 C6 0F 28 74 24 50 48 83 C4 60 5F C3 0F 1F 00 7D E2 3B 00 7D E2 3B 00
RelocAddr<GET_ARMOR_WARMTH_RATING>GetArmorWarmthRating_Native(0x003BD510);

//text:00007FF7F661D770
//   .text : 00007FF7F661D770; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//   .text:00007FF7F661D770
//   .text : 00007FF7F661D770
//   .text : 00007FF7F661D770; float __fastcall GetWarmth(TESForm *a1)
//   .text:00007FF7F661D770                         GetWarmth       proc near; CODE XREF : sub_7FF7F661DF90 + 11↓p
//   .text : 00007FF7F661D770; GetTotalArmorAndWarmth + 1FB↓p ...
//   .text:00007FF7F661D770
//   .text : 00007FF7F661D770                         var_38 = qword ptr - 38h
//   .text : 00007FF7F661D770                         var_30 = qword ptr - 30h
//   .text : 00007FF7F661D770                         var_28 = qword ptr - 28h
//   .text : 00007FF7F661D770                         var_18 = xmmword ptr - 18h
//   .text : 00007FF7F661D770                         arg_0 = byte ptr  8
//   .text : 00007FF7F661D770                         arg_8 = dword ptr  10h
//   .text : 00007FF7F661D770                         arg_10 = qword ptr  18h
//   .text : 00007FF7F661D770
//   .text : 00007FF7F661D770 48 83 EC 58                             sub     rsp, 58h
//   .text : 00007FF7F661D774 0F B6 41 1A                             movzx   eax, byte ptr[rcx + 1Ah]
//   .text : 00007FF7F661D778 0F 29 74 24 40                          movaps[rsp + 58h + var_18], xmm6
//   .text : 00007FF7F661D77D 0F 57 F6                                xorps   xmm6, xmm6
//   .text : 00007FF7F661D780 83 F8 1A                                cmp     eax, 1Ah
//   .text : 00007FF7F661D783 74 1B                                   jz      short loc_7FF7F661D7A0
//   .text : 00007FF7F661D785 83 F8 1F                                cmp     eax, 1Fh
//   .text : 00007FF7F661D788 0F 85 A1 00 00 00                       jnz     loc_7FF7F661D82F
//   .text : 00007FF7F661D78E F3 0F 10 05 B2 37 A4 01                 movss   xmm0, cs : dword_7FF7F8060F48
//   .text : 00007FF7F661D796 0F 28 74 24 40                          movaps  xmm6, [rsp + 58h + var_18]
//   .text : 00007FF7F661D79B 48 83 C4 58                             add     rsp, 58h
//   .text : 00007FF7F661D79F C3                                      retn
//   .text : 00007FF7F661D7A0; -------------------------------------------------------------------------- -
//   .text:00007FF7F661D7A0
//   .text : 00007FF7F661D7A0                         loc_7FF7F661D7A0 : ; CODE XREF : GetWarmth + 13↑j
//   .text : 00007FF7F661D7A0 48 8D 05 E9 0B A4 01                    lea     rax, off_7FF7F805E390
//   .text:00007FF7F661D7A7 C7 44 24 68 00 00 00 00                 mov[rsp + 58h + arg_8], 0
//   .text : 00007FF7F661D7AF 48 89 44 24 70                          mov[rsp + 58h + arg_10], rax
//   .text : 00007FF7F661D7B4 48 8D 54 24 20                          lea     rdx, [rsp + 58h + var_38]
//   .text : 00007FF7F661D7B9 48 8D 44 24 60                          lea     rax, [rsp + 58h + arg_0]
//   .text : 00007FF7F661D7BE 48 81 C1 D8 01 00 00                    add     rcx, 1D8h
//   .text : 00007FF7F661D7C5 48 89 44 24 20                          mov[rsp + 58h + var_38], rax
//   .text : 00007FF7F661D7CA 48 8D 44 24 68                          lea     rax, [rsp + 58h + arg_8]
//   .text : 00007FF7F661D7CF 48 89 44 24 28                          mov[rsp + 58h + var_30], rax
//   .text : 00007FF7F661D7D4 48 8D 44 24 70                          lea     rax, [rsp + 58h + arg_10]
//   .text : 00007FF7F661D7D9 48 89 44 24 30                          mov[rsp + 58h + var_28], rax
//   .text : 00007FF7F661D7DE E8 8D 02 00 00                          call    sub_7FF7F661DA70
//   .text : 00007FF7F661D7E3 8B 54 24 68                             mov     edx, [rsp + 58h + arg_8]
//   .text : 00007FF7F661D7E7 85 D2                                   test    edx, edx
//   .text : 00007FF7F661D7E9 74 44                                   jz      short loc_7FF7F661D82F
//   .text : 00007FF7F661D7EB 48 8B 4C 24 70                          mov     rcx, [rsp + 58h + arg_10]
//   .text : 00007FF7F661D7F0 F6 C2 01                                test    dl, 1
//   .text : 00007FF7F661D7F3 74 08                                   jz      short loc_7FF7F661D7FD
//   .text:00007FF7F661D7F5 48 8B 01                                mov     rax, [rcx]
//   .text : 00007FF7F661D7F8 F3 0F 10 70 08                          movss   xmm6, dword ptr[rax + 8]
//   .text:00007FF7F661D7FD
//   .text : 00007FF7F661D7FD                         loc_7FF7F661D7FD : ; CODE XREF : GetWarmth + 83↑j
//   .text : 00007FF7F661D7FD F6 C2 02                                test    dl, 2
//   .text : 00007FF7F661D800 74 09                                   jz      short loc_7FF7F661D80B
//   .text:00007FF7F661D802 48 8B 41 08                             mov     rax, [rcx + 8]
//   .text:00007FF7F661D806 F3 0F 58 70 08                          addss   xmm6, dword ptr[rax + 8]
//   .text:00007FF7F661D80B
//   .text : 00007FF7F661D80B                         loc_7FF7F661D80B : ; CODE XREF : GetWarmth + 90↑j
//   .text : 00007FF7F661D80B F6 C2 04                                test    dl, 4
//   .text : 00007FF7F661D80E 74 09                                   jz      short loc_7FF7F661D819
//   .text:00007FF7F661D810 48 8B 41 10                             mov     rax, [rcx + 10h]
//   .text : 00007FF7F661D814 F3 0F 58 70 08                          addss   xmm6, dword ptr[rax + 8]
//   .text:00007FF7F661D819
//   .text : 00007FF7F661D819                         loc_7FF7F661D819 : ; CODE XREF : GetWarmth + 9E↑j
//   .text : 00007FF7F661D819 F6 C2 08                                test    dl, 8
//   .text:00007FF7F661D81C 74 09                                   jz      short loc_7FF7F661D827
//   .text:00007FF7F661D81E 48 8B 41 18                             mov     rax, [rcx + 18h]
//   .text : 00007FF7F661D822 F3 0F 58 70 08                          addss   xmm6, dword ptr[rax + 8]
//   .text:00007FF7F661D827
//   .text : 00007FF7F661D827                         loc_7FF7F661D827 : ; CODE XREF : GetWarmth + AC↑j
//   .text : 00007FF7F661D827 F3 0F 59 35 01 37 A4 01                 mulss   xmm6, cs : dword_7FF7F8060F30
//   .text : 00007FF7F661D82F
//   .text : 00007FF7F661D82F                         loc_7FF7F661D82F : ; CODE XREF : GetWarmth + 18↑j
//   .text : 00007FF7F661D82F; GetWarmth + 79↑j
//   .text:00007FF7F661D82F 0F 28 C6                                movaps  xmm0, xmm6
//   .text : 00007FF7F661D832 0F 28 74 24 40                          movaps  xmm6, [rsp + 58h + var_18]
//   .text : 00007FF7F661D837 48 83 C4 58                             add     rsp, 58h
//   .text : 00007FF7F661D83B C3                                      retn
//   .text : 00007FF7F661D83B                         GetWarmth       endp
//   .text : 00007FF7F661D83B
//   .text : 00007FF7F661D83B; -------------------------------------------------------------------------- -

//Unpacked
//HxD Raw 03 00 4C 89 B7 D0 03 03 00 44 89 B7 D8 03 03 00 4C 89 B7 E8 03 03 00 4C 89 B7 F0 03 03 00 83 CB
//CFF Explorer .text 030300008891FC0303008891FE030300488DB9A0020300488BCFE821A191FF40
RelocAddr<_IsSurvivalMode> IsSurvivalMode(0x008DAAB0);
//.text:00000001408DAAB0                                                 IsSurvivalMode  proc near; CODE XREF : sub_1401A1730:loc_1401A17ACp
//.text:00000001408DAAB0; sub_1401A1730 + 9Ep ...
//.text:00000001408DAAB0 48 83 EC 28                                                     sub     rsp, 28h
//.text:00000001408DAAB4 E8 57 C7 81 FF                                                  call    sub_1400F7210
//.text:00000001408DAAB9 80 B8 C2 0C 00 00 00                                            cmp     byte ptr[rax + 0CC2h], 0
//.text:00000001408DAAC0 74 2B                                                           jz      short loc_1408DAAED
//.text:00000001408DAAC2 48 8B 88 30 0A 00 00                                            mov     rcx, [rax + 0A30h]
//.text:00000001408DAAC9 48 85 C9                                                        test    rcx, rcx
//.text:00000001408DAACC 74 1F                                                           jz      short loc_1408DAAED
//.text:00000001408DAACE F3 0F 10 05 12 88 C4 00                                         movss   xmm0, cs:dword_1415232E8
//.text : 00000001408DAAD6 0F 2E 41 34                                                     ucomiss xmm0, dword ptr[rcx + 34h]
//.text:00000001408DAADA 75 0A                                                           jnz     short loc_1408DAAE6
//.text:00000001408DAADC B8 01 00 00 00                                                  mov     eax, 1
//.text:00000001408DAAE1 48 83 C4 28                                                     add     rsp, 28h
//.text:00000001408DAAE5 C3                                                              retn
//.text:00000001408DAAE6; -------------------------------------------------------------------------- -


//Unpacked
//HxD Raw 8D 49 1E 48 89 44 24 20 F3 0F 11 44 24 40 E8 4D BA A9 FF 48 8B 47 10 48 8B 48 10 8B 41 68 C1 E8
//HxD Raw 8D 49 1E 48 89 44 24 20 F3 0F 11 44 24 40 E8 AD B1 A9 FF 48 8B 47 10 48 8B 48 10 8B 41 68 C1 E8 -->1.5.39
//HxD Raw 8D 49 1E 48 89 44 24 20 F3 0F 11 44 24 40 E8 FD B3 A9 FF 48 8B 47 10 48 8B 48 10 8B 41 68 C1 E8 -->1.5.50
//CFF Explorer .text 8B65024889442438C744244000000000488B014533C0488D542438FF5008C743
RelocAddr<GET_MAGIC_ITEM_DESCRIPTION> GetMagicItemDescription2(0x00892CD0);

// Base Address = 7FF690BE0000
//text:00007FF691471320; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//	.text:00007FF691471320
//	.text : 00007FF691471320; Attributes: library function static bp - based frame fpd = 1000h
//	.text : 00007FF691471320
//	.text : 00007FF691471320 sub_7FF691471320 proc near; CODE XREF : sub_7FF69146F4C0 + D23↑p
//	.text : 00007FF691471320; sub_7FF69146F4C0 + DA1↑p ...
//	.text:00007FF691471320
//	.text : 00007FF691471320 var_10E0 = qword ptr - 10E0h
//	.text : 00007FF691471320 var_10D8 = qword ptr - 10D8h
//	.text : 00007FF691471320 var_10D0 = qword ptr - 10D0h
//	.text : 00007FF691471320 var_10C0 = qword ptr - 10C0h
//	.text : 00007FF691471320 var_10B8 = qword ptr - 10B8h
//	.text : 00007FF691471320 var_10B0 = qword ptr - 10B0h
//	.text : 00007FF691471320 var_10A8 = qword ptr - 10A8h
//	.text : 00007FF691471320 var_10A0 = qword ptr - 10A0h
//	.text : 00007FF691471320 var_1098 = qword ptr - 1098h
//	.text : 00007FF691471320 var_1090 = byte ptr - 1090h
//	.text : 00007FF691471320 var_1088 = qword ptr - 1088h
//	.text : 00007FF691471320 DstBuf = byte ptr - 1080h
//	.text : 00007FF691471320 Dst = byte ptr - 880h
//	.text : 00007FF691471320 var_80 = xmmword ptr - 80h
//	.text : 00007FF691471320 var_70 = xmmword ptr - 70h
//	.text : 00007FF691471320 var_60 = xmmword ptr - 60h
//	.text : 00007FF691471320 var_50 = xmmword ptr - 50h
//	.text : 00007FF691471320 var_40 = xmmword ptr - 40h
//	.text : 00007FF691471320 var_30 = xmmword ptr - 30h
//	.text : 00007FF691471320 var_20 = byte ptr - 20h
//	.text : 00007FF691471320 arg_0 = qword ptr  10h
//	.text : 00007FF691471320 arg_8 = dword ptr  18h
//	.text : 00007FF691471320 arg_10 = dword ptr  20h
//	.text : 00007FF691471320 arg_18 = qword ptr  28h
//	.text : 00007FF691471320
//	.text : 00007FF691471320; FUNCTION CHUNK AT.text:00007FF691471DE0 SIZE 0000000B BYTES
//	.text : 00007FF691471320; FUNCTION CHUNK AT.text:00007FF69200010D SIZE 0000000C BYTES
//	.text : 00007FF691471320
//	.text : 00007FF691471320; __unwind{ // __CxxFrameHandler3
//	.text:00007FF691471320                 push    rbp
//	.text : 00007FF691471322                 push    rdi
//	.text : 00007FF691471323                 push    r12
//	.text : 00007FF691471325                 push    r14
//	.text : 00007FF691471327                 push    r15
//	.text : 00007FF691471329                 lea     rbp,[rsp - 0FE0h]
//	.text : 00007FF691471331                 mov     eax, 10E0h
//	.text : 00007FF691471336                 call    _alloca_probe
//	.text : 00007FF69147133B                 sub     rsp, rax
//	.text : 00007FF69147133E                 mov[rsp + 1100h + var_1088], 0FFFFFFFFFFFFFFFEh
//	.text : 00007FF691471347                 mov[rsp + 1100h + arg_0], rbx
//	.text : 00007FF69147134F                 mov[rsp + 1100h + arg_18], rsi
//	.text : 00007FF691471357                 movaps[rsp + 1100h + var_30], xmm6
//	.text : 00007FF69147135F                 movaps[rsp + 1100h + var_40], xmm7
//	.text : 00007FF691471367                 movaps[rsp + 1100h + var_50], xmm8
//	.text : 00007FF691471370                 movaps[rsp + 1100h + var_60], xmm9
//	.text : 00007FF691471379                 movaps[rsp + 1100h + var_70], xmm10
//	.text : 00007FF691471382                 movaps[rsp + 1100h + var_80], xmm11
//	.text : 00007FF69147138B                 mov     r15, r8
//	.text : 00007FF69147138E                 mov     rsi, rdx
//	.text : 00007FF691471391                 xor     dil, dil
//	.text : 00007FF691471394                 xor     r14d, r14d
//	.text : 00007FF691471397                 test    rdx, rdx
//	.text : 00007FF69147139A                 jz      short loc_7FF6914713B5
//	.text : 00007FF69147139C                 cmp[rdx + 68h], r14d
//	.text : 00007FF6914713A0                 jbe     short loc_7FF6914713AB
//	.text : 00007FF6914713A2                 mov     rax,[rdx + 58h]
//	.text : 00007FF6914713A6                 mov     rbx,[rax]
//	.text : 00007FF6914713A9                 jmp     short loc_7FF6914713AD
//	.text : 00007FF6914713AB; -------------------------------------------------------------------------- -
//	.text:00007FF6914713AB
//	.text : 00007FF6914713AB loc_7FF6914713AB : ; CODE XREF : sub_7FF691471320 + 80↑j
//	.text : 00007FF6914713AB                 xor     ebx, ebx
//	.text : 00007FF6914713AD
//	.text : 00007FF6914713AD loc_7FF6914713AD : ; CODE XREF : sub_7FF691471320 + 89↑j
//	.text : 00007FF6914713AD                 mov     r14d, 1
//	.text : 00007FF6914713B3                 jmp     short loc_7FF6914713B7
//	.text : 00007FF6914713B5; -------------------------------------------------------------------------- -
//	.text:00007FF6914713B5
//	.text : 00007FF6914713B5 loc_7FF6914713B5 : ; CODE XREF : sub_7FF691471320 + 7A↑j
//	.text : 00007FF6914713B5                 xor     ebx, ebx
//	.text : 00007FF6914713B7
//	.text : 00007FF6914713B7 loc_7FF6914713B7 : ; CODE XREF : sub_7FF691471320 + 93↑j
//	.text : 00007FF6914713B7                 xor     edx, edx; Val
//	.text:00007FF6914713B9                 mov     r8d, 800h; Size
//	.text:00007FF6914713BF                 lea     rcx,[rbp + 1000h + Dst]; Dst
//	.text:00007FF6914713C6                 call    memset
//	.text : 00007FF6914713CB                 xor     r8d, r8d
//	.text : 00007FF6914713CE                 lea     rdx, Str1
//	.text : 00007FF6914713D5                 mov     rcx, r15
//	.text : 00007FF6914713D8                 call    sub_7FF690CD9F90
//	.text : 00007FF6914713DD                 test    rsi, rsi
//	.text : 00007FF6914713E0                 jz      short loc_7FF69147142A
//	.text : 00007FF6914713E2                 xor     eax, eax
//	.text : 00007FF6914713E4                 mov[rsp + 1100h + var_10B8], rax
//	.text : 00007FF6914713E9                 lea     rax, ? ? _7GetMagicItemDescriptionFunctor@?A0x97efe095@@6B@; const `anonymous namespace'::GetMagicItemDescriptionFunctor::`vftable'
//	.text:00007FF6914713F0                 mov[rsp + 1100h + var_10C0], rax
//	.text : 00007FF6914713F5                 mov[rsp + 1100h + var_10B0], r15
//	.text : 00007FF6914713FA                 mov     rax, cs : qword_7FF693B47750
//	.text : 00007FF691471401                 mov[rsp + 1100h + var_10A8], rax
//	.text : 00007FF691471406                 mov     rax, cs : qword_7FF693B47758
//	.text : 00007FF69147140D                 mov[rsp + 1100h + var_10A0], rax
//	.text : 00007FF691471412                 mov[rsp + 1100h + var_1098], rsi
//	.text : 00007FF691471417                 mov[rsp + 1100h + var_1090], 0
//	.text : 00007FF69147141C
//	.text : 00007FF69147141C loc_7FF69147141C : ; DATA XREF : .rdata : 00007FF6927C4F10↓o
//	.text : 00007FF69147141C;   try {
//	.text:00007FF69147141C                 lea     rdx,[rsp + 1100h + var_10C0]
//		.text : 00007FF691471421                 mov     rcx, rsi
//		.text : 00007FF691471424                 call    sub_7FF690CE2130
//		.text : 00007FF691471429                 nop
//		.text : 00007FF691471429;
//} // starts at 7FF69147141C
//	 .text:00007FF69147142A
//		 .text : 00007FF69147142A loc_7FF69147142A : ; CODE XREF : sub_7FF691471320 + C0↑j
//		 .text : 00007FF69147142A; DATA XREF : .rdata : 00007FF6927C4F18↓o
//		 .text : 00007FF69147142A                 movzx   eax, word ptr[r15 + 8]
//		 .text : 00007FF69147142F                 mov     ecx, 0FFFFh
//		 .text : 00007FF691471434                 cmp     ax, cx
//		 .text : 00007FF691471437                 jnz     short loc_7FF69147144B
//		 .text : 00007FF691471439                 mov     rcx,[r15]
//		 .text : 00007FF69147143C or rax, 0FFFFFFFFFFFFFFFFh
//		 .text : 00007FF691471440
//		 .text : 00007FF691471440 loc_7FF691471440 : ; CODE XREF : sub_7FF691471320 + 127↓j
//		 .text : 00007FF691471440                 inc     rax
//		 .text : 00007FF691471443                 cmp     byte ptr[rcx + rax], 0
//		 .text : 00007FF691471447                 jnz     short loc_7FF691471440
//		 .text : 00007FF691471449                 jmp     short loc_7FF69147144E
//		 .text : 00007FF69147144B; -------------------------------------------------------------------------- -
//		 .text:00007FF69147144B
//		 .text : 00007FF69147144B loc_7FF69147144B : ; CODE XREF : sub_7FF691471320 + 117↑j
//		 .text : 00007FF69147144B                 movzx   eax, ax
//		 .text : 00007FF69147144E
//		 .text : 00007FF69147144E loc_7FF69147144E : ; CODE XREF : sub_7FF691471320 + 129↑j
//		 .text : 00007FF69147144E                 test    eax, eax
//		 .text : 00007FF691471450                 jnz     loc_7FF6914716FB
//		 .text : 00007FF691471456                 test    rsi, rsi
//		 .text : 00007FF691471459                 jz      loc_7FF6914716E9
//		 .text : 00007FF69147145F                 lea     r12, asc_7FF6922A68AC; "+"
//		 .text:00007FF691471466                 movss   xmm9, cs : dword_7FF69222C150
//		 .text : 00007FF69147146F                 movss   xmm10, cs : dword_7FF692173404
//		 .text : 00007FF691471478                 xorps   xmm7, xmm7
//		 .text : 00007FF69147147B                 movss   xmm6, cs : dword_7FF692115318
//		 .text : 00007FF691471483                 movss   xmm8, cs : dword_7FF69212B648
//		 .text : 00007FF69147148C                 movss   xmm11, cs : dword_7FF69216E014
//		 .text : 00007FF691471495
//		 .text : 00007FF691471495 loc_7FF691471495 : ; CODE XREF : sub_7FF691471320 + 3C4↓j
//		 .text : 00007FF691471495                 test    rbx, rbx
//		 .text : 00007FF691471498                 jz      loc_7FF6914716E9
//		 .text : 00007FF69147149E                 mov     rax,[rbx + 10h]
//		 .text : 00007FF6914714A2                 mov     ecx,[rax + 68h]
//		 .text : 00007FF6914714A5                 shr     ecx, 0Fh
//		 .text : 00007FF6914714A8                 test    cl, 1
//		 .text : 00007FF6914714AB                 jnz     loc_7FF6914716CC
//		 .text : 00007FF6914714B1                 test    dil, dil
//		 .text : 00007FF6914714B4                 jz      short loc_7FF6914714CF
//		 .text : 00007FF6914714B6                 lea     r8, asc_7FF6922A68A8; ". "
//		 .text:00007FF6914714BD                 mov     edx, 800h; SizeInBytes
//		 .text:00007FF6914714C2                 lea     rcx,[rbp + 1000h + Dst]; Dst
//		 .text:00007FF6914714C9                 call    cs : strcat_s
//		 .text : 00007FF6914714CF
//		 .text : 00007FF6914714CF loc_7FF6914714CF : ; CODE XREF : sub_7FF691471320 + 194↑j
//		 .text : 00007FF6914714CF                 mov     rcx, rbx
//		 .text : 00007FF6914714D2                 call    sub_7FF690CD8630
//		 .text : 00007FF6914714D7                 movd    xmm0, eax
//		 .text : 00007FF6914714DB                 cvtdq2ps xmm0, xmm0
//		 .text : 00007FF6914714DE                 movss[rbp + 1000h + arg_8], xmm0
//		 .text : 00007FF6914714E6                 mov     rcx, rbx
//		 .text : 00007FF6914714E9                 call    sub_7FF690CD8570
//		 .text : 00007FF6914714EE                 movss[rbp + 1000h + arg_10], xmm0
//		 .text : 00007FF6914714F6                 lea     rax,[rbp + 1000h + arg_8]
//		 .text : 00007FF6914714FD                 mov[rsp + 1100h + var_10E0], rax
//		 .text : 00007FF691471502                 xor     r9d, r9d
//		 .text : 00007FF691471505                 mov     r8, rsi
//		 .text : 00007FF691471508                 mov     rdx, cs : g_ThePlayer
//		 .text : 00007FF69147150F                 lea     ecx,[r9 + 1Eh]
//		 .text : 00007FF691471513                 call    sub_7FF690F0EDB0
//		 .text : 00007FF691471518                 lea     rax,[rbp + 1000h + arg_10]
//		 .text : 00007FF69147151F                 mov[rsp + 1100h + var_10E0], rax
//		 .text : 00007FF691471524                 xor     r9d, r9d
//		 .text : 00007FF691471527                 mov     r8, rsi
//		 .text : 00007FF69147152A                 mov     rdx, cs : g_ThePlayer
//		 .text : 00007FF691471531                 lea     ecx,[r9 + 1Dh]
//		 .text : 00007FF691471535                 call    sub_7FF690F0EDB0
//		 .text : 00007FF69147153A                 cvttss2si rdi,[rbp + 1000h + arg_8]
//		 .text : 00007FF691471543                 cvttss2si rcx,[rbp + 1000h + arg_10]
//		 .text : 00007FF69147154C                 test    ecx, ecx
//		 .text : 00007FF69147154E                 jz      short loc_7FF6914715A2
//		 .text : 00007FF691471550                 lea     rdx, Str1
//		 .text : 00007FF691471557                 cmovnz  rdx, r12
//		 .text : 00007FF69147155B                 mov     rax, cs : qword_7FF693B47758
//		 .text : 00007FF691471562                 mov[rsp + 1100h + var_10D0], rax
//		 .text : 00007FF691471567                 mov     dword ptr[rsp + 1100h + var_10D8], ecx
//		 .text : 00007FF69147156B                 mov[rsp + 1100h + var_10E0], rdx
//		 .text : 00007FF691471570                 mov     r9, cs : qword_7FF693B47750
//		 .text : 00007FF691471577                 lea     r8, aSSUS; "%s%s%u%s "
//		 .text:00007FF69147157E                 mov     edx, 800h; SizeInBytes
//		 .text:00007FF691471583                 lea     rcx,[rbp + 1000h + DstBuf]; DstBuf
//		 .text:00007FF691471587                 call    sprintf_s
//		 .text : 00007FF69147158C                 lea     r8,[rbp + 1000h + DstBuf]; Src
//		 .text:00007FF691471590                 mov     edx, 800h; SizeInBytes
//		 .text:00007FF691471595                 lea     rcx,[rbp + 1000h + Dst]; Dst
//		 .text:00007FF69147159C                 call    cs : strcat_s
//		 .text : 00007FF6914715A2
//		 .text : 00007FF6914715A2 loc_7FF6914715A2 : ; CODE XREF : sub_7FF691471320 + 22E↑j
//		 .text : 00007FF6914715A2                 mov     rcx, rbx
//		 .text : 00007FF6914715A5                 call    sub_7FF690CD86E0
//		 .text : 00007FF6914715AA                 mov     rcx, rax
//		 .text : 00007FF6914715AD                 call    sub_7FF690D9AFD0
//		 .text : 00007FF6914715B2                 mov     r8, rax; Src
//		 .text:00007FF6914715B5                 mov     edx, 800h; SizeInBytes
//		 .text:00007FF6914715BA                 lea     rcx,[rbp + 1000h + Dst]; Dst
//		 .text:00007FF6914715C1                 call    cs : strcat_s
//		 .text : 00007FF6914715C7                 test    edi, edi
//		 .text : 00007FF6914715C9                 jz      loc_7FF6914716C9
//		 .text : 00007FF6914715CF                 mov     eax, edi
//		 .text : 00007FF6914715D1                 xorps   xmm1, xmm1
//		 .text : 00007FF6914715D4                 cvtsi2ss xmm1, rax
//		 .text : 00007FF6914715D9                 comiss  xmm1, xmm9
//		 .text : 00007FF6914715DD                 jb      short loc_7FF691471614
//		 .text : 00007FF6914715DF                 mulss   xmm1, xmm10
//		 .text : 00007FF6914715E4                 cvttss2si eax, xmm1
//		 .text : 00007FF6914715E8                 movd    xmm2, eax
//		 .text : 00007FF6914715EC                 cvtdq2ps xmm2, xmm2
//		 .text : 00007FF6914715EF                 movaps  xmm0, xmm1
//		 .text : 00007FF6914715F2                 subss   xmm0, xmm2
//		 .text : 00007FF6914715F6                 comiss  xmm0, xmm7
//		 .text : 00007FF6914715F9                 jnb     short loc_7FF6914715FF
//		 .text : 00007FF6914715FB                 subss   xmm2, xmm6
//		 .text : 00007FF6914715FF
//		 .text : 00007FF6914715FF loc_7FF6914715FF : ; CODE XREF : sub_7FF691471320 + 2D9↑j
//		 .text : 00007FF6914715FF                 ucomiss xmm2, xmm6
//		 .text : 00007FF691471602                 mov     rax, cs : off_7FF6929E1938
//		 .text : 00007FF691471609                 jz      short loc_7FF69147167D
//		 .text : 00007FF69147160B                 mov     rax, cs : off_7FF6929E18F0
//		 .text : 00007FF691471612                 jmp     short loc_7FF69147167D
//		 .text : 00007FF691471614; -------------------------------------------------------------------------- -
//		 .text:00007FF691471614
//		 .text : 00007FF691471614 loc_7FF691471614 : ; CODE XREF : sub_7FF691471320 + 2BD↑j
//		 .text : 00007FF691471614                 comiss  xmm1, xmm8
//		 .text : 00007FF691471618                 jb      short loc_7FF69147164F
//		 .text : 00007FF69147161A                 mulss   xmm1, xmm11
//		 .text : 00007FF69147161F                 cvttss2si eax, xmm1
//		 .text : 00007FF691471623                 movd    xmm2, eax
//		 .text : 00007FF691471627                 cvtdq2ps xmm2, xmm2
//		 .text : 00007FF69147162A                 movaps  xmm0, xmm1
//		 .text : 00007FF69147162D                 subss   xmm0, xmm2
//		 .text : 00007FF691471631                 comiss  xmm0, xmm7
//		 .text : 00007FF691471634                 jnb     short loc_7FF69147163A
//		 .text : 00007FF691471636                 subss   xmm2, xmm6
//		 .text : 00007FF69147163A
//		 .text : 00007FF69147163A loc_7FF69147163A : ; CODE XREF : sub_7FF691471320 + 314↑j
//		 .text : 00007FF69147163A                 ucomiss xmm2, xmm6
//		 .text : 00007FF69147163D                 mov     rax, cs : off_7FF6929E1920
//		 .text : 00007FF691471644                 jz      short loc_7FF69147167D
//		 .text : 00007FF691471646                 mov     rax, cs : off_7FF6929E18D8
//		 .text : 00007FF69147164D                 jmp     short loc_7FF69147167D
//		 .text : 00007FF69147164F; -------------------------------------------------------------------------- -
//		 .text:00007FF69147164F
//		 .text : 00007FF69147164F loc_7FF69147164F : ; CODE XREF : sub_7FF691471320 + 2F8↑j
//		 .text : 00007FF69147164F                 cvttss2si eax, xmm1
//		 .text : 00007FF691471653                 movd    xmm2, eax
//		 .text : 00007FF691471657                 cvtdq2ps xmm2, xmm2
//		 .text : 00007FF69147165A                 movaps  xmm0, xmm1
//		 .text : 00007FF69147165D                 subss   xmm0, xmm2
//		 .text : 00007FF691471661                 comiss  xmm0, xmm7
//		 .text : 00007FF691471664                 jnb     short loc_7FF69147166A
//		 .text : 00007FF691471666                 subss   xmm2, xmm6
//		 .text : 00007FF69147166A
//		 .text : 00007FF69147166A loc_7FF69147166A : ; CODE XREF : sub_7FF691471320 + 344↑j
//		 .text : 00007FF69147166A                 ucomiss xmm2, xmm6
//		 .text : 00007FF69147166D                 mov     rax, cs : off_7FF6929E1908
//		 .text : 00007FF691471674                 jz      short loc_7FF69147167D
//		 .text : 00007FF691471676                 mov     rax, cs : off_7FF6929DFE80
//		 .text : 00007FF69147167D
//		 .text : 00007FF69147167D loc_7FF69147167D : ; CODE XREF : sub_7FF691471320 + 2E9↑j
//		 .text : 00007FF69147167D; sub_7FF691471320 + 2F2↑j ...
//		 .text:00007FF69147167D                 mov[rsp + 1100h + var_10D0], rax
//		 .text : 00007FF691471682                 mov     rax, cs : qword_7FF693B47758
//		 .text : 00007FF691471689                 mov[rsp + 1100h + var_10D8], rax
//		 .text : 00007FF69147168E                 cvtps2pd xmm0, xmm1
//		 .text : 00007FF691471691                 movsd[rsp + 1100h + var_10E0], xmm0
//		 .text : 00007FF691471697                 mov     r9, cs : qword_7FF693B47750
//		 .text : 00007FF69147169E                 lea     r8, aS0fSS; " %s%.0f%s %s"
//		 .text:00007FF6914716A5                 mov     edx, 800h; SizeInBytes
//		 .text:00007FF6914716AA                 lea     rcx,[rbp + 1000h + DstBuf]; DstBuf
//		 .text:00007FF6914716AE                 call    sprintf_s
//		 .text : 00007FF6914716B3                 lea     r8,[rbp + 1000h + DstBuf]; Src
//		 .text:00007FF6914716B7                 mov     edx, 800h; SizeInBytes
//		 .text:00007FF6914716BC                 lea     rcx,[rbp + 1000h + Dst]; Dst
//		 .text:00007FF6914716C3                 call    cs : strcat_s
//		 .text : 00007FF6914716C9
//		 .text : 00007FF6914716C9 loc_7FF6914716C9 : ; CODE XREF : sub_7FF691471320 + 2A9↑j
//		 .text : 00007FF6914716C9                 mov     dil, 1
//		 .text : 00007FF6914716CC
//		 .text : 00007FF6914716CC loc_7FF6914716CC : ; CODE XREF : sub_7FF691471320 + 18B↑j
//		 .text : 00007FF6914716CC                 cmp     r14d,[rsi + 68h]
//		 .text : 00007FF6914716D0                 jnb     short loc_7FF6914716DF
//		 .text : 00007FF6914716D2                 mov     ecx, r14d
//		 .text : 00007FF6914716D5                 mov     rax,[rsi + 58h]
//		 .text : 00007FF6914716D9                 mov     rbx,[rax + rcx * 8]
//		 .text : 00007FF6914716DD                 jmp     short loc_7FF6914716E1
//		 .text : 00007FF6914716DF; -------------------------------------------------------------------------- -
//		 .text:00007FF6914716DF
//		 .text : 00007FF6914716DF loc_7FF6914716DF : ; CODE XREF : sub_7FF691471320 + 3B0↑j
//		 .text : 00007FF6914716DF                 xor     ebx, ebx
//		 .text : 00007FF6914716E1
//		 .text : 00007FF6914716E1 loc_7FF6914716E1 : ; CODE XREF : sub_7FF691471320 + 3BD↑j
//		 .text : 00007FF6914716E1                 inc     r14d
//		 .text : 00007FF6914716E4                 jmp     loc_7FF691471495
//		 .text : 00007FF6914716E9; -------------------------------------------------------------------------- -
//		 .text:00007FF6914716E9
//		 .text : 00007FF6914716E9 loc_7FF6914716E9 : ; CODE XREF : sub_7FF691471320 + 139↑j
//		 .text : 00007FF6914716E9; sub_7FF691471320 + 178↑j
//		 .text:00007FF6914716E9                 xor     r8d, r8d
//		 .text : 00007FF6914716EC                 lea     rdx,[rbp + 1000h + Dst]
//		 .text : 00007FF6914716F3                 mov     rcx, r15
//		 .text : 00007FF6914716F6                 call    sub_7FF690CD9F90
//		 .text : 00007FF6914716FB
//		 .text : 00007FF6914716FB loc_7FF6914716FB : ; CODE XREF : sub_7FF691471320 + 130↑j
//		 .text : 00007FF6914716FB                 lea     r11,[rsp + 1100h + var_20]
//		 .text : 00007FF691471703                 mov     rbx,[r11 + 30h]
//		 .text : 00007FF691471707                 mov     rsi,[r11 + 48h]
//		 .text : 00007FF69147170B                 movaps  xmm6, xmmword ptr[r11 - 10h]
//		 .text : 00007FF691471710                 movaps  xmm7, xmmword ptr[r11 - 20h]
//		 .text : 00007FF691471715                 movaps  xmm8, xmmword ptr[r11 - 30h]
//		 .text : 00007FF69147171A                 movaps  xmm9, xmmword ptr[r11 - 40h]
//		 .text : 00007FF69147171F                 movaps  xmm10, xmmword ptr[r11 - 50h]
//		 .text : 00007FF691471724                 movaps  xmm11, xmmword ptr[r11 - 60h]
//		 .text : 00007FF691471729                 mov     rsp, r11
//		 .text : 00007FF69147172C                 pop     r15
//		 .text : 00007FF69147172E                 pop     r14
//		 .text : 00007FF691471730                 pop     r12
//		 .text : 00007FF691471732                 pop     rdi
//		 .text : 00007FF691471733                 pop     rbp
//		 .text : 00007FF691471734                 retn
//		 .text : 00007FF691471734; } // starts at 7FF691471320
//	.text:00007FF691471734 sub_7FF691471320 endp
//		 .text : 00007FF691471734

//Unpacked
//HxD Raw 1C 91 00 00 00 48 8B 0D 2C 7F 6B 02 E8 4F 15 38 00 84 C0 75 06 83 4B 1C 04 EB 1C 48 8B 4B 10 48 -->1.5.16
//HxD Raw 1C 91 00 00 00 48 8B 0D FC 7E 6B 02 E8 4F 15 38 00 84 C0 75 06 83 4B 1C 04 EB 1C 48 8B 4B 10 48 -->1.5.23
//HxD Raw 1C 91 00 00 00 48 8B 0D FC 85 6B 02 E8 9F 15 38 00 84 C0 75 06 83 4B 1C 04 EB 1C 48 8B 4B 10 48 -->1.5.39
//HxD Raw 1C 91 00 00 00 48 8B 0D BC 88 6B 02 E8 3F 15 38 00 84 C0 75 06 83 4B 1C 04 EB 1C 48 8B 4B 10 48 -->1.5.50
//CFF Explorer .text F6C701742740F6C7047513488B0D4E507C02488B01488BD3FF506090EB0EBA38 --> 1.5.16
//CFF Explorer .text F6C701742740F6C7047513488B0D1E507C02488B01488BD3FF506090EB0EBA38 --> 1.5.23
RelocAddr<PROCESS_SURVIVAL_MODE> ProcessSurvivalMode(0x008930F0);
//.text:00000001408930F0; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//.text:00000001408930F0
//.text:00000001408930F0
//.text:00000001408930F0                                                 ProcessSurvivalMode proc near; CODE XREF : sub_140890E70 + 96Bp
//.text:00000001408930F0; sub_140890E70 + D2Fp ...
//.text:00000001408930F0
//.text:00000001408930F0                                                 var_18 = qword ptr - 18h
//.text:00000001408930F0                                                 var_10 = qword ptr - 10h
//.text:00000001408930F0                                                 arg_0 = qword ptr  8
//.text:00000001408930F0                                                 arg_8 = qword ptr  10h
//.text:00000001408930F0                                                 arg_10 = qword ptr  18h
//.text:00000001408930F0
//.text:00000001408930F0 41 56                                                           push    r14
//.text:00000001408930F2 48 83 EC 30                                                     sub     rsp, 30h
//.text:00000001408930F6 48 8B 01                                                        mov     rax, [rcx]
//.text:00000001408930F9 4C 8B F1                                                        mov     r14, rcx
//.text:00000001408930FC 48 85 C0                                                        test    rax, rax
//.text:00000001408930FF 48 8D 0D AA C1 C8 00                                            lea     rcx, Str1
//.text:0000000140893106 BA 5B 00 00 00                                                  mov     edx, 5Bh; Val
//.text:000000014089310B 48 0F 45 C8                                                     cmovnz  rcx, rax; Str
//.text:000000014089310F FF 15 6B 67 C7 00                                               call    cs : __imp_strchr
//.text : 0000000140893115 48 85 C0                                                        test    rax, rax
//.text:0000000140893118 0F 84 E1 01 00 00                                               jz      loc_1408932FF
//.text:000000014089311E 41 0F B7 46 08                                                  movzx   eax, word ptr[r14 + 8]
//.text:0000000140893123 B9 FF FF 00 00                                                  mov     ecx, 0FFFFh
//.text:0000000140893128
//.text:0000000140893128                                                 loc_140893128 : ; DATA XREF : .rdata : 0000000141BD35FCo
//.text:0000000140893128;.rdata:0000000141BD3610o ...
//.text:0000000140893128 48 89 5C 24 40                                                  mov[rsp + 38h + arg_0], rbx
//.text:000000014089312D 48 89 6C 24 48                                                  mov[rsp + 38h + arg_8], rbp
//.text:0000000140893132 48 89 7C 24 28                                                  mov[rsp + 38h + var_10], rdi
//.text:0000000140893137 4C 89 7C 24 20                                                  mov[rsp + 38h + var_18], r15
//.text:000000014089313C 66 3B C1                                                        cmp     ax, cx
//.text:000000014089313F 75 1A                                                           jnz     short loc_14089315B
//.text:0000000140893141 49 8B 0E                                                        mov     rcx, [r14]
//.text:0000000140893144 48 83 C8 FF or rax, 0FFFFFFFFFFFFFFFFh
//.text:0000000140893148 0F 1F 84 00 00 00 00 00                                         nop     dword ptr[rax + rax + 00000000h]
//.text:0000000140893150
//.text:0000000140893150                                                 loc_140893150 : ; CODE XREF : ProcessSurvivalMode + 67j
//.text:0000000140893150 48 FF C0                                                        inc     rax
//.text:0000000140893153 80 3C 01 00                                                     cmp     byte ptr[rcx + rax], 0
//.text:0000000140893157 75 F7                                                           jnz     short loc_140893150
//.text:0000000140893159 EB 03                                                           jmp     short loc_14089315E
//.text:000000014089315B; -------------------------------------------------------------------------- -


// Base Address = 7FF690BE0000
//.text:00007FF691471740; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//.text:00007FF691471740
//.text : 00007FF691471740
//.text : 00007FF691471740 sub_7FF691471740 proc near; CODE XREF : sub_7FF69146F4C0 + 96B↑p
//.text : 00007FF691471740; sub_7FF69146F4C0 + D2F↑p ...
//.text:00007FF691471740
//.text : 00007FF691471740 var_18 = qword ptr - 18h
//.text : 00007FF691471740 var_10 = qword ptr - 10h
//.text : 00007FF691471740 arg_0 = qword ptr  8
//.text : 00007FF691471740 arg_8 = qword ptr  10h
//.text : 00007FF691471740 arg_10 = qword ptr  18h
//.text : 00007FF691471740
//.text : 00007FF691471740                 push    r14
//.text : 00007FF691471742                 sub     rsp, 30h
//.text : 00007FF691471746                 mov     rax, [rcx]
//.text : 00007FF691471749                 mov     r14, rcx
//.text : 00007FF69147174C                 test    rax, rax
//.text : 00007FF69147174F                 lea     rcx, Str1
//.text : 00007FF691471756                 mov     edx, 5Bh; Val
//.text:00007FF69147175B                 cmovnz  rcx, rax; Str
//.text:00007FF69147175F                 call    cs : __imp_strchr
//.text : 00007FF691471765                 test    rax, rax
//.text : 00007FF691471768                 jz      loc_7FF69147194F
//.text : 00007FF69147176E                 movzx   eax, word ptr[r14 + 8]
//.text : 00007FF691471773                 mov     ecx, 0FFFFh
//.text : 00007FF691471778
//.text : 00007FF691471778 loc_7FF691471778 : ; DATA XREF : .rdata : 00007FF6927C4F3C↓o
//.text : 00007FF691471778;.rdata:00007FF6927C4F50↓o ...
//.text : 00007FF691471778                 mov[rsp + 38h + arg_0], rbx
//.text : 00007FF69147177D                 mov[rsp + 38h + arg_8], rbp
//.text : 00007FF691471782                 mov[rsp + 38h + var_10], rdi
//.text : 00007FF691471787                 mov[rsp + 38h + var_18], r15
//.text : 00007FF69147178C                 cmp     ax, cx
//.text : 00007FF69147178F                 jnz     short loc_7FF6914717AB
//.text : 00007FF691471791                 mov     rcx, [r14]
//.text : 00007FF691471794 or rax, 0FFFFFFFFFFFFFFFFh
//.text : 00007FF691471798                 nop     dword ptr[rax + rax + 00000000h]
//.text : 00007FF6914717A0
//.text : 00007FF6914717A0 loc_7FF6914717A0 : ; CODE XREF : sub_7FF691471740 + 67↓j
//.text : 00007FF6914717A0                 inc     rax
//.text : 00007FF6914717A3                 cmp     byte ptr[rcx + rax], 0
//.text : 00007FF6914717A7                 jnz     short loc_7FF6914717A0
//.text : 00007FF6914717A9                 jmp     short loc_7FF6914717AE
//.text : 00007FF6914717AB; -------------------------------------------------------------------------- -
//.text:00007FF6914717AB
//.text : 00007FF6914717AB loc_7FF6914717AB : ; CODE XREF : sub_7FF691471740 + 4F↑j
//.text : 00007FF6914717AB                 movzx   eax, ax
//.text : 00007FF6914717AE
//.text : 00007FF6914717AE loc_7FF6914717AE : ; CODE XREF : sub_7FF691471740 + 69↑j
//.text : 00007FF6914717AE                 cmp     cs : dword_7FF692AB6C88, 2
//.text : 00007FF6914717B5                 lea     ebx, [rax + 1]
//.text : 00007FF6914717B8                 jz      short loc_7FF6914717CD
//.text : 00007FF6914717BA                 lea     rdx, dword_7FF692AB6C88
//.text : 00007FF6914717C1                 lea     rcx, unk_7FF692AB6800
//.text : 00007FF6914717C8                 call    sub_7FF6917E0D30
//.text : 00007FF6914717CD
//.text : 00007FF6914717CD loc_7FF6914717CD : ; CODE XREF : sub_7FF691471740 + 78↑j
//.text : 00007FF6914717CD                 xor     edx, edx
//.text : 00007FF6914717CF                 lea     rcx, unk_7FF692AB6800
//.text : 00007FF6914717D6                 call    sub_7FF6917DFE60
//.text : 00007FF6914717DB                 mov     rcx, rax
//.text : 00007FF6914717DE                 mov     r8d, 8
//.text : 00007FF6914717E4                 mov     rdx, rbx
//.text : 00007FF6914717E7                 call    sub_7FF6917E1B00
//.text : 00007FF6914717EC                 mov     rcx, [r14]
//.text : 00007FF6914717EF                 lea     r8, Str1
//.text : 00007FF6914717F6                 test    rcx, rcx
//.text : 00007FF6914717F9                 mov     rdx, rbx; SizeInBytes
//.text:00007FF6914717FC                 mov     r15, rax
//.text : 00007FF6914717FF                 cmovnz  r8, rcx; Src
//.text:00007FF691471803                 mov     rcx, rax; Dst
//.text:00007FF691471806                 call    cs : __imp_strcpy_s
//.text : 00007FF69147180C                 xor     r8d, r8d
//.text : 00007FF69147180F                 lea     rdx, Str1
//.text : 00007FF691471816                 mov     rcx, r14
//.text : 00007FF691471819                 call    sub_7FF690CD9F90
//.text : 00007FF69147181E                 mov     edx, 5Bh; Val
//.text:00007FF691471823                 mov     rcx, r15; Str
//.text:00007FF691471826                 mov     rbp, r15
//.text : 00007FF691471829                 call    cs : __imp_strchr
//.text : 00007FF69147182F                 mov     rdi, rax
//.text : 00007FF691471832                 test    rax, rax
//.text : 00007FF691471835                 jz      loc_7FF6914718FB
//.text : 00007FF69147183B
//.text : 00007FF69147183B loc_7FF69147183B : ; DATA XREF : .rdata : 00007FF6927C4F50↓o
//.text : 00007FF69147183B;.rdata:00007FF6927C4F60↓o ...
//.text : 00007FF69147183B                 mov[rsp + 38h + arg_10], rsi
//.text : 00007FF691471840
//.text : 00007FF691471840 loc_7FF691471840 : ; CODE XREF : sub_7FF691471740 + 1B0↓j
//.text : 00007FF691471840                 mov     edx, 5Dh; Val
//.text:00007FF691471845                 mov     rcx, rdi; Str
//.text:00007FF691471848                 call    cs : __imp_strchr
//.text : 00007FF69147184E                 mov     rsi, rax
//.text : 00007FF691471851                 test    rax, rax
//.text : 00007FF691471854                 jz      short loc_7FF6914718BB
//.text : 00007FF691471856                 mov     edx, 3Dh; Val
//.text:00007FF69147185B                 mov     byte ptr[rax], 0
//.text : 00007FF69147185E                 mov     rcx, rdi; Str
//.text:00007FF691471861                 call    cs : __imp_strchr
//.text : 00007FF691471867                 mov     rbx, rax
//.text : 00007FF69147186A                 test    rax, rax
//.text : 00007FF69147186D                 jz      short loc_7FF69147187E
//.text : 00007FF69147186F                 cmp     rax, rsi
//.text : 00007FF691471872                 jbe     short loc_7FF691471878
//.text : 00007FF691471874                 xor     ebx, ebx
//.text : 00007FF691471876                 jmp     short loc_7FF69147187E
//.text : 00007FF691471878; -------------------------------------------------------------------------- -
//.text:00007FF691471878
//.text : 00007FF691471878 loc_7FF691471878 : ; CODE XREF : sub_7FF691471740 + 132↑j
//.text : 00007FF691471878                 mov     byte ptr[rax], 0
//.text : 00007FF69147187B                 inc     rbx
//.text : 00007FF69147187E
//.text : 00007FF69147187E loc_7FF69147187E : ; CODE XREF : sub_7FF691471740 + 12D↑j
//.text : 00007FF69147187E; sub_7FF691471740 + 136↑j
//.text:00007FF69147187E                 mov     rdx, rbp
//.text : 00007FF691471881                 mov     byte ptr[rdi], 0
//.text : 00007FF691471884                 mov     rcx, r14
//.text : 00007FF691471887                 call    sub_7FF690CD9290
//.text : 00007FF69147188C                 lea     rcx, [rdi + 1]; Str1
//.text:00007FF691471890                 lea     rdx, aSurv; "SURV"
//.text:00007FF691471897                 call    cs : __imp__stricmp
//.text : 00007FF69147189D                 test    eax, eax
//.text : 00007FF69147189F                 jnz     short loc_7FF6914718B5
//.text : 00007FF6914718A1                 call    sub_7FF6914B9220
//.text : 00007FF6914718A6                 test    al, al
//.text : 00007FF6914718A8                 jz      short loc_7FF6914718B5
//.text : 00007FF6914718AA                 mov     rdx, rbx
//.text : 00007FF6914718AD                 mov     rcx, r14
//.text : 00007FF6914718B0                 call    sub_7FF690CD9290
//.text : 00007FF6914718B5
//.text : 00007FF6914718B5 loc_7FF6914718B5 : ; CODE XREF : sub_7FF691471740 + 15F↑j
//.text : 00007FF6914718B5; sub_7FF691471740 + 168↑j
//.text:00007FF6914718B5                 lea     rbp, [rsi + 1]
//.text : 00007FF6914718B9                 jmp     short loc_7FF6914718DC
//.text : 00007FF6914718BB; -------------------------------------------------------------------------- -
//.text:00007FF6914718BB
//.text : 00007FF6914718BB loc_7FF6914718BB : ; CODE XREF : sub_7FF691471740 + 114↑j
//.text : 00007FF6914718BB                 mov     rdx, rbp
//.text : 00007FF6914718BE                 mov     byte ptr[rdi], 0
//.text : 00007FF6914718C1                 mov     rcx, r14
//.text : 00007FF6914718C4                 call    sub_7FF690CD9290
//.text : 00007FF6914718C9                 lea     rdx, asc_7FF6922A66D0; "["
//.text:00007FF6914718D0                 mov     rcx, r14
//.text : 00007FF6914718D3                 call    sub_7FF690CD9290
//.text : 00007FF6914718D8                 lea     rbp, [rdi + 1]
//.text : 00007FF6914718DC
//.text : 00007FF6914718DC loc_7FF6914718DC : ; CODE XREF : sub_7FF691471740 + 179↑j
//.text : 00007FF6914718DC                 mov     edx, 5Bh; Val
//.text:00007FF6914718E1                 mov     rcx, rbp; Str
//.text:00007FF6914718E4                 call    cs : __imp_strchr
//.text : 00007FF6914718EA                 mov     rdi, rax
//.text : 00007FF6914718ED                 test    rax, rax
//.text : 00007FF6914718F0                 jnz     loc_7FF691471840
//.text : 00007FF6914718F6                 mov     rsi, [rsp + 38h + arg_10]
//.text : 00007FF6914718FB
//.text : 00007FF6914718FB loc_7FF6914718FB : ; CODE XREF : sub_7FF691471740 + F5↑j
//.text : 00007FF6914718FB; DATA XREF : .pdata : 00007FF69411E4B8↓o ...
//.text : 00007FF6914718FB                 mov     rdx, rbp
//.text : 00007FF6914718FE                 mov     rcx, r14
//.text : 00007FF691471901                 call    sub_7FF690CD9290
//.text : 00007FF691471906                 cmp     cs : dword_7FF692AB6C88, 2
//.text : 00007FF69147190D                 mov     rdi, [rsp + 38h + var_10]
//.text : 00007FF691471912                 mov     rbp, [rsp + 38h + arg_8]
//.text : 00007FF691471917                 mov     rbx, [rsp + 38h + arg_0]
//.text : 00007FF69147191C                 jz      short loc_7FF691471931
//.text : 00007FF69147191E
//.text : 00007FF69147191E loc_7FF69147191E : ; DATA XREF : .pdata : 00007FF69411E4C4↓o
//.text : 00007FF69147191E;.pdata:00007FF69411E4D0↓o
//.text : 00007FF69147191E                 lea     rdx, dword_7FF692AB6C88
//.text : 00007FF691471925                 lea     rcx, unk_7FF692AB6800
//.text : 00007FF69147192C                 call    sub_7FF6917E0D30
//.text : 00007FF691471931
//.text : 00007FF691471931 loc_7FF691471931 : ; CODE XREF : sub_7FF691471740 + 1DC↑j
//.text : 00007FF691471931                 xor     edx, edx
//.text : 00007FF691471933                 lea     rcx, unk_7FF692AB6800
//.text : 00007FF69147193A                 call    sub_7FF6917DFE60
//.text : 00007FF69147193F                 mov     rcx, rax
//.text : 00007FF691471942                 mov     rdx, r15
//.text : 00007FF691471945                 call    sub_7FF6917E2120
//.text : 00007FF69147194A                 mov     r15, [rsp + 38h + var_18]
//.text : 00007FF69147194F
//.text : 00007FF69147194F loc_7FF69147194F : ; CODE XREF : sub_7FF691471740 + 28↑j
//.text : 00007FF69147194F; DATA XREF : .pdata : 00007FF69411E4D0↓o ...
//.text : 00007FF69147194F                 add     rsp, 30h
//.text : 00007FF691471953                 pop     r14
//.text : 00007FF691471955                 retn
//.text : 00007FF691471955 sub_7FF691471740 endp
//.text : 00007FF691471955
//.text : 00007FF691471955; -------------------------------------------------------------------------- -

float CAHZScaleform::GetBaseDamage(TESAmmo* pthisAmmo)
{
   return pthisAmmo->settings.damage;
}

bool CAHZScaleform::GetIsKnownEnchantment(TESObjectREFR *targetRef)
{
   PlayerCharacter* pPC = (*g_thePlayer);
   TESForm *baseForm;
   if (pPC && targetRef && (baseForm = targetRef->baseForm) && 
      (baseForm->GetFormType() == kFormType_Weapon || baseForm->GetFormType() == kFormType_Armor || baseForm->GetFormType() == kFormType_Ammo)) 
   {
      EnchantmentItem * enchantment = NULL;
      TESEnchantableForm * enchantable = DYNAMIC_CAST(baseForm, TESForm, TESEnchantableForm);
      bool wasExtra = false;
      if (enchantable) { // Check the item for a base enchantment
         enchantment = enchantable->enchantment;
      }
      if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(targetRef->extraData.GetByType(kExtraData_Enchantment)))
      {
         wasExtra = true;
         enchantment = extraEnchant->enchant;
      }

      if (enchantment)
      {
         if ((enchantment->flags & TESForm::kFlagPlayerKnows) == TESForm::kFlagPlayerKnows) {
            return true;
         }

         if (enchantment->data.baseEnchantment)
         {
            if ((enchantment->data.baseEnchantment->flags & TESForm::kFlagPlayerKnows) == TESForm::kFlagPlayerKnows) {
               return true;
            }
         }
      }

      // Its safe to assume that if it not a base enchanted item, that it was enchanted by the player and therefore, they
      // know the enchantment
      if (wasExtra)
      {
         return true;
      }

   }
   return false;
}

double CAHZScaleform::GetActualDamage(AHZWeaponData *weaponData)
{
   if (!weaponData)
      return 0.0;

   PlayerCharacter* pPC = (*g_thePlayer);

   if (pPC)
   {
      InventoryEntryData objDesc(weaponData->equipData.pForm, 0);

      // Allocate a list to send
      objDesc.extendDataList = new tList<BaseExtraList>();

      if (weaponData->equipData.pExtraData)
      {
         objDesc.extendDataList->Insert(weaponData->equipData.pExtraData);
      }

      float fDamage = CALL_MEMBER_FN(pPC, GetDamage)(&objDesc);

      // Delete the allocated dummy list
      delete objDesc.extendDataList;

      // This could be rounded, but the the script decide
      return mRound(fDamage);
   }

   return 0.0;
}

double CAHZScaleform::GetArmorWarmthRating(AHZArmorData* armorData)
{
   if (!armorData->armor)
      return 0.0;

   InventoryEntryData objDesc(armorData->equipData.pForm, 0);

   // Allocate a dummy list so skyrim does not crash. For armor information
   // skyrim doesn't appear to need the list
   objDesc.extendDataList = new tList<BaseExtraList>();
   if (armorData->equipData.pExtraData)
   {
      objDesc.extendDataList->Insert(armorData->equipData.pExtraData);
   }

   double fRating = GetArmorWarmthRating_Native(objDesc.type);

   // Delete the allocated dummy list
   delete objDesc.extendDataList;

   // This could be rounded, but the the script decide
   return mRound(fRating);

   return 0.0;
}

double CAHZScaleform::GetArmorWarmthRating(TESObjectREFR* targetRef)
{
   if (!targetRef || !targetRef->baseForm)
      return 0.0;

   if (targetRef->baseForm->GetFormType() != kFormType_Armor || !IsSurvivalMode())
   {
      return 0.0;
   }

   AHZArmorData armorData(targetRef);
   return GetArmorWarmthRating(&armorData);
}

double CAHZScaleform::GetPlayerWarmthRating(void)
{

   return 0.0;
}

double CAHZScaleform::GetActualArmorRating(AHZArmorData* armorData)
{
   if (!armorData->armor)
      return 0.0;

   PlayerCharacter* pPC = (*g_thePlayer);

   if (pPC)
   {
      InventoryEntryData objDesc(armorData->equipData.pForm, 0);

      // Allocate a dummy list so skyrim does not crash. For armor information
      // skyrim doesn't appear to need the list
      objDesc.extendDataList = new tList<BaseExtraList>();
      if (armorData->equipData.pExtraData)
      {
         objDesc.extendDataList->Insert(armorData->equipData.pExtraData);
      }

      double fRating = CALL_MEMBER_FN(pPC, GetArmorValue)(&objDesc);

      // Delete the allocated dummy list
      delete objDesc.extendDataList;

      // This could be rounded, but the the script decide
      return mRound(fRating);
   }

   return 0.0;
}

double CAHZScaleform::GetTotalActualArmorRating(void)
{
   double totalRating = 0.0;
   double rating = 0.0;
   // Keep a list of items to make sure they are not added more than once
   // Some items take up more than one slot
   std::list<TESForm*> clist;
   for (UInt64 slot = 1; slot <= (UInt64)0x2000; slot <<= 1)
   {
      AHZArmorData armorData = CAHZArmorInfo::GetArmorFromSlotMask(slot);
      if (armorData.equipData.pForm)
      {
         if (find(clist.begin(), clist.end(), armorData.equipData.pForm) == clist.end())
         {
            clist.push_front(armorData.equipData.pForm);
            if (armorData.armor)
            {
               totalRating += GetActualArmorRating(&armorData);
            }
         }
      }
   }
   return mRound(totalRating);
}

double CAHZScaleform::GetTotalWarmthRating(void)
{
   PlayerCharacter* pPC = (*g_thePlayer);

   if (!pPC)
   {
      return 0.0;
   }

   return GetActorWarmthRating_Native(pPC, 0.0);
}

double CAHZScaleform::mRound(double r)
{
   return (r >= 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

double CAHZScaleform::GetArmorRatingDiff(TESObjectREFR *thisArmor)
{
   UInt64 slot = 1;
   float oldArmorRating = 0.0;
   float newArmorRating = 0.0;
   float oldTotalArmorRating = 0.0;
   float newTotalArmorRating = 0.0;
   double deltaRating = 0.0;
   if (!thisArmor)
      return 0.0;

   // Get the new armor rating
   AHZArmorData armorData(thisArmor);
   if (!armorData.armor)
      return 0.0;

   newArmorRating = GetActualArmorRating(&armorData);

   // Get the armor rating from the armor that shares the same slot
   AHZArmorData sameSlotData = CAHZArmorInfo::GetArmorFromSlotMask(
      armorData.armor->bipedObject.GetSlotMask());
   if (sameSlotData.armor)
   {
      oldArmorRating = GetActualArmorRating(&sameSlotData);
   }

   // Get the total
   oldTotalArmorRating = GetTotalActualArmorRating();

   newTotalArmorRating = (oldTotalArmorRating - oldArmorRating) + newArmorRating;

   deltaRating = newTotalArmorRating - oldTotalArmorRating;

   return deltaRating;
}

double CAHZScaleform::GetWarmthRatingDiff(TESObjectREFR *thisArmor)
{
   UInt64 slot = 1;
   float oldArmorRating = 0.0;
   float newArmorRating = 0.0;
   float oldTotalArmorRating = 0.0;
   float newTotalArmorRating = 0.0;
   double deltaRating = 0.0;
   if (!thisArmor)
      return 0.0;

   // Get the new armor rating
   AHZArmorData armorData(thisArmor);
   if (!armorData.armor)
      return 0.0;

   newArmorRating = GetArmorWarmthRating(&armorData);

   // Get the armor rating from the armor that shares the same slot
   AHZArmorData sameSlotData = CAHZArmorInfo::GetArmorFromSlotMask(
      armorData.armor->bipedObject.GetSlotMask());
   if (sameSlotData.armor)
   {
      oldArmorRating = GetArmorWarmthRating(&sameSlotData);
   }

   // Get the total
   oldTotalArmorRating = GetTotalWarmthRating();

   newTotalArmorRating = (oldTotalArmorRating - oldArmorRating) + newArmorRating;

   deltaRating = newTotalArmorRating - oldTotalArmorRating;

   return deltaRating;
}

double CAHZScaleform::GetTotalActualWeaponDamage(void)
{
   float totalWeaponDamage = 0.0;
   bool is2Handed = FALSE;
   AHZWeaponData leftWeapon = CAHZWeaponInfo::GetLeftHandWeapon();
   AHZWeaponData rightWeapon = CAHZWeaponInfo::GetRightHandWeapon();
   AHZWeaponData equippedAmmo = CAHZWeaponInfo::GetEquippedAmmo();

   if (leftWeapon.weapon)
   {
      if (IsBow(leftWeapon.weapon))
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&leftWeapon);

         // Add the arrow damage
         if (equippedAmmo.ammo && !isBolt(equippedAmmo.ammo))
         {
            totalWeaponDamage += GetActualDamage(&equippedAmmo);
         }
      }
      else if (IsCrossBow(leftWeapon.weapon))
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&leftWeapon);

         // Add the arrow damage
         if (equippedAmmo.ammo && isBolt(equippedAmmo.ammo))
         {
            totalWeaponDamage += GetActualDamage(&equippedAmmo);
         }
      }
      else if (IsTwoHanded(leftWeapon.weapon))
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&leftWeapon);
      }
      else if (IsOneHanded(leftWeapon.weapon))
      {
         totalWeaponDamage = GetActualDamage(&leftWeapon);
      }
   }

   if (rightWeapon.weapon)
   {
      if (IsBow(rightWeapon.weapon) && !is2Handed)
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&rightWeapon);

         // Add the arrow damage
         if (equippedAmmo.ammo && !isBolt(equippedAmmo.ammo))
         {
            totalWeaponDamage += GetActualDamage(&equippedAmmo);
         }
      }
      else if (IsCrossBow(rightWeapon.weapon) && !is2Handed)
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&rightWeapon);

         // Add the arrow damage
         if (equippedAmmo.ammo && isBolt(equippedAmmo.ammo))
         {
            totalWeaponDamage += GetActualDamage(&equippedAmmo);
         }
      }
      else if (IsTwoHanded(rightWeapon.weapon) && !is2Handed)
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&rightWeapon);
      }
      else if (IsOneHanded(rightWeapon.weapon))
      {
         // Add the damage from the second weapon
         totalWeaponDamage += GetActualDamage(&rightWeapon);
      }
   }
   return totalWeaponDamage;
}

bool CAHZScaleform::isBolt(TESAmmo *thisAmmo)
{
   return (thisAmmo->isBolt());
}

double CAHZScaleform::GetWeaponDamageDiff(TESObjectREFR *targetWeaponOrAmmo)
{
   double totalWeaponDamage = 0.0;
   double targetArrowDamage = 0.0;
   AHZWeaponData leftWeapon;
   AHZWeaponData rightWeapon;
   AHZWeaponData targetWeapon;
   AHZWeaponData equippedAmmo;

   if (!targetWeaponOrAmmo)
      return 0.0;

   targetWeapon = CAHZWeaponInfo::GetWeaponInfo(targetWeaponOrAmmo);
   equippedAmmo = CAHZWeaponInfo::GetEquippedAmmo();

   //DumpClass(targetWeapon.ammo, 256);

    // Must be a weapon or armor targeted
   if (targetWeapon.weapon)
   {
      if (equippedAmmo.ammo)
      {
         // TODO Try to get the equipped arrow with extra data
         if (IsBow(targetWeapon.weapon) && !isBolt(equippedAmmo.ammo))
         {
            targetArrowDamage = GetActualDamage(&equippedAmmo);
         }
         else if (IsCrossBow(targetWeapon.weapon) && isBolt(equippedAmmo.ammo))
         {
            targetArrowDamage = GetActualDamage(&equippedAmmo);
         }
      }
   }
   else if (targetWeapon.ammo)
   {
      //targetAmmo = targetWeapon.ammo;
   }
   else
   {
      return 0.0;
   }

   rightWeapon = CAHZWeaponInfo::GetRightHandWeapon();
   leftWeapon = CAHZWeaponInfo::GetLeftHandWeapon();

   if (leftWeapon.weapon)
   {
      if (IsBow(leftWeapon.weapon))
      {
         float tempDamage = GetActualDamage(&leftWeapon);
         float tempArrowDamage = 0.0;

         // Add the arrow damage
         if (equippedAmmo.ammo && !isBolt(equippedAmmo.ammo))
         {
            tempArrowDamage = GetActualDamage(&equippedAmmo);
            tempDamage += tempArrowDamage;
         }

         if (targetWeapon.weapon)
         {
            return (GetActualDamage(&targetWeapon) + targetArrowDamage) - tempDamage;
         }
         else if (targetWeapon.ammo && !isBolt(targetWeapon.ammo))
         {
            return ((tempDamage - tempArrowDamage) + GetActualDamage(&targetWeapon)) - tempDamage;
         }
         else
         {
            return 0.0;
         }
      }
      else if (IsCrossBow(leftWeapon.weapon))
      {
         float tempDamage = GetActualDamage(&leftWeapon);
         float tempArrowDamage = 0.0;

         // Add the arrow damage
         if (equippedAmmo.ammo && isBolt(equippedAmmo.ammo))
         {
            tempArrowDamage = GetActualDamage(&equippedAmmo);
            tempDamage += tempArrowDamage;
         }

         if (targetWeapon.weapon)
         {
            return (GetActualDamage(&targetWeapon) + targetArrowDamage) - tempDamage;
         }
         else if (targetWeapon.ammo && isBolt(targetWeapon.ammo))
         {
            return ((tempDamage - tempArrowDamage) + GetActualDamage(&targetWeapon) - tempDamage);
         }
         else
         {
            return 0.0;
         }
      }
      else if (IsTwoHanded(leftWeapon.weapon) && targetWeapon.weapon)
      {
         return (GetActualDamage(&targetWeapon) + targetArrowDamage) - GetActualDamage(&leftWeapon);
      }
      else if (IsOneHanded(leftWeapon.weapon))
      {
         totalWeaponDamage = GetActualDamage(&leftWeapon);
      }
   }

   if (rightWeapon.weapon)
   {
      if (IsOneHanded(rightWeapon.weapon))
      {
         // Add the damage from the second weapon
         totalWeaponDamage += GetActualDamage(&rightWeapon);
      }
   }

   // If we made it this far either no weapon is equipped or single handed weapons are equipped
   if (targetWeapon.weapon)
   {
      return (GetActualDamage(&targetWeapon) + targetArrowDamage) - totalWeaponDamage;
   }

   return 0.0;
}

bool CAHZScaleform::IsTwoHanded(TESObjectWEAP * thisWeapon)
{
   //kType_HandToHandMelee = 0,
   //kType_OneHandSword,
   //kType_OneHandDagger,
   //kType_OneHandAxe,
   //kType_OneHandMace,
   //kType_TwoHandSword,
   //kType_TwoHandAxe,
   //kType_Bow,
   //kType_Staff,
   //kType_CrossBow,
   //kType_H2H,
   //kType_1HS,
   //kType_1HD,
   //kType_1HA,
   //kType_1HM,
   //kType_2HS,
   //kType_2HA,
   //kType_Bow2,
   //kType_Staff2,
   //kType_CBow
   return (thisWeapon->type() == TESObjectWEAP::GameData::kType_TwoHandSword ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_TwoHandAxe ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_CrossBow ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_2HS ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_2HA ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow2 ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_CBow);
}

bool CAHZScaleform::IsOneHanded(TESObjectWEAP * thisWeapon)
{
   //kType_HandToHandMelee = 0,
   //kType_OneHandSword,
   //kType_OneHandDagger,
   //kType_OneHandAxe,
   //kType_OneHandMace,
   //kType_TwoHandSword,
   //kType_TwoHandAxe,
   //kType_Bow,
   //kType_Staff,
   //kType_CrossBow,
   //kType_H2H,
   //kType_1HS,
   //kType_1HD,
   //kType_1HA,
   //kType_1HM,
   //kType_2HS,
   //kType_2HA,
   //kType_Bow2,
   //kType_Staff2,
   //kType_CBow
   return (thisWeapon->type() == TESObjectWEAP::GameData::kType_OneHandSword ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_OneHandDagger ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_OneHandAxe ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_OneHandMace ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_1HS ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_1HD ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_1HA ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_1HM);
}

//bool CAHZUtility::IsBowType(TESObjectWEAP * thisWeapon)
//{
//			//kType_HandToHandMelee = 0,
//			//kType_OneHandSword,
//			//kType_OneHandDagger,
//			//kType_OneHandAxe,
//			//kType_OneHandMace,
//			//kType_TwoHandSword,
//			//kType_TwoHandAxe,
//			//kType_Bow,
//			//kType_Staff,
//			//kType_CrossBow,
//			//kType_H2H,
//			//kType_1HS,
//			//kType_1HD,
//			//kType_1HA,
//			//kType_1HM,
//			//kType_2HS,
//			//kType_2HA,
//			//kType_Bow2,
//			//kType_Staff2,
//			//kType_CBow
//	return (thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow ||
//			thisWeapon->type() == TESObjectWEAP::GameData::kType_CrossBow ||
//			thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow2 ||
//			thisWeapon->type() == TESObjectWEAP::GameData::kType_CBow);
//}

bool CAHZScaleform::IsBow(TESObjectWEAP * thisWeapon)
{
   //kType_HandToHandMelee = 0,
   //kType_OneHandSword,
   //kType_OneHandDagger,
   //kType_OneHandAxe,
   //kType_OneHandMace,
   //kType_TwoHandSword,
   //kType_TwoHandAxe,
   //kType_Bow,
   //kType_Staff,
   //kType_CrossBow,
   //kType_H2H,
   //kType_1HS,
   //kType_1HD,
   //kType_1HA,
   //kType_1HM,
   //kType_2HS,
   //kType_2HA,
   //kType_Bow2,
   //kType_Staff2,
   //kType_CBow
   return (thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow2);
}

bool CAHZScaleform::IsCrossBow(TESObjectWEAP * thisWeapon)
{
   //kType_HandToHandMelee = 0,
   //kType_OneHandSword,
   //kType_OneHandDagger,
   //kType_OneHandAxe,
   //kType_OneHandMace,
   //kType_TwoHandSword,
   //kType_TwoHandAxe,
   //kType_Bow,
   //kType_Staff,
   //kType_CrossBow,
   //kType_H2H,
   //kType_1HS,
   //kType_1HD,
   //kType_1HA,
   //kType_1HM,
   //kType_2HS,
   //kType_2HA,
   //kType_Bow2,
   //kType_Staff2,
   //kType_CBow
   return (thisWeapon->type() == TESObjectWEAP::GameData::kType_CrossBow ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_CBow);
}

AlchemyItem * CAHZScaleform::GetAlchemyItemFromLeveledList(TESForm *thisObject)
{
   if (thisObject->formType == kFormType_LeveledItem)
   {
      TESLevItem *lvli = DYNAMIC_CAST(thisObject, TESForm, TESLevItem);

      // Get the first form and see if it is an ingredient
      if (lvli->leveledList.length > 0)
      {
         for (int i = 0; i < lvli->leveledList.length; i++)
         {
            TESForm *itemform = (TESForm *)lvli->leveledList.entries[i].form;
            if (itemform)
            {
               if (itemform->formType == kFormType_Potion)
               {
                  AlchemyItem *alchemyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
                  return alchemyItem;
               }
            }
         }
         //for (int i = 0; i < lvli->leveledList.length; i++)
         //{
         //   TESForm *itemform = (TESForm *)lvli->leveledList.entries[i].form;
         //   if (itemform)
         //   {
         //      if (itemform->formType == kFormType_Ingredient)
         //      {
         //         IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
         //         return ingredient;
         //      }
         //      // Nested leveled lists
         //      else if (itemform->formType == kFormType_LeveledItem)
         //      {
         //         return GetIngredientFromLeveledList(itemform);
         //      }
         //   }
         //}
      }
   }

   return NULL;
}

IngredientItem* CAHZScaleform::GetIngredientFromLeveledList(TESForm *thisObject)
{
   if (thisObject->formType == kFormType_LeveledItem)
   {
      TESLevItem *lvli = DYNAMIC_CAST(thisObject, TESForm, TESLevItem);

      // Get the first form and see if it is an ingredient
      if (lvli->leveledList.length > 0)
      {
         for (int i = 0; i < lvli->leveledList.length; i++)
         {
            TESForm *itemform = (TESForm *)lvli->leveledList.entries[i].form;
            if (itemform)
            {
               if (itemform->formType == kFormType_Ingredient)
               {
                  IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
                  return ingredient;
               }
            }
         }
         //for (int i = 0; i < lvli->leveledList.length; i++)
         //{
         //   TESForm *itemform = (TESForm *)lvli->leveledList.entries[i].form;
         //   if (itemform)
         //   {
         //      if (itemform->formType == kFormType_Ingredient)
         //      {
         //         IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
         //         return ingredient;
         //      }
         //      // Nested leveled lists
         //      else if (itemform->formType == kFormType_LeveledItem)
         //      {
         //         return GetIngredientFromLeveledList(itemform);
         //      }
         //   }
         //}
      }
   }

   return NULL;
}

IngredientItem* CAHZScaleform::GetIngredient(TESForm *thisObject)
{
   if (!thisObject)
      return NULL;

   TESObjectREFR*reference = AHZGetReference(thisObject);
   if (reference)
   {
      thisObject = reference->baseForm;
   }

   if (thisObject->GetFormType() == kFormType_Ingredient)
      return DYNAMIC_CAST(thisObject, TESForm, IngredientItem);

   if (thisObject->GetFormType() == kFormType_Flora)
   {
      TESFlora *flora = DYNAMIC_CAST(thisObject, TESForm, TESFlora);
      if (flora)
      {
         TESForm *form = (TESForm *)flora->produce.produce;

         // If the ingredient is actually an ingredient
         if (form->formType == kFormType_Ingredient)
         {
            return DYNAMIC_CAST(flora->produce.produce, TESForm, IngredientItem);
         }

         // If the ingredient is actually a levelitem (Harvest overhaul mod or a coin purse)
         else if (form->formType == kFormType_LeveledItem)
         {
            TESForm *itemform = GetIngredientFromLeveledList(form);

            if (!itemform)
            {
               return NULL;
            }
            else if (itemform->formType == kFormType_Ingredient)
            {
               IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
               return ingredient;
            }
         }
         else if (form->formType == kFormType_List)
         {
            BGSListForm *lvli = DYNAMIC_CAST(form, TESForm, BGSListForm);

            // Get the first form and see if it is an ingredient
            if (lvli->forms.count > 0)
            {
               TESForm *itemform = (TESForm *)lvli->forms.entries[0];
               if (itemform)
               {
                  IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
                  return ingredient;
               }
            }
         }
      }
   }
   else if (thisObject->GetFormType() == kFormType_Tree)
   {
      TESObjectTREE *tree = DYNAMIC_CAST(thisObject, TESForm, TESObjectTREE);
      if (tree)
      {
         TESForm *form = (TESForm *)tree->produce.produce;//DYNAMIC_CAST(tree->produce.produce, IngredientItem, TESForm);

         // If the ingredient is actually an ingredient
         if (form->formType == kFormType_Ingredient)
         {
            return DYNAMIC_CAST(tree->produce.produce, TESForm, IngredientItem);
         }

         // If the ingredient is actually a levelitem (Harvest overhaul mod or a coin purse)
         else if (form->formType == kFormType_LeveledItem)
         {
            TESForm *itemform = GetIngredientFromLeveledList(form);

            if (!itemform)
            {
               return NULL;
            }
            else if (itemform->formType == kFormType_Ingredient)
            {
               IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
               return ingredient;
            }
         }
         else if (form->formType == kFormType_List)
         {
            BGSListForm *lvli = DYNAMIC_CAST(form, TESForm, BGSListForm);

            // Get the first form and see if it is an ingredient
            if (lvli->forms.count > 0)
            {
               TESForm *itemform = (TESForm *)lvli->forms.entries[0];
               if (itemform)
               {
                  IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
                  return ingredient;
               }
            }
         }
      }
   }

   return NULL;
}

SpellItem* CAHZScaleform::GetSpellItem(TESForm *thisObject)
{
   if (!thisObject)
      return NULL;

   TESObjectREFR*reference = AHZGetReference(thisObject);
   if (reference)
   {
      thisObject = reference->baseForm;
   }

   return DYNAMIC_CAST(thisObject, TESForm, SpellItem);
}

AlchemyItem* CAHZScaleform::GetAlchemyItem(TESForm *thisObject)
{
   if (!thisObject)
      return NULL;

   TESObjectREFR*reference = AHZGetReference(thisObject);
   if (reference)
   {
      thisObject = reference->baseForm;
   }

   if (thisObject->GetFormType() == kFormType_Potion)
      return DYNAMIC_CAST(thisObject, TESForm, AlchemyItem);

   if (thisObject->GetFormType() == kFormType_Flora)
   {
      TESFlora *flora = DYNAMIC_CAST(thisObject, TESForm, TESFlora);
      if (flora)
      {
         TESForm *form = (TESForm *)flora->produce.produce;

         // If the food is actually food
         if (form->formType == kFormType_Potion)
         {
            return DYNAMIC_CAST(form, TESForm, AlchemyItem);
         }

         // If the food is actually a levelitem (Harvest overhaul mod or a coin purse)
         else if (form->formType == kFormType_LeveledItem)
         {
            TESForm *itemform = GetAlchemyItemFromLeveledList(form);

            if (!itemform)
            {
               return NULL;
            }
            else if (itemform->formType == kFormType_Potion)
            {
               AlchemyItem *alchmyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
               return alchmyItem;
            }
         }
         else if (form->formType == kFormType_List)
         {
            BGSListForm *lvli = DYNAMIC_CAST(form, TESForm, BGSListForm);

            // Get the first form and see if it is an ingredient
            if (lvli->forms.count > 0)
            {
               TESForm *itemform = (TESForm *)lvli->forms.entries[0];
               if (itemform)
               {
                  AlchemyItem *alchmyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
                  return alchmyItem;
               }
            }
         }
      }
   }
   else if (thisObject->GetFormType() == kFormType_Tree)
   {
      TESObjectTREE *tree = DYNAMIC_CAST(thisObject, TESForm, TESObjectTREE);
      if (tree)
      {
         TESForm *form = (TESForm *)tree->produce.produce;

         // If the produce is actually food
         if (form->formType == kFormType_Potion)
         {
            return DYNAMIC_CAST(form, TESForm, AlchemyItem);
         }

         // If the ingredient is actually a levelitem (Harvest overhaul mod or a coin purse)
         else if (form->formType == kFormType_LeveledItem)
         {
            TESForm *itemform = GetAlchemyItemFromLeveledList(form);

            if (!itemform)
            {
               return NULL;
            }
            else if (itemform->formType == kFormType_Potion)
            {
               AlchemyItem *alchmyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
               return alchmyItem;
            }
         }
         else if (form->formType == kFormType_List)
         {
            BGSListForm *lvli = DYNAMIC_CAST(form, TESForm, BGSListForm);

            // Get the first form and see if it is an ingredient
            if (lvli->forms.count > 0)
            {
               TESForm *itemform = (TESForm *)lvli->forms.entries[0];
               if (itemform)
               {
                  AlchemyItem *alchmyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
                  return alchmyItem;
               }
            }
         }
      }
   }

   return NULL;
}

bool CAHZScaleform::CanPickUp(UInt32 formType)
{
   return (formType == kFormType_Weapon ||
      formType == kFormType_Armor ||
      formType == kFormType_SoulGem ||
      formType == kFormType_Potion ||
      formType == kFormType_Misc ||
      formType == kFormType_Ingredient ||
      formType == kFormType_Book ||
      formType == kFormType_Ammo ||
      formType == kFormType_ScrollItem ||
      formType == kFormType_Outfit ||
      formType == kFormType_Key);
}

string CAHZScaleform::GetTargetName(TESForm *thisObject)
{
   string name;
   
   TESObjectREFR * reference = AHZGetReference(thisObject);

   if (!reference)
   {
      return name;
   }

   TESFullName* pFullName = DYNAMIC_CAST(reference->baseForm, TESForm, TESFullName);

   const char* displayName = reference->extraData.GetDisplayName(reference->baseForm);

   // If the name can be created
   if (displayName)
   {
      name.append(displayName);
   }
   // Use the base name
   else if (pFullName)
   {
      name.append(pFullName->name.data);
   }
   else // second attempt to get the name
   {
      name.append(reference->baseForm->GetFullName());
   }

   // If this is a soul gem, also get the gem size name
   if (reference->baseForm->formType == kFormType_SoulGem)
   {
      TESSoulGem *gem = DYNAMIC_CAST(reference->baseForm, TESForm, TESSoulGem);
      if (gem)
      {
         char * soulName = NULL;
         SettingCollectionMap	* settings = *g_gameSettingCollection;
         switch (gem->soulSize)
         {
         case 1: soulName = settings->Get("sSoulLevelNamePetty")->data.s; break;
         case 2: soulName = settings->Get("sSoulLevelNameLesser")->data.s; break;
         case 3: soulName = settings->Get("sSoulLevelNameCommon")->data.s; break;
         case 4: soulName = settings->Get("sSoulLevelNameGreater")->data.s; break;
         case 5: soulName = settings->Get("sSoulLevelNameGrand")->data.s; break;
         default: break;
         }

         if (soulName)
         {
            name.append(" (");
            name.append(soulName);
            name.append(")");
         }
      }
   }

   return name;
};

bool CAHZScaleform::GetIsBookAndWasRead(TESObjectREFR *theObject)
{
   if (!theObject)
      return false;

   if (theObject->baseForm->GetFormType() != kFormType_Book)
      return false;

   TESObjectBOOK *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectBOOK);
   if (item && ((item->data.flags & TESObjectBOOK::Data::kType_Read) == TESObjectBOOK::Data::kType_Read))
   {
      return true;
   }
   else
   {
      return false;
   }
}

static UInt32 lasttargetRef;
void CAHZScaleform::ProcessEnemyInformation(GFxFunctionHandler::Args * args)
{
   PlayerCharacter* pPC = (*g_thePlayer);
   UInt16 npcLevel = 0;
   UInt16 playerLevel = 0;

   if (pPC)
   {
      npcLevel = GetCurrentEnemyLevel();
      if (npcLevel >= 1)
      {
         playerLevel = CALL_MEMBER_FN(pPC, GetLevel)();
      }
   }

   GFxValue obj;
   args->movie->CreateObject(&obj);
   RegisterNumber(&obj, "EnemyLevel", npcLevel);
   RegisterNumber(&obj, "PlayerLevel", playerLevel);
   if (args->args[0].HasMember("outObj"))
   {
      args->args[0].SetMember("outObj", &obj);
   }
}

string CAHZScaleform::GetArmorWeightClass(TESObjectREFR *theObject)
{
   string desc;

   if (!theObject)
      return desc;

   if (theObject->baseForm->GetFormType() != kFormType_Armor)
      return desc;

   TESObjectARMO *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectARMO);
   if (!item)
      return desc;

   ActorValueList * avList = ActorValueList::GetSingleton();
   if (avList && item->bipedObject.data.weightClass <= 1)
   {
      // Utilize the AV value to get the localized name for "Light Armor"
      if (item->bipedObject.data.weightClass == 0)
      {
         ActorValueInfo * info = avList->GetActorValue(12);
         if (info)
         {
            TESFullName *fname = DYNAMIC_CAST(info, ActorValueInfo, TESFullName);
            if (fname && fname->name.data)
            {
               desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">     ");
               desc.append(fname->name.data);
               desc.append("<\\FONT>");
            }
         }
      }

      // Utilize the AV value to get the localized name for "Heavy Armor"
      else if (item->bipedObject.data.weightClass == 1)
      {
         ActorValueInfo * info = avList->GetActorValue(11);
         if (info)
         {
            TESFullName *fname = DYNAMIC_CAST(info, ActorValueInfo, TESFullName);
            if (fname && fname->name.data)
            {
               desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">     ");
               desc.append(fname->name.data);
               desc.append("<\\FONT>");
            }
         }
      }
   }
   return desc;
};

string CAHZScaleform::GetValueToWeight(TESObjectREFR *theObject, const char * stringFromHUD, const char * vmTranslated)
{
	string desc;

	if (!theObject)
		return desc;

	if (!theObject->baseForm)
		return desc;

	if (!stringFromHUD)
		return desc;

	//<TEXTFORMAT INDENT="0" LEFTMARGIN="0" RIGHTMARGIN="0" LEADING="2"><P ALIGN="CENTER"><FONT FACE="$EverywhereMediumFont" SIZE="15" COLOR="#999999" KERNING="0">WEIGHT </FONT><FONT FACE="$EverywhereBoldFont" SIZE="24" COLOR="#FFFFFF" KERNING="0">0.5</FONT><FONT FACE="$EverywhereMediumFont" SIZE="15" COLOR="#999999" KERNING="0">      VALUE </FONT><FONT FACE="$EverywhereBoldFont" SIZE="24" COLOR="#FFFFFF" KERNING="0">21</FONT></P></TEXTFORMAT>

	// Using regex from the HUD string to extract the value and weight values.  The SKSE version are either broken or unreliable
	std::regex rgx(R"(\s+([0-9]*\.?[0-9]+))");
	std::smatch match;
	string s = stringFromHUD;
	const string cs = const_cast<string &>(s);
	vector<string> parts;

	while (regex_search(s, match, rgx))
	{
		if (!match.size())
		{
			return desc;
		}

		parts.push_back(match[0]);

		s = match.suffix();
	}

	if (parts.size() < 2)
	{
		return desc;
	}

	// The fixed positions of the matches (containing groups)
	string weight = parts[parts.size() - 2];
	string value = parts[parts.size() - 1];
	char *end;

	float weightValue = strtof(weight.c_str(), &end);
	float valueValue = strtof(value.c_str(), &end);

	// Don't show a neg or 0 ratio, its pointless
	if (weightValue <= 0.0 || valueValue <= 0.0)
	{
		return desc;
	}

	float vW = valueValue / weightValue;

	// Add the VW label
	desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">     ");
	desc.append(vmTranslated);
	desc.append(" <\\FONT>");

	char floatHold[64];
	size_t size = 64;

	//Rounding trick
	sprintf_s(floatHold, size, "%.2f", vW);
	vW = strtof(floatHold, &end);

	if (vW < 1.0)
	{
		sprintf_s(floatHold, size, "%.1g", vW);
	}
	else
	{
		sprintf_s(floatHold, size, "%.0f", vW);
	}

	desc.append("<FONT FACE=\"$EverywhereBoldFont\"SIZE=\"24\"COLOR=\"#FFFFFF\"KERNING=\"0\">");
	desc.append(floatHold);
	desc.append("<\\FONT>");

	return desc;


	//string desc;

	//if (!theObject)
	//	return desc;

	//if (!theObject->baseForm)
	//	return desc;

	//if (!stringFromHUD)
	//	return desc;

	//char *end;
	//float weightValue = 0.0;
	//float valueValue = 0.0;
	//std::istringstream iss(stringFromHUD);
	//std::string throwaway;

	//vector<string> parts;
	//int i = 0;
	//// Get the weight and value from the HUD text since there is no decoded way (reliably) to get the value for all forms and references
	//do 
	//{
	//	parts.push_back("");
	//} while (iss >> parts[i++]); // stream the different fields.  THe weight and height are the last
	//
	//if (parts.size() < 4)
	//{
	//	return desc;
	//}

	//// Remove the last empty string if one exists
	//if (parts[parts.size() - 1] == "")
	//{
	//	parts.pop_back();
	//}

	//// check the size again
	//if (parts.size() < 4)
	//{
	//	return desc;
	//}

	//// The last value should be the "Value"
	//// The third from last should be the weight
	//weightValue = atof(parts[parts.size() - 3].c_str());
	//valueValue = atof(parts[parts.size() - 1].c_str());

	//// Don't show a neg or 0 ratio, its pointless
	//if ((mRound(weightValue * 100) / 100) <= 0.0 || (mRound(valueValue * 100) / 100) <= 0.0)
	//{
	//	return desc;
	//}

	//float vW = valueValue / weightValue;

	//// Add the VW label
	//desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">     ");
	//desc.append(vmTranslated);
	//desc.append(" <\\FONT>");

	//char floatHold[64];
	//size_t size = 64;

	////Rounding trick
	//sprintf_s(floatHold, size, "%.2f", vW);
	//vW = strtof(floatHold, &end);

	//if (vW < 1.0)
	//{
	//	sprintf_s(floatHold, size, "%.1g", vW);
	//}
	//else
	//{
	//	sprintf_s(floatHold, size, "%.0f", vW);
	//}

	//desc.append("<FONT FACE=\"$EverywhereBoldFont\"SIZE=\"24\"COLOR=\"#FFFFFF\"KERNING=\"0\">");
	//desc.append(floatHold);
	//desc.append("<\\FONT>");
 //  
	//return desc;
};

string CAHZScaleform::GetBookSkill(TESObjectREFR *theObject)
{
   string desc;
   if (theObject->baseForm->GetFormType() == kFormType_Book)
   {
      TESObjectBOOK *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectBOOK);

      if (!item)
         return desc;

      // If this is a spell book, then it is not a skill book
      if ((item->data.flags & TESObjectBOOK::Data::kType_Spell) == TESObjectBOOK::Data::kType_Spell)
         return desc;

      if (((item->data.flags & TESObjectBOOK::Data::kType_Skill) == TESObjectBOOK::Data::kType_Skill) &&
         item->data.teaches.skill)
      {
         ActorValueList * avList = ActorValueList::GetSingleton();
         if (avList)
         {
            ActorValueInfo * info = avList->GetActorValue(item->data.teaches.skill);
            if (info)
            {
               TESFullName *fname = DYNAMIC_CAST(info, ActorValueInfo, TESFullName);
               if (fname && fname->name.data)
               {
                  desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">       ");
                  desc.append(fname->name.data);
                  desc.append("<\\FONT>");
               }
            }
         }
      }
   }
   return desc;
}

void CAHZScaleform::AppendDescription(TESDescription *desObj, TESForm *parent, std::string& description)
{
   BSString bsDescription;
   string tempString = "";

   if (parent->GetFormType() == kFormType_Book)
   {
      CALL_MEMBER_FN(desObj, Get)(&bsDescription, parent, 0x4D414E43);
      if (&bsDescription)
      {
         tempString.clear();
         tempString.append(bsDescription.Get());
         if (tempString != "LOOKUP FAILED!" && tempString.length() > 1)
         {
            string formatted = "";
            FormatDescription(tempString, formatted);
            description.append(formatted);
         }
      }
   }
   else
   {
      BSString bsDescription2;
      TESDescription * desc = DYNAMIC_CAST(parent, TESForm, TESDescription);
      if (desc)
      {
         CALL_MEMBER_FN(desc, Get)(&bsDescription2, parent, 0x43534544);
         tempString.clear();
         if (&bsDescription2)
            tempString.append(bsDescription2.Get());
         if (tempString != "LOOKUP FAILED!" && tempString.length() > 1)
         {
            string formatted = "";
            FormatDescription(tempString, formatted);
            description.append(formatted);
         }
         else
         {
            CALL_MEMBER_FN(desc, Get)(&bsDescription2, parent, 0);
            tempString.clear();
            if (&bsDescription2)
               tempString.append(bsDescription2.Get());
            if (tempString != "LOOKUP FAILED!" && tempString.length() > 1)
            {
               string formatted = "";
               FormatDescription(tempString, formatted);
               description.append(formatted);
            }
         }
      }
   }
}

string CAHZScaleform::GetEffectsDescription(TESObjectREFR *theObject)
{
   BSString description;
   string effectDescription;
   string  desc;
   string effectsString;
   MagicItem * magicItem = NULL;

   if (!theObject)
      return desc;

   tArray<MagicItem::EffectItem*> *effectList = NULL;
   SettingCollectionMap *settings = *g_gameSettingCollection;

   if (theObject->baseForm->GetFormType() == kFormType_Potion)
   {
      AlchemyItem *item = DYNAMIC_CAST(theObject->baseForm, TESForm, AlchemyItem);

      if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(theObject->extraData.GetByType(kExtraData_Enchantment))) // Enchanted
      {
         if (extraEnchant->enchant)
         {
            GetMagicItemDescription(extraEnchant->enchant, effectDescription);
            desc.append(effectDescription);
         }
      }

      if (item)
      {
         GetMagicItemDescription(item, effectDescription);
         desc.append(effectDescription);
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_Weapon)
   {
      TESObjectWEAP *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectWEAP);

      // If there was no effects, then display athe description if available
      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description, item, desc);
      }

      if (item && !desc.length())
      {
         //Get enchantment description
         if (item && item->enchantable.enchantment)
         {
            GetMagicItemDescription(item->enchantable.enchantment, effectDescription);
            desc.append(effectDescription);
         }

         // Items modified by the player
         else if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(theObject->extraData.GetByType(kExtraData_Enchantment))) // Enchanted
         {
            if (extraEnchant->enchant)
            {
               GetMagicItemDescription(extraEnchant->enchant, effectDescription);
               desc.append(effectDescription);
            }
         }
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_Armor)
   {
      TESObjectARMO *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectARMO);

      // If there was no effects, then display athe description if available
      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description, item, desc);
      }

      if (item && !desc.length())
      {
         //Get enchantment description
         if (item && item->enchantable.enchantment)
         {
            GetMagicItemDescription(item->enchantable.enchantment, effectDescription);
            desc.append(effectDescription);
         }

         // Items modified by the player
         else if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(theObject->extraData.GetByType(kExtraData_Enchantment))) // Enchanted
         {
            if (extraEnchant->enchant)
            {
               GetMagicItemDescription(extraEnchant->enchant, effectDescription);
               desc.append(effectDescription);
            }
         }
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_Ammo)
   {
      TESAmmo *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESAmmo);

      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description, item, desc);
      }

      if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(theObject->extraData.GetByType(kExtraData_Enchantment))) // Enchanted
      {
         if (extraEnchant->enchant)
         {
            GetMagicItemDescription(extraEnchant->enchant, effectDescription);
            desc.append(effectDescription);
         }
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_Book)
   {
      TESObjectBOOK *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectBOOK);

      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description2, item, desc);
      }

      if (item &&
         ((item->data.flags & TESObjectBOOK::Data::kType_Spell) == TESObjectBOOK::Data::kType_Spell) && !desc.length())
      {
         if (item->data.teaches.spell)
         {
            GetMagicItemDescription(item->data.teaches.spell, effectDescription);
            desc.append(effectDescription);
         }
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_ScrollItem)
   {
      ScrollItem *item = DYNAMIC_CAST(theObject->baseForm, TESForm, ScrollItem);
      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description, item, desc);

         if (!desc.length())
         {
            GetMagicItemDescription(item, effectDescription);
            desc.append(effectDescription);
         }
      }
   }
   return desc;
};

void CAHZScaleform::ProcessTargetEffects(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   TESObjectREFR * pTargetReference = targetObject;
   AlchemyItem *alchemyItem = NULL;
   SpellItem *spellItem = NULL;
   IngredientItem *ingredientItem = NULL;
   string name;

   if (!args)
   {
      return;
   }

   bool calculateInvenotry = args->args[1].GetBool();

   if (!calculateInvenotry)
   {
      args->args[0].DeleteMember("inventoryObj");
   }

   // No valid reference
   if (!pTargetReference)
   {
      args->args[0].DeleteMember("effectsObj");
      args->args[0].DeleteMember("ingredientObj");
      args->args[0].DeleteMember("inventoryObj");
      return;
   }

   TESForm *targetForm = AHZGetForm(pTargetReference);

   // See if its an ingredient.  Note they are formated differently with known effects;
   if ((ingredientItem = GetIngredient(targetForm)) != NULL)
   {
      args->args[0].DeleteMember("effectsObj");
      BuildIngredientObject(ingredientItem, args);

      if (calculateInvenotry)
      {
         BuildInventoryObject(ingredientItem, args);
      }

      return;
   }

   // See if its harvestable food
   else if ((alchemyItem = GetAlchemyItem(targetForm)) != NULL)
   {
      string effectDescription;
      GetMagicItemDescription(alchemyItem, effectDescription);
      name.append(effectDescription);

      if (calculateInvenotry)
      {
         BuildInventoryObject(alchemyItem, args);
      }
   }

   // Spell items like blessings
   else if ((spellItem = GetSpellItem(targetForm)) != NULL)
   {
      AppendDescription(&(spellItem->description), spellItem, name);

      if (!name.length())
      {
         string effectDescription;
         GetMagicItemDescription(spellItem, effectDescription);
         name.append(effectDescription);
      }

      if (calculateInvenotry)
      {
         BuildInventoryObject(spellItem, args);
      }
   }
   else //For all effects from books, potions, weapon enchantments, etc.
   {
      // Get the effects description if it exists for this object
      name = GetEffectsDescription(pTargetReference);

      if (calculateInvenotry)
      {
         BuildInventoryObject(targetForm, args);
      }
   }

   // If the name contains a string
   if (name.length())
   {
      GFxValue obj;
      args->movie->CreateObject(&obj);

      name = CAHZUtilities::trim(name);

      RegisterString(&obj, args->movie, "effectsDescription",  name.c_str());

      // Add the object to the scaleform function
      args->args[0].SetMember("effectsObj", &obj);
   }
   else
   {
      args->args[0].DeleteMember("effectsObj");
   }
};

void CAHZScaleform::ProcessArmorClass(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   TESObjectREFR * pTargetReference = targetObject;
   static string weightClass;

   // If the target is not valid or it can't be picked up by the player
   if (!pTargetReference)
   {
      SetResultString(args, "");
      return;
   }

   weightClass.clear();
   weightClass.append(GetArmorWeightClass(pTargetReference).c_str());

   SetResultString(args, weightClass.c_str());
};

void CAHZScaleform::ProcessValueToWeight(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   TESObjectREFR * pTargetReference = targetObject;
   static string valueToWeight;

   // If the target is not valid or it can't be picked up by the player
   if (!pTargetReference)
   {
      SetResultString(args, "");
      return;
   }

   valueToWeight.clear();
   valueToWeight.append(GetValueToWeight(pTargetReference, args->args[0].GetString(), args->args[1].GetString()).c_str());

   SetResultString(args, valueToWeight.c_str());
};

void CAHZScaleform::ProcessBookSkill(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   TESObjectREFR * pTargetReference = targetObject;
   static string bookSkill;

   // If the target is not valid or it can't be picked up by the player
   if (!pTargetReference)
   {
      SetResultString(args, "");
      return;
   }

   bookSkill.clear();
   bookSkill.append(GetBookSkill(pTargetReference).c_str());

   SetResultString(args,
      bookSkill.c_str());
};

void CAHZScaleform::SetResultString(GFxFunctionHandler::Args *args, const char * str)
{
   args->result->SetString(str);
};

void CAHZScaleform::ReplaceStringInPlace(std::string& subject, const std::string& search,
   const std::string& replace)
{
   size_t pos = 0;
   while ((pos = subject.find(search, pos)) != std::string::npos)
   {
      subject.replace(pos, search.length(), replace);
      pos += replace.length();
   }
};

void CAHZScaleform::ProcessTargetObject(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   TESObjectREFR * pTargetReference = targetObject;
   float totalArmorOrWeapon = 0.0;
   float difference = 0.0;
   float totalWarmthRating = 0.0;
   float warmthDifference = 0.0;
   bool isSurvivalMode = false;
   float warmthRating = 0.0;

   if (!args)
   {
      return;
   }

   if (!targetObject)
   {
      args->args[0].DeleteMember("targetObj");
      return;
   }

   GFxValue obj;
   args->movie->CreateObject(&obj);

   if (pTargetReference->baseForm->GetFormType() == kFormType_Weapon ||
      pTargetReference->baseForm->GetFormType() == kFormType_Ammo)
   {
      TESForm *form = NULL;
      TESAmmo *ammo = NULL;

      // If ammo is NULL, it is OK
      totalArmorOrWeapon = GetTotalActualWeaponDamage();
      difference = GetWeaponDamageDiff(pTargetReference);
   }
   else if (pTargetReference->baseForm->GetFormType() == kFormType_Armor)
   {
      totalArmorOrWeapon = GetTotalActualArmorRating();
      difference = GetArmorRatingDiff(pTargetReference);

      if (IsSurvivalMode())
      {
         isSurvivalMode = true;
         totalWarmthRating = GetTotalWarmthRating();
         warmthDifference = GetWarmthRatingDiff(pTargetReference);
         warmthRating = GetArmorWarmthRating(pTargetReference);
      }

   }

   // Enter the data into the Scaleform function
   RegisterNumber(&obj, "ratingOrDamage", totalArmorOrWeapon);
   RegisterNumber(&obj, "difference", difference);
   RegisterNumber(&obj, "totalWarmthRating", totalWarmthRating);
   RegisterNumber(&obj, "warmthRating", warmthRating);
   RegisterNumber(&obj, "warmthDifference", warmthDifference);
   RegisterBoolean(&obj, "isSurvivalMode", isSurvivalMode);

   float weight = CALL_MEMBER_FN(pTargetReference, GetWeight)();
   if (pTargetReference->extraData.HasType(kExtraData_Count))
   {
      ExtraCount* xCount = static_cast<ExtraCount*>(pTargetReference->extraData.GetByType(kExtraData_Count));
      if (xCount)
      {
         weight = weight * (float)(SInt16)(xCount->count & 0x7FFF);
      }
   }

   RegisterNumber(&obj, "objWeight", weight);

   // Used by the scaleform script to know if this is a weapon, armor, or something else
   RegisterNumber(&obj, "formType", pTargetReference->baseForm->GetFormType());
   args->args[0].SetMember("targetObj", &obj);
};

void CAHZScaleform::BuildIngredientObject(IngredientItem* ingredient, GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   // If no ingredient, then we are done here
   if (!ingredient)
   {
      args->args[0].DeleteMember("ingredientObj");
      return;
   }

   string strings[4];

   // Not all ingredients have 4 effects
   UInt32 effectsCount = ingredient->effectItemList.count;

   for (int i = 0; i < 4; i++)
   {
      strings[i].clear();
      if (GetIsNthEffectKnown(ingredient, i))
      {
         MagicItem::EffectItem* pEI = NULL;
         ingredient->effectItemList.GetNthItem(i, pEI);
         if (pEI)
         {
            TESFullName* pFullName = DYNAMIC_CAST(pEI->mgef, TESForm, TESFullName);
            if (pFullName)
            {
               strings[i].append(pFullName->name.data); 
            }
         }
      }
   }
   GFxValue obj2;
   args->movie->CreateObject(&obj2);

   if (effectsCount >= 1)
      RegisterString(&obj2, args->movie, "effect1", strings[0].c_str());

   if (effectsCount >= 2)
      RegisterString(&obj2, args->movie, "effect2", strings[1].c_str());

   if (effectsCount >= 3)
      RegisterString(&obj2, args->movie, "effect3", strings[2].c_str());

   if (effectsCount >= 4)
      RegisterString(&obj2, args->movie, "effect4", strings[3].c_str());
   args->args[0].SetMember("ingredientObj", &obj2);
};

void CAHZScaleform::BuildInventoryObject(TESForm* form, GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   // Used to store the name
   string name;

   // Used to store the count of the item
   UInt32 itemCount;

   TESObjectREFR * reference = AHZGetReference(form);

   if (reference)
   {
      // Get the number of this in the inventory
      itemCount = CAHZPlayerInfo::GetItemAmount(reference->baseForm->formID);
      name = CAHZScaleform::GetTargetName(reference);
   }
   else if (form)
   {
      // Get the number of this in the inventory
      itemCount = CAHZPlayerInfo::GetItemAmount(form->formID);
      TESFullName* pFullName = DYNAMIC_CAST(form, TESForm, TESFullName);
      if (pFullName)
      {
         name.append(pFullName->name.data);
      }
   }

   // If the name contains a string
   if (name.length())
   {
      GFxValue obj;
      args->movie->CreateObject(&obj);

      RegisterString(&obj, args->movie, "inventoryName", name.c_str());
      RegisterNumber(&obj, "inventoryCount", itemCount);

      // Add the object to the scaleform function
      args->args[0].SetMember("inventoryObj", &obj);
   }
   else
   {
      args->args[0].DeleteMember("inventoryObj");
   }
};

void CAHZScaleform::RegisterString(GFxValue * dst, GFxMovieView * view, const char * name, const char * str)
{
   GFxValue	fxValue;
   fxValue.SetString(str);
   dst->SetMember(name, &fxValue);
};

void CAHZScaleform::RegisterNumber(GFxValue * dst, const char * name, double value)
{
   GFxValue	fxValue;
   fxValue.SetNumber(value);
   dst->SetMember(name, &fxValue);
};

void CAHZScaleform::RegisterBoolean(GFxValue * dst, const char * name, bool value)
{
   GFxValue	fxValue;
   fxValue.SetBool(value);
   dst->SetMember(name, &fxValue);
};

void CAHZScaleform::ProcessValidTarget(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   TESObjectREFR * pTargetReference = targetObject;

   if (!args)
   {
      return;
   }

   if (!pTargetReference)
   {
      // return false, indicating that the target object is not valid for acquiring data
      args->result->SetBool(false);
      args->args[0].DeleteMember("dataObj");
      return;
   }

   bool canCarry = false;

   TESForm *targetForm = AHZGetForm(pTargetReference);
   TESForm *spellItem = NULL;

   // If the target is not valid or it can't be picked up by the player
   if ((canCarry = (GetIngredient(targetForm) != NULL)) ||
      (canCarry = (GetAlchemyItem(targetForm) != NULL)) ||
      (canCarry = CanPickUp(pTargetReference->baseForm->GetFormType()) ||
      (pTargetReference->baseForm->GetFormType() == kFormType_Activator && targetForm)) ||
         ((spellItem = GetSpellItem(targetForm)) != NULL))
   {
      if (pTargetReference->baseForm->GetFormType() == kFormType_Activator && targetForm && !CanPickUp(targetForm->formType))
      {
         canCarry = false;
      }

      if (spellItem)
      {
         canCarry = false;
      }

      GFxValue obj;
      args->movie->CreateObject(&obj);

      RegisterBoolean(&obj, "canCarry", canCarry);

      // Add the object to the scaleform function
      args->args[0].SetMember("outObj", &obj);

      // return false, indicating that the target object is not valid for acquiring data
      args->result->SetBool(true);
   }
   else
   {
      // Add the object to the scaleform function
      args->args[0].DeleteMember("outObj");

      // The object is valid
      args->result->SetBool(false);
   }
}

void CAHZScaleform::ProcessPlayerData(GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   GFxValue obj;
   args->movie->CreateObject(&obj);

   UInt32 actorValue = LookupActorValueByName("InventoryWeight");
   float encumbranceNumber = ((*g_thePlayer)->actorValueOwner.GetCurrent(actorValue));
   actorValue = LookupActorValueByName("CarryWeight");
   float maxEncumbranceNumber = ((*g_thePlayer)->actorValueOwner.GetCurrent(actorValue));

   // Enter the data into the Scaleform function
   RegisterNumber(&obj, "encumbranceNumber", encumbranceNumber);
   RegisterNumber(&obj, "maxEncumbranceNumber", maxEncumbranceNumber);
   RegisterNumber(&obj, "goldNumber", CAHZPlayerInfo::GetGoldAmount());
   args->args[0].SetMember("playerObj", &obj);
}

void CAHZScaleform::GetMagicItemDescription(MagicItem * item, std::string& description)
{
   string outerString = "";
   description.clear();

   BSString temp;

   GetMagicItemDescription2(NULL, item, &temp);
   char *temp2 = ProcessSurvivalMode(&temp);

   description.append(temp.Get());
}

void CAHZScaleform::FormatDescription(std::string& unFormated, std::string& formatted)
{
   string outerString = "";
   formatted.clear();

   const char numberFormatter[] = "<font face = '$EverywhereMediumFont' size = '20' color = '#FFFFFF'>%.0f</font>";
   const char stringFormatter[] = "<font face = '$EverywhereMediumFont' size = '20' color = '#FFFFFF'>%s</font>";
   char tempformatter[1000];
   bool canBeAdded = true;

   std::regex survivalRegex("\\[SURV=.+\\]");
   std::smatch survivalMatch;
   const string survivalConst = const_cast<string &>(unFormated);
   if ((regex_search(survivalConst.begin(), survivalConst.end(), survivalMatch, survivalRegex)))
   {
      ReplaceStringInPlace(unFormated, "[SURV=", "");
      size_t offset = (size_t)(unFormated.length() - 1);
      size_t count = 1;
      unFormated.erase(offset, count);
      canBeAdded = IsSurvivalMode();
   }
   else
   {
      canBeAdded = true;
   }

   if (canBeAdded)
   {
      std::regex rgx("\\<\\d+?\\.?\\d*\\>|\\<\\w*\\>");
      std::smatch match;

      const string cs = const_cast<string &>(unFormated);
      string::const_iterator searchStart(cs.cbegin());
      string workingString = unFormated;

      while (regex_search(searchStart, cs.end(), match, rgx))
      {
         string temps = match[0];
         ReplaceStringInPlace(temps, "<", "");
         ReplaceStringInPlace(temps, ">", "");
         string origMatch = match[0];

         sprintf_s(tempformatter, 1000, stringFormatter, temps.c_str());
         ReplaceStringInPlace(workingString, origMatch, tempformatter);

         searchStart += match.position() + match.length();
      }
      outerString.append(workingString);
   }

   //TrimHelper(outerString);
   formatted.append(outerString);
}