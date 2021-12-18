## daly-bms-uart-smt32
STM32 library for communicating with Daly BMS over UART.
- daly-bms-uart.h é o arquivo de cabeçalho da biblioteca.
- daly-bms-uart.c é o arquivo de aplicação das função da biblioteca.

## The DALY BMS UART Protocol

Esta é a aparência de um pacote de saída. Fixo em 13 bytes. 
| Start Byte      | Host Address | Command ID | Data Length | Data | Checksum | 
| - | - | - | - | - | - | 
| 0xA5 | 0x80 | See below | 0x08 (fixed) | 0x0000000000000000 (8 bytes) | See below |

Esta é a aparência de um pacote de entrada. Neste caso, o comando "VOUT_IOUT_SOC" que retorna a tensão corrente e carga da bateria.
| Start Byte      | Host Address | Command ID | Data Length | Data | Checksum | 
| - | - | - | - | - | - | 
| 0xA5 | 0x01 | 0x90 (see below) | 0x08 (fixed?*) | 0x023A0000753001ED (8 bytes) | 0x0D (See below) |

#### Data section

#### Checksum
O último byte do pacote é uma soma de verificação, que é calculada somando todos os bytes restantes no pacote e truncando o resultado para um byte. (0xA5 + 0x01 + 0x90 + ... + 0xED = 0x30D = 0x0D).  
