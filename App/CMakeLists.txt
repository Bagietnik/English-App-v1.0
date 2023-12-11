add_library(App STATIC
    App.cpp
)

target_link_libraries(App mysqlcppconn DB Menu)

target_include_directories(App PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
