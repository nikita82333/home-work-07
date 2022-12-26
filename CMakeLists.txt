cmake_minimum_required(VERSION 3.11)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(cmd VERSION ${PROJECT_VERSION})
add_executable(bulk_cli main.cpp Command.cpp Controller.cpp Receiver.cpp)

set_target_properties(bulk_cli PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

if (MSVC)
    target_compile_options(bulk_cli PRIVATE
            /W4
            )
else ()
    target_compile_options(bulk_cli PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()

install(TARGETS bulk_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
