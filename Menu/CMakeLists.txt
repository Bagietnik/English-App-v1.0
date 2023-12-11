add_library(Menu STATIC
    Menu.cpp
)

target_link_libraries(Menu)

target_include_directories(Menu PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)