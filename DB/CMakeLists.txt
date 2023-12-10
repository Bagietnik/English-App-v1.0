add_library(DB STATIC
    DB.cpp
)

target_link_libraries(DB mysqlcppconn)

target_include_directories(DB PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
