add_executable(christmas-card main.cpp)
target_link_libraries(christmas-card PUBLIC card)
set_target_properties(christmas-card PROPERTIES FOLDER Tools)
