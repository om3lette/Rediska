add_subdirectory(common)
add_subdirectory(data-structures)

add_subdirectory(worker)
add_subdirectory(cache)

add_subdirectory(frontend)


add_executable(Rediska main.cpp)
target_link_libraries(Rediska PRIVATE
    frontend
    worker
    cache
    common
    data-structures
)

# Convenience target
add_custom_target(run
    COMMAND $<TARGET_FILE:Rediska>
    DEPENDS Rediska
    USES_TERMINAL
    COMMENT "Building and running Rediska"
)
