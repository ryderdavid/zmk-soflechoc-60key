cmake_minimum_required(VERSION 3.20.0)

# Only compile on the central half (left) when display + our widget are enabled.
if(CONFIG_ZMK_WIDGET_MOD_STATUS AND CONFIG_ZMK_DISPLAY)
    if(NOT CONFIG_ZMK_SPLIT OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
        add_subdirectory(src)
    endif()
endif()
