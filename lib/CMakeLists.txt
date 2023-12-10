add_library(card
    include/card.h
    card.cpp
)
target_include_directories(card PUBLIC include)
set_target_properties(card PROPERTIES FOLDER Libraries)
