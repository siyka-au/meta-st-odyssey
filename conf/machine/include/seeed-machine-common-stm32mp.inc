#@DESCRIPTION: Common Machine configuration for STM32 systems

# Define specific common layer name
MACHINEOVERRIDES .= ":stm32mp157c-odyssey"

# =========================================================================
# boot scheme
# =========================================================================
# List of supported boot schemes
BOOTSCHEME_LABELS ?= "trusted optee"

# =========================================================================
# boot device
# =========================================================================
BOOTDEVICE_LABELS ?= "emmc sdcard"

UBOOT_CONFIG:append:stm32mp157c-odyssey = " ${@bb.utils.contains_any('BOOTSCHEME_LABELS', 'optee trusted', 'trusted_stm32mp15', '', d)} "

# =========================================================================
# optee
# =========================================================================
# Map OPTEE configuration to device tree list
OPTEE_CONF = "${STM32MP_DEVICETREE}"

# =========================================================================
# Machine settings
# =========================================================================
STM32MP_DEVICETREE:append = "${STM32MP_DT_FILES_ODYSSEY}"

IMAGE_FSTYPES:remove = "tar.xz"


# =========================================================================
# Device Storage
# =========================================================================
# Enable the board device storage support with STM32MP_DT_FILES_ODYSSEY according to BOOTDEVICE_LABELS
DEVICE_BOARD_ENABLE:EMMC    += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'emmc', '${STM32MP_DT_FILES_ODYSSEY}', '', d)}"
DEVICE_BOARD_ENABLE:SDCARD  += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'sdcard', '${STM32MP_DT_FILES_ODYSSEY}', '', d)}"

# =========================================================================
# Flashlayout
# =========================================================================
# Set the FLASHLAYOUT_TYPE_LABELS to STM32MP_DT_FILES_ODYSSEY according to BOOTDEVICE_LABELS
FLASHLAYOUT_TYPE_LABELS:emmc        = "${@bb.utils.contains('BOOTDEVICE_LABELS', 'emmc', '${STM32MP_DT_FILES_ODYSSEY}', '', d)}"
FLASHLAYOUT_TYPE_LABELS:sdcard      = "${@bb.utils.contains('BOOTDEVICE_LABELS', 'sdcard', '${STM32MP_DT_FILES_ODYSSEY}', '', d)}"

# Specific settings for 'extensible' and 'deleteall' configurations
FLASHLAYOUT_CONFIG_LABELS:deleteall = "cubemx"
FLASHLAYOUT_TYPE_LABELS:deleteall:cubemx = "${STM32MP_DT_FILES_ODYSSEY}"
FLASHLAYOUT_TYPE_LABELS:extensible = "${STM32MP_DT_FILES_ODYSSEY}"
