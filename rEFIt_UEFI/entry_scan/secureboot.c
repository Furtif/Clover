/*
 * refit/scan/secureboot.c
 *
 * Copyright (c) 2006-2010 Christoph Pfisterer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *  * Neither the name of Christoph Pfisterer nor the names of the
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "entry_scan.h"

#include <Protocol/Security.h>
#include <Protocol/Security2.h>

#ifndef DEBUG_ALL
#define DEBUG_SECURE_BOOT 1
#else
#define DEBUG_SECURE_BOOT DEBUG_ALL
#endif

#if DEBUG_SECURE_BOOT == 0
#define DBG(...)
#else
#define DBG(...) DebugLog(DEBUG_SECURE_BOOT, __VA_ARGS__)
#endif

// Enable secure boot
VOID EnableSecureBoot(VOID)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  CHAR16     *ErrorString = NULL;
  // Check in setup mode
  if (gSettings.SecureBoot || !gSettings.SecureBootSetupMode) {
    return;
  }
  // TODO: Load keys
  // TODO: Enroll keys
  // Get this image's certificate
  if (!EFI_ERROR(Status)) {
    if (SelfLoadedImage != NULL) {
      UINTN  CloverSignatureSize = 0;
      VOID  *CloverSignature = GetImageSignatureList(SelfLoadedImage->ImageBase, SelfLoadedImage->ImageSize, &CloverSignatureSize, FALSE);
      if (CloverSignature != NULL) {
        if (CloverSignatureSize > 0) {
          // Enroll this image's certificate
          Status = AddImageSignatureList(CloverSignature, CloverSignatureSize);
        } else {
          // No signature list found
          Status = EFI_NOT_FOUND;
        }
        FreePool(CloverSignature);
      } else {
        // No signature list found
        Status = EFI_NOT_FOUND;
      }
    } else {
      // No signature list found
      Status = EFI_NOT_FOUND;
    }
    if (EFI_ERROR(Status)) {
      ErrorString = L"Clover does not have a certificate";
    }
  }
  // Reinit secure boot now
  InitializeSecureBoot();
  // Install the security policy hooks or redisable
  if (!EFI_ERROR(Status)) {
    Status = InstallSecureBoot();
    if (EFI_ERROR(Status)) {
      ErrorString = L"secure boot protocols not found";
    }
  }
  if (EFI_ERROR(Status)) {
    CHAR16 *Str = PoolPrint(L"Enabling secure boot failed because\n%s", ErrorString);
    if (Str != NULL) {
      AlertMessage(L"Enable Secure Boot", Str);
      FreePool(Str);
    }
    DBG("Enabling secure boot failed because %s! Status: %r\n", ErrorString, Status);
    DisableSecureBoot();
  }
}

CONST CHAR16 *SecureBootPolicyToStr(IN UINTN Policy)
{
  STATIC CONST CHAR16 *SecureBootPolicyStrings[] = {
    L"Deny",
    L"Allow",
    L"Query",
    L"Insert",
    L"WhiteList",
    L"BlackList",
    L"User",
  };
  STATIC CONST UINTN  SecureBootPolicyStringsCount = (sizeof(SecureBootPolicyStrings) / (sizeof(CONST CHAR16 *)));
  if (Policy < SecureBootPolicyStringsCount) {
    return SecureBootPolicyStrings[Policy];
  }
  return L"Deny";
}

STATIC VOID PrintSecureBootInfo(VOID)
{
  // Nothing to do if secure boot is disabled or in setup mode
  if (!gSettings.SecureBoot) {
    DBG("Secure Boot: %a\n", (gSettings.SecureBootSetupMode ? "Setup" : "Disabled"));
  } else {
    // Secure boot is enabled
    DBG("Secure Boot: %a\n", (gSettings.SecureBootSetupMode ? "Forced" : "Enabled"));
    DBG("Boot Policy: %s\n", SecureBootPolicyToStr(gSettings.SecureBootPolicy));
  }
}

// Disable secure boot
VOID DisableSecureBoot(VOID)
{
  // Check in user mode
  if (gSettings.SecureBootSetupMode || !gSettings.SecureBoot) {
    return;
  }
  UninstallSecureBoot();
  // TODO: Remove keys
  // Reinit secure boot now
  InitializeSecureBoot();
  PrintSecureBootInfo();
}

// The previous protocol functions
STATIC EFI_SECURITY_FILE_AUTHENTICATION_STATE gSecurityFileAuthentication;
STATIC EFI_SECURITY2_FILE_AUTHENTICATION      gSecurity2FileAuthentication;

// Pre check the secure boot policy
STATIC BOOLEAN EFIAPI
PrecheckSecureBootPolicy(IN OUT EFI_STATUS                     *AuthenticationStatus,
                         IN     CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
  CHAR16 *DevicePathStr;
  UINTN   Index;
  if ((AuthenticationStatus == NULL) || (DevicePath == NULL)) {
    return FALSE;
  }
  switch (gSettings.SecureBootPolicy) {
  case SECURE_BOOT_POLICY_ALLOW:
    // Allow all images
    *AuthenticationStatus = EFI_SUCCESS;
    return TRUE;

  case SECURE_BOOT_POLICY_WHITELIST:
    // Check the white list for this image
    DevicePathStr = FileDevicePathToStr(DevicePath);
    if (DevicePathStr == NULL) {
      return FALSE;
    }
    for (Index = 0; Index < gSettings.SecureBootWhiteListCount; ++Index) {
      if ((gSettings.SecureBootWhiteList[Index] != NULL) &&
          (StriStr(DevicePathStr, gSettings.SecureBootWhiteList[Index]) != NULL)) {
        // White listed
        *AuthenticationStatus = EFI_SUCCESS;
        return TRUE;
      }
    }
    return TRUE;

  case SECURE_BOOT_POLICY_BLACKLIST:
    // Check the black list for this image
    DevicePathStr = FileDevicePathToStr(DevicePath);
    if (DevicePathStr == NULL) {
      return FALSE;
    }
    for (Index = 0; Index < gSettings.SecureBootBlackListCount; ++Index) {
      if ((gSettings.SecureBootBlackList[Index] != NULL) &&
          (StriStr(DevicePathStr, gSettings.SecureBootBlackList[Index]) != NULL)) {
        // Black listed
        return TRUE;
      }
    }
    *AuthenticationStatus = EFI_SUCCESS;
    return TRUE;

  case SECURE_BOOT_POLICY_USER:
    DevicePathStr = FileDevicePathToStr(DevicePath);
    if (DevicePathStr == NULL) {
      return FALSE;
    }
    // Check the black list for this image
    for (Index = 0; Index < gSettings.SecureBootBlackListCount; ++Index) {
      if ((gSettings.SecureBootBlackList[Index] != NULL) &&
          (StriStr(DevicePathStr, gSettings.SecureBootBlackList[Index]) != NULL)) {
        // Black listed
        return TRUE;
      }
    }
    // Check the white list for this image
    for (Index = 0; Index < gSettings.SecureBootWhiteListCount; ++Index) {
      if ((gSettings.SecureBootWhiteList[Index] != NULL) &&
          (StriStr(DevicePathStr, gSettings.SecureBootWhiteList[Index]) != NULL)) {
        // White listed
        *AuthenticationStatus = EFI_SUCCESS;
        return TRUE;
      }
    }
    break;
  }
  return FALSE;
}

// Check the secure boot policy
STATIC BOOLEAN EFIAPI
CheckSecureBootPolicy(IN OUT EFI_STATUS                     *AuthenticationStatus,
                      IN     CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
                      IN     VOID                           *FileBuffer,
                      IN     UINTN                           FileSize)
{
  UINTN UserResponse = SECURE_BOOT_POLICY_DENY;
  switch (gSettings.SecureBootPolicy) {
  case SECURE_BOOT_POLICY_QUERY:
  case SECURE_BOOT_POLICY_USER:
    // Query user to allow image or deny image or insert image signature
    UserResponse = QuerySecureBootUser(DevicePath);
    DBG("VerifySecureBootImage: User selected policy: %s\n", SecureBootPolicyToStr(UserResponse));
    // Perform user action
    switch (UserResponse) {
    case SECURE_BOOT_POLICY_ALLOW:
      *AuthenticationStatus = EFI_SUCCESS;

    case SECURE_BOOT_POLICY_DENY:
    default:
      return TRUE;

    case SECURE_BOOT_POLICY_INSERT:
      // If this is forced mode then no insert
      if (gSettings.SecureBootSetupMode) {
        return TRUE;
      }
      break;
    }
    // Purposeful fallback to insert

  case SECURE_BOOT_POLICY_INSERT:
    // Insert image signature
    InsertSecureBootImage(DevicePath, FileBuffer, FileSize);
    *AuthenticationStatus = EFI_SUCCESS;
    return TRUE;

  case SECURE_BOOT_POLICY_ALLOW:
    // Allow all images
    *AuthenticationStatus = EFI_SUCCESS;
    return TRUE;

  case SECURE_BOOT_POLICY_DENY:
     // Deny all images
     return TRUE;
  }
  return FALSE;
}


// Override EFI_SECURITY_ARCH_PROTOCOL
EFI_STATUS EFIAPI
InternalFileAuthentication(IN CONST EFI_SECURITY_ARCH_PROTOCOL *This,
                           IN UINT32                            AuthenticationStatus,
                           IN CONST EFI_DEVICE_PATH_PROTOCOL   *DevicePath)
{
  EFI_STATUS Status = EFI_SECURITY_VIOLATION;
  // Check secure boot policy
  if (!PrecheckSecureBootPolicy(&Status, DevicePath)) {
    // Return original security policy
    Status = gSecurityFileAuthentication(This, AuthenticationStatus, DevicePath);
    if (EFI_ERROR(Status)) {
      // Check security policy on image
      CheckSecureBootPolicy(&Status, DevicePath, NULL, 0);
    }
  }
  if (EFI_ERROR(Status)) {
    CHAR16 *DevicePathStr = FileDevicePathToStr(DevicePath);
    if (DevicePathStr) {
      DBG("VerifySecureBootImage(1): %r %s\n", Status, DevicePathStr);
      FreePool(DevicePathStr);
    }
  }
  return Status;
}

// Override EFI_SECURITY2_ARCH_PROTOCOL
EFI_STATUS EFIAPI
Internal2FileAuthentication(IN CONST EFI_SECURITY2_ARCH_PROTOCOL *This,
                            IN CONST EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
                            IN VOID                              *FileBuffer,
                            IN UINTN                              FileSize,
                            IN BOOLEAN                            BootPolicy)
{
  EFI_STATUS Status = EFI_SECURITY_VIOLATION;
  // Check secure boot policy
  if (!PrecheckSecureBootPolicy(&Status, DevicePath)) {
    // Return original security policy
    Status = gSecurity2FileAuthentication(This, DevicePath, FileBuffer, FileSize, BootPolicy);
    if (EFI_ERROR(Status)) {
      CheckSecureBootPolicy(&Status, DevicePath, FileBuffer, FileSize);
    }
  }
  if (EFI_ERROR(Status)) {
    CHAR16 *DevicePathStr = FileDevicePathToStr(DevicePath);
    if (DevicePathStr) {
      DBG("VerifySecureBootImage(2): %r %s\n", Status, DevicePathStr);
      FreePool(DevicePathStr);
    }
  }
  return Status;
}

// Verify boot policy for image
EFI_STATUS VerifySecureBootImage(IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
  EFI_STATUS Status = EFI_SECURITY_VIOLATION;
  if (!PrecheckSecureBootPolicy(&Status, DevicePath)) {
    if (!CheckSecureBootPolicy(&Status, DevicePath, NULL, 0)) {
      Status = EFI_SUCCESS;
    }
  }
  if (EFI_ERROR(Status)) {
    CHAR16 *DevicePathStr = FileDevicePathToStr(DevicePath);
    if (DevicePathStr) {
      DBG("VerifySecureBootImage: %r %s\n", Status, DevicePathStr);
      FreePool(DevicePathStr);
    }
  }
  return Status;
}

// Install secure boot
EFI_STATUS InstallSecureBoot(VOID)
{
  EFI_STATUS                   Status;
  EFI_SECURITY_ARCH_PROTOCOL  *Security = NULL;
  EFI_SECURITY2_ARCH_PROTOCOL *Security2 = NULL;
  // Check if already installed
  if (gSecurityFileAuthentication) {
    return EFI_SUCCESS;
  }
  PrintSecureBootInfo();
  // Nothing to do if secure boot is disabled or in setup mode
  if (!gSettings.SecureBoot || gSettings.SecureBootSetupMode) {
    return EFI_SUCCESS;
  }
  // Locate security protocols
  gBS->LocateProtocol(&gEfiSecurity2ArchProtocolGuid, NULL, (VOID **)&Security2);
  Status = gBS->LocateProtocol(&gEfiSecurityArchProtocolGuid, NULL, (VOID **)&Security);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  if (Security == NULL) {
    return EFI_NOT_FOUND;
  }
  // Install policy hooks
  gSecurityFileAuthentication = Security->FileAuthenticationState;
  Security->FileAuthenticationState = InternalFileAuthentication;
  if (Security2) {
    gSecurity2FileAuthentication = Security2->FileAuthentication;
    Security2->FileAuthentication = Internal2FileAuthentication;
  }
  return EFI_SUCCESS;
}

// Uninstall secure boot
VOID UninstallSecureBoot(VOID)
{
  // Uninstall policy hooks
  if (gSecurityFileAuthentication) {
    EFI_SECURITY_ARCH_PROTOCOL  *Security = NULL;
    // Restore the security protocol function
    gBS->LocateProtocol(&gEfiSecurityArchProtocolGuid, NULL, (VOID **)&Security);
    if (Security) {
      Security->FileAuthenticationState = gSecurityFileAuthentication;
    }
    gSecurityFileAuthentication = 0;
  }
  if (gSecurity2FileAuthentication) {
    EFI_SECURITY2_ARCH_PROTOCOL *Security2 = NULL;
    // Restory the security 2 protocol function
    gBS->LocateProtocol(&gEfiSecurity2ArchProtocolGuid, NULL, (VOID **)&Security2);
    if (Security2) {
      Security2->FileAuthentication = gSecurity2FileAuthentication;
    }
    gSecurity2FileAuthentication = 0;
  }
}

// Initialize secure boot
VOID InitializeSecureBoot(VOID)
{
  // Set secure boot variables to firmware values
  UINTN Size = sizeof(gSettings.SecureBootSetupMode);
  gRT->GetVariable(L"SetupMode", &gEfiGlobalVariableGuid, NULL, &Size, &gSettings.SecureBootSetupMode);
  Size = sizeof(gSettings.SecureBoot);
  gRT->GetVariable(L"SecureBoot", &gEfiGlobalVariableGuid, NULL, &Size, &gSettings.SecureBoot);
  // Make sure that secure boot is disabled if in setup mode, this will
  //  allow us to specify later in settings that we want to override
  //  setup mode and pretend like we are in secure boot mode to enforce
  //  secure boot policy even when secure boot is not present/disabled.
  if (gSettings.SecureBootSetupMode) {
    gSettings.SecureBoot = 0;
  }
}
