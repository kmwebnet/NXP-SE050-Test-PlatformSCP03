#ifndef SSS_APIS_INC_FSL_SSS_FTR_H_
#define SSS_APIS_INC_FSL_SSS_FTR_H_

/* ************************************************************************** */
/* Defines                                                                    */
/* ************************************************************************** */

/* clang-format off */

#define SSS_HAVE_MBEDTLS     (1)
#define SSS_HAVE_OPENSSL     (0)

/* A71CH IC */
#define SSS_HAVE_A71CH       (0)

/* A71CL IC */
#define SSS_HAVE_A71CL       (0)

/* A71CH or A71CL IC */
#define SSS_HAVE_A71XX       (SSS_HAVE_A71CH + SSS_HAVE_A71CL)

/** Early access release Applet, CH/CL Compatible implementation */
#define SSS_HAVE_SE050_EAR_CH   (0)
#define SSS_HAVE_SE050_EAR_CL   (0)

#define SSS_HAVE_SE050_EAR   (SSS_HAVE_SE050_EAR_CH + SSS_HAVE_SE050_EAR_CL)

/** Next generation of SE050 Applet */
/* Successor of A71CH */
#define SSS_HAVE_SE050_A       (0)
/* Successor of A71CL */
#define SSS_HAVE_SE050_B       (0)
/* Super set of A and B */
#define SSS_HAVE_SE050_C       (1)

#define SSS_HAVE_SE05X (SSS_HAVE_SE050_A + SSS_HAVE_SE050_B + SSS_HAVE_SE050_C)

#define SSS_HAVE_LOOPBACK    (0)

#define SSS_HAVE_SSCP        (SSS_HAVE_A71XX + SSS_HAVE_SE050_EAR)

/* mbedTLS ALT implementations */
#define SSS_HAVE_ALT_A71CH      (0)
#define SSS_HAVE_ALT_SSS        (1)

#define SSS_HAVE_ALT         (SSS_HAVE_ALT_A71CH + SSS_HAVE_ALT_SSS)

#if (SSS_HAVE_A71XX + SSS_HAVE_SE05X + SSS_HAVE_SE050_EAR) >= 2
#   error Multiple SEs selected. Select only one Secure Element at a time.
#endif

/* Set to 1 for any SE */
#define SSS_HAVE_SE              (0 + SSS_HAVE_SE05X )

#define SSS_HAVE_SSS         (SSS_HAVE_MBEDTLS +  SSS_HAVE_OPENSSL + SSS_HAVE_SSCP + SSS_HAVE_SE05X)

/* Which cloud is being used/configured */

#define SSS_HAVE_GCP (0)     /* Google Cloud Platform */
#define SSS_HAVE_IBM (0)     /* IBM Watson */
#define SSS_HAVE_AWS (0)     /* Amazon web services */
#define SSS_HAVE_AZURE (0) /* Azure web services */

/* ********************************* */
/* Individual features of sub-system */
/* ********************************* */

/* ECC Mode is availabe */
#define SSS_HAVE_ECC (1)

/* RSA is available */
#define SSS_HAVE_RSA (1)

/* FIPS Mode is enabled */
#define SSS_HAVE_FIPS (0)

/* TPM BARRETO_NAEHRIG Curve is enabled */
#define SSS_HAVE_TPM_BN (1)

/* Edwards Curve is enabled */
#define SSS_HAVE_EC_ED (1)

/* Montgomery Curve is enabled */
#define SSS_HAVE_EC_MONT (1)

/* Enable usage of secure messaging channels */

#define SSS_HAVE_SCP_SCP03_SSS (1)

/* With NXP NFC Reader Library */
#define SSS_HAVE_NXPNFCRDLIB (0)

/* TLS handshake support on SE is enabled */
#define SSS_HAVE_TLS_HANDSHAKE (1)

/* Import Export Key is enabled */
#define SSS_HAVE_IMPORT (1)

/* # CMake Features : Start */

/* ====================================================================== *
 * == Feature selection/values ========================================== *
 * ====================================================================== */


/** SE05X Secure Element : Symmetric AES */
#define SSSFTR_SE05X_AES 1

/** SE05X Secure Element : Elliptic Curve Cryptography */
#define SSSFTR_SE05X_ECC 1

/** SE05X Secure Element : RSA */
#define SSSFTR_SE05X_RSA 1

/** SE05X Secure Element : KEY operations : SET Key */
#define SSSFTR_SE05X_KEY_SET 1

/** SE05X Secure Element : KEY operations : GET Key */
#define SSSFTR_SE05X_KEY_GET 1

/** SE05X Secure Element : Authenticate via FastSCP */
#define SSSFTR_SE05X_AuthFastSCP 1

/** SE05X Secure Element : Allow creation of user/authenticated session.
 *
 * If the intended deployment only uses Platform SCP
 * Or it is a pure session less integration, this can
 * save some code size. */
#define SSSFTR_SE05X_AuthSession 1

/** SE05X Secure Element : Allow creation/deletion of Crypto Objects
 *
 * If disabled, new Crypto Objects are neither created and
 * old/existing Crypto Objects are not deleted.
 * It is assumed that during provisioning phase, the required
 * Crypto Objects are pre-created or they are never going to
 * be needed. */
#define SSSFTR_SE05X_CREATE_DELETE_CRYPTOOBJ 1

/** Software : Symmetric AES */
#define SSSFTR_SW_AES 1

/** Software : Elliptic Curve Cryptography */
#define SSSFTR_SW_ECC 1

/** Software : RSA */
#define SSSFTR_SW_RSA 1

/** Software : KEY operations : SET Key */
#define SSSFTR_SW_KEY_SET 1

/** Software : KEY operations : GET Key */
#define SSSFTR_SW_KEY_GET 1

/** Software : Used as a test counterpart
 *
 * e.g. Major part of the mebdTLS SSS layer is purely used for
 * testing of Secure Element implementation, and can be avoided
 * fully during many production scenarios. */
#define SSSFTR_SW_TESTCOUNTERPART 0

/* ====================================================================== *
 * == Computed Options ================================================== *
 * ====================================================================== */

/** Symmetric AES */
#define SSSFTR_AES               (SSSFTR_SE05X_AES + SSSFTR_SW_AES)
/** Elliptic Curve Cryptography */
#define SSSFTR_ECC               (SSSFTR_SE05X_ECC + SSSFTR_SW_ECC)
/** RSA */
#define SSSFTR_RSA               (SSSFTR_SE05X_RSA + SSSFTR_SW_RSA)
/** KEY operations : SET Key */
#define SSSFTR_KEY_SET           (SSSFTR_SE05X_KEY_SET + SSSFTR_SW_KEY_SET)
/** KEY operations : GET Key */
#define SSSFTR_KEY_GET           (SSSFTR_SE05X_KEY_GET + SSSFTR_SW_KEY_GET)
/** KEY operations */
#define SSSFTR_KEY               (SSSFTR_KEY_SET + SSSFTR_KEY_GET)
/** KEY operations */
#define SSSFTR_SE05X_KEY         (SSSFTR_SE05X_KEY_SET + SSSFTR_SE05X_KEY_GET)
/** KEY operations */
#define SSSFTR_SW_KEY            (SSSFTR_SW_KEY_SET + SSSFTR_SW_KEY_GET)

/* # CMake Features : END */

/* For backwards compatibility */
#define SSS_HAVE_TESTCOUNTERPART (SSSFTR_SW_TESTCOUNTERPART)

#define MBEDTLS_CONFIG_FILE "mbedtls/esp_config.h"

/*
 * Example RSA keys, for selftest and benchmark purposes
 */

#define RSA_PRIVATE_KEY_1024                                            \
"-----BEGIN RSA PRIVATE KEY-----\r\n"                                   \
"MIICWwIBAAKBgQDA0UszjREl+JklUyevaN8fb0Gp13Dzb4pY3MCoJK15BWoeoUFA\r\n"  \
"IVvuI0C8bRm/i1OO4BN9tSRrRjW+S89YbYy1C73PUgKZSejjnEFA4chcSOKOhZlM\r\n"  \
"6K7+Pcrcx+sdiDu1DheODMiSFhoxt+H6IUvBEGkI5AWFu5MDP7wlU/AZfQIDAQAB\r\n"  \
"AoGAU6o9HEhIuZYuNZDodmdl8YjgECdIfojWmgpnmk4X65xa2KGV45LWBfXMADbC\r\n"  \
"5mc5QZSfQHuaKuYTKdhRRwh59c9VPwYhN8hdgFzbJS9KfJTDuKhsZrdomHRN2fHK\r\n"  \
"Jn5MrbVCeZPbYS0M1PzVgEz/BGRp4Ik3RAxTlt+XBtunHA0CQQDz6Gor3gFTdCWM\r\n"  \
"XtrWEfMW+arWvPUBlOhw3U0YgpWqdea36YeXd9DEIIKn9bQU4g0SjkpO7jd/ccBm\r\n"  \
"zM89dfjXAkEAymB11gLDd0JZhUCk155uBucaZeez/VNucEgvjWDphRInqJg+2JW2\r\n"  \
"gSgXNFeSTY9iKlLdBL1zYdywOXM3fd6RywJAIqFYGbxeodO21RROq+BGjHeMWwrf\r\n"  \
"Godi7Utue9FmoJo21NvyZX4chQw8oM5Q8DocMwtC36wQ8yZac/4WWpqaZwJAbMIy\r\n"  \
"EXUivrC1k1sOO6I01xjTovhGTlnL/COPCpeOZ6k+DujivVqX3glBjyuQwIXR55To\r\n"  \
"mmeF3o3PVtCIfehiyQJATsyRPJ1FOYIlIywMSaGHqSpVoebWbDQ6BhYOOvmx5/Zd\r\n"  \
"Tun1+7WrtPoxM+LQumgPEdx7VDq2L4SetYB/Md1OSQ==\r\n"                      \
"-----END RSA PRIVATE KEY-----\r\n"

#define RSA_PRIVATE_KEY_2048                                            \
"-----BEGIN RSA PRIVATE KEY-----\r\n"                                   \
"MIIEogIBAAKCAQEA2dwVr+IMGEtA2/MCP6fA5eb/6B18Bq6e7gw8brNPkm3E6LyR\r\n"  \
"4DnMJVxZmw3bPDKBDoKzfntkMESi/Yw5UopLtVfjGfWeQWPClqffLZBsZ60BRAsg\r\n"  \
"/g+ID5tgzxSuxzftypK59uexOVCAm7hCKZHGO3DbI7bLY27j7VAgEP7d/yuaz5Fx\r\n"  \
"Kl/vu7shqrBoz6ABJVJD3KC8nUiMRUCXRINmxbyUUjA4DnicZv6+xrGKr36r6M8h\r\n"  \
"VYLa5msKc8WzbnBWzpUsrpb4/r7ML+qp92gdSfVJ8/bLiU7h2C7faDA59uaqrFK9\r\n"  \
"xmDdx7FaWhGQs3LWW6w1UNgkPS0FDYUslpsnsQIDAQABAoIBAC7IJNwM5V3+IuJY\r\n"  \
"T35Nzo1PyloUosJokvY5KGz5Ejg2XBdCDu0gXCcVqqQyGIbXrYDpLhQV+RCoXHun\r\n"  \
"tdN0oQdC5SB47s/J1Uo2qCUHo0+sBd6PqTkFKsl3KxWssk9TQjvCwC412IefMs69\r\n"  \
"hW+ZvwCanmQP56LleApIr2oW4KLfW8Ry/QfZlua+dizctdN7+H1mWwgZQTY9T27J\r\n"  \
"6RtGRA5NVkKVPzIHVJfdpKoO7xGg1g06aEbPB/VmGvZaaFWWnaf7uRvFjLZecBLu\r\n"  \
"QSx2DA/GDjirlDYj99PJb7DtB4xRtKzsyw0o+xapC8w6OtIl/3xFt9moCu2jGrsx\r\n"  \
"vpjHdfECgYEA7fSACRseIs9gAIVX8wq6gayTpA47DHYWAD6IQfIj35SJ+AgsvbFF\r\n"  \
"4AmrwDhcJVPmDy1N4nLBfyGAMt/2CfiYkdkW6QFX/ULRMMBL/G7kWV8hYQDICB2g\r\n"  \
"xaMRN1lPCmFq6BkSWjwIYTnYDFBDWVm1GVT8TMtJoM8Erej9qC0PeFUCgYEA6mF3\r\n"  \
"bigO3t8f5sig+XepaftEUbkJMzo72TVRnIR2ycdR2ihelPQ+25g9dwV0ZA5XXhBS\r\n"  \
"DKOABWjMM739Mwmy9v26Dlmu9R01zHQktMvtEAyfz7lk2NF0aMuj8285OJUBf9bz\r\n"  \
"Cq3MjtMCD+4CZ6iaEqCdUKOuxfpx5cWVJV+qve0CgYBhD1YaYMFOGaBjFgDl1f51\r\n"  \
"Xltqk5NqZdBbkSYrIAWZ8RDF5y+4wFJsLAWuhk6vuyUgE66tK3nZzWRpXAkT0B8L\r\n"  \
"fq1lpXKqj1KcvBNCiEkEW1VWJ+dvyAYIF5eyJ++hoFLnETL3M32HivyhKSwPihPg\r\n"  \
"nVW8TT9fJJIYDe1JZ/fjcQKBgHJfv7UsrR0LSvkG3K8AOtbx+8PZhOjPuRbk0v+L\r\n"  \
"EKCkuIe5/XW4vtfQMeZb7hFJgk7vrepm+vkoy8VQKDf4urGW3W1VTHBmobM01hi4\r\n"  \
"DuYvEul+Mf0wMRtWjJolo4m+BO5KiW2jpFfqFm6JmfjVqOIAKOSKC6am8V/MDF0h\r\n"  \
"kyN9AoGAT9oOiEXMolbkDZw/QCaBiRoAGlGlNYUkJ+58U6OjIZLISw6aFv+Y2uE0\r\n"  \
"mEImItjuYZtSYKblWikp6ldPoKlt9bwEFe3c6IZ8kJ3+xyEyAGrvjXjEY7PzP6dp\r\n"  \
"Ajbjp9X9uocEBv9W/KsBLdQ7yizcL/toHwdBO4vQqmqTvAc5IIw=\r\n"              \
"-----END RSA PRIVATE KEY-----\r\n"

#define RSA_PRIVATE_KEY_4096                                            \
"-----BEGIN RSA PRIVATE KEY-----\r\n"                                   \
"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\r\n"  \
"-----END RSA PRIVATE KEY-----\r\n" 










/* clang-format on */

#endif /* SSS_APIS_INC_FSL_SSS_FTR_H_ */


