cmake_minimum_required (VERSION 3.5.1)

set(CMAKE_TOOLCHAIN_FILE Toolchain-djgpp.cmake)

project (DosGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=i386 -s")

include_directories(
    3rd_party/mikmod/include
    3rd_party/allegro/include
    )

add_executable(${PROJECT_NAME}.exe
    main.cpp
    image_utils.cpp
    mikmod_sound.cpp
    engine.cpp
    logging.cpp
    level_holder.cpp
    title_screen.cpp
    enemy_level.cpp
    first_enemy.cpp
    stageclearlevel.cpp
    )


target_link_libraries(${PROJECT_NAME}.exe
    ${CMAKE_CURRENT_LIST_DIR}/3rd_party/allegro/lib/liballeg.a
    ${CMAKE_CURRENT_LIST_DIR}/3rd_party/mikmod/lib/libmikmod.a
    )

add_custom_command(
    TARGET ${PROJECT_NAME}.exe
    POST_BUILD
    COMMAND rm -f ${PROJECT_NAME}C.exe
    COMMAND upx --lzma ${PROJECT_NAME}.exe -o ${PROJECT_NAME}C.exe
    )

add_custom_target(
    run
    COMMAND dosbox -conf run_in_dosbox.conf
    DEPENDS ${PROJECT_NAME}.exe
    )
