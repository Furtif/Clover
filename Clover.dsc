## @file
#  An EFI/Framework Emulation Platform with UEFI HII interface supported.
#
#  Developer's UEFI Emulation. DUET provides an EFI/UEFI IA32/X64 environment on legacy BIOS,
#  to help developing and debugging native EFI/UEFI drivers.
#
#  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution. The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
##
[Defines]
  PLATFORM_NAME                  = Clover
  PLATFORM_GUID                  = 199E24E0-0989-42aa-87F2-611A8C397E72
  PLATFORM_VERSION               = 0.92
  DSC_SPECIFICATION              = 0x00010006
  OUTPUT_DIRECTORY               = Build/Clover
  SUPPORTED_ARCHITECTURES        = X64|IA32
  BUILD_TARGETS                  = RELEASE|DEBUG
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = Clover/Clover.fdf

  !ifndef OPENSSL_VERSION
    DEFINE OPENSSL_VERSION       = 1.0.1e
  !endif

################################################################################
#
# Library Class section - list of all Library Classes needed by this Platform.
#
################################################################################
[LibraryClasses]
  #
  # Entry point
  #
  PeimEntryPoint|MdePkg/Library/PeimEntryPoint/PeimEntryPoint.inf
  DxeCoreEntryPoint|MdePkg/Library/DxeCoreEntryPoint/DxeCoreEntryPoint.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  #
  # Basic
  #
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  #BaseMemoryLib|MdePkg/Library/UefiMemoryLib/UefiMemoryLib.inf
  #BaseMemoryLib|MdePkg/Library/BaseMemoryLibSse2/BaseMemoryLibSse2.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  CpuLib|MdePkg/Library/BaseCpuLib/BaseCpuLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  PciExpressLib|MdePkg/Library/BasePciExpressLib/BasePciExpressLib.inf
  #PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
  #PciExpressLib|MdePkg/Library/DxeRuntimePciExpressLib/DxeRuntimePciExpressLib.inf
  CacheMaintenanceLib|MdePkg/Library/BaseCacheMaintenanceLib/BaseCacheMaintenanceLib.inf
  #PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
  PeCoffLib|Clover/Library/VBoxPeCoffLib/VBoxPeCoffLib.inf
  PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  CustomizedDisplayLib|MdeModulePkg/Library/CustomizedDisplayLib/CustomizedDisplayLib.inf
  #
  # UEFI & PI
  #
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  UefiRuntimeLib|MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  #UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  UefiHiiServicesLib|Clover/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf
  #EfiFileLib|EmbeddedPkg/Library/EfiFileLib/EfiFileLib.inf
  #EblNetworkLib|EmbeddedPkg/Library/EblNetworkLib/EblNetworkLib.inf
  #EblCmdLib|EmbeddedPkg/Library/EblCmdLibNull/EblCmdLibNull.inf  
  FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
  SortLib|MdeModulePkg/Library/UefiSortLib/UefiSortLib.inf
  UefiCpuLib|UefiCpuPkg/Library/BaseUefiCpuLib/BaseUefiCpuLib.inf
!ifdef ENABLE_SECURE_BOOT
  OpensslLib|Clover/Library/OpensslLib/openssl-$(OPENSSL_VERSION)/OpensslLib.inf
  IntrinsicLib|Clover/Library/IntrinsicLib/IntrinsicLib.inf
!else
  OpensslLib|Clover/Library/OpensslLib/OpensslLibNull.inf
!endif
  
  #
  # Generic Modules
  #
  UefiUsbLib|MdePkg/Library/UefiUsbLib/UefiUsbLib.inf
  UefiScsiLib|MdePkg/Library/UefiScsiLib/UefiScsiLib.inf
  OemHookStatusCodeLib|MdeModulePkg/Library/OemHookStatusCodeLibNull/OemHookStatusCodeLibNull.inf
  #GenericBdsLib|IntelFrameworkModulePkg/Library/GenericBdsLib/GenericBdsLib.inf
  GenericBdsLib|Clover/Library/GenericBdsLib/GenericBdsLib.inf
  SecurityManagementLib|MdeModulePkg/Library/DxeSecurityManagementLib/DxeSecurityManagementLib.inf
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibNull/DxeCapsuleLibNull.inf
  #PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf
  NetLib|MdeModulePkg/Library/DxeNetLib/DxeNetLib.inf
  #
  # Platform
  #
  #PlatformBdsLib|DuetPkg/Library/DuetBdsLib/PlatformBds.inf
  PlatformBdsLib|Clover/Library/OsxBdsPlatformLib/PlatformBds.inf
  #TimerLib|DuetPkg/Library/DuetTimerLib/DuetTimerLib.inf
  TimerLib|Clover/Library/DuetTimerLib/DuetTimerLib.inf
  #
  # Misc
  #
  PerformanceLib|MdePkg/Library/BasePerformanceLibNull/BasePerformanceLibNull.inf
  DebugAgentLib|MdeModulePkg/Library/DebugAgentLibNull/DebugAgentLibNull.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
#  PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  LockBoxLib|MdeModulePkg/Library/SmmLockBoxLib/SmmLockBoxDxeLib.inf
  CpuExceptionHandlerLib|MdeModulePkg/Library/CpuExceptionHandlerLibNull/CpuExceptionHandlerLibNull.inf
  SmbusLib|MdePkg/Library/DxeSmbusLib/DxeSmbusLib.inf
  S3BootScriptLib|MdeModulePkg/Library/PiDxeS3BootScriptLib/DxeS3BootScriptLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
  ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf

  #SerialPortLib|PcAtChipsetPkg/Library/SerialIoLib/SerialIoLib.inf
  SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
  MtrrLib|UefiCpuPkg/Library/MtrrLib/MtrrLib.inf
  IoApicLib|PcAtChipsetPkg/Library/BaseIoApicLib/BaseIoApicLib.inf
  LocalApicLib|UefiCpuPkg/Library/BaseXApicLib/BaseXApicLib.inf
  #LocalApicLib|UefiCpuPkg/Library/BaseXApicX2ApicLib/BaseXApicX2ApicLib.inf
  
  #
  # To save size, use NULL library for DebugLib and ReportStatusCodeLib.
  # If need status code output, do library instance overriden as below DxeMain.inf does
  #
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf  
  ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf
  
  TpmMeasurementLib|MdeModulePkg/Library/TpmMeasurementLibNull/TpmMeasurementLibNull.inf
  AuthVariableLib|MdeModulePkg/Library/AuthVariableLibNull/AuthVariableLibNull.inf
  VarCheckLib|MdeModulePkg/Library/VarCheckLib/VarCheckLib.inf

  #
  # Our libs
  #
  MemLogLib|Clover/Library/MemLogLibDefault/MemLogLibDefault.inf
  VideoBiosPatchLib|Clover/Library/VideoBiosPatchLib/VideoBiosPatchLib.inf

[LibraryClasses.common.DXE_CORE]
  HobLib|MdePkg/Library/DxeCoreHobLib/DxeCoreHobLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  MemoryAllocationLib|MdeModulePkg/Library/DxeCoreMemoryAllocationLib/DxeCoreMemoryAllocationLib.inf

[LibraryClasses.common.PEIM]
  MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
  HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
  LockBoxLib|MdeModulePkg/Library/SmmLockBoxLib/SmmLockBoxPeiLib.inf

[LibraryClasses.IA32.PEIM, LibraryClasses.X64.PEIM]
  PeiServicesTablePointerLib|MdePkg/Library/PeiServicesTablePointerLibIdt/PeiServicesTablePointerLibIdt.inf

[LibraryClasses.common.DXE_DRIVER]
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf

[LibraryClasses.common.DXE_SMM_DRIVER]
  SmmServicesTableLib|MdePkg/Library/SmmServicesTableLib/SmmServicesTableLib.inf
  MemoryAllocationLib|MdePkg/Library/SmmMemoryAllocationLib/SmmMemoryAllocationLib.inf
  
 
  
###################################################################################################
#
# Components Section - list of the modules and components that will be processed by compilation
#                      tools and the EDK II tools to generate PE32/PE32+/Coff image files.
#
# Note: The EDK II DSC file is not used to specify how compiled binary images get placed
#       into firmware volume images. This section is just a list of modules to compile from
#       source into UEFI-compliant binaries.
#       It is the FDF file that contains information on combining binary files into firmware
#       volume images, whose concept is beyond UEFI and is described in PI specification.
#       Binary modules do not need to be listed in this section, as they should be
#       specified in the FDF file. For example: Shell binary (Shell_Full.efi), FAT binary (Fat.efi),
#       Logo (Logo.bmp), and etc.
#       There may also be modules listed in this section that are not required in the FDF file,
#       When a module listed here is excluded from FDF file, then UEFI-compliant binary will be
#       generated for it, but the binary will not be put into any firmware volume.
#
###################################################################################################
[Components]
	#DuetPkg/BootSector/BootSector.inf

  #DuetPkg/DxeIpl/DxeIpl.inf {
  Clover/OsxDxeIpl/DxeIpl.inf {
    <LibraryClasses>
      #
      # If no following overriden for ReportStatusCodeLib library class,
      # All other module can *not* output debug information even they are use not NULL library
      # instance for DebugLib and ReportStatusCodeLib
      #
      #ReportStatusCodeLib|MdeModulePkg/Library/DxeReportStatusCodeLib/DxeReportStatusCodeLib.inf
      ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf
  }
 #MdeModulePkg/Core/Dxe/DxeMain.inf {
 Clover/OsxDxeCore/DxeMain.inf {
    #
    # Enable debug output for DxeCore module, this is a sample for how to enable debug output
    # for a module. If need turn on debug output for other module, please copy following overriden
    # PCD and library instance to other module's override section.
    #
    <PcdsFixedAtBuild>
      gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x0
      gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x82
      #0x82
      gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000042
      #0x80000042
    <LibraryClasses>
      BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
      MemoryAllocationLib|MdeModulePkg/Library/DxeCoreMemoryAllocationLib/DxeCoreMemoryAllocationLib.inf
     # DebugLib|IntelFrameworkModulePkg/Library/PeiDxeDebugLibReportStatusCode/PeiDxeDebugLibReportStatusCode.inf
     # ReportStatusCodeLib|DuetPkg/Library/DxeCoreReportStatusCodeLibFromHob/DxeCoreReportStatusCodeLibFromHob.inf
     DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
 	 ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf
 	 PeCoffLib|Clover/Library/VBoxPeCoffLib/VBoxPeCoffLib.inf

  }

  MdeModulePkg/Universal/PCD/Dxe/Pcd.inf
  MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  MdeModulePkg/Universal/MonotonicCounterRuntimeDxe/MonotonicCounterRuntimeDxe.inf

  #DuetPkg/FSVariable/FSVariable.inf
  MdeModulePkg/Universal/Variable/EmuRuntimeDxe/EmuVariableRuntimeDxe.inf
  MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
  MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/VarCheckUefiLib/VarCheckUefiLib.inf
  }

  MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  MdeModulePkg/Universal/MemoryTest/NullMemoryTestDxe/NullMemoryTestDxe.inf
  MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
  MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
    <PcdsPatchableInModule>
      gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|0
      gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|0
  }
  MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
  MdeModulePkg/Universal/SetupBrowserDxe/SetupBrowserDxe.inf
  MdeModulePkg/Universal/DisplayEngineDxe/DisplayEngineDxe.inf
  #MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  Clover/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  #MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf
  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  MdeModulePkg/Universal/SmbiosDxe/SmbiosDxe.inf
  DuetPkg/SmbiosGenDxe/SmbiosGen.inf
  #Clover/OsxSmbiosDxe/SmbiosDxe.inf
  #Clover/OemSmbiosGenDxe/SmbiosGen.inf

  #DuetPkg/EfiLdr/EfiLdr.inf {
  Clover/OsxEfiLdr/EfiLdr.inf {
    <LibraryClasses>
      DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
      BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
      
      #NULL|IntelFrameworkModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
      NULL|Clover/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  }
  #IntelFrameworkModulePkg/Universal/BdsDxe/BdsDxe.inf {
  Clover/OsxBdsDxe/BdsDxe.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  }
  MdeModulePkg/Universal/EbcDxe/EbcDxe.inf
  Clover/UefiCpuPkg/CpuIo2Dxe/CpuIo2Dxe.inf
  #UefiCpuPkg/CpuIo2Dxe/CpuIo2Dxe.inf
  #Clover/UefiCpuPkg/CpuDxe/CpuDxe.inf
  #UefiCpuPkg/CpuDxe/CpuDxe.inf
  Clover/CpuDxe/Cpu.inf
  PcAtChipsetPkg/8259InterruptControllerDxe/8259.inf {
      <PcdsFixedAtBuild>
      gPcAtChipsetPkgTokenSpaceGuid.Pcd8259LegacyModeMask|0xFFFC
  }
  #DuetPkg/AcpiResetDxe/Reset.inf
  Clover/AcpiReset/Reset.inf
  #DuetPkg/LegacyMetronome/Metronome.inf
  MdeModulePkg/Universal/Metronome/Metronome.inf
# EdkCompatibilityPkg/Compatibility/MpServicesOnFrameworkMpServicesThunk/MpServicesOnFrameworkMpServicesThunk.inf

  #Chipset
  #PcAtChipsetPkg/PcatRealTimeClockRuntimeDxe/PcatRealTimeClockRuntimeDxe.inf
  Clover/PcatRealTimeClockRuntimeDxe/PcatRealTimeClockRuntimeDxe.inf
  PcAtChipsetPkg/8254TimerDxe/8254Timer.inf
  PcAtChipsetPkg/HpetTimerDxe/HpetTimerDxe.inf
  #PcAtChipsetPkg/PciHostBridgeDxe/PciHostBridgeDxe.inf
  #DuetPkg/PciRootBridgeNoEnumerationDxe/PciRootBridgeNoEnumeration.inf
  Clover/PciRootBridgeDxe/PciRootBridge.inf
  #DuetPkg/PciBusNoEnumerationDxe/PciBusNoEnumeration.inf
  Clover/OsxPciBusNoEnumerationDxe/PciBusNoEnumeration.inf
  #MdeModulePkg/Bus/Pci/PciBusDxe/PciBusDxe.inf
  #Clover/PciBusDxe/PciBusDxe.inf
  MdeModulePkg/Bus/Pci/NvmExpressDxe/NvmExpressDxe.inf
  
  #DataHub
  #Clover/VBoxAppleSim/VBoxAppleSim.inf
  IntelFrameworkModulePkg/Universal/DataHubDxe/DataHubDxe.inf
  #IntelFrameworkModulePkg/Universal/DataHubStdErrDxe/DataHubStdErrDxe.inf
  
  # foreign file system support
  Clover/DriverOverride/DriverOverride.inf
  Clover/VBoxFsDxe/VBoxHfs.inf
  Clover/VBoxFsDxe/VBoxIso9660.inf
  #Clover/VBoxFsDxe/VBoxFsDxe.inf
  Clover/VBoxFsDxe/VBoxExt2.inf
  Clover/VBoxFsDxe/VBoxExt4.inf
  Clover/VBoxFsDxe/VBoxReiserFS.inf
  #EmbeddedPkg/Universal/MmcDxe/MmcDxe.inf
  #Clover/OsxMmcDxe/MmcDxe.inf
  Clover/FatPkg/EnhancedFatDxe/Fat.inf
  # FS from grub
!ifndef NO_GRUB_DRIVERS
  Clover/GrubFS/src/EXFAT.inf
  Clover/GrubFS/src/HFSPLUS.inf
  Clover/GrubFS/src/ISO9660.inf
  Clover/GrubFS/src/NTFS.inf
  Clover/GrubFS/src/UDF.inf
  #Clover/GrubFS/src/UFS.inf
  #Clover/GrubFS/src/UFS2.inf
  #Clover/GrubFS/src/XFS.inf
!endif

  #Video
  IntelFrameworkModulePkg/Bus/Pci/VgaMiniPortDxe/VgaMiniPortDxe.inf
  #Clover/VBoxVgaMiniPort/VgaMiniPortDxe.inf
  #IntelFrameworkModulePkg/Universal/Console/VgaClassDxe/VgaClassDxe.inf
  #Clover/VgaClassDxe/VgaClassDxe.inf
  #Clover/IntelGmaDxe/Gop.inf
  #DuetPkg/BiosVideoThunkDxe/BiosVideo.inf
  Clover/BiosVideo/BiosVideo.inf
  #Clover/BiosVideoAuto/BiosVideo.inf
  Clover/LegacyBios/VideoDxe/VideoDxe.inf

  # IDE/AHCI Support
!ifdef USE_BIOS_BLOCKIO
  Clover/LegacyBios/BlockIoDxe/BlockIoDxe.inf
!else
  #Clover/Trash/VBoxIdeControllerDxe/VBoxIdeControllerDxe.inf
  #Clover/Trash/VBoxIdeBusDxe/VBoxIdeBusDxe.inf
  #DuetPkg/SataControllerDxe/SataControllerDxe.inf
  Clover/SataControllerDxe/SataControllerDxe.inf
  #MdeModulePkg/Bus/Ata/AtaAtapiPassThru/AtaAtapiPassThru.inf
  Clover/AtaAtapi/AtaAtapiPassThru.inf
  #MdeModulePkg/Bus/Ata/AtaBusDxe/AtaBusDxe.inf
  Clover/AtaBus/AtaBusDxe.inf
  #MdeModulePkg/Bus/Scsi/ScsiBusDxe/ScsiBusDxe.inf
  Clover/DVDBus/ScsiBusDxe.inf
  #MdeModulePkg/Bus/Scsi/ScsiDiskDxe/ScsiDiskDxe.inf
  Clover/DVDDisk/ScsiDiskDxe.inf
  #IntelFrameworkModulePkg/Bus/Pci/IdeBusDxe/IdeBusDxe.inf
!endif

  # Usb Support
  MdeModulePkg/Bus/Pci/UhciDxe/UhciDxe.inf
  Clover/OhciDxe/OhciDxe.inf
  MdeModulePkg/Bus/Pci/EhciDxe/EhciDxe.inf
#  MdeModulePkg/Bus/Pci/XhciDxe/XhciDxe.inf
  Clover/Patches_for_EDK2/XhciDxe/XhciDxe.inf
#  MdeModulePkg/Bus/Usb/UsbBusDxe/UsbBusDxe.inf
  Clover/Patches_for_EDK2/UsbBusDxe/UsbBusDxe.inf
  MdeModulePkg/Bus/Usb/UsbKbDxe/UsbKbDxe.inf
  MdeModulePkg/Bus/Usb/UsbMassStorageDxe/UsbMassStorageDxe.inf
  MdeModulePkg/Bus/Usb/UsbMouseDxe/UsbMouseDxe.inf
  #Clover/Patches_for_EDK2/UsbMouseDxe/UsbMouseDxe.inf

  # ISA Support
  PcAtChipsetPkg/IsaAcpiDxe/IsaAcpi.inf
  IntelFrameworkModulePkg/Bus/Isa/IsaBusDxe/IsaBusDxe.inf
  #IntelFrameworkModulePkg/Bus/Isa/IsaSerialDxe/IsaSerialDxe.inf
  IntelFrameworkModulePkg/Bus/Isa/Ps2KeyboardDxe/Ps2keyboardDxe.inf
  #IntelFrameworkModulePkg/Bus/Isa/IsaFloppyDxe/IsaFloppyDxe.inf
  IntelFrameworkModulePkg/Bus/Isa/Ps2MouseAbsolutePointerDxe/Ps2MouseAbsolutePointerDxe.inf
  #IntelFrameworkModulePkg/Bus/Isa/Ps2MouseDxe/Ps2MouseDxe.inf
  Clover/Ps2MouseDxe/Ps2MouseDxe.inf
 
  # ACPI Support
  #MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf
  Clover/OsxAcpiTableDxe/AcpiTableDxe.inf
  #MdeModulePkg/Universal/Acpi/AcpiPlatformDxe/AcpiPlatformDxe.inf
  Clover/OsxAcpiPlatformDxe/AcpiPlatformDxe.inf

  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
  #MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  Clover/PartitionDxe/PartitionDxe.inf

  #FD
  #IntelFrameworkModulePkg/Universal/Acpi/AcpiS3SaveDxe/AcpiS3SaveDxe.inf
  #Clover/SaveResume/AcpiS3SaveDxe/AcpiS3SaveDxe.inf
  #MdeModulePkg/Universal/Acpi/S3SaveStateDxe/S3SaveStateDxe.inf
  #MdeModulePkg/Universal/Acpi/SmmS3SaveState/SmmS3SaveState.inf
  #MdeModulePkg/Universal/Acpi/BootScriptExecutorDxe/BootScriptExecutorDxe.inf
  #Clover/SaveResume/BootScriptExecutorDxe/BootScriptExecutorDxe.inf
  #UefiCpuPkg/Universal/Acpi/S3Resume2Pei/S3Resume2Pei.inf

  # Bios Thunk
  #IntelFrameworkModulePkg/Csm/BiosThunk/VideoDxe/VideoDxe.inf
  #IntelFrameworkModulePkg/Csm/LegacyBiosDxe/LegacyBiosDxe.inf
  #IntelFrameworkModulePkg/Csm/BiosThunk/BlockIoDxe/BlockIoDxe.inf
  #IntelFrameworkModulePkg/Csm/BiosThunk/KeyboardDxe/KeyboardDxe.inf
  Clover/BiosKeyboard/KeyboardDxe.inf
  #IntelFrameworkModulePkg/Universal/LegacyRegionDxe/LegacyRegionDxe.inf
  #MdeModulePkg/Universal/LegacyRegion2Dxe/LegacyRegion2Dxe.inf
  Clover/LegacyBios/Region2Dxe/LegacyRegion2Dxe.inf

  # Misc
  Clover/FSInject/FSInject.inf
  Clover/MsgLog/MsgLog.inf
!ifdef DEBUG_ON_SERIAL_PORT

  Clover/DumpUefiCalls/DumpUefiCalls.inf {
    <PcdsFixedAtBuild>
      gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x07
      gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0xFFFFFFFF
    <LibraryClasses>
      DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
      SerialPortLib|MdeModulePkg/Library/BaseSerialPortLib16550/BaseSerialPortLib16550.inf
  }

!else

  Clover/DumpUefiCalls/DumpUefiCalls.inf {
  	<LibraryClasses>
  		PeCoffLib|Clover/Library/VBoxPeCoffLib/VBoxPeCoffLib.inf
  }


!endif
  
  # Drivers for Aptio loading - should go to Clover's /EFI/drivers64UEFI dir
  Clover/OsxFatBinaryDrv/OsxFatBinaryDrv.inf


  # Drivers for Phoenix UEFI loading - should go to Clover's /EFI/drivers64UEFI dir
  Clover/EmuVariableUefi/EmuVariableRuntimeDxe.inf {
    <PcdsFixedAtBuild>
      gEfiMdeModulePkgTokenSpaceGuid.PcdEmuVariableNvStoreReserved|0
      gEfiMdeModulePkgTokenSpaceGuid.PcdMaxVariableSize|0x3000
      gEfiMdeModulePkgTokenSpaceGuid.PcdMaxHardwareErrorVariableSize|0x8000
      gEfiMdeModulePkgTokenSpaceGuid.PcdVariableStoreSize|0x40000
      gEfiMdeModulePkgTokenSpaceGuid.PcdVariableCollectStatistics|FALSE
      gEfiMdeModulePkgTokenSpaceGuid.PcdHwErrStorageSize|0x0000
  }

  Clover/AppleImageCodec/AppleImageCodec.inf
  #
  # Sample Application
  #
  #MdeModulePkg/Application/HelloWorld/HelloWorld.inf
  #MdeModulePkg/Application/VariableInfo/VariableInfo.inf
  #Clover/Sample/Application/Sample.inf
  #Clover/gptsync/gptsync.inf
  Clover/bdmesg_efi/bdmesg.inf
  
!ifdef DEBUG_ON_SERIAL_PORT

	Clover/rEFIt_UEFI/refit.inf {
  
	#
     # Enable debug output.
     #

	<PcdsFixedAtBuild>
 
		gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x07
 
		gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0xFFFFFFFF

	<LibraryClasses>
 
		SerialPortLib|MdeModulePkg/Library/BaseSerialPortLib16550/BaseSerialPortLib16550.inf

		DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf

	DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
	}
!else

	Clover/rEFIt_UEFI/refit.inf {
    <LibraryClasses>
      BaseMemoryLib|MdePkg/Library/UefiMemoryLib/UefiMemoryLib.inf      
  }
!endif

[Components.X64]
#!ifndef CLANG
  Clover/OsxAptioFixDrv/OsxAptioFixDrv.inf
  Clover/OsxAptioFixDrv/OsxAptioFix2Drv.inf
  Clover/OsxLowMemFixDrv/OsxLowMemFixDrv.inf
#!endif  
  #Clover/OsxAptioFixDrv/OsxAptioFixDrv.inf {
    #
    # Enable debug output.
    #
   # <PcdsFixedAtBuild>
   #   gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x07
   #   gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0xFFFFFFFF
   # <LibraryClasses>
   #   SerialPortLib|MdeModulePkg/Library/BaseSerialPortLib16550/BaseSerialPortLib16550.inf
   #   DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
   #   DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  #}

###################################################################################################
#
# BuildOptions Section - Define the module specific tool chain flags that should be used as
#                        the default flags for a module. These flags are appended to any 
#                        standard flags that are defined by the build process. They can be 
#                        applied for any modules or only those modules with the specific 
#                        module style (EDK or EDKII) specified in [Components] section.
#
###################################################################################################
[BuildOptions]

!ifdef ENABLE_VBIOS_PATCH_CLOVEREFI
  DEFINE VBIOS_PATCH_CLOVEREFI_FLAG = -DCLOVER_VBIOS_PATCH_IN_CLOVEREFI
!endif

!ifdef ONLY_SATA_0
  DEFINE ONLY_SATA_0_FLAG = -DONLY_SATA_0
!endif

!ifdef USE_BIOS_BLOCKIO
  DEFINE BLOCKIO_FLAG = -DUSE_BIOS_BLOCKIO
!ifdef DISABLE_USB_CONTROLLERS_WHEN_BLOCKIO
  DEFINE DISABLE_USB_CONTROLLERS = 1
!endif
!endif  

!ifdef DISABLE_USB_CONTROLLERS
  DEFINE NOUSB_FLAG = -DDISABLE_USB_SUPPORT
!endif  

!ifdef DISABLE_USB_SUPPORT
  DEFINE NOUSB_FLAG = -DDISABLE_USB_SUPPORT
!endif  

!ifdef DISABLE_UDMA_SUPPORT
  DEFINE NOUDMA_FLAG = -DDISABLE_UDMA_SUPPORT
!endif  

# Slice: I propose this flag always true
#!ifdef AMD_SUPPORT
  DEFINE AMD_FLAG = -DAMD_SUPPORT
#!endif  

!ifdef ENABLE_SECURE_BOOT
  DEFINE SECURE_BOOT_FLAG = -DENABLE_SECURE_BOOT
!endif

!ifdef ANDX86
  DEFINE ANDX86_FLAG = -DANDX86
!endif

#!ifdef LODEPNG
  DEFINE LODEPNG_FLAG = -DLODEPNG
#!endif

#!ifdef CHECK_FLAGS
  DEFINE CHECKS = -DCHECK_FLAGS
#!endif

!ifdef ENABLE_PS2MOUSE_LEGACYBOOT
  DEFINE PS2MOUSE_LEGACYBOOT_FLAG = -DENABLE_PS2MOUSE_LEGACYBOOT
!endif

!ifdef DEBUG_ON_SERIAL_PORT
  DEFINE DEBUG_ON_SERIAL_PORT_FLAG = -DDEBUG_ON_SERIAL_PORT
!endif

!ifdef DISABLE_LTO
	DEFINE DISABLE_LTO_FLAG = -fno-lto
!endif	

  DEFINE BUILD_OPTIONS=-DMDEPKG_NDEBUG -DCLOVER_BUILD $(VBIOS_PATCH_CLOVEREFI_FLAG) $(ONLY_SATA_0_FLAG) $(BLOCKIO_FLAG) $(NOUSB_FLAG) $(AMD_FLAG) $(SECURE_BOOT_FLAG) $(LODEPNG_FLAG) $(ANDX86_FLAG) $(PS2MOUSE_LEGACYBOOT_FLAG) $(DEBUG_ON_SERIAL_PORT_FLAG) $(NOUDMA_FLAG) $(CHECKS)

  #MSFT:*_*_*_CC_FLAGS  = /FAcs /FR$(@R).SBR /wd4701 /wd4703 $(BUILD_OPTIONS)
  MSFT:*_*_*_CC_FLAGS  = /FAcs /FR$(@R).SBR $(BUILD_OPTIONS) -Dinline=__inline
  
  XCODE:*_*_*_CC_FLAGS = -fno-unwind-tables -Os $(BUILD_OPTIONS) -Wno-msvc-include $(DISABLE_LTO_FLAG)
  GCC:*_*_*_CC_FLAGS   = $(BUILD_OPTIONS) 
  #-Wunused-but-set-variable
  # -Os -fno-omit-frame-pointer -maccumulate-outgoing-args
