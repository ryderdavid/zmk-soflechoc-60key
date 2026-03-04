# Path to the nice!view shield sources inside the ZMK application tree.
# CMAKE_SOURCE_DIR is the zmk/app directory during a ZMK firmware build.
set(NICE_VIEW_WIDGET_DIR "${CMAKE_SOURCE_DIR}/boards/shields/nice_view")

zephyr_library()

# Make nice!view widget headers available (widgets/status.h, util.h, bolt.h)
zephyr_library_include_directories(${NICE_VIEW_WIDGET_DIR})

# ZMK app include dir (for zmk/hid.h, zmk/display.h, etc.)
zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)

# Our replacement status screen + the modifier widget
zephyr_library_sources(custom_status_screen.c)
zephyr_library_sources(mod_status.c)

# Custom 1-bpp fonts with Mac modifier symbols (⇧ ⌃ ⌥ ⌘) at four sizes
zephyr_library_sources(mac_symbols_14.c)
zephyr_library_sources(mac_symbols_22.c)
zephyr_library_sources(mac_symbols_32.c)
zephyr_library_sources(mac_symbols_48.c)

# 8px font for ticker stacked modifier display (bundled, not from nice_view)
zephyr_library_sources(mac_symbols_8.c)

# Re-compile the nice!view widget sources that we gate off via
# CONFIG_NICE_VIEW_WIDGET_STATUS=n (to prevent duplicate symbols).
zephyr_library_sources("${NICE_VIEW_WIDGET_DIR}/widgets/status.c")
zephyr_library_sources("${NICE_VIEW_WIDGET_DIR}/widgets/bolt.c")
zephyr_library_sources("${NICE_VIEW_WIDGET_DIR}/widgets/util.c")
