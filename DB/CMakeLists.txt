add_library(DB STATIC
    DB.cpp
)

target_link_libraries(DB mysqlcppconn App)

target_include_directories(DB PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
