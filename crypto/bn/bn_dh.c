/*
 * Written by Dr Stephen N Henson (steve@openssl.org) for the OpenSSL project
 * 2011.
 */
/* ====================================================================
 * Copyright (c) 2011 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    licensing@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */

#include "bn_lcl.h"
#include "e_os.h"

#ifndef OPENSSL_NO_DH
#include <openssl/dh.h>
/* DH parameters from RFC5114 */

# if BN_BITS2 == 64
static const BN_ULONG dh1024_160_p[] = {
    0xDF1FB2BC2E4A4371ULL, 0xE68CFDA76D4DA708ULL, 0x45BF37DF365C1A65ULL,
    0xA151AF5F0DC8B4BDULL, 0xFAA31A4FF55BCCC0ULL, 0x4EFFD6FAE5644738ULL,
    0x98488E9C219A7372ULL, 0xACCBDD7D90C4BD70ULL, 0x24975C3CD49B83BFULL,
    0x13ECB4AEA9061123ULL, 0x9838EF1E2EE652C0ULL, 0x6073E28675A23D18ULL,
    0x9A6A9DCA52D23B61ULL, 0x52C99FBCFB06A3C6ULL, 0xDE92DE5EAE5D54ECULL,
    0xB10B8F96A080E01DULL
};

static const BN_ULONG dh1024_160_g[] = {
    0x855E6EEB22B3B2E5ULL, 0x858F4DCEF97C2A24ULL, 0x2D779D5918D08BC8ULL,
    0xD662A4D18E73AFA3ULL, 0x1DBF0A0169B6A28AULL, 0xA6A24C087A091F53ULL,
    0x909D0D2263F80A76ULL, 0xD7FBD7D3B9A92EE1ULL, 0x5E91547F9E2749F4ULL,
    0x160217B4B01B886AULL, 0x777E690F5504F213ULL, 0x266FEA1E5C41564BULL,
    0xD6406CFF14266D31ULL, 0xF8104DD258AC507FULL, 0x6765A442EFB99905ULL,
    0xA4D1CBD5C3FD3412ULL
};

static const BN_ULONG dh1024_160_q[] = {
    0x64B7CB9D49462353ULL, 0x81A8DF278ABA4E7DULL, 0x00000000F518AA87ULL
};

static const BN_ULONG dh2048_224_p[] = {
    0x0AC4DFFE0C10E64FULL, 0xCF9DE5384E71B81CULL, 0x7EF363E2FFA31F71ULL,
    0xE3FB73C16B8E75B9ULL, 0xC9B53DCF4BA80A29ULL, 0x23F10B0E16E79763ULL,
    0xC52172E413042E9BULL, 0xBE60E69CC928B2B9ULL, 0x80CD86A1B9E587E8ULL,
    0x315D75E198C641A4ULL, 0xCDF93ACC44328387ULL, 0x15987D9ADC0A486DULL,
    0x7310F7121FD5A074ULL, 0x278273C7DE31EFDCULL, 0x1602E714415D9330ULL,
    0x81286130BC8985DBULL, 0xB3BF8A3170918836ULL, 0x6A00E0A0B9C49708ULL,
    0xC6BA0B2C8BBC27BEULL, 0xC9F98D11ED34DBF6ULL, 0x7AD5B7D0B6C12207ULL,
    0xD91E8FEF55B7394BULL, 0x9037C9EDEFDA4DF8ULL, 0x6D3F8152AD6AC212ULL,
    0x1DE6B85A1274A0A6ULL, 0xEB3D688A309C180EULL, 0xAF9A3C407BA1DF15ULL,
    0xE6FA141DF95A56DBULL, 0xB54B1597B61D0A75ULL, 0xA20D64E5683B9FD1ULL,
    0xD660FAA79559C51FULL, 0xAD107E1E9123A9D0ULL
};

static const BN_ULONG dh2048_224_g[] = {
    0x84B890D3191F2BFAULL, 0x81BC087F2A7065B3ULL, 0x19C418E1F6EC0179ULL,
    0x7B5A0F1C71CFFF4CULL, 0xEDFE72FE9B6AA4BDULL, 0x81E1BCFE94B30269ULL,
    0x566AFBB48D6C0191ULL, 0xB539CCE3409D13CDULL, 0x6AA21E7F5F2FF381ULL,
    0xD9E263E4770589EFULL, 0x10E183EDD19963DDULL, 0xB70A8137150B8EEBULL,
    0x051AE3D428C8F8ACULL, 0xBB77A86F0C1AB15BULL, 0x6E3025E316A330EFULL,
    0x19529A45D6F83456ULL, 0xF180EB34118E98D1ULL, 0xB5F6C6B250717CBEULL,
    0x09939D54DA7460CDULL, 0xE247150422EA1ED4ULL, 0xB8A762D0521BC98AULL,
    0xF4D027275AC1348BULL, 0xC17669101999024AULL, 0xBE5E9001A8D66AD7ULL,
    0xC57DB17C620A8652ULL, 0xAB739D7700C29F52ULL, 0xDD921F01A70C4AFAULL,
    0xA6824A4E10B9A6F0ULL, 0x74866A08CFE4FFE3ULL, 0x6CDEBE7B89998CAFULL,
    0x9DF30B5C8FFDAC50ULL, 0xAC4032EF4F2D9AE3ULL
};

static const BN_ULONG dh2048_224_q[] = {
    0xBF389A99B36371EBULL, 0x1F80535A4738CEBCULL, 0xC58D93FE99717710ULL,
    0x00000000801C0D34ULL
};

static const BN_ULONG dh2048_256_p[] = {
    0xDB094AE91E1A1597ULL, 0x693877FAD7EF09CAULL, 0x6116D2276E11715FULL,
    0xA4B54330C198AF12ULL, 0x75F26375D7014103ULL, 0xC3A3960A54E710C3ULL,
    0xDED4010ABD0BE621ULL, 0xC0B857F689962856ULL, 0xB3CA3F7971506026ULL,
    0x1CCACB83E6B486F6ULL, 0x67E144E514056425ULL, 0xF6A167B5A41825D9ULL,
    0x3AD8347796524D8EULL, 0xF13C6D9A51BFA4ABULL, 0x2D52526735488A0EULL,
    0xB63ACAE1CAA6B790ULL, 0x4FDB70C581B23F76ULL, 0xBC39A0BF12307F5CULL,
    0xB941F54EB1E59BB8ULL, 0x6C5BFC11D45F9088ULL, 0x22E0B1EF4275BF7BULL,
    0x91F9E6725B4758C0ULL, 0x5A8A9D306BCF67EDULL, 0x209E0C6497517ABDULL,
    0x3BF4296D830E9A7CULL, 0x16C3D91134096FAAULL, 0xFAF7DF4561B2AA30ULL,
    0xE00DF8F1D61957D4ULL, 0x5D2CEED4435E3B00ULL, 0x8CEEF608660DD0F2ULL,
    0xFFBBD19C65195999ULL, 0x87A8E61DB4B6663CULL
};

static const BN_ULONG dh2048_256_g[] = {
    0x664B4C0F6CC41659ULL, 0x5E2327CFEF98C582ULL, 0xD647D148D4795451ULL,
    0x2F63078490F00EF8ULL, 0x184B523D1DB246C3ULL, 0xC7891428CDC67EB6ULL,
    0x7FD028370DF92B52ULL, 0xB3353BBB64E0EC37ULL, 0xECD06E1557CD0915ULL,
    0xB7D2BBD2DF016199ULL, 0xC8484B1E052588B9ULL, 0xDB2A3B7313D3FE14ULL,
    0xD052B985D182EA0AULL, 0xA4BD1BFFE83B9C80ULL, 0xDFC967C1FB3F2E55ULL,
    0xB5045AF2767164E1ULL, 0x1D14348F6F2F9193ULL, 0x64E67982428EBC83ULL,
    0x8AC376D282D6ED38ULL, 0x777DE62AAAB8A862ULL, 0xDDF463E5E9EC144BULL,
    0x0196F931C77A57F2ULL, 0xA55AE31341000A65ULL, 0x901228F8C28CBB18ULL,
    0xBC3773BF7E8C6F62ULL, 0xBE3A6C1B0C6B47B1ULL, 0xFF4FED4AAC0BB555ULL,
    0x10DBC15077BE463FULL, 0x07F4793A1A0BA125ULL, 0x4CA7B18F21EF2054ULL,
    0x2E77506660EDBD48ULL, 0x3FB32C9B73134D0BULL
};

static const BN_ULONG dh2048_256_q[] = {
    0xA308B0FE64F5FBD3ULL, 0x99B1A47D1EB3750BULL, 0xB447997640129DA2ULL,
    0x8CF83642A709A097ULL
};

# elif BN_BITS2 == 32

static const BN_ULONG dh1024_160_p[] = {
    0x2E4A4371, 0xDF1FB2BC, 0x6D4DA708, 0xE68CFDA7, 0x365C1A65, 0x45BF37DF,
    0x0DC8B4BD, 0xA151AF5F, 0xF55BCCC0, 0xFAA31A4F, 0xE5644738, 0x4EFFD6FA,
    0x219A7372, 0x98488E9C, 0x90C4BD70, 0xACCBDD7D, 0xD49B83BF, 0x24975C3C,
    0xA9061123, 0x13ECB4AE, 0x2EE652C0, 0x9838EF1E, 0x75A23D18, 0x6073E286,
    0x52D23B61, 0x9A6A9DCA, 0xFB06A3C6, 0x52C99FBC, 0xAE5D54EC, 0xDE92DE5E,
    0xA080E01D, 0xB10B8F96
};

static const BN_ULONG dh1024_160_g[] = {
    0x22B3B2E5, 0x855E6EEB, 0xF97C2A24, 0x858F4DCE, 0x18D08BC8, 0x2D779D59,
    0x8E73AFA3, 0xD662A4D1, 0x69B6A28A, 0x1DBF0A01, 0x7A091F53, 0xA6A24C08,
    0x63F80A76, 0x909D0D22, 0xB9A92EE1, 0xD7FBD7D3, 0x9E2749F4, 0x5E91547F,
    0xB01B886A, 0x160217B4, 0x5504F213, 0x777E690F, 0x5C41564B, 0x266FEA1E,
    0x14266D31, 0xD6406CFF, 0x58AC507F, 0xF8104DD2, 0xEFB99905, 0x6765A442,
    0xC3FD3412, 0xA4D1CBD5
};

static const BN_ULONG dh1024_160_q[] = {
    0x49462353, 0x64B7CB9D, 0x8ABA4E7D, 0x81A8DF27, 0xF518AA87
};

static const BN_ULONG dh2048_224_p[] = {
    0x0C10E64F, 0x0AC4DFFE, 0x4E71B81C, 0xCF9DE538, 0xFFA31F71, 0x7EF363E2,
    0x6B8E75B9, 0xE3FB73C1, 0x4BA80A29, 0xC9B53DCF, 0x16E79763, 0x23F10B0E,
    0x13042E9B, 0xC52172E4, 0xC928B2B9, 0xBE60E69C, 0xB9E587E8, 0x80CD86A1,
    0x98C641A4, 0x315D75E1, 0x44328387, 0xCDF93ACC, 0xDC0A486D, 0x15987D9A,
    0x1FD5A074, 0x7310F712, 0xDE31EFDC, 0x278273C7, 0x415D9330, 0x1602E714,
    0xBC8985DB, 0x81286130, 0x70918836, 0xB3BF8A31, 0xB9C49708, 0x6A00E0A0,
    0x8BBC27BE, 0xC6BA0B2C, 0xED34DBF6, 0xC9F98D11, 0xB6C12207, 0x7AD5B7D0,
    0x55B7394B, 0xD91E8FEF, 0xEFDA4DF8, 0x9037C9ED, 0xAD6AC212, 0x6D3F8152,
    0x1274A0A6, 0x1DE6B85A, 0x309C180E, 0xEB3D688A, 0x7BA1DF15, 0xAF9A3C40,
    0xF95A56DB, 0xE6FA141D, 0xB61D0A75, 0xB54B1597, 0x683B9FD1, 0xA20D64E5,
    0x9559C51F, 0xD660FAA7, 0x9123A9D0, 0xAD107E1E
};

static const BN_ULONG dh2048_224_g[] = {
    0x191F2BFA, 0x84B890D3, 0x2A7065B3, 0x81BC087F, 0xF6EC0179, 0x19C418E1,
    0x71CFFF4C, 0x7B5A0F1C, 0x9B6AA4BD, 0xEDFE72FE, 0x94B30269, 0x81E1BCFE,
    0x8D6C0191, 0x566AFBB4, 0x409D13CD, 0xB539CCE3, 0x5F2FF381, 0x6AA21E7F,
    0x770589EF, 0xD9E263E4, 0xD19963DD, 0x10E183ED, 0x150B8EEB, 0xB70A8137,
    0x28C8F8AC, 0x051AE3D4, 0x0C1AB15B, 0xBB77A86F, 0x16A330EF, 0x6E3025E3,
    0xD6F83456, 0x19529A45, 0x118E98D1, 0xF180EB34, 0x50717CBE, 0xB5F6C6B2,
    0xDA7460CD, 0x09939D54, 0x22EA1ED4, 0xE2471504, 0x521BC98A, 0xB8A762D0,
    0x5AC1348B, 0xF4D02727, 0x1999024A, 0xC1766910, 0xA8D66AD7, 0xBE5E9001,
    0x620A8652, 0xC57DB17C, 0x00C29F52, 0xAB739D77, 0xA70C4AFA, 0xDD921F01,
    0x10B9A6F0, 0xA6824A4E, 0xCFE4FFE3, 0x74866A08, 0x89998CAF, 0x6CDEBE7B,
    0x8FFDAC50, 0x9DF30B5C, 0x4F2D9AE3, 0xAC4032EF
};

static const BN_ULONG dh2048_224_q[] = {
    0xB36371EB, 0xBF389A99, 0x4738CEBC, 0x1F80535A, 0x99717710, 0xC58D93FE,
    0x801C0D34
};

static const BN_ULONG dh2048_256_p[] = {
    0x1E1A1597, 0xDB094AE9, 0xD7EF09CA, 0x693877FA, 0x6E11715F, 0x6116D227,
    0xC198AF12, 0xA4B54330, 0xD7014103, 0x75F26375, 0x54E710C3, 0xC3A3960A,
    0xBD0BE621, 0xDED4010A, 0x89962856, 0xC0B857F6, 0x71506026, 0xB3CA3F79,
    0xE6B486F6, 0x1CCACB83, 0x14056425, 0x67E144E5, 0xA41825D9, 0xF6A167B5,
    0x96524D8E, 0x3AD83477, 0x51BFA4AB, 0xF13C6D9A, 0x35488A0E, 0x2D525267,
    0xCAA6B790, 0xB63ACAE1, 0x81B23F76, 0x4FDB70C5, 0x12307F5C, 0xBC39A0BF,
    0xB1E59BB8, 0xB941F54E, 0xD45F9088, 0x6C5BFC11, 0x4275BF7B, 0x22E0B1EF,
    0x5B4758C0, 0x91F9E672, 0x6BCF67ED, 0x5A8A9D30, 0x97517ABD, 0x209E0C64,
    0x830E9A7C, 0x3BF4296D, 0x34096FAA, 0x16C3D911, 0x61B2AA30, 0xFAF7DF45,
    0xD61957D4, 0xE00DF8F1, 0x435E3B00, 0x5D2CEED4, 0x660DD0F2, 0x8CEEF608,
    0x65195999, 0xFFBBD19C, 0xB4B6663C, 0x87A8E61D
};

static const BN_ULONG dh2048_256_g[] = {
    0x6CC41659, 0x664B4C0F, 0xEF98C582, 0x5E2327CF, 0xD4795451, 0xD647D148,
    0x90F00EF8, 0x2F630784, 0x1DB246C3, 0x184B523D, 0xCDC67EB6, 0xC7891428,
    0x0DF92B52, 0x7FD02837, 0x64E0EC37, 0xB3353BBB, 0x57CD0915, 0xECD06E15,
    0xDF016199, 0xB7D2BBD2, 0x052588B9, 0xC8484B1E, 0x13D3FE14, 0xDB2A3B73,
    0xD182EA0A, 0xD052B985, 0xE83B9C80, 0xA4BD1BFF, 0xFB3F2E55, 0xDFC967C1,
    0x767164E1, 0xB5045AF2, 0x6F2F9193, 0x1D14348F, 0x428EBC83, 0x64E67982,
    0x82D6ED38, 0x8AC376D2, 0xAAB8A862, 0x777DE62A, 0xE9EC144B, 0xDDF463E5,
    0xC77A57F2, 0x0196F931, 0x41000A65, 0xA55AE313, 0xC28CBB18, 0x901228F8,
    0x7E8C6F62, 0xBC3773BF, 0x0C6B47B1, 0xBE3A6C1B, 0xAC0BB555, 0xFF4FED4A,
    0x77BE463F, 0x10DBC150, 0x1A0BA125, 0x07F4793A, 0x21EF2054, 0x4CA7B18F,
    0x60EDBD48, 0x2E775066, 0x73134D0B, 0x3FB32C9B
};

static const BN_ULONG dh2048_256_q[] = {
    0x64F5FBD3, 0xA308B0FE, 0x1EB3750B, 0x99B1A47D, 0x40129DA2, 0xB4479976,
    0xA709A097, 0x8CF83642
};

# else
#  error "unsupported BN_BITS2"
# endif

/* Macro to make a BIGNUM from static data */

# define make_dh_bn(x) const BIGNUM _bignum_##x = { (BN_ULONG *) x, \
                        OSSL_NELEM(x),\
                        OSSL_NELEM(x),\
                        0, BN_FLG_STATIC_DATA };


make_dh_bn(dh1024_160_p)
make_dh_bn(dh1024_160_g)
make_dh_bn(dh1024_160_q)
make_dh_bn(dh2048_224_p)
make_dh_bn(dh2048_224_g)
make_dh_bn(dh2048_224_q)
make_dh_bn(dh2048_256_p)
make_dh_bn(dh2048_256_g)
make_dh_bn(dh2048_256_q)

#endif
