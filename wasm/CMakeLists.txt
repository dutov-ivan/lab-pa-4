cmake_minimum_required(VERSION 3.10.0)
project(tiny-db-clusterized-rebuild VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)


add_executable(TinyDb
    main.cpp
)

# target_link_options(TinyDb PRIVATE
#     --bind
#     -sMODULARIZE=1
#     -sEXPORT_ES6=1
#     --emit-tsd "$<TARGET_FILE_DIR:TinyDb>/TinyDb.d.ts" # or wherever else you want it to go

# )
