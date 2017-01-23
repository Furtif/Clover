/*
 * HDA injector, part of the Chameleon Boot Loader Project
 *
 * Ported and adapted by Fabio (ErmaC), October 2016.
 *
 * HDA injector is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HDA injector is distributed in the hope that it will be useful, but
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __LIBSAIO_HDA_H
#define __LIBSAIO_HDA_H
#include "device_inject.h"

//extern CHAR8 *gDeviceProperties;

//BOOLEAN setup_hda_devprop(pci_dt_t *hda_dev, CHAR8 *OSVersion);

struct hda_controller_devices;
typedef struct
{
    UINT32      model;
    CHAR8		*desc;
} hda_controller_devices;

struct hdacc_codecs;
typedef struct
{
    UINT32      id;
    UINT32      rev;
    CHAR8       *name;
} hdacc_codecs;

#define UNKNOWN "Unknown "

/****************************************************************************
 * Miscellanious defines
 ****************************************************************************/

/* Controller models */
#define HDA_MODEL_CONSTRUCT(vendor, model) (((UINT32)(model) << 16) | ((vendor##_VENDORID) & 0xffff))

/* Intel */
#define INTEL_VENDORID		0x8086
#define HDA_INTEL_OAK		HDA_MODEL_CONSTRUCT(INTEL, 0x080a)
#define HDA_INTEL_BAY		HDA_MODEL_CONSTRUCT(INTEL, 0x0f04)
#define HDA_INTEL_HSW1		HDA_MODEL_CONSTRUCT(INTEL, 0x0a0c)
#define HDA_INTEL_HSW2		HDA_MODEL_CONSTRUCT(INTEL, 0x0c0c)
#define HDA_INTEL_HSW3		HDA_MODEL_CONSTRUCT(INTEL, 0x0d0c)
#define HDA_INTEL_BDW		HDA_MODEL_CONSTRUCT(INTEL, 0x160c)
#define HDA_INTEL_CPT		HDA_MODEL_CONSTRUCT(INTEL, 0x1c20)
#define HDA_INTEL_PATSBURG	HDA_MODEL_CONSTRUCT(INTEL, 0x1d20)
#define HDA_INTEL_PPT1		HDA_MODEL_CONSTRUCT(INTEL, 0x1e20) // Macmini6,2
#define HDA_INTEL_BRASWELL 	HDA_MODEL_CONSTRUCT(INTEL, 0x2284)
#define HDA_INTEL_82801F	HDA_MODEL_CONSTRUCT(INTEL, 0x2668)
#define HDA_INTEL_63XXESB	HDA_MODEL_CONSTRUCT(INTEL, 0x269a)
#define HDA_INTEL_82801G	HDA_MODEL_CONSTRUCT(INTEL, 0x27d8)
#define HDA_INTEL_82801H	HDA_MODEL_CONSTRUCT(INTEL, 0x284b)
#define HDA_INTEL_82801I	HDA_MODEL_CONSTRUCT(INTEL, 0x293e)
#define HDA_INTEL_ICH9		HDA_MODEL_CONSTRUCT(INTEL, 0x293f)
#define HDA_INTEL_82801JI	HDA_MODEL_CONSTRUCT(INTEL, 0x3a3e)
#define HDA_INTEL_82801JD	HDA_MODEL_CONSTRUCT(INTEL, 0x3a6e)
#define HDA_INTEL_PCH		HDA_MODEL_CONSTRUCT(INTEL, 0x3b56)
#define HDA_INTEL_PCH2		HDA_MODEL_CONSTRUCT(INTEL, 0x3b57)
#define HDA_INTEL_MACBOOKPRO92	HDA_MODEL_CONSTRUCT(INTEL, 0x7270)
#define HDA_INTEL_SCH		HDA_MODEL_CONSTRUCT(INTEL, 0x811b)
#define HDA_INTEL_LPT1		HDA_MODEL_CONSTRUCT(INTEL, 0x8c20)
#define HDA_INTEL_LPT2		HDA_MODEL_CONSTRUCT(INTEL, 0x8c21)
#define HDA_INTEL_WCPT		HDA_MODEL_CONSTRUCT(INTEL, 0x8ca0)
#define HDA_INTEL_WELLS1	HDA_MODEL_CONSTRUCT(INTEL, 0x8d20)
#define HDA_INTEL_WELLS2	HDA_MODEL_CONSTRUCT(INTEL, 0x8d21)
#define HDA_INTEL_WCPTLP 	HDA_MODEL_CONSTRUCT(INTEL, 0x9ca0)
#define HDA_INTEL_LPTLP1	HDA_MODEL_CONSTRUCT(INTEL, 0x9c20)
#define HDA_INTEL_LPTLP2	HDA_MODEL_CONSTRUCT(INTEL, 0x9c21)
#define HDA_INTEL_SRSPLP 	HDA_MODEL_CONSTRUCT(INTEL, 0x9d70)
#define HDA_INTEL_SRSP		HDA_MODEL_CONSTRUCT(INTEL, 0xa170)
#define HDA_INTEL_ALL		HDA_MODEL_CONSTRUCT(INTEL, 0xffff)

/* Nvidia */
#define NVIDIA_VENDORID		0x10de
// AppleHDA binary contain 0a00de10 (10de000a)
// AppleHDAController binary contain de10ea0b (10de0bea)
#define HDA_NVIDIA_MCP51	HDA_MODEL_CONSTRUCT(NVIDIA, 0x026c)
#define HDA_NVIDIA_MCP55	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0371)
#define HDA_NVIDIA_MCP61_1	HDA_MODEL_CONSTRUCT(NVIDIA, 0x03e4)
#define HDA_NVIDIA_MCP61_2	HDA_MODEL_CONSTRUCT(NVIDIA, 0x03f0)
#define HDA_NVIDIA_MCP65_1	HDA_MODEL_CONSTRUCT(NVIDIA, 0x044a)
#define HDA_NVIDIA_MCP65_2	HDA_MODEL_CONSTRUCT(NVIDIA, 0x044b)
#define HDA_NVIDIA_MCP67_1	HDA_MODEL_CONSTRUCT(NVIDIA, 0x055c)
#define HDA_NVIDIA_MCP67_2	HDA_MODEL_CONSTRUCT(NVIDIA, 0x055d)
#define HDA_NVIDIA_MCP78_1	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0774)
#define HDA_NVIDIA_MCP78_2	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0775)
#define HDA_NVIDIA_MCP78_3	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0776)
#define HDA_NVIDIA_MCP78_4	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0777)
#define HDA_NVIDIA_MCP73_1	HDA_MODEL_CONSTRUCT(NVIDIA, 0x07fc)
#define HDA_NVIDIA_MCP73_2	HDA_MODEL_CONSTRUCT(NVIDIA, 0x07fd)
#define HDA_NVIDIA_MCP79_1	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0ac0)
#define HDA_NVIDIA_MCP79_2	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0ac1)
#define HDA_NVIDIA_MCP79_3	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0ac2)
#define HDA_NVIDIA_MCP79_4	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0ac3)
#define HDA_NVIDIA_0BE2		HDA_MODEL_CONSTRUCT(NVIDIA, 0x0be2)
#define HDA_NVIDIA_0BE3		HDA_MODEL_CONSTRUCT(NVIDIA, 0x0be3) // [GeForce 210] HDAcodec
#define HDA_NVIDIA_0BE4		HDA_MODEL_CONSTRUCT(NVIDIA, 0x0be4) // [GeForge GT 240] HDACodec 10de000d (0d00de10)
#define HDA_NVIDIA_GT100	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0be5) // [GeForge GTX 470] HDACodec 10de0010 (1000de10)
#define HDA_NVIDIA_GT106	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0be9)
#define HDA_NVIDIA_GT108	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0bea) // HDACodec
#define HDA_NVIDIA_GT104	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0beb)
#define HDA_NVIDIA_GT116	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0bee)
#define HDA_NVIDIA_MCP89_1	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0d94)
#define HDA_NVIDIA_MCP89_2	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0d95)
#define HDA_NVIDIA_MCP89_3	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0d96)
#define HDA_NVIDIA_MCP89_4	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0d97)
#define HDA_NVIDIA_GF119	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0e08)
#define HDA_NVIDIA_GF110_1	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0e09)
#define HDA_NVIDIA_GF110_2	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0e0c) // HDACodec de101600 (10de0016), Controller Binary de100c0e x2
#define HDA_NVIDIA_GK104	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0e0a)
#define HDA_NVIDIA_GK106	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0e0b)
#define HDA_NVIDIA_GK110	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0e1a)
#define HDA_NVIDIA_GK107	HDA_MODEL_CONSTRUCT(NVIDIA, 0x0e1b) // HDACodec de104200 (10de0042)
#define HDA_NVIDIA_GP104_2      HDA_MODEL_CONSTRUCT(NVIDIA, 0x10f0) // GeForce GTX 1070
#define HDA_NVIDIA_GM204_2      HDA_MODEL_CONSTRUCT(NVIDIA, 0x0fbb) // GeForce GTX 970
#define HDA_NVIDIA_ALL		HDA_MODEL_CONSTRUCT(NVIDIA, 0xffff)

/* ATI */
#define ATI_VENDORID		0x1002
#define HDA_ATI_SB450		HDA_MODEL_CONSTRUCT(ATI, 0x437b)
#define HDA_ATI_SB600		HDA_MODEL_CONSTRUCT(ATI, 0x4383)
#define HDA_ATI_HUDSON		HDA_MODEL_CONSTRUCT(ATI, 0x780d)
#define HDA_ATI_RS600		HDA_MODEL_CONSTRUCT(ATI, 0x793b)
#define HDA_ATI_RS690		HDA_MODEL_CONSTRUCT(ATI, 0x7919)
#define HDA_ATI_RS780		HDA_MODEL_CONSTRUCT(ATI, 0x960f)
#define HDA_ATI_RS880		HDA_MODEL_CONSTRUCT(ATI, 0x970f)
#define HDA_ATI_TRINITY		HDA_MODEL_CONSTRUCT(ATI, 0x9902)
#define HDA_ATI_R600		HDA_MODEL_CONSTRUCT(ATI, 0xaa00)
#define HDA_ATI_RV630		HDA_MODEL_CONSTRUCT(ATI, 0xaa08)
#define HDA_ATI_RV610		HDA_MODEL_CONSTRUCT(ATI, 0xaa10)
#define HDA_ATI_RV670		HDA_MODEL_CONSTRUCT(ATI, 0xaa18)
#define HDA_ATI_RV635		HDA_MODEL_CONSTRUCT(ATI, 0xaa20)
#define HDA_ATI_RV620		HDA_MODEL_CONSTRUCT(ATI, 0xaa28)
#define HDA_ATI_RV770		HDA_MODEL_CONSTRUCT(ATI, 0xaa30)
#define HDA_ATI_RV730		HDA_MODEL_CONSTRUCT(ATI, 0xaa38)
#define HDA_ATI_RV710		HDA_MODEL_CONSTRUCT(ATI, 0xaa40)
#define HDA_ATI_RV740		HDA_MODEL_CONSTRUCT(ATI, 0xaa48)
#define HDA_ATI_RV870		HDA_MODEL_CONSTRUCT(ATI, 0xaa50)
#define HDA_ATI_RV840		HDA_MODEL_CONSTRUCT(ATI, 0xaa58) // Codec 021001aa (1002aa01)
#define HDA_ATI_RV830		HDA_MODEL_CONSTRUCT(ATI, 0xaa60)
#define HDA_ATI_RV810		HDA_MODEL_CONSTRUCT(ATI, 0xaa68)
#define HDA_ATI_RV970		HDA_MODEL_CONSTRUCT(ATI, 0xaa80)
#define HDA_ATI_RV940		HDA_MODEL_CONSTRUCT(ATI, 0xaa88)
#define HDA_ATI_RV930		HDA_MODEL_CONSTRUCT(ATI, 0xaa90)
#define HDA_ATI_RV910		HDA_MODEL_CONSTRUCT(ATI, 0xaa98)
#define HDA_ATI_R1000		HDA_MODEL_CONSTRUCT(ATI, 0xaaa0)
#define HDA_ATI_SI		HDA_MODEL_CONSTRUCT(ATI, 0xaaa8)
#define HDA_ATI_VERDE		HDA_MODEL_CONSTRUCT(ATI, 0xaab0)
#define HDA_ATI_ALL		HDA_MODEL_CONSTRUCT(ATI, 0xffff)

/* RDC */
#define RDC_VENDORID		0x17f3
#define HDA_RDC_M3010		HDA_MODEL_CONSTRUCT(RDC, 0x3010)

/* VIA */
#define VIA_VENDORID		0x1106
#define HDA_VIA_VT82XX		HDA_MODEL_CONSTRUCT(VIA, 0x3288)
#define HDA_VIA_ALL		HDA_MODEL_CONSTRUCT(VIA, 0xffff)

/* SiS */
#define SIS_VENDORID		0x1039
#define HDA_SIS_966		HDA_MODEL_CONSTRUCT(SIS, 0x7502)
#define HDA_SIS_ALL		HDA_MODEL_CONSTRUCT(SIS, 0xffff)

/* ULI */
#define ULI_VENDORID		0x10b9
#define HDA_ULI_M5461		HDA_MODEL_CONSTRUCT(ULI, 0x5461)
#define HDA_ULI_ALL		HDA_MODEL_CONSTRUCT(ULI, 0xffff)

/* =================== C O D E C   I N F O R M A T I O N ===================== */

#define HDA_CODEC_CONSTRUCT(vendor, id) (((UINT32)(vendor##_VENDORID) << 16) | ((id) & 0xffff))

/* ATI */
#define HDA_CODEC_ATIRS600_1    HDA_CODEC_CONSTRUCT(ATI, 0x793c)
#define HDA_CODEC_ATIRS600_2    HDA_CODEC_CONSTRUCT(ATI, 0x7919)
#define HDA_CODEC_ATIRS690      HDA_CODEC_CONSTRUCT(ATI, 0x791a)
#define HDA_CODEC_ATIR6XX       HDA_CODEC_CONSTRUCT(ATI, 0xaa01)
#define HDA_CODEC_ATIXXXX       HDA_CODEC_CONSTRUCT(ATI, 0xffff)

/* Cirrus Logic */
#define CIRRUSLOGIC_VENDORID    0x1013
#define HDA_CODEC_CS4206        HDA_CODEC_CONSTRUCT(CIRRUSLOGIC, 0x4206)
#define HDA_CODEC_CS4207        HDA_CODEC_CONSTRUCT(CIRRUSLOGIC, 0x4207)
#define HDA_CODEC_CS4208        HDA_CODEC_CONSTRUCT(CIRRUSLOGIC, 0x4208)
#define HDA_CODEC_CS4210        HDA_CODEC_CONSTRUCT(CIRRUSLOGIC, 0x4210)
#define HDA_CODEC_CS4213        HDA_CODEC_CONSTRUCT(CIRRUSLOGIC, 0x4213)
#define HDA_CODEC_CSXXXX        HDA_CODEC_CONSTRUCT(CIRRUSLOGIC, 0xffff)

/* Motorola */
#define MOTO_VENDORID           0x1057
#define HDA_CODEC_MOTOXXXX      HDA_CODEC_CONSTRUCT(MOTO, 0xffff)

/* Silicon Image */
#define SII_VENDORID    0x1095
#define HDA_CODEC_SII1390       HDA_CODEC_CONSTRUCT(SII, 0x1390)
#define HDA_CODEC_SII1392       HDA_CODEC_CONSTRUCT(SII, 0x1392)
#define HDA_CODEC_SIIXXXX       HDA_CODEC_CONSTRUCT(SII, 0xffff)

/* NVIDIA */
#define HDA_CODEC_NVIDIAMCP78   HDA_CODEC_CONSTRUCT(NVIDIA, 0x0002)
#define HDA_CODEC_NVIDIAMCP78_2 HDA_CODEC_CONSTRUCT(NVIDIA, 0x0003)
#define HDA_CODEC_NVIDIAMCP78_3 HDA_CODEC_CONSTRUCT(NVIDIA, 0x0005)
#define HDA_CODEC_NVIDIAMCP78_4 HDA_CODEC_CONSTRUCT(NVIDIA, 0x0006)
#define HDA_CODEC_NVIDIAMCP7A   HDA_CODEC_CONSTRUCT(NVIDIA, 0x0007)
#define HDA_CODEC_NVIDIAGT220   HDA_CODEC_CONSTRUCT(NVIDIA, 0x000a)
#define HDA_CODEC_NVIDIAGT21X   HDA_CODEC_CONSTRUCT(NVIDIA, 0x000b)
#define HDA_CODEC_NVIDIAMCP89   HDA_CODEC_CONSTRUCT(NVIDIA, 0x000c)
#define HDA_CODEC_NVIDIAGT240   HDA_CODEC_CONSTRUCT(NVIDIA, 0x000d)
#define HDA_CODEC_NVIDIAGTX470  HDA_CODEC_CONSTRUCT(NVIDIA, 0x0010)
#define HDA_CODEC_NVIDIAGTS450  HDA_CODEC_CONSTRUCT(NVIDIA, 0x0011)
#define HDA_CODEC_NVIDIAGT440   HDA_CODEC_CONSTRUCT(NVIDIA, 0x0014)
#define HDA_CODEC_NVIDIAGTX550  HDA_CODEC_CONSTRUCT(NVIDIA, 0x0015)
#define HDA_CODEC_NVIDIAGTX570  HDA_CODEC_CONSTRUCT(NVIDIA, 0x0018)
#define HDA_CODEC_NVIDIAGT610	HDA_CODEC_CONSTRUCT(NVIDIA, 0x001c)
#define HDA_CODEC_NVIDIAMCP67   HDA_CODEC_CONSTRUCT(NVIDIA, 0x0067)
#define HDA_CODEC_NVIDIAMCP73   HDA_CODEC_CONSTRUCT(NVIDIA, 0x8001)
#define HDA_CODEC_NVIDIAXXXX    HDA_CODEC_CONSTRUCT(NVIDIA, 0xffff)

/* Realtek */
#define REALTEK_VENDORID        0x10ec
#define HDA_CODEC_ALC221        HDA_CODEC_CONSTRUCT(REALTEK, 0x0221)
#define HDA_CODEC_ALC231        HDA_CODEC_CONSTRUCT(REALTEK, 0x0231)
#define HDA_CODEC_ALC233        HDA_CODEC_CONSTRUCT(REALTEK, 0x0233)
#define HDA_CODEC_ALC235        HDA_CODEC_CONSTRUCT(REALTEK, 0x0235)
#define HDA_CODEC_ALC255        HDA_CODEC_CONSTRUCT(REALTEK, 0x0255)
#define HDA_CODEC_ALC256        HDA_CODEC_CONSTRUCT(REALTEK, 0x0256)
#define HDA_CODEC_ALC260        HDA_CODEC_CONSTRUCT(REALTEK, 0x0260)
#define HDA_CODEC_ALC262        HDA_CODEC_CONSTRUCT(REALTEK, 0x0262)
#define HDA_CODEC_ALC267        HDA_CODEC_CONSTRUCT(REALTEK, 0x0267)
#define HDA_CODEC_ALC268        HDA_CODEC_CONSTRUCT(REALTEK, 0x0268)
#define HDA_CODEC_ALC269        HDA_CODEC_CONSTRUCT(REALTEK, 0x0269)
#define HDA_CODEC_ALC270        HDA_CODEC_CONSTRUCT(REALTEK, 0x0270)
#define HDA_CODEC_ALC272        HDA_CODEC_CONSTRUCT(REALTEK, 0x0272)
#define HDA_CODEC_ALC273        HDA_CODEC_CONSTRUCT(REALTEK, 0x0273)
#define HDA_CODEC_ALC275        HDA_CODEC_CONSTRUCT(REALTEK, 0x0275)
#define HDA_CODEC_ALC276        HDA_CODEC_CONSTRUCT(REALTEK, 0x0276)
#define HDA_CODEC_ALC280	HDA_CODEC_CONSTRUCT(REALTEK, 0x0280)
#define HDA_CODEC_ALC282	HDA_CODEC_CONSTRUCT(REALTEK, 0x0282)
#define HDA_CODEC_ALC283	HDA_CODEC_CONSTRUCT(REALTEK, 0x0283)
#define HDA_CODEC_ALC284	HDA_CODEC_CONSTRUCT(REALTEK, 0x0284)
#define HDA_CODEC_ALC285	HDA_CODEC_CONSTRUCT(REALTEK, 0x0285)
#define HDA_CODEC_ALC286	HDA_CODEC_CONSTRUCT(REALTEK, 0x0286)
#define HDA_CODEC_ALC288	HDA_CODEC_CONSTRUCT(REALTEK, 0x0288)
#define HDA_CODEC_ALC290	HDA_CODEC_CONSTRUCT(REALTEK, 0x0290)
#define HDA_CODEC_ALC292	HDA_CODEC_CONSTRUCT(REALTEK, 0x0292)
#define HDA_CODEC_ALC293	HDA_CODEC_CONSTRUCT(REALTEK, 0x0293)
#define HDA_CODEC_ALC298	HDA_CODEC_CONSTRUCT(REALTEK, 0x0298)
#define HDA_CODEC_ALC660        HDA_CODEC_CONSTRUCT(REALTEK, 0x0660)
#define HDA_CODEC_ALC662        HDA_CODEC_CONSTRUCT(REALTEK, 0x0662)
#define HDA_CODEC_ALC663        HDA_CODEC_CONSTRUCT(REALTEK, 0x0663)
#define HDA_CODEC_ALC665        HDA_CODEC_CONSTRUCT(REALTEK, 0x0665)
#define HDA_CODEC_ALC667        HDA_CODEC_CONSTRUCT(REALTEK, 0x0667)
#define HDA_CODEC_ALC668        HDA_CODEC_CONSTRUCT(REALTEK, 0x0668)
#define HDA_CODEC_ALC670        HDA_CODEC_CONSTRUCT(REALTEK, 0x0670)
#define HDA_CODEC_ALC671        HDA_CODEC_CONSTRUCT(REALTEK, 0x0671)
#define HDA_CODEC_ALC680        HDA_CODEC_CONSTRUCT(REALTEK, 0x0680)
#define HDA_CODEC_ALC861        HDA_CODEC_CONSTRUCT(REALTEK, 0x0861)
#define HDA_CODEC_ALC861VD      HDA_CODEC_CONSTRUCT(REALTEK, 0x0862)
#define HDA_CODEC_ALC867        HDA_CODEC_CONSTRUCT(REALTEK, 0x0867)
#define HDA_CODEC_ALC880        HDA_CODEC_CONSTRUCT(REALTEK, 0x0880)
#define HDA_CODEC_ALC882        HDA_CODEC_CONSTRUCT(REALTEK, 0x0882)
#define HDA_CODEC_ALC883        HDA_CODEC_CONSTRUCT(REALTEK, 0x0883)
#define HDA_CODEC_ALC885        HDA_CODEC_CONSTRUCT(REALTEK, 0x0885)
#define HDA_CODEC_ALC886        HDA_CODEC_CONSTRUCT(REALTEK, 0x0886)
#define HDA_CODEC_ALC887        HDA_CODEC_CONSTRUCT(REALTEK, 0x0887)
#define HDA_CODEC_ALC888        HDA_CODEC_CONSTRUCT(REALTEK, 0x0888)
#define HDA_CODEC_ALC889        HDA_CODEC_CONSTRUCT(REALTEK, 0x0889)
#define HDA_CODEC_ALC892        HDA_CODEC_CONSTRUCT(REALTEK, 0x0892)
#define HDA_CODEC_ALC898        HDA_CODEC_CONSTRUCT(REALTEK, 0x0899)
//#define HDA_CODEC_ALC898        HDA_CODEC_CONSTRUCT(REALTEK, 0x0898)
//#define HDA_CODEC_ALC899        HDA_CODEC_CONSTRUCT(REALTEK, 0x0899)
#define HDA_CODEC_ALC900        HDA_CODEC_CONSTRUCT(REALTEK, 0x0900)
#define HDA_CODEC_ALCXXXX       HDA_CODEC_CONSTRUCT(REALTEK, 0xffff)

/* Creative */
#define CREATIVE_VENDORID       0x1102
#define HDA_CODEC_XFIEA         HDA_CODEC_CONSTRUCT(CREATIVE, 0x000a)
#define HDA_CODEC_XFIED         HDA_CODEC_CONSTRUCT(CREATIVE, 0x000b)
#define HDA_CODEC_SB0880        HDA_CODEC_CONSTRUCT(CREATIVE, 0x000d)
#define HDA_CODEC_CA0132        HDA_CODEC_CONSTRUCT(CREATIVE, 0x0011)
#define HDA_CODEC_CAXXXX        HDA_CODEC_CONSTRUCT(CREATIVE, 0xffff)

/* VIA */
#define HDA_CODEC_VT1708_8      HDA_CODEC_CONSTRUCT(VIA, 0x1708)
#define HDA_CODEC_VT1708_9      HDA_CODEC_CONSTRUCT(VIA, 0x1709)
#define HDA_CODEC_VT1708_A      HDA_CODEC_CONSTRUCT(VIA, 0x170a)
#define HDA_CODEC_VT1708_B      HDA_CODEC_CONSTRUCT(VIA, 0x170b)
#define HDA_CODEC_VT1709_0      HDA_CODEC_CONSTRUCT(VIA, 0xe710)
#define HDA_CODEC_VT1709_1      HDA_CODEC_CONSTRUCT(VIA, 0xe711)
#define HDA_CODEC_VT1709_2      HDA_CODEC_CONSTRUCT(VIA, 0xe712)
#define HDA_CODEC_VT1709_3      HDA_CODEC_CONSTRUCT(VIA, 0xe713)
#define HDA_CODEC_VT1709_4      HDA_CODEC_CONSTRUCT(VIA, 0xe714)
#define HDA_CODEC_VT1709_5      HDA_CODEC_CONSTRUCT(VIA, 0xe715)
#define HDA_CODEC_VT1709_6      HDA_CODEC_CONSTRUCT(VIA, 0xe716)
#define HDA_CODEC_VT1709_7      HDA_CODEC_CONSTRUCT(VIA, 0xe717)
#define HDA_CODEC_VT1708B_0     HDA_CODEC_CONSTRUCT(VIA, 0xe720)
#define HDA_CODEC_VT1708B_1     HDA_CODEC_CONSTRUCT(VIA, 0xe721)
#define HDA_CODEC_VT1708B_2     HDA_CODEC_CONSTRUCT(VIA, 0xe722)
#define HDA_CODEC_VT1708B_3     HDA_CODEC_CONSTRUCT(VIA, 0xe723)
#define HDA_CODEC_VT1708B_4     HDA_CODEC_CONSTRUCT(VIA, 0xe724)
#define HDA_CODEC_VT1708B_5     HDA_CODEC_CONSTRUCT(VIA, 0xe725)
#define HDA_CODEC_VT1708B_6     HDA_CODEC_CONSTRUCT(VIA, 0xe726)
#define HDA_CODEC_VT1708B_7     HDA_CODEC_CONSTRUCT(VIA, 0xe727)
#define HDA_CODEC_VT1708S_0     HDA_CODEC_CONSTRUCT(VIA, 0x0397)
#define HDA_CODEC_VT1708S_1     HDA_CODEC_CONSTRUCT(VIA, 0x1397)
#define HDA_CODEC_VT1708S_2     HDA_CODEC_CONSTRUCT(VIA, 0x2397)
#define HDA_CODEC_VT1708S_3     HDA_CODEC_CONSTRUCT(VIA, 0x3397)
#define HDA_CODEC_VT1708S_4     HDA_CODEC_CONSTRUCT(VIA, 0x4397)
#define HDA_CODEC_VT1708S_5     HDA_CODEC_CONSTRUCT(VIA, 0x5397)
#define HDA_CODEC_VT1708S_6     HDA_CODEC_CONSTRUCT(VIA, 0x6397)
#define HDA_CODEC_VT1708S_7     HDA_CODEC_CONSTRUCT(VIA, 0x7397)
#define HDA_CODEC_VT1702_0      HDA_CODEC_CONSTRUCT(VIA, 0x0398)
#define HDA_CODEC_VT1702_1      HDA_CODEC_CONSTRUCT(VIA, 0x1398)
#define HDA_CODEC_VT1702_2      HDA_CODEC_CONSTRUCT(VIA, 0x2398)
#define HDA_CODEC_VT1702_3      HDA_CODEC_CONSTRUCT(VIA, 0x3398)
#define HDA_CODEC_VT1702_4      HDA_CODEC_CONSTRUCT(VIA, 0x4398)
#define HDA_CODEC_VT1702_5      HDA_CODEC_CONSTRUCT(VIA, 0x5398)
#define HDA_CODEC_VT1702_6      HDA_CODEC_CONSTRUCT(VIA, 0x6398)
#define HDA_CODEC_VT1702_7      HDA_CODEC_CONSTRUCT(VIA, 0x7398)
#define HDA_CODEC_VT1716S_0     HDA_CODEC_CONSTRUCT(VIA, 0x0433)
#define HDA_CODEC_VT1716S_1     HDA_CODEC_CONSTRUCT(VIA, 0xa721)
#define HDA_CODEC_VT1718S_0     HDA_CODEC_CONSTRUCT(VIA, 0x0428)
#define HDA_CODEC_VT1718S_1     HDA_CODEC_CONSTRUCT(VIA, 0x4428)
#define HDA_CODEC_VT1802_0      HDA_CODEC_CONSTRUCT(VIA, 0x0446)
#define HDA_CODEC_VT1802_1      HDA_CODEC_CONSTRUCT(VIA, 0x8446)
#define HDA_CODEC_VT1812        HDA_CODEC_CONSTRUCT(VIA, 0x0448)
#define HDA_CODEC_VT1818S       HDA_CODEC_CONSTRUCT(VIA, 0x0440)
#define HDA_CODEC_VT1828S       HDA_CODEC_CONSTRUCT(VIA, 0x4441)
#define HDA_CODEC_VT2002P_0     HDA_CODEC_CONSTRUCT(VIA, 0x0438)
#define HDA_CODEC_VT2002P_1     HDA_CODEC_CONSTRUCT(VIA, 0x4438)
#define HDA_CODEC_VT2020        HDA_CODEC_CONSTRUCT(VIA, 0x0441)
#define HDA_CODEC_VTXXXX        HDA_CODEC_CONSTRUCT(VIA, 0xffff)

/* IDT */
#define IDT_VENDORID            0x111d
#define HDA_CODEC_IDT92HD75BX   HDA_CODEC_CONSTRUCT(IDT, 0x7603)
#define HDA_CODEC_IDT92HD83C1X  HDA_CODEC_CONSTRUCT(IDT, 0x7604)
#define HDA_CODEC_IDT92HD81B1X  HDA_CODEC_CONSTRUCT(IDT, 0x7605)
#define HDA_CODEC_IDT92HD75B3   HDA_CODEC_CONSTRUCT(IDT, 0x7608)
#define HDA_CODEC_IDT92HD88B3   HDA_CODEC_CONSTRUCT(IDT, 0x7666)
#define HDA_CODEC_IDT92HD88B1   HDA_CODEC_CONSTRUCT(IDT, 0x7667)
#define HDA_CODEC_IDT92HD88B2   HDA_CODEC_CONSTRUCT(IDT, 0x7668)
#define HDA_CODEC_IDT92HD88B4   HDA_CODEC_CONSTRUCT(IDT, 0x7669)
#define HDA_CODEC_IDT92HD73D1   HDA_CODEC_CONSTRUCT(IDT, 0x7674)
#define HDA_CODEC_IDT92HD73C1   HDA_CODEC_CONSTRUCT(IDT, 0x7675)
#define HDA_CODEC_IDT92HD73E1   HDA_CODEC_CONSTRUCT(IDT, 0x7676)
#define HDA_CODEC_IDT92HD95     HDA_CODEC_CONSTRUCT(IDT, 0x7695)
#define HDA_CODEC_IDT92HD71B8   HDA_CODEC_CONSTRUCT(IDT, 0x76b0)
#define HDA_CODEC_IDT92HD71B8_2 HDA_CODEC_CONSTRUCT(IDT, 0x76b1)
#define HDA_CODEC_IDT92HD71B7   HDA_CODEC_CONSTRUCT(IDT, 0x76b2)
#define HDA_CODEC_IDT92HD71B7_2 HDA_CODEC_CONSTRUCT(IDT, 0x76b3)
#define HDA_CODEC_IDT92HD71B6   HDA_CODEC_CONSTRUCT(IDT, 0x76b4)
#define HDA_CODEC_IDT92HD71B6_2 HDA_CODEC_CONSTRUCT(IDT, 0x76b5)
#define HDA_CODEC_IDT92HD71B5   HDA_CODEC_CONSTRUCT(IDT, 0x76b6)
#define HDA_CODEC_IDT92HD71B5_2 HDA_CODEC_CONSTRUCT(IDT, 0x76b7)
#define HDA_CODEC_IDT92HD89C3   HDA_CODEC_CONSTRUCT(IDT, 0x76c0)
#define HDA_CODEC_IDT92HD89C2   HDA_CODEC_CONSTRUCT(IDT, 0x76c1)
#define HDA_CODEC_IDT92HD89C1   HDA_CODEC_CONSTRUCT(IDT, 0x76c2)
#define HDA_CODEC_IDT92HD89B3   HDA_CODEC_CONSTRUCT(IDT, 0x76c3)
#define HDA_CODEC_IDT92HD89B2   HDA_CODEC_CONSTRUCT(IDT, 0x76c4)
#define HDA_CODEC_IDT92HD89B1   HDA_CODEC_CONSTRUCT(IDT, 0x76c5)
#define HDA_CODEC_IDT92HD89E3   HDA_CODEC_CONSTRUCT(IDT, 0x76c6)
#define HDA_CODEC_IDT92HD89E2   HDA_CODEC_CONSTRUCT(IDT, 0x76c7)
#define HDA_CODEC_IDT92HD89E1   HDA_CODEC_CONSTRUCT(IDT, 0x76c8)
#define HDA_CODEC_IDT92HD89D3   HDA_CODEC_CONSTRUCT(IDT, 0x76c9)
#define HDA_CODEC_IDT92HD89D2   HDA_CODEC_CONSTRUCT(IDT, 0x76ca)
#define HDA_CODEC_IDT92HD89D1   HDA_CODEC_CONSTRUCT(IDT, 0x76cb)
#define HDA_CODEC_IDT92HD89F3   HDA_CODEC_CONSTRUCT(IDT, 0x76cc)
#define HDA_CODEC_IDT92HD89F2   HDA_CODEC_CONSTRUCT(IDT, 0x76cd)
#define HDA_CODEC_IDT92HD89F1   HDA_CODEC_CONSTRUCT(IDT, 0x76ce)
#define HDA_CODEC_IDT92HD87B1_3 HDA_CODEC_CONSTRUCT(IDT, 0x76d1)
#define HDA_CODEC_IDT92HD83C1C  HDA_CODEC_CONSTRUCT(IDT, 0x76d4)
#define HDA_CODEC_IDT92HD81B1C  HDA_CODEC_CONSTRUCT(IDT, 0x76d5)
#define HDA_CODEC_IDT92HD87B2_4 HDA_CODEC_CONSTRUCT(IDT, 0x76d9)
#define HDA_CODEC_IDT92HD93BXX  HDA_CODEC_CONSTRUCT(IDT, 0x76df)
#define HDA_CODEC_IDT92HD91BXX  HDA_CODEC_CONSTRUCT(IDT, 0x76e0)
#define HDA_CODEC_IDT92HD98BXX  HDA_CODEC_CONSTRUCT(IDT, 0x76e3)
#define HDA_CODEC_IDT92HD99BXX  HDA_CODEC_CONSTRUCT(IDT, 0x76e5)
#define HDA_CODEC_IDT92HD90BXX  HDA_CODEC_CONSTRUCT(IDT, 0x76e7)
#define HDA_CODEC_IDT92HD66B1X5 HDA_CODEC_CONSTRUCT(IDT, 0x76e8)
#define HDA_CODEC_IDT92HD66B2X5 HDA_CODEC_CONSTRUCT(IDT, 0x76e9)
#define HDA_CODEC_IDT92HD66B3X5 HDA_CODEC_CONSTRUCT(IDT, 0x76ea)
#define HDA_CODEC_IDT92HD66C1X5 HDA_CODEC_CONSTRUCT(IDT, 0x76eb)
#define HDA_CODEC_IDT92HD66C2X5 HDA_CODEC_CONSTRUCT(IDT, 0x76ec)
#define HDA_CODEC_IDT92HD66C3X5 HDA_CODEC_CONSTRUCT(IDT, 0x76ed)
#define HDA_CODEC_IDT92HD66B1X3 HDA_CODEC_CONSTRUCT(IDT, 0x76ee)
#define HDA_CODEC_IDT92HD66B2X3 HDA_CODEC_CONSTRUCT(IDT, 0x76ef)
#define HDA_CODEC_IDT92HD66B3X3 HDA_CODEC_CONSTRUCT(IDT, 0x76f0)
#define HDA_CODEC_IDT92HD66C1X3 HDA_CODEC_CONSTRUCT(IDT, 0x76f1)
#define HDA_CODEC_IDT92HD66C2X3 HDA_CODEC_CONSTRUCT(IDT, 0x76f2)
#define HDA_CODEC_IDT92HD66C3_65        HDA_CODEC_CONSTRUCT(IDT, 0x76f3)
#define HDA_CODEC_IDTXXXX       HDA_CODEC_CONSTRUCT(IDT, 0xffff)

/* LSI - Lucent/Agere */
#define AGERE_VENDORID  0x11c1
#define HDA_CODEC_AGEREXXXX     HDA_CODEC_CONSTRUCT(AGERE, 0xffff)

/* Analog Devices */
#define ANALOGDEVICES_VENDORID  0x11d4
#define HDA_CODEC_AD1884A       HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x184a)
#define HDA_CODEC_AD1882        HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1882)
#define HDA_CODEC_AD1883        HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1883)
#define HDA_CODEC_AD1884        HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1884)
#define HDA_CODEC_AD1984A       HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x194a)
#define HDA_CODEC_AD1984B       HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x194b)
#define HDA_CODEC_AD1981HD      HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1981)
#define HDA_CODEC_AD1983        HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1983)
#define HDA_CODEC_AD1984        HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1984)
#define HDA_CODEC_AD1986A       HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1986)
#define HDA_CODEC_AD1987        HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1987)
#define HDA_CODEC_AD1988        HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x1988)
#define HDA_CODEC_AD1988B       HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x198b)
#define HDA_CODEC_AD1882A       HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x882a)
#define HDA_CODEC_AD1989A       HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x989a)
#define HDA_CODEC_AD1989B       HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0x989b)
#define HDA_CODEC_ADXXXX        HDA_CODEC_CONSTRUCT(ANALOGDEVICES, 0xffff)

/* CMedia */
#define CMEDIA_VENDORID         0x13f6
#define HDA_CODEC_CMI8880       HDA_CODEC_CONSTRUCT(CMEDIA, 0x8880)
#define HDA_CODEC_CMI9880       HDA_CODEC_CONSTRUCT(CMEDIA, 0x9880)
#define HDA_CODEC_CMIXXXX       HDA_CODEC_CONSTRUCT(CMEDIA, 0xffff)

/* Conexant */
#define CONEXANT_VENDORID       0x14f1
#define HDA_CODEC_CX20549       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5045)
#define HDA_CODEC_CX20551       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5047)
#define HDA_CODEC_CX20561       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5051)
#define HDA_CODEC_CX20582       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5066)
#define HDA_CODEC_CX20583       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5067)
#define HDA_CODEC_CX20584       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5068)
#define HDA_CODEC_CX20585       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5069)
#define HDA_CODEC_CX20588       HDA_CODEC_CONSTRUCT(CONEXANT, 0x506c)
#define HDA_CODEC_CX20590       HDA_CODEC_CONSTRUCT(CONEXANT, 0x506e)
#define HDA_CODEC_CX20631       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5097)
#define HDA_CODEC_CX20632       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5098)
#define HDA_CODEC_CX20641       HDA_CODEC_CONSTRUCT(CONEXANT, 0x50a1)
#define HDA_CODEC_CX20642       HDA_CODEC_CONSTRUCT(CONEXANT, 0x50a2)
#define HDA_CODEC_CX20651       HDA_CODEC_CONSTRUCT(CONEXANT, 0x50ab)
#define HDA_CODEC_CX20652       HDA_CODEC_CONSTRUCT(CONEXANT, 0x50ac)
#define HDA_CODEC_CX20664       HDA_CODEC_CONSTRUCT(CONEXANT, 0x50b8)
#define HDA_CODEC_CX20665       HDA_CODEC_CONSTRUCT(CONEXANT, 0x50b9)
#define HDA_CODEC_CX20751       HDA_CODEC_CONSTRUCT(CONEXANT, 0x510f)
#define HDA_CODEC_CX20751_2	HDA_CODEC_CONSTRUCT(CONEXANT, 0x5110)
#define HDA_CODEC_CX20751_4	HDA_CODEC_CONSTRUCT(CONEXANT, 0x5111)
#define HDA_CODEC_CX20755       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5113)
#define HDA_CODEC_CX20756       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5114)
#define HDA_CODEC_CX20757       HDA_CODEC_CONSTRUCT(CONEXANT, 0x5115)
#define HDA_CODEC_CX20952       HDA_CODEC_CONSTRUCT(CONEXANT, 0x51d7)
#define HDA_CODEC_CXXXXX        HDA_CODEC_CONSTRUCT(CONEXANT, 0xffff)

/* Chrontel */
#define CHRONTEL_VENDORID       0x17e8
#define HDA_CODEC_CHXXXX        HDA_CODEC_CONSTRUCT(CHRONTEL, 0xffff)

/* LG */
#define LG_VENDORID       0x1854
#define HDA_CODEC_LGXXXX        HDA_CODEC_CONSTRUCT(LG, 0xffff)

/* Wolfson Microelectronics */
#define WOLFSON_VENDORID       0x14ec
#define HDA_CODEC_WMXXXX        HDA_CODEC_CONSTRUCT(WOLFSON, 0xffff)

/* QEMU */
#define QEMU_VENDORID       0x1af4
#define HDA_CODEC_QEMUXXXX        HDA_CODEC_CONSTRUCT(QEMU, 0xffff)

/* CMedia */
#define CMEDIA2_VENDORID        0x434d
#define HDA_CODEC_CMI98802      HDA_CODEC_CONSTRUCT(CMEDIA2, 0x4980)
#define HDA_CODEC_CMIXXXX2      HDA_CODEC_CONSTRUCT(CMEDIA2, 0xffff)

/* INTEL */
#define HDA_CODEC_INTELIP	HDA_CODEC_CONSTRUCT(INTEL, 0x0054)
#define HDA_CODEC_INTELBL	HDA_CODEC_CONSTRUCT(INTEL, 0x2801)
#define HDA_CODEC_INTELCA	HDA_CODEC_CONSTRUCT(INTEL, 0x2802)
#define HDA_CODEC_INTELEL	HDA_CODEC_CONSTRUCT(INTEL, 0x2803)
#define HDA_CODEC_INTELIP2	HDA_CODEC_CONSTRUCT(INTEL, 0x2804)
#define HDA_CODEC_INTELCPT	HDA_CODEC_CONSTRUCT(INTEL, 0x2805)
#define HDA_CODEC_INTELPPT	HDA_CODEC_CONSTRUCT(INTEL, 0x2806) // Panther Point HDMI
#define HDA_CODEC_INTELLLP	HDA_CODEC_CONSTRUCT(INTEL, 0x2807) // Haswell HDMI
#define HDA_CODEC_INTELBRW	HDA_CODEC_CONSTRUCT(INTEL, 0x2808) // Broadwell HDMI
#define HDA_CODEC_INTELSKL	HDA_CODEC_CONSTRUCT(INTEL, 0x2809) // Skylake HDMI
#define HDA_CODEC_INTELBRO	HDA_CODEC_CONSTRUCT(INTEL, 0x280a) // Broxton HDMI
#define HDA_CODEC_INTELKAB	HDA_CODEC_CONSTRUCT(INTEL, 0x280b) // Kabylake HDMI
#define HDA_CODEC_INTELCDT	HDA_CODEC_CONSTRUCT(INTEL, 0x2880) // CedarTrail HDMI
#define HDA_CODEC_INTELVLV	HDA_CODEC_CONSTRUCT(INTEL, 0x2882) // Valleyview2 HDMI
#define HDA_CODEC_INTELBSW	HDA_CODEC_CONSTRUCT(INTEL, 0x2883) // Braswell HDMI
#define HDA_CODEC_INTELCL	HDA_CODEC_CONSTRUCT(INTEL, 0x29fb) // Crestline HDMI
#define HDA_CODEC_INTELXXXX	HDA_CODEC_CONSTRUCT(INTEL, 0xffff)

/* Sigmatel */
#define SIGMATEL_VENDORID       0x8384
#define HDA_CODEC_STAC9230X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7612)
#define HDA_CODEC_STAC9230D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7613)
#define HDA_CODEC_STAC9229X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7614)
#define HDA_CODEC_STAC9229D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7615)
#define HDA_CODEC_STAC9228X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7616)
#define HDA_CODEC_STAC9228D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7617)
#define HDA_CODEC_STAC9227X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7618)
#define HDA_CODEC_STAC9227D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7619)
#define HDA_CODEC_STAC9274      HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7620)
#define HDA_CODEC_STAC9274D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7621)
#define HDA_CODEC_STAC9273X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7622)
#define HDA_CODEC_STAC9273D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7623)
#define HDA_CODEC_STAC9272X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7624)
#define HDA_CODEC_STAC9272D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7625)
#define HDA_CODEC_STAC9271X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7626)
#define HDA_CODEC_STAC9271D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7627)
#define HDA_CODEC_STAC9274X5NH  HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7628)
#define HDA_CODEC_STAC9274D5NH  HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7629)
#define HDA_CODEC_STAC9202      HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7632)
#define HDA_CODEC_STAC9202D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7633)
#define HDA_CODEC_STAC9250      HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7634)
#define HDA_CODEC_STAC9250D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7635)
#define HDA_CODEC_STAC9251      HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7636)
#define HDA_CODEC_STAC9250D_1   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7637)
#define HDA_CODEC_IDT92HD700X   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7638)
#define HDA_CODEC_IDT92HD700D   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7639)
#define HDA_CODEC_IDT92HD206X   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7645)
#define HDA_CODEC_IDT92HD206D   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7646)
#define HDA_CODEC_CXD9872RDK    HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7661)
#define HDA_CODEC_STAC9872AK    HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7662)
#define HDA_CODEC_CXD9872AKD    HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7664)
#define HDA_CODEC_STAC9221      HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7680)
#define HDA_CODEC_STAC922XD     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7681)
#define HDA_CODEC_STAC9221_A2   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7682)
#define HDA_CODEC_STAC9221D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7683)
#define HDA_CODEC_STAC9220      HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7690)
#define HDA_CODEC_STAC9200D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7691)
#define HDA_CODEC_IDT92HD005    HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7698)
#define HDA_CODEC_IDT92HD005D   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7699)
#define HDA_CODEC_STAC9205X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x76a0)
#define HDA_CODEC_STAC9205D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x76a1)
#define HDA_CODEC_STAC9204X     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x76a2)
#define HDA_CODEC_STAC9204D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x76a3)
#define HDA_CODEC_STAC9255      HDA_CODEC_CONSTRUCT(SIGMATEL, 0x76a4)
#define HDA_CODEC_STAC9255D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x76a5)
#define HDA_CODEC_STAC9254      HDA_CODEC_CONSTRUCT(SIGMATEL, 0x76a6)
#define HDA_CODEC_STAC9254D     HDA_CODEC_CONSTRUCT(SIGMATEL, 0x76a7)
#define HDA_CODEC_STAC9220_A2   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7880)
#define HDA_CODEC_STAC9220_A1   HDA_CODEC_CONSTRUCT(SIGMATEL, 0x7882)
#define HDA_CODEC_STACXXXX      HDA_CODEC_CONSTRUCT(SIGMATEL, 0xffff)

#endif /* !__LIBSAIO_GMA_H */
