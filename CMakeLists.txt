cmake_minimum_required(VERSION 3.21)
project(nauty_test)

set(NAUTY_FOLDER "src/nauty2_8_9/")
set(OVERRIDE_FOLDER "src/")

include_directories(${NAUTY_FOLDER})

add_executable(${PROJECT_NAME} main.c
    ${OVERRIDE_FOLDER}nauty.c
    ${OVERRIDE_FOLDER}nautil.c
    ${OVERRIDE_FOLDER}naugraph.c
    ${NAUTY_FOLDER}schreier.c
    ${NAUTY_FOLDER}naurng.c
    ${NAUTY_FOLDER}gtools.c)

# target_link_libraries(${PROJECT_NAME} "/Users/jim/Dropbox/Wayne State/Research/Graph Isomorphism/code/nauty/nauty2_8_9/nauty.a")