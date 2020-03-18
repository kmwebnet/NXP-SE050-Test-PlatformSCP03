# NXP SE050 Test-PlatformSCP03

This communicates NXP SE050 secure chip from ESP32 and execute "get infos" sample code with transport encryption.  
it helps to make sure the connection between them.

# Requirements

  Platformio(PIO Core:4.1.0 PLATFORM: Espressif 32 1.11.1) with VS Code environment.  
  install "Espressif 32" platform definition on Platformio  

# Environment reference
  
  Espressif ESP32-DevkitC  
  this project initialize both of I2C 0,1 port, and the device on I2C port 0 is absent.  
  pin assined as below:  


      I2C 0 SDA GPIO_NUM_18
      I2C 0 SCL GPIO_NUM_19

      I2C 1 SDA GPIO_NUM_21
      I2C 1 SCL GPIO_NUM_22
          
  NXP SE050C1(on I2C port 1)  

if you use other variants you need to change ENC, MAC, DEK key definition on port/ex_sss_auth.h]

Never use this code as production unless you change 3 keys to your ownn.

# Usage

"git clone --recursive " on your target directory. 
and download "Plug & Trust MW Release v02.12.04" from NXP website
and put the contents into src as "simw-top" folder. 
you need to change a serial port number which actually connected to ESP32 in platformio.ini.  

# Run this project

just execute "Upload" on Platformio.  

you can get the result as follows:

```
       App:INFO :PlugAndTrust_v02.12.04_20200228
       App:INFO :If you want to over-ride the selection, use ENV=EX_SSS_BOOT_SSS_PORT or pass in command line arguments.
       sss:INFO :atr (Len=35)
      00 A0 00 00    03 96 04 03    E8 00 FE 02    0B 03 E8 08
      01 00 00 00    00 64 00 00    0A 4A 43 4F    50 34 20 41
      54 50 4F
       App:WARN :#####################################################
       App:INFO :uid (Len=18)
      04 00 50 01    4A 66 D8 75    07 78 E6 04    7E 91 0A 94
      66 80
       App:WARN :#####################################################
       App:INFO :Applet Major = 3
       App:INFO :Applet Minor = 1
       App:INFO :Applet patch = 0
       App:INFO :AppletConfig = 6FFF
       App:INFO :With    ECDAA
       App:INFO :With    ECDSA_ECDH_ECDHE
       App:INFO :With    EDDSA
       App:INFO :With    DH_MONT
       App:INFO :With    HMAC
       App:INFO :With    RSA_PLAIN
       App:INFO :With    RSA_CRT
       App:INFO :With    AES
       App:INFO :With    DES
       App:INFO :With    PBKDF
       App:INFO :With    TLS
       App:INFO :With    MIFARE
       App:INFO :With    I2CM
       App:INFO :SecureBox = 010B
       App:INFO :ex_sss Finished
```

there is no warning "communication Channel is Plain".


# License

This software is released under the MIT license unless otherwise specified in the included source code. See License. 
