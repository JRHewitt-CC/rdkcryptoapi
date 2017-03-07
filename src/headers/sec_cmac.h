/* Written by Dr Stephen N Henson (steve@openssl.org) for the OpenSSL
 * project.
 */
/* ====================================================================
 * Copyright (c) 2010 The OpenSSL Project.  All rights reserved.
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
 */


#ifndef HEADER_CMAC_H
#define HEADER_CMAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <openssl/evp.h>

/* Opaque */
typedef struct Comcast_CMAC_CTX_st Comcast_CMAC_CTX;

struct Comcast_CMAC_CTX_st
    {
    /* Cipher context to use */
    EVP_CIPHER_CTX cctx;
    /* Keys k1 and k2 */
    unsigned char k1[EVP_MAX_BLOCK_LENGTH];
    unsigned char k2[EVP_MAX_BLOCK_LENGTH];
    /* Temporary block */
    unsigned char tbl[EVP_MAX_BLOCK_LENGTH];
    /* Last (possibly partial) block */
    unsigned char last_block[EVP_MAX_BLOCK_LENGTH];
    /* Number of bytes in last block: -1 means context not initialised */
    int nlast_block;
    };

/* Comcast: Removed
CMAC_CTX *CMAC_CTX_new(void);
*/

/* Comcast: Added */
void Comcast_CMAC_CTX_init(Comcast_CMAC_CTX *ctx);
/* End of Comcast: Added */

void Comcast_CMAC_CTX_cleanup(Comcast_CMAC_CTX *ctx);
/* Comcast: Removed
void Comcast_CMAC_CTX_free(Comcast_CMAC_CTX *ctx);
*/
EVP_CIPHER_CTX *Comcast_CMAC_CTX_get0_cipher_ctx(Comcast_CMAC_CTX *ctx);
/* Comcast: Removed
int Comcast_CMAC_CTX_copy(Comcast_CMAC_CTX *out, const Comcast_CMAC_CTX *in);
 */

int Comcast_CMAC_Init(Comcast_CMAC_CTX *ctx, const void *key, size_t keylen,
            const EVP_CIPHER *cipher, ENGINE *impl);
int Comcast_CMAC_Update(Comcast_CMAC_CTX *ctx, const void *data, size_t dlen);
int Comcast_CMAC_Final(Comcast_CMAC_CTX *ctx, unsigned char *out, unsigned int *poutlen);
int Comcast_CMAC_resume(Comcast_CMAC_CTX *ctx);

#ifdef  __cplusplus
}
#endif
#endif