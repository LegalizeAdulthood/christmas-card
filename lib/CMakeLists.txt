if(WIN32)
    find_package(unofficial-pdcurses CONFIG REQUIRED)
endif()

add_library(card
    include/card.h
    card.cpp
    gothic.h
    gothic.cpp
    options.h
    options.cpp
    renderer.h
    sprite.h
    wide.h
    wide.cpp
)
target_compile_features(card PUBLIC cxx_std_17)
target_include_directories(card PUBLIC include)
target_link_libraries(card PRIVATE unofficial::pdcurses::pdcurses)
set_target_properties(card PROPERTIES FOLDER Libraries)
