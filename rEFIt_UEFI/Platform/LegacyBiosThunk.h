/*++

Copyright (c) 2006 - 2008, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:
  LegacyBiosThunk.h

Abstract:

--*/
#ifndef _LEGACY_BIOS_THUNK_H_
#define _LEGACY_BIOS_THUNK_H_

#include <Uefi.h>

//
// Driver Consumed Protocol Prototypes
//
#include <Protocol/DevicePath.h>
#include <Protocol/PciIo.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/ComponentName.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/UgaDraw.h>
#include <Protocol/VgaMiniPort.h>
#include <Protocol/Legacy8259.h>
#include <Protocol/EdidActive.h>
#include <Protocol/EdidDiscovered.h>
#include <Protocol/DevicePath.h>

#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>

#include <IndustryStandard/Pci.h>

#define EFI_SEGMENT(_Adr)     (UINT16) ((UINT16) (((UINTN) (_Adr)) >> 4) & 0xf000)
#define EFI_OFFSET(_Adr)      (UINT16) (((UINT16) ((UINTN) (_Adr))) & 0xffff)

//
// Function declarations
//
/*EFI_STATUS
EFIAPI
InitializeLegacyBiosThunk (
  IN EFI_HANDLE                       ImageHandle,
  IN EFI_SYSTEM_TABLE                 *SystemTable
  );*/

VOID
InitializeBiosIntCaller (
//  THUNK_CONTEXT     *ThunkContext
  );

VOID
InitializeInterruptRedirection (
//  IN  EFI_LEGACY_8259_PROTOCOL  *Legacy8259
  );

BOOLEAN
EFIAPI
LegacyBiosInt86 (
//  IN  EFI_LEGACY_BIOS_THUNK_PROTOCOL  *This,
  IN  UINT8                         BiosInt,
  IN  IA32_REGISTER_SET				*Regs
  );

BOOLEAN
EFIAPI
LegacyBiosFarCall86 (
//  IN  EFI_LEGACY_BIOS_THUNK_PROTOCOL  *This,
  IN  UINT16                        Segment,
  IN  UINT16                        Offset,
  IN  IA32_REGISTER_SET				*Regs //,
//  IN  VOID                          *Stack,
//  IN  UINTN                         StackSize
  );

#endif
