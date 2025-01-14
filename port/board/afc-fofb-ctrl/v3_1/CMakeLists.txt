#Select which microcontroller and board are being used
if (NOT TARGET_CONTROLLER)
  set(TARGET_CONTROLLER "LPC1764" CACHE STRING "Target MMC Controller")
endif()

if (NOT TARGET_BOARD_NAME)
    set(TARGET_BOARD_NAME "AFC FOFB" CACHE STRING "Board Name")
endif()

# Check if TARGET_BOARD_NAME fits in out field structure. Must fit
# the TARGET_BOARD_NAME length plus "-RTM". But let's give some extra
# room for a little bit more in case we want to change "-RTM" to
# something else.
set(TARGET_BOARD_NAME_MAX_LENGTH 10)

string(LENGTH ${TARGET_BOARD_NAME} TARGET_BOARD_NAME_LENGTH)
if(${TARGET_BOARD_NAME_LENGTH} GREATER ${TARGET_BOARD_NAME_MAX_LENGTH})
    message(FATAL_ERROR
        "${ColourBold}${Red}TARGET_BOARD_NAME (${TARGET_BOARD_NAME}) length \
        (${TARGET_BOARD_NAME_LENGTH}) is greater than \
        ${TARGET_BOARD_NAME_MAX_LENGTH}.${ColourReset}")
endif()

#List all modules used by this board
set(TARGET_MODULES
  "FRU"
  "PAYLOAD"
  "SDR"
  "SCANSTA1101"
  "ADN4604"
  "FPGA_SPI"
  "DAC_AD84XX"
  "HOTSWAP_SENSOR"
  "EEPROM_AT24MAC"
  "EEPROM_24XX64"
  "LM75"
  "MAX6642"
  "INA220_VOLTAGE"
  "INA220_CURRENT"
  "HPM"
  "RTM"
  "UART_DEBUG"
  "PCA9554"
  "SYSUTILS"
  )

if (NOT DISABLE_WATCHDOG)
  list(APPEND TARGET_MODULES "WATCHDOG")
endif()

set(BOARD_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#Include the modules sources
set(PROJ_SRCS ${PROJ_SRCS} ${BOARD_PATH}/sdr_list.c)
set(PROJ_SRCS ${PROJ_SRCS} ${BOARD_PATH}/i2c_mapping.c)
set(PROJ_SRCS ${PROJ_SRCS} ${BOARD_PATH}/ipmi_oem.c)

if (";${TARGET_MODULES};" MATCHES ";PAYLOAD;")
  set(PROJ_SRCS ${PROJ_SRCS} ${BOARD_PATH}/payload.c)
  set(MODULES_FLAGS "${MODULES_FLAGS} -DMODULE_PAYLOAD")
endif()

#Extra definitions
if (FRU_WRITE_EEPROM)
  message(STATUS "FRU EEPROM will be written if no valid data is found!")
  set(MODULES_FLAGS "${MODULES_FLAGS} -DFRU_WRITE_EEPROM")
  set(FRU_WRITE_EEPROM false CACHE BOOL "Set this flag to enable writing the board ID on the EEPROM" FORCE)
endif()

#Set the variables in the main scope
set(TARGET_MODULES ${TARGET_MODULES} PARENT_SCOPE)
set(MODULES_FLAGS ${MODULES_FLAGS} PARENT_SCOPE)
set(PROJ_SRCS ${PROJ_SRCS} PARENT_SCOPE)
set(PROJ_HDRS ${PROJ_HDRS} ${BOARD_PATH})
set(PROJ_HDRS ${PROJ_HDRS} PARENT_SCOPE)
